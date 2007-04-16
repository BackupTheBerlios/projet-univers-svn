/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

    std::map<Formula*,std::string> DeducedTrait::m_destructors ;

    int Formula::m_next_identifier = 0 ;

    int Formula::m_maximum_depth = 0 ;

    std::map<int,std::set<Formula*> > Formula::m_stratification ;

    std::map<std::string,TraitFormula*> TraitFormula::m_traits_formulae ;

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

    TraitFormula* TraitFormula::get(const std::string& i_trait_name)
    {
      Log::InternalMessage("TraitFormula::get getting " + i_trait_name) ;
      std::map<std::string,TraitFormula*>::iterator trait ;
      trait = m_traits_formulae.find(i_trait_name) ;
      if (trait != m_traits_formulae.end())
      {
        Log::InternalMessage("TraitFormula::get got " + i_trait_name) ;
        return trait->second ;
      }

      Log::InternalMessage("TraitFormula::get did not got " + i_trait_name) ;
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
    
    FormulaAnd::FormulaAnd()
    : Formula()
    {
      generateIdentifier() ;
    }


    FormulaNot::FormulaNot()
    : Formula()
    {
      generateIdentifier() ;
    }

    void FormulaNot::addChild(Formula* i_formula)
    {
      check(m_children.size() == 0,"FormulaNot can has only one child formula") ;
      
      Formula::addChild(i_formula) ;
    }

    TraitFormula* TraitFormula::build(const std::string& i_trait_name)
    {
      TraitFormula* result = get(i_trait_name) ;
      if (! result)
      {
        result = new TraitFormula(i_trait_name) ;
        m_traits_formulae[i_trait_name] = result ;
      }
      
      return result ;
    }

    TraitFormula::TraitFormula(const std::string& i_trait_name)
    : Formula()
    {
      check((m_identifier==-1),"TraitFormula::TraitFormula invalid identifier") ;
      check((m_depth==0),"TraitFormula::TraitFormula invalid depth") ;
    }

    DeducedTrait::~DeducedTrait()
    {}

      /// Register @c i_builder as the builder of @c i_formula.
    void DeducedTrait::registerTrait(
        Formula*            i_formula,
        DeducedTraitBuilder i_builder,
        const std::string&  i_trait_name)
    {
      m_builders[i_formula] = i_builder ;
      m_destructors[i_formula] = i_trait_name ;
    }

    DeducedTrait::DeducedTrait()
    {}

      

        




  // @}
  /*!
    @name Initial evaluation
  */
  // @{
    
    void Formula::evaluateInitial(Object* i_object)
    {
      
      for(int depth = 0 ; depth <= m_maximum_depth ; ++depth)
      {
        Log::InternalMessage("Formula::init dealing with depth=" + toString((float)depth)) ;
        
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
      Log::InternalMessage("FormulaAnd::eval Entering id=" + toString((float)m_identifier)) ;
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
      
      Log::InternalMessage("FormulaAnd::eval Leaving id=" 
                           + toString((float)m_identifier)
                           + " with initial value=" 
                           + toString((float)validity)) ;
    }

    void FormulaOr::eval(Object* i_object)
    {
      Log::InternalMessage("FormulaOr::eval Entering id=" + toString((float)m_identifier)) ;
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

      Log::InternalMessage("FormulaOr::eval Leaving id=" 
                           + toString((float)m_identifier)
                           + " with initial value=" 
                           + toString((float)validity)) ;
    }

    void FormulaNot::eval(Object* i_object)
    {
      check((m_children.size()== 1),"FormulaNot::eval children problem") ;
      Log::InternalMessage("FormulaNot::eval Entering id=" + toString((float)m_identifier)) ;
      
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
      Log::InternalMessage("FormulaNot::eval Leaving id=" 
                           + toString((float)m_identifier)
                           + " with initial value=" 
                           + toString((float)validity)) ;
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


    void TraitFormula::addTrait(Object* i_object,const std::string& i_trait_name)
    {
      check(i_object,"TraitFormula::addTrait no object")

      Log::InternalMessage("TraitFormula::addTrait") ;
      TraitFormula* trait_formula = get(i_trait_name) ;
      if (trait_formula)
      {
        trait_formula->becomeTrue(i_object) ;
      }
    }

    void TraitFormula::removeTrait(Object* i_object,const std::string& i_trait_name)
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

      check(i_formula,"DeducedTrait::notify no formula")
      check(i_object,"DeducedTrait::notify no object")
      Log::InternalMessage("DeducedTrait::notify") ;

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
        std::map<Formula*,std::string>::const_iterator destructor ;
        destructor = m_destructors.find(i_formula) ;
        if (destructor != m_destructors.end())
        {
          i_object->_remove(destructor->second) ;
        }
      }
    }


    void Formula::addChildTrue(Object* i_object)
    {
      Log::InternalMessage("Formula::addChildTrue Entering id=" + toString((float)m_identifier)) ;
      check(i_object,"Formula::addChildTrue no object") ;
      
      unsigned short true_child = i_object->getNumberOfTrueChildFormulae(this) ;

      Log::InternalMessage("Formula id=" + toString((float)m_identifier) + " has now " + toString((float)true_child + 1) + " true children") ;
      i_object->setNumberOfTrueChildFormulae(this,true_child+1) ;
      onAddChildTrue(i_object) ;

      Log::InternalMessage("Formula::addChildTrue Leaving id=" + toString((float)m_identifier)) ;
    }

    void Formula::addChildFalse(Object* i_object)
    {
      Log::InternalMessage("Formula::addChildFalse Entering id=" + toString((float)m_identifier)) ;

      i_object->setNumberOfTrueChildFormulae(
        this,i_object->getNumberOfTrueChildFormulae(this)-1) ;

      Log::InternalMessage("Formula id=" + toString((float)m_identifier) + " has now " + toString((float)i_object->getNumberOfTrueChildFormulae(this)) + " true children") ;

      onAddChildFalse(i_object) ;
    }

    void Formula::becomeTrue(Object* i_object)
    {
      check(i_object,"Formula::becomeTrue no object")
      Log::InternalMessage("Formula::becomeTrue Entering id=" + toString((float)m_identifier)) ;
      if (m_identifier >= 0)
      {
        Log::InternalMessage("Formula::becomeTrue setting object validity") ;
        i_object->setValidity(this,true) ;
      }
      Log::InternalMessage("Formula::becomeTrue setting notifying deductions") ;
      DeducedTrait::notify(this,true,i_object) ;
      Log::InternalMessage("Formula::becomeTrue setting notifying parents") ;
      notifyParentTrue(i_object) ;
      Log::InternalMessage("Formula::becomeTrue setting Leaving") ;
    }

    void Formula::becomeFalse(Object* i_object)
    {
      Log::InternalMessage("Formula::becomeFalse") ;
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
      Log::InternalMessage("FormulaAnd::onAddChildTrue Entering id=" + toString((float)m_identifier)) ;
      if (! isValid(i_object) && 
          i_object->getNumberOfTrueChildFormulae(this) == m_children.size())
      {
        becomeTrue(i_object) ;
      }
      Log::InternalMessage("FormulaAnd::onAddChildTrue Leaving id=" + toString((float)m_identifier)) ;
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
      Log::ErrorMessage("TraitFormula::onAddChildTrue") ;
    }
    
    void TraitFormula::onAddChildFalse(Object* i_object) 
    {
      Log::ErrorMessage("TraitFormula::onAddChildFalse") ;
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
  
    void TraitFormula::updateTrait(Object* i_object,const std::string& i_trait_name)
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
      Log::InternalMessage("Formula::update Entering") ;
      
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
      Log::InternalMessage("DeducedTrait::update Entering") ;

      std::map<Formula*,std::string>::const_iterator destructor ;
      destructor = m_destructors.find(i_formula) ;
      if (destructor != m_destructors.end())
      {
        i_object->_get(destructor->second)->notify() ;
      }      
      Log::InternalMessage("DeducedTrait::update Leaving") ;
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

  // @}

  }
}
