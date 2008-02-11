/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/deduced_trait.h>

namespace ProjetUnivers {
  namespace Kernel {

    namespace
    { 
      struct Formulae
      {
        std::set<Formula*> m_formulae ;
        
        ~Formulae()
        {
          for(std::set<Formula*>::iterator formula = m_formulae.begin() ;
              formula != m_formulae.end() ;
              ++formula)
          {
            delete *formula ;
          }
        }
        
      };
    }
    
    /// Formulae storage.
    Formulae formulae ;

    std::map<Formula*,DeducedTraitBuilder> DeducedTrait::m_builders ;

    std::map<Formula*,TypeIdentifier> DeducedTrait::m_destructors ;

    int Formula::m_next_identifier = 0 ;

    int Formula::m_maximum_depth = 0 ;

    std::map<int,std::set<Formula*> > Formula::m_stratification ;

    std::map<TypeIdentifier,TraitFormula*> TraitFormula::m_traits_formulae ;

  /*!
    @name Access
  */ 
  // @{
    
    bool Formula::isValid(Object* i_object) const
    {
      return i_object->getValidity(this) ;
    }

    int Formula::getIdentifier() const
    {
      return m_identifier ;      
    }
    
    unsigned int Formula::getNumberOfFormulae()
    {
      return m_next_identifier ;
    }

    TraitFormula* TraitFormula::get(const TypeIdentifier& i_trait_name)
    {
//      InternalMessage("Kernel","TraitFormula::get getting " + i_trait_name.toString()) ;
      std::map<TypeIdentifier,TraitFormula*>::iterator trait ;
      trait = m_traits_formulae.find(i_trait_name) ;
      if (trait != m_traits_formulae.end())
      {
//        InternalMessage("Kernel","TraitFormula::get got " + i_trait_name.toString()) ;
        return trait->second ;
      }

//      InternalMessage("Kernel","TraitFormula::get did not got " + i_trait_name.toString()) ;
      return NULL ;      
    }
    
    int Formula::getDepth() const
    {
      return m_depth ;
    }
    
  // @}
  /*!
    @name Construction
  */ 
  // @{
  
    Formula::Formula()
    : m_identifier(-1),
      m_depth(0)
    {
      formulae.m_formulae.insert(this) ;
      m_stratification[m_depth].insert(this) ;
    }

    Formula::~Formula()
    {}

    std::string Formula::print() const
    {
      std::string result(internalPrint() + "(") ;
      
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        if (child==m_children.begin())
          result += (*child)->print() ;
        else
          result += "," + (*child)->print() ;
      }
      
      return result + ")" ;
    }

    void Formula::addChild(Formula* i_formula)
    {
      i_formula->addParent(this) ;
      
      m_children.insert(i_formula) ;
      
      if (getDepth() < i_formula->getDepth() + 1)
      {
        m_stratification[getDepth()].erase(this) ;
        setDepth(i_formula->getDepth() + 1) ;
        m_stratification[getDepth()].insert(this) ;
      }
    }

    void Formula::addParent(Formula* i_formula)
    {
      m_parents.insert(i_formula) ;
    }

    void Formula::generateIdentifier()
    {
      m_identifier = m_next_identifier ;
      ++m_next_identifier ;
    }

    void Formula::setDepth(int i_depth)
    {
      m_depth = i_depth ;
      if (i_depth > m_maximum_depth)
      {
        m_maximum_depth = i_depth ;
      }
    }

    FormulaOr::FormulaOr()
    : Formula()
    {
      generateIdentifier() ;
    }

    std::string FormulaOr::internalPrint() const
    {
      return "Or" ;
    }
    
    FormulaAnd::FormulaAnd()
    : Formula()
    {
      generateIdentifier() ;
    }

    std::string FormulaAnd::internalPrint() const
    {
      return "And" ;
    }

    FormulaNot::FormulaNot()
    : Formula()
    {
      generateIdentifier() ;
    }

    std::string FormulaNot::internalPrint() const
    {
      return "Not" ;
    }

    void FormulaNot::addChild(Formula* i_formula)
    {
      CHECK(m_children.size() == 0,"FormulaNot can has only one child formula") ;
      
      Formula::addChild(i_formula) ;
    }

    TraitFormula* TraitFormula::build(const TypeIdentifier& i_trait_name)
    {
      TraitFormula* result = get(i_trait_name) ;
      if (! result)
      {
        result = new TraitFormula(i_trait_name) ;
        m_traits_formulae[i_trait_name] = result ;
      }
      
      return result ;
    }

