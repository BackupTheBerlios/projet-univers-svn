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

    
    Formula::StaticStorage* Formula::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

    DeducedTrait::StaticStorage* DeducedTrait::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

    TraitFormula::StaticStorage* TraitFormula::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

    HasParentFormula::StaticStorage* HasParentFormula::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }
    
  /*!
    @name Access
  */ 
  // @{
    
    bool Formula::isValid(Object* object) const
    {
      return object->getValidity(this) ;
    }

    int Formula::getIdentifier() const
    {
      return m_identifier ;      
    }
    
    unsigned int Formula::getNumberOfFormulae()
    {
      return StaticStorage::get()->m_next_identifier ;
    }

    TraitFormula* TraitFormula::get(const TypeIdentifier& trait_name)
    {
//      InternalMessage("Kernel","TraitFormula::get getting " + trait_name.toString()) ;
      std::map<TypeIdentifier,TraitFormula*>::iterator trait ;
      trait = StaticStorage::get()->m_traits_formulae.find(trait_name) ;
      if (trait != StaticStorage::get()->m_traits_formulae.end())
      {
//        InternalMessage("Kernel","TraitFormula::get got " + trait_name.toString()) ;
        return trait->second ;
      }

//      InternalMessage("Kernel","TraitFormula::get did not got " + trait_name.toString()) ;
      return NULL ;      
    }
    
    int Formula::getDepth() const
    {
      return m_depth ;
    }

    HasParentFormula* HasParentFormula::get(const TypeIdentifier& trait_name)
    {
//      InternalMessage("Kernel","TraitFormula::get getting " + trait_name.toString()) ;
      std::map<TypeIdentifier,HasParentFormula*>::iterator trait ;
      trait = StaticStorage::get()->m_parent_traits_formulae.find(trait_name) ;
      if (trait != StaticStorage::get()->m_parent_traits_formulae.end())
      {
//        InternalMessage("Kernel","TraitFormula::get got " + trait_name.toString()) ;
        return trait->second ;
      }

//      InternalMessage("Kernel","TraitFormula::get did not got " + trait_name.toString()) ;
      return NULL ;      
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
      StaticStorage::get()->m_formulae.insert(this) ;
      StaticStorage::get()->m_stratification[m_depth].insert(this) ;
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

    void Formula::addChild(Formula* formula)
    {
      formula->addParent(this) ;
      
      m_children.insert(formula) ;
      
      if (getDepth() < formula->getDepth() + 1)
      {
        StaticStorage::get()->m_stratification[getDepth()].erase(this) ;
        setDepth(formula->getDepth() + 1) ;
        StaticStorage::get()->m_stratification[getDepth()].insert(this) ;
      }
    }

    void Formula::addParent(Formula* formula)
    {
      m_parents.insert(formula) ;
    }

    void Formula::generateIdentifier()
    {
      m_identifier = StaticStorage::get()->m_next_identifier ;
      ++StaticStorage::get()->m_next_identifier ;
    }

    void Formula::setDepth(int i_depth)
    {
      m_depth = i_depth ;
      if (i_depth > StaticStorage::get()->m_maximum_depth)
      {
        StaticStorage::get()->m_maximum_depth = i_depth ;
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

    void FormulaNot::addChild(Formula* formula)
    {
      CHECK(m_children.size() == 0,"FormulaNot can has only one child formula") ;
      
      Formula::addChild(formula) ;
    }

    TraitFormula* TraitFormula::build(const TypeIdentifier& trait_name)
    {
      TraitFormula* result = get(trait_name) ;
      if (! result)
      {
        result = new TraitFormula(trait_name) ;
        StaticStorage::get()->m_traits_formulae[trait_name] = result ;
      }
      
      return result ;
    }

    TraitFormula::TraitFormula(const TypeIdentifier& trait_name)
    : Formula(),
      m_trait(trait_name)
    {
      CHECK((m_identifier==-1),"TraitFormula::TraitFormula invalid identifier") ;
      CHECK((m_depth==0),"TraitFormula::TraitFormula invalid depth") ;
    }
    
    std::string TraitFormula::internalPrint() const
    {
      return "HasTrait(" + m_trait.toString() + ")" ;
    }

    HasParentFormula* HasParentFormula::build(const TypeIdentifier& trait_name)
    {
      HasParentFormula* result = get(trait_name) ;
      if (! result)
      {
        result = new HasParentFormula(trait_name) ;
        StaticStorage::get()->m_parent_traits_formulae[trait_name] = result ;
      }
      
      return result ;
    }
    
    HasParentFormula::HasParentFormula(const TypeIdentifier& trait_name)
    : Formula(),
      m_trait(trait_name)
    {
      generateIdentifier() ;
      CHECK((m_depth==0),"HasParentFormula::HasParentFormula invalid depth") ;
    }

    std::string HasParentFormula::internalPrint() const
    {
      return "HasParent(" + m_trait.toString() + ")" ;
    }
    
    DeducedTrait::~DeducedTrait()
    {}

    void DeducedTrait::registerTrait(
        Formula*            formula,
        DeducedTraitBuilder i_builder,
        const TypeIdentifier&  trait_name)
    {
      StaticStorage::get()->m_builders[formula] = i_builder ;
      StaticStorage::get()->m_destructors.insert(std::pair<Formula*,TypeIdentifier>(formula,trait_name)) ;
    }

    DeducedTrait::DeducedTrait()
    {}

    std::string DeducedTrait::printDeclarations()
    {
      std::string result ;
      
      for(std::map<Formula*,TypeIdentifier>::const_iterator 
            declaration = StaticStorage::get()->m_destructors.begin() ;
          declaration != StaticStorage::get()->m_destructors.end() ;
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
    
    void Formula::evaluateInitial(Object* object)
    {
      
      for(int depth = 0 ; depth <= StaticStorage::get()->m_maximum_depth ; ++depth)
      {
//        InternalMessage("Kernel","Formula::init dealing with depth=" + toString((float)depth)) ;
        
        for(std::set<Formula*>::const_iterator 
              formula = StaticStorage::get()->m_stratification[depth].begin() ;
            formula != StaticStorage::get()->m_stratification[depth].end() ;
            ++formula)
        {
          
          (*formula)->eval(object) ;
        }
      }
    }
    
    void DeducedTrait::evaluateInitial(Object* object)
    {
      InternalMessage("Kernel","DeducedTrait::evaluateInitial on object " + toString(object->getIdentifier())) ;
      /// calculate all formulas.
      Formula::evaluateInitial(object) ;
      /// if we have new conclusions -> we set them
      for(std::map<Formula*,DeducedTraitBuilder>::const_iterator 
            builder = StaticStorage::get()->m_builders.begin() ;
          builder != StaticStorage::get()->m_builders.end() ;
          ++builder)
      {
        if (object->getValidity(builder->first))
        {
          InternalMessage("Kernel","Formula " + builder->first->print() 
                                   + " is true for objectid= " 
                                   + toString(object->getIdentifier())) ;
          object->_add((builder->second)()) ;
        }
      }
    }

    void FormulaAnd::eval(Object* object)
    {
//      InternalMessage("Kernel","FormulaAnd::eval Entering id=" + toString((float)m_identifier)) ;
      bool validity = true ; 
      int true_child_number = 0 ;
       
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        validity &= object->getValidity(*child) ;
        
        if (object->getValidity(*child))
        {
          ++true_child_number ;
        }
      }
      
      object->setValidity(this,validity) ;
      object->setNumberOfTrueChildFormulae(this,true_child_number) ;
      
//      InternalMessage("Kernel","FormulaAnd::eval Leaving id=" 
//                           + toString((float)m_identifier)
//                           + " with initial value=" 
//                           + toString((float)validity)) ;
    }

    void FormulaOr::eval(Object* object)
    {
//      InternalMessage("Kernel","FormulaOr::eval Entering id=" + toString((float)m_identifier)) ;
      bool validity = false ; 
      int true_child_number = 0 ;
      
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        validity |= object->getValidity(*child) ;

        if (object->getValidity(*child))
        {
          ++true_child_number ;
        }
      }
      
      object->setValidity(this,validity) ;
      object->setNumberOfTrueChildFormulae(this,true_child_number) ;

//      InternalMessage("Kernel","FormulaOr::eval Leaving id=" 
//                           + toString((float)m_identifier)
//                           + " with initial value=" 
//                           + toString((float)validity)) ;
    }

    void FormulaNot::eval(Object* object)
    {
      CHECK((m_children.size()== 1),"FormulaNot::eval children problem") ;
//      InternalMessage("Kernel","FormulaNot::eval Entering id=" + toString((float)m_identifier)) ;
      
      bool validity ; 
      int true_child_number = 0 ;
      
      std::set<Formula*>::const_iterator child = m_children.begin() ;

      if (object->getValidity(*child))
      {
        validity = false ; 
        true_child_number = 1 ;
      }
      else
      {
        validity = true ;
      }
      object->setNumberOfTrueChildFormulae(this,true_child_number) ;
      
      object->setValidity(this,validity) ;
//      InternalMessage("Kernel","FormulaNot::eval Leaving id=" 
//                           + toString((float)m_identifier)
//                           + " with initial value=" 
//                           + toString((float)validity)) ;
    }

    void TraitFormula::eval(Object* object)
    {
      object->setValidity(this,false) ;
    }

    void HasParentFormula::eval(Object* object)
    {
      InternalMessage("Kernel","HasParentFormula::eval") ;
      unsigned int number_of_parents = object->getNumberOfParent(m_trait) ;
      object->setNumberOfTrueChildFormulae(this,number_of_parents) ;
      object->setValidity(this,number_of_parents > 0) ;
      
      InternalMessage("Kernel","HasParentFormula::eval " + toString(number_of_parents)) ;
    }
    
  // @}
  /*!
    @name Continuous evaluation
  */
  // @{


    void TraitFormula::addTrait(Object* object,const TypeIdentifier& trait_name)
    {
      CHECK(object,"TraitFormula::addTrait no object")

      InternalMessage("Kernel","TraitFormula::addTrait(" + trait_name.toString() + ")") ;
      TraitFormula* trait_formula = get(trait_name) ;
      if (trait_formula)
      {
        trait_formula->becomeTrue(object) ;
      }
    }

    void TraitFormula::removeTrait(Object* object,const TypeIdentifier& trait_name)
    {
      TraitFormula* trait_formula = get(trait_name) ;
      if (trait_formula)
      {
        trait_formula->becomeFalse(object) ;
      }
    }

    void HasParentFormula::addTrait(Object* object,const TypeIdentifier& trait_name)
    {
      CHECK(object,"HasParentFormula::addTrait no object")
      
      InternalMessage("Kernel","HasParentFormula::addTrait(" + trait_name.toString() + ")") ;
      HasParentFormula* trait_formula = get(trait_name) ;
      if (trait_formula)
      {
        trait_formula->addParent(object) ;
      }
    }

    void HasParentFormula::removeTrait(Object* object,const TypeIdentifier& trait_name)
    {
      InternalMessage("Kernel","HasParentFormula::removeTrait(" + trait_name.toString() + ")") ;
      HasParentFormula* trait_formula = get(trait_name) ;
      if (trait_formula)
      {
        // handle current object
        trait_formula->removedParent(object) ;
      }
    }

    void HasParentFormula::addParent(Object* object)
    {
      /*
        Here we use the number of true child formulae on objects to code the 
        number of parents with trait @c trait_name
        
        Direct parent just add been added
      */
      // formula is true for current object
      if (isValid(object))
        // update because parent with trait has changed 
        DeducedTrait::update(this,object) ;
      else
        becomeTrue(object) ;

      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+1) ;
        
      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ; 
          child != object->getChildren().end() ;
          ++child)
      {
        addParent(*child) ;
      }
    }
    
    void HasParentFormula::removedParent(Object* object)
    {
      /*
        Here we use the number of true child formulae on objects to code the 
        number of parents with trait @c trait_name
        
        Direct parent with trait has changed
        
      */
      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child-1) ;
        
      if (true_child == 1)
        becomeFalse(object) ;
      else
        // still true but parent has changed
        DeducedTrait::update(this,object) ;
      
      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ; 
          child != object->getChildren().end() ;
          ++child)
      {
        removedParent(*child) ;
      }
      
    }

    void HasParentFormula::changeParent(Object* object,Object* old_parent)
    {
      for(std::map<TypeIdentifier,HasParentFormula*>::const_iterator 
            formula = StaticStorage::get()->m_parent_traits_formulae.begin() ;
          formula != StaticStorage::get()->m_parent_traits_formulae.end() ;
          ++formula)
      {
        formula->second->onChangedParent(object,old_parent) ;
      }
    }
    
    void HasParentFormula::onChangedParent(Object* object,Object* old_parent)
    {
      bool old_validity = isValid(object) ;

      unsigned int number_of_parents = object->getNumberOfParent(m_trait) ;
      object->setNumberOfTrueChildFormulae(this,number_of_parents) ;

      bool new_validity = number_of_parents != 0 ;
      if (old_validity && new_validity)
      {
        // update because parent with trait has changed 
        DeducedTrait::update(this,object) ;
      }
      else if (old_validity && !new_validity)
      {
        becomeFalse(object) ;
      }
      else if (!old_validity && new_validity)
      {
        becomeTrue(object) ;
      }
    }
    
    void DeducedTrait::notify(Formula* formula,
                              bool i_validity,
                              Object* object)
    {

      CHECK(formula,"DeducedTrait::notify no formula")
      CHECK(object,"DeducedTrait::notify no object")
      InternalMessage("Kernel","DeducedTrait::notify") ;

      if (i_validity)
      {
        std::map<Formula*,DeducedTraitBuilder>::const_iterator builder ;
        builder = StaticStorage::get()->m_builders.find(formula) ;
        if (builder != StaticStorage::get()->m_builders.end())
        {

          DeducedTrait* new_trait = (builder->second)() ;
          object->_add(new_trait) ;
        }
      }
      else
      {
        std::map<Formula*,TypeIdentifier>::const_iterator destructor ;
        destructor = StaticStorage::get()->m_destructors.find(formula) ;
        if (destructor != StaticStorage::get()->m_destructors.end())
        {
          object->_remove(destructor->second) ;
        }
      }
    }

    void Formula::addChildTrue(Object* object)
    {
//      InternalMessage("Kernel","Formula::addChildTrue Entering id=" + toString((float)m_identifier)) ;
      CHECK(object,"Formula::addChildTrue no object") ;
      
      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;

//      InternalMessage("Kernel","Formula id=" + toString((float)m_identifier) + " has now " + toString((float)true_child + 1) + " true children") ;
      InternalMessage("Kernel","Formula " + print() 
                               + " with a total of " + toString(m_children.size()) + "children "
                               + " has now " + toString((float)true_child + 1) 
                               + " true children for objectid= " 
                               + toString(object->getIdentifier())) ;

      object->setNumberOfTrueChildFormulae(this,true_child+1) ;
      onAddChildTrue(object) ;

//      InternalMessage("Kernel","Formula::addChildTrue Leaving id=" + toString((float)m_identifier)) ;
    }

    void Formula::addChildFalse(Object* object)
    {
//      InternalMessage("Kernel","Formula::addChildFalse Entering id=" + toString((float)m_identifier)) ;

      object->setNumberOfTrueChildFormulae(
        this,object->getNumberOfTrueChildFormulae(this)-1) ;

//      InternalMessage("Kernel","Formula id=" + toString((float)m_identifier) + " has now " + toString((float)object->getNumberOfTrueChildFormulae(this)) + " true children") ;

      onAddChildFalse(object) ;
    }

    void Formula::becomeTrue(Object* object)
    {
      CHECK(object,"Formula::becomeTrue no object")

      InternalMessage("Kernel","Formula " + print() 
                               + " has became true for objectid= " 
                               + toString(object->getIdentifier())) ;

      if (m_identifier >= 0)
      {
//        InternalMessage("Kernel","Formula::becomeTrue setting object validity") ;
        object->setValidity(this,true) ;
      }
//      InternalMessage("Kernel","Formula::becomeTrue setting notifying deductions") ;
      DeducedTrait::notify(this,true,object) ;
//      InternalMessage("Kernel","Formula::becomeTrue setting notifying parents") ;
      notifyParentTrue(object) ;
//      InternalMessage("Kernel","Formula::becomeTrue setting Leaving") ;
    }

    void Formula::becomeFalse(Object* object)
    {
      InternalMessage("Kernel","Formula " + print() 
                               + " has became false for objectid= " 
                               + toString(object->getIdentifier())) ;
      if (m_identifier >= 0)
      {
        object->setValidity(this,false) ;
      }
      DeducedTrait::notify(this,false,object) ;
      notifyParentFalse(object) ;
    }

    void Formula::notifyParentTrue(Object* object)
    {
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->addChildTrue(object) ;
      }
    }

    void Formula::notifyParentFalse(Object* object)
    {
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->addChildFalse(object) ;
      }
    }
    
    void FormulaAnd::onAddChildFalse(Object* object) 
    {
      if (isValid(object))
      {
        becomeFalse(object) ;
      }
    }

    void FormulaAnd::onAddChildTrue(Object* object) 
    {
//      InternalMessage("Kernel","FormulaAnd::onAddChildTrue Entering id=" + toString((float)m_identifier)) ;
      if (! isValid(object) && 
          object->getNumberOfTrueChildFormulae(this) == m_children.size())
      {
        becomeTrue(object) ;
      }
//      InternalMessage("Kernel","FormulaAnd::onAddChildTrue Leaving id=" + toString((float)m_identifier)) ;
    }
    
    void FormulaOr::onAddChildTrue(Object* object) 
    {
      if (! isValid(object))
      {
        becomeTrue(object) ;
      }
    }

    void FormulaOr::onAddChildFalse(Object* object) 
    {
      if (isValid(object) && 
          object->getNumberOfTrueChildFormulae(this) == 0)
      {
        becomeFalse(object) ;
      }
    }
      
    void TraitFormula::onAddChildTrue(Object* object) 
    {
      ErrorMessage("TraitFormula::onAddChildTrue") ;
    }
    
    void TraitFormula::onAddChildFalse(Object* object) 
    {
      ErrorMessage("TraitFormula::onAddChildFalse") ;
    }

    void HasParentFormula::onAddChildTrue(Object* object) 
    {
      ErrorMessage("HasParentFormula::onAddChildTrue") ;
    }
    
    void HasParentFormula::onAddChildFalse(Object* object) 
    {
      ErrorMessage("HasParentFormula::onAddChildFalse") ;
    }
    
    void TraitFormula::onChildUpdated(Object* object)
    {
      //// error
    }

    void HasParentFormula::onChildUpdated(Object* object)
    {
      //// error
    }

    void FormulaNot::onAddChildTrue(Object* object)
    {
      if (isValid(object))
      {
        becomeFalse(object) ;
      }
    }
    
    void FormulaNot::onAddChildFalse(Object* object)
    {
      if (! isValid(object))
      {
        becomeTrue(object) ;
      }
    }


  // @}
  /*!
    Trait udate propagation
  */
  // @{
  
    void TraitFormula::updateTrait(Object* object,const TypeIdentifier& trait_name)
    {
      if (!object)
        return ;
      
      TraitFormula* trait = get(trait_name) ;
      if (trait)
      {
        trait->update(object) ;
      }
    }

    void HasParentFormula::updateTrait(Object* object,const TypeIdentifier& trait_name)
    {
      if (!object)
        return ;
      
      HasParentFormula* trait = get(trait_name) ;
      if (trait)
      {
        trait->update(object) ;
        
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ; 
            child != object->getChildren().end() ;
            ++child)
        {
          trait->updateParentTrait(*child) ;
        }
        
      }
    }

    void HasParentFormula::updateParentTrait(Object* object)
    {
      // if object has not the trait...
      if (object->traits.find(m_trait) == object->traits.end())
      {
        update(object) ;
        
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ; 
            child != object->getChildren().end() ;
            ++child)
        {
          updateParentTrait(*child) ;
        }
      }
    }
    
    void Formula::update(Object* object)
    {
      /// notify deduced traits...
//      InternalMessage("Kernel","Formula::update Entering") ;
      
      if (isValid(object))
      {
        DeducedTrait::update(this,object) ;
      }
      
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->onChildUpdated(object) ;
      }
    }
    
    void DeducedTrait::update(Formula* formula,
                              Object* object)
    {
//      InternalMessage("Kernel","DeducedTrait::update Entering") ;

      std::map<Formula*,TypeIdentifier>::const_iterator destructor ;
      destructor = StaticStorage::get()->m_destructors.find(formula) ;
      if (destructor != StaticStorage::get()->m_destructors.end())
      {
        object->_get(destructor->second)->notify() ;
      }      
//      InternalMessage("Kernel","DeducedTrait::update Leaving") ;
    }

    const TypeIdentifier& DeducedTrait::getLatestUpdatedTrait() const
    {
      return Trait::m_latest_updated_trait.top() ;
    }

    void FormulaOr::onChildUpdated(Object* object)
    {
      update(object) ;
    }

    void FormulaAnd::onChildUpdated(Object* object)
    {
      update(object) ;
    }

    void FormulaNot::onChildUpdated(Object* object)
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