    TraitFormula::TraitFormula(const TypeIdentifier& i_trait_name)
    : Formula(),
      m_trait(i_trait_name)
    {
      CHECK((m_identifier==-1),"TraitFormula::TraitFormula invalid identifier") ;
      CHECK((m_depth==0),"TraitFormula::TraitFormula invalid depth") ;
    }

    std::string TraitFormula::internalPrint() const
    {
      return "HasTrait(" + m_trait.toString() + ")" ;
    }

    DeducedTrait::~DeducedTrait()
    {}

      /// Register @c i_builder as the builder of @c i_formula.
    void DeducedTrait::registerTrait(
        Formula*            i_formula,
        DeducedTraitBuilder i_builder,
        const TypeIdentifier&  i_trait_name)
    {
      m_builders[i_formula] = i_builder ;
      m_destructors.insert(std::pair<Formula*,TypeIdentifier>(i_formula,i_trait_name)) ;
    }

    DeducedTrait::DeducedTrait()
    {}

    std::string DeducedTrait::printDeclarations()
    {
      std::string result ;
      
      for(std::map<Formula*,TypeIdentifier>::const_iterator declaration = m_destructors.begin() ;
          declaration != m_destructors.end() ;
          ++declaration)
      {
        result += "DeclareDeducedTrait(" + declaration->second.toString() + ","
                  + declaration->first->print() +")\n" ;  
      }
      
      return result ;
    }

        




  // @}
  /*!
    @name Initial evaluation
  */
  // @{
    
    void Formula::evaluateInitial(Object* i_object)
    {
      
      for(int depth = 0 ; depth <= m_maximum_depth ; ++depth)
      {
//        InternalMessage("Kernel","Formula::init dealing with depth=" + toString((float)depth)) ;
        
        for(std::set<Formula*>::const_iterator formula = m_stratification[depth].begin() ;
            formula != m_stratification[depth].end() ;
            ++formula)
        {
          
          (*formula)->eval(i_object) ;
        }
      }
    }
    
    void DeducedTrait::evaluateInitial(Object* i_object)
    {
      /// calculate all formulas.
      Formula::evaluateInitial(i_object) ;
      
      /// if we have new conclusions -> we set them
      for(std::map<Formula*,DeducedTraitBuilder>::const_iterator builder = m_builders.begin() ;
          builder != m_builders.end() ;
          ++builder)
      {
        if (i_object->getValidity(builder->first))
        {
          i_object->_add((builder->second)()) ;
        }
      }
    }

    void FormulaAnd::eval(Object* i_object)
    {
//      InternalMessage("Kernel","FormulaAnd::eval Entering id=" + toString((float)m_identifier)) ;
      bool validity = true ; 
      int true_child_number = 0 ;
       
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        validity &= i_object->getValidity(*child) ;
        
        if (i_object->getValidity(*child))
        {
          ++true_child_number ;
        }
      }
      
      i_object->setValidity(this,validity) ;
      i_object->setNumberOfTrueChildFormulae(this,true_child_number) ;
      
//      InternalMessage("Kernel","FormulaAnd::eval Leaving id=" 
//                           + toString((float)m_identifier)
//                           + " with initial value=" 
//                           + toString((float)validity)) ;
    }

    void FormulaOr::eval(Object* i_object)
    {
//      InternalMessage("Kernel","FormulaOr::eval Entering id=" + toString((float)m_identifier)) ;
      bool validity = false ; 
      int true_child_number = 0 ;
      
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        validity |= i_object->getValidity(*child) ;

        if (i_object->getValidity(*child))
        {
          ++true_child_number ;
        }
      }
      
      i_object->setValidity(this,validity) ;
      i_object->setNumberOfTrueChildFormulae(this,true_child_number) ;

//      InternalMessage("Kernel","FormulaOr::eval Leaving id=" 
//                           + toString((float)m_identifier)
//                           + " with initial value=" 
//                           + toString((float)validity)) ;
    }

    void FormulaNot::eval(Object* i_object)
    {
      CHECK((m_children.size()== 1),"FormulaNot::eval children problem") ;
//      InternalMessage("Kernel","FormulaNot::eval Entering id=" + toString((float)m_identifier)) ;
      
      bool validity ; 
      int true_child_number = 0 ;
      
      std::set<Formula*>::const_iterator child = m_children.begin() ;

      if (i_object->getValidity(*child))
      {
        validity = false ; 
        true_child_number = 1 ;
      }
      else
      {
        validity = true ;
      }
      i_object->setNumberOfTrueChildFormulae(this,true_child_number) ;
      
      i_object->setValidity(this,validity) ;
//      InternalMessage("Kernel","FormulaNot::eval Leaving id=" 
//                           + toString((float)m_identifier)
//                           + " with initial value=" 
//                           + toString((float)validity)) ;
    }

    void TraitFormula::eval(Object* i_object)
    {
      i_object->setValidity(this,false) ;
    }

  // @}
  /*!
    @name Continuous evaluation
  */
  // @{


    void TraitFormula::addTrait(Object* i_object,const TypeIdentifier& i_trait_name)
    {
      CHECK(i_object,"TraitFormula::addTrait no object")

      InternalMessage("Kernel","TraitFormula::addTrait(" + i_trait_name.toString() + ")") ;
      TraitFormula* trait_formula = get(i_trait_name) ;
      if (trait_formula)
      {
        trait_formula->becomeTrue(i_object) ;
      }
    }

    void TraitFormula::removeTrait(Object* i_object,const TypeIdentifier& i_trait_name)
    {
      TraitFormula* trait_formula = get(i_trait_name) ;
      if (trait_formula)
      {
        trait_formula->becomeFalse(i_object) ;
      }
    }

    
    void DeducedTrait::notify(Formula* i_formula,
                              bool i_validity,
                              Object* i_object)
    {

      CHECK(i_formula,"DeducedTrait::notify no formula")
      CHECK(i_object,"DeducedTrait::notify no object")
//      InternalMessage("Kernel","DeducedTrait::notify") ;

      if (i_validity)
      {
        std::map<Formula*,DeducedTraitBuilder>::const_iterator builder ;
        builder = m_builders.find(i_formula) ;
        if (builder != m_builders.end())
        {

          DeducedTrait* new_trait = (builder->second)() ;
          i_object->_add(new_trait) ;
        }
      }
      else
      {
        std::map<Formula*,TypeIdentifier>::const_iterator destructor ;
        destructor = m_destructors.find(i_formula) ;
        if (destructor != m_destructors.end())
        {
          i_object->_remove(destructor->second) ;
        }
      }
    }


    void Formula::addChildTrue(Object* i_object)
    {
//      InternalMessage("Kernel","Formula::addChildTrue Entering id=" + toString((float)m_identifier)) ;
      CHECK(i_object,"Formula::addChildTrue no object") ;
      
      unsigned short true_child = i_object->getNumberOfTrueChildFormulae(this) ;

//      InternalMessage("Kernel","Formula id=" + toString((float)m_identifier) + " has now " + toString((float)true_child + 1) + " true children") ;
      InternalMessage("Kernel","Formula " + print() 
                               + " with a total of " + toString(m_children.size()) + "children "
                               + " has now " + toString((float)true_child + 1) 
                               + " true children for objectid= " 
                               + toString(i_object->getIdentifier())) ;

      i_object->setNumberOfTrueChildFormulae(this,true_child+1) ;
      onAddChildTrue(i_object) ;

//      InternalMessage("Kernel","Formula::addChildTrue Leaving id=" + toString((float)m_identifier)) ;
    }

    void Formula::addChildFalse(Object* i_object)
    {
//      InternalMessage("Kernel","Formula::addChildFalse Entering id=" + toString((float)m_identifier)) ;

      i_object->setNumberOfTrueChildFormulae(
        this,i_object->getNumberOfTrueChildFormulae(this)-1) ;

//      InternalMessage("Kernel","Formula id=" + toString((float)m_identifier) + " has now " + toString((float)i_object->getNumberOfTrueChildFormulae(this)) + " true children") ;

      onAddChildFalse(i_object) ;
    }

    void Formula::becomeTrue(Object* i_object)
    {
      CHECK(i_object,"Formula::becomeTrue no object")

      InternalMessage("Kernel","Formula " + print() 
                               + " has became true for objectid= " 
                               + toString(i_object->getIdentifier())) ;

      if (m_identifier >= 0)
      {
//        InternalMessage("Kernel","Formula::becomeTrue setting object validity") ;
        i_object->setValidity(this,true) ;
      }
//      InternalMessage("Kernel","Formula::becomeTrue setting notifying deductions") ;
      DeducedTrait::notify(this,true,i_object) ;
//      InternalMessage("Kernel","Formula::becomeTrue setting notifying parents") ;
      notifyParentTrue(i_object) ;
//      InternalMessage("Kernel","Formula::becomeTrue setting Leaving") ;
    }

    void Formula::becomeFalse(Object* i_object)
    {
      InternalMessage("Kernel","Formula " + print() 
                               + " has became false for objectid= " 
                               + toString(i_object->getIdentifier())) ;
      if (m_identifier >= 0)
      {
        i_object->setValidity(this,false) ;
      }
      DeducedTrait::notify(this,false,i_object) ;
      notifyParentFalse(i_object) ;
    }

    void Formula::notifyParentTrue(Object* i_object)
    {
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->addChildTrue(i_object) ;
      }
    }

    void Formula::notifyParentFalse(Object* i_object)
    {
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->addChildFalse(i_object) ;
      }
    }
    
    void FormulaAnd::onAddChildFalse(Object* i_object) 
    {
      if (isValid(i_object))
      {
        becomeFalse(i_object) ;
      }
    }

    void FormulaAnd::onAddChildTrue(Object* i_object) 
    {
//      InternalMessage("Kernel","FormulaAnd::onAddChildTrue Entering id=" + toString((float)m_identifier)) ;
      if (! isValid(i_object) && 
          i_object->getNumberOfTrueChildFormulae(this) == m_children.size())
      {
        becomeTrue(i_object) ;
      }
//      InternalMessage("Kernel","FormulaAnd::onAddChildTrue Leaving id=" + toString((float)m_identifier)) ;
    }
    
    void FormulaOr::onAddChildTrue(Object* i_object) 
    {
      if (! isValid(i_object))
      {
        becomeTrue(i_object) ;
      }
    }

    void FormulaOr::onAddChildFalse(Object* i_object) 
    {
      if (isValid(i_object) && 
          i_object->getNumberOfTrueChildFormulae(this) == 0)
      {
        becomeFalse(i_object) ;
      }
    }
      
    void TraitFormula::onAddChildTrue(Object* i_object) 
    {
      ErrorMessage("TraitFormula::onAddChildTrue") ;
    }
    
    void TraitFormula::onAddChildFalse(Object* i_object) 
    {
      ErrorMessage("TraitFormula::onAddChildFalse") ;
    }

    void TraitFormula::onChildUpdated(Object* i_object)
    {
      //// error
    }

    void FormulaNot::onAddChildTrue(Object* i_object)
    {
      if (isValid(i_object))
      {
        becomeFalse(i_object) ;
      }
    }
    
    void FormulaNot::onAddChildFalse(Object* i_object)
    {
      if (! isValid(i_object))
      {
        becomeTrue(i_object) ;
      }
    }


  // @}
  /*!
    Trait udate propagation
  */
  // @{
  
    void TraitFormula::updateTrait(Object* i_object,const TypeIdentifier& i_trait_name)
    {
      TraitFormula* trait = get(i_trait_name) ;
      if (trait)
      {
        trait->update(i_object) ;
      }
    }

    void Formula::update(Object* i_object)
    {
      /// notify deduced traits...
//      InternalMessage("Kernel","Formula::update Entering") ;
      
      if (isValid(i_object))
      {
        DeducedTrait::update(this,i_object) ;
      }
      
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->onChildUpdated(i_object) ;
      }
    }
    
    
    void DeducedTrait::update(Formula* i_formula,
                              Object* i_object)
    {
//      InternalMessage("Kernel","DeducedTrait::update Entering") ;

      std::map<Formula*,TypeIdentifier>::const_iterator destructor ;
      destructor = m_destructors.find(i_formula) ;
      if (destructor != m_destructors.end())
      {
        i_object->_get(destructor->second)->notify() ;
      }      
//      InternalMessage("Kernel","DeducedTrait::update Leaving") ;
    }

    const TypeIdentifier& DeducedTrait::getLatestUpdatedTrait() const
    {
      return Trait::m_latest_updated_trait ;
    }

    void FormulaOr::onChildUpdated(Object* i_object)
    {
      update(i_object) ;
    }

    void FormulaAnd::onChildUpdated(Object* i_object)
    {
      update(i_object) ;
    }

    void FormulaNot::onChildUpdated(Object* i_object)
    {
      /// nothing
    }

    void DeducedTrait::notify()
    {
      _updated() ;
      TraitFormula::updateTrait(getObject(),getObjectTypeIdentifier(this)) ;
    }


  // @}

  }
}
