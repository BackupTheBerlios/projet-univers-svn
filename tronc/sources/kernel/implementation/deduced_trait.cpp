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

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
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
  
    HasChildFormula::StaticStorage* HasChildFormula::StaticStorage::get()
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
      std::map<TypeIdentifier,TraitFormula*>::iterator trait ;
      trait = StaticStorage::get()->m_traits_formulae.find(trait_name) ;
      if (trait != StaticStorage::get()->m_traits_formulae.end())
      {
        return trait->second ;
      }

      return NULL ;      
    }
    
    std::set<TraitFormula*> TraitFormula::find(Trait* i_trait)
    {
      TypeIdentifier type(getObjectTypeIdentifier(i_trait)) ;
      
      std::map<TypeIdentifier,std::set<TraitFormula*> >::const_iterator finder =
        StaticStorage::get()->m_impacted_formulae.find(type) ;
      
      if (finder != StaticStorage::get()->m_impacted_formulae.end())
        
        return finder->second ;
      
      std::set<TraitFormula*> result ;
      
      for(std::map<TypeIdentifier,TraitFormula*>::const_iterator trait = StaticStorage::get()->m_traits_formulae.begin() ;
          trait != StaticStorage::get()->m_traits_formulae.end() ;
          ++trait)
      {
        if (trait->first.isInstance(i_trait))
        {
          result.insert(trait->second) ;
        }
      }
      
      StaticStorage::get()->m_impacted_formulae[type] = result ;
      
      return result ;      
    }
    
    int Formula::getDepth() const
    {
      return m_depth ;
    }

    HasParentFormula* HasParentFormula::get(const TypeIdentifier& trait_name)
    {
      std::map<TypeIdentifier,HasParentFormula*>::iterator trait ;
      trait = StaticStorage::get()->m_parent_traits_formulae.find(trait_name) ;
      if (trait != StaticStorage::get()->m_parent_traits_formulae.end())
      {
        return trait->second ;
      }

      return NULL ;      
    }
    
    std::set<HasParentFormula*> HasParentFormula::find(Trait* i_trait)
    {
      TypeIdentifier type(getObjectTypeIdentifier(i_trait)) ;
      
      std::map<TypeIdentifier,std::set<HasParentFormula*> >::const_iterator finder =
        StaticStorage::get()->m_impacted_formulae.find(type) ;
      
      if (finder != StaticStorage::get()->m_impacted_formulae.end())
        
        return finder->second ;
      
      std::set<HasParentFormula*> result ;
      
      for(std::map<TypeIdentifier,HasParentFormula*>::const_iterator trait = StaticStorage::get()->m_parent_traits_formulae.begin() ;
          trait != StaticStorage::get()->m_parent_traits_formulae.end() ;
          ++trait)
      {
        if (trait->first.isInstance(i_trait))
        {
          result.insert(trait->second) ;
        }
      }
      StaticStorage::get()->m_impacted_formulae[type] = result ;
      
      return result ;      
    }
    
    HasChildFormula* HasChildFormula::get(const TypeIdentifier& trait_name)
    {
      std::map<TypeIdentifier,HasChildFormula*>::iterator trait ;
      trait = StaticStorage::get()->m_child_traits_formulae.find(trait_name) ;
      if (trait != StaticStorage::get()->m_child_traits_formulae.end())
      {
        return trait->second ;
      }

      return NULL ;      
    }
    
    std::set<HasChildFormula*> HasChildFormula::find(Trait* i_trait)
    {
      TypeIdentifier type(getObjectTypeIdentifier(i_trait)) ;
      
      std::map<TypeIdentifier,std::set<HasChildFormula*> >::const_iterator finder =
        StaticStorage::get()->m_impacted_formulae.find(type) ;
      
      if (finder != StaticStorage::get()->m_impacted_formulae.end())
        
        return finder->second ;
      
      std::set<HasChildFormula*> result ;
      
      for(std::map<TypeIdentifier,HasChildFormula*>::const_iterator trait = StaticStorage::get()->m_child_traits_formulae.begin() ;
          trait != StaticStorage::get()->m_child_traits_formulae.end() ;
          ++trait)
      {
        if (trait->first.isInstance(i_trait))
        {
          result.insert(trait->second) ;
        }
      }
      
      StaticStorage::get()->m_impacted_formulae[type] = result ;

      return result ;      
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

    HasChildFormula* HasChildFormula::build(const TypeIdentifier& trait_name)
    {
      HasChildFormula* result = get(trait_name) ;
      if (! result)
      {
        result = new HasChildFormula(trait_name) ;
        StaticStorage::get()->m_child_traits_formulae[trait_name] = result ;
      }
      return result ;
    }
    
    HasChildFormula::HasChildFormula(const TypeIdentifier& trait_name)
    : Formula(),
      m_trait(trait_name)
    {
      generateIdentifier() ;
      CHECK((m_depth==0),"HasChildFormula::HasChildFormula invalid depth") ;
    }

    std::string HasChildFormula::internalPrint() const
    {
      return "HasChild(" + m_trait.toString() + ")" ;
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

    std::set<TypeIdentifier> Formula::getDependentTraits() const
    {
      std::set<TypeIdentifier> result ;
      
      std::map<Formula*,TypeIdentifier>::const_iterator finder = 
        DeducedTrait::StaticStorage::get()->m_destructors.find((Formula*)this) ;
      
      if (finder != DeducedTrait::StaticStorage::get()->m_destructors.end())
        
        result.insert(finder->second) ;
      
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        std::set<TypeIdentifier> temp((*parent)->getDependentTraits()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      
      return result ;
    }
    
    std::set<TypeIdentifier> DeducedTrait::getDependentTraits(Trait* trait)
    {
      TypeIdentifier type(getObjectTypeIdentifier(trait)) ;
      
      std::map<TypeIdentifier,std::set<TypeIdentifier> >::iterator finder = 
        StaticStorage::get()->m_dependent_traits.find(type) ;
      
      if (finder != StaticStorage::get()->m_dependent_traits.end())
      {
        return finder->second ;
      }
      
      std::set<TypeIdentifier> result(TraitFormula::getDependentTraits(trait)) ;
      std::set<TypeIdentifier> temp1(HasParentFormula::getDependentTraits(trait)) ;
      std::set<TypeIdentifier> temp2(HasChildFormula::getDependentTraits(trait)) ;
      result.insert(temp1.begin(),temp1.end()) ;
      result.insert(temp2.begin(),temp2.end()) ;
      StaticStorage::get()->m_dependent_traits[type] = result ;
      return result ;
    }

    std::set<TypeIdentifier> TraitFormula::getDependentTraits(Trait* trait)
    {
      std::set<TypeIdentifier> result ;
      std::set<TraitFormula*> formulae(find(trait)) ;
      for(std::set<TraitFormula*>::const_iterator formula = formulae.begin() ;
          formula != formulae.end() ;
          ++formula)
      {
        std::set<TypeIdentifier> temp(((Formula*)*formula)->getDependentTraits()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<TypeIdentifier> HasParentFormula::getDependentTraits(Trait* trait)
    {
      std::set<TypeIdentifier> result ;
      std::set<HasParentFormula*> formulae(find(trait)) ;
      for(std::set<HasParentFormula*>::const_iterator formula = formulae.begin() ;
          formula != formulae.end() ;
          ++formula)
      {
        std::set<TypeIdentifier> temp(((Formula*)*formula)->getDependentTraits()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }
    
    std::set<TypeIdentifier> HasChildFormula::getDependentTraits(Trait* trait)
    {
      std::set<TypeIdentifier> result ;
      std::set<HasChildFormula*> formulae(find(trait)) ;
      for(std::set<HasChildFormula*>::const_iterator formula = formulae.begin() ;
          formula != formulae.end() ;
          ++formula)
      {
        std::set<TypeIdentifier> temp(((Formula*)*formula)->getDependentTraits()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }
    
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
        for(std::set<Formula*>::const_iterator 
              formula = StaticStorage::get()->m_stratification[depth].begin() ;
            formula != StaticStorage::get()->m_stratification[depth].end() ;
            ++formula)
        {
          
          (*formula)->eval(object) ;
          if ((*formula)->isValid(object))
            DeducedTrait::notify(*formula,true,object) ;
          
        }
      }
    }
    
    void DeducedTrait::evaluateInitial(Object* object)
    {
      /// calculate all formulas.
      Formula::evaluateInitial(object) ;
    }

    void FormulaAnd::eval(Object* object)
    {
      bool validity = true ; 
      int true_child_number = 0 ;
       
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        bool child_validity = (*child)->isValid(object) ;
        validity &= child_validity ;
        
        if (child_validity)
        {
          ++true_child_number ;
        }
      }
      
      object->setValidity(this,validity) ;
      object->setNumberOfTrueChildFormulae(this,true_child_number) ;
      
    }

    void FormulaOr::eval(Object* object)
    {
      bool validity = false ; 
      int true_child_number = 0 ;
      
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        bool child_validity = (*child)->isValid(object) ;
        
        validity |= child_validity ;

        if (child_validity)
        {
          ++true_child_number ;
        }
      }
      
      object->setValidity(this,validity) ;
      object->setNumberOfTrueChildFormulae(this,true_child_number) ;

    }

    void FormulaNot::eval(Object* object)
    {
      CHECK((m_children.size()== 1),"FormulaNot::eval children problem") ;
      
      bool validity ; 
      int true_child_number = 0 ;
      
      std::set<Formula*>::const_iterator child = m_children.begin() ;

      if ((*child)->isValid(object))
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
    }

    void TraitFormula::eval(Object* object)
    {
      // nothing to do : its false...
    }

    bool TraitFormula::isValid(Object* object) const
    {
      return object->getTrait(m_trait) ;
    }
    
    void HasParentFormula::eval(Object* object)
    {
      unsigned int number_of_parents = object->getNumberOfParent(m_trait) ;
      object->setNumberOfTrueChildFormulae(this,number_of_parents) ;
      object->setValidity(this,number_of_parents > 0) ;
    }

    void HasChildFormula::eval(Object* object)
    {
      unsigned int number_of_children = object->getNumberOfChildren(m_trait) ;
      object->setNumberOfTrueChildFormulae(this,number_of_children) ;
      object->setValidity(this,number_of_children > 0) ;
    }
    
  // @}
  /*!
    @name Continuous evaluation
  */
  // @{


    void TraitFormula::addTrait(Object* object,Trait* trait)
    {
      CHECK(object,"TraitFormula::addTrait no object")
      std::set<TraitFormula*> formulaes = find(trait) ;
      for(std::set<TraitFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->becomeTrue(object) ;
      }
    }

    void TraitFormula::removeTrait(Object* object,Trait* trait)
    {
      
      std::set<TraitFormula*> formulaes = find(trait) ;
      for(std::set<TraitFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->becomeFalse(object) ;
      }
    }

    void HasParentFormula::addTrait(Object* object,Trait* trait)
    {
      CHECK(object,"HasParentFormula::addTrait no object")

      std::set<HasParentFormula*> formulaes = find(trait) ;
      for(std::set<HasParentFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->addParent(object) ;
      }
    }

    void HasParentFormula::removeTrait(Object* object,Trait* trait)
    {
      std::set<HasParentFormula*> formulaes = find(trait) ;
      for(std::set<HasParentFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->removedParent(object) ;
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
        update(object) ;
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
        update(object) ;
      
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
      /* 
        @c object has changed parent : its number of parents with m_trait may 
        change
      */  
      
      bool old_validity = isValid(object) ;
      bool has_trait = object->getTrait(m_trait) != NULL ;
      unsigned int number_of_parents = 0 ;

      if (has_trait)
      {
        ++number_of_parents ;
      }
      
      Object* new_parent = object->getParent() ;
      if (new_parent)
      {
        number_of_parents += new_parent->getNumberOfTrueChildFormulae(this) ;
      }
      
      object->setNumberOfTrueChildFormulae(this,number_of_parents) ;
      
      bool new_validity = number_of_parents != 0 ;
      
      if (old_validity && new_validity && ! has_trait)
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

      // iterate on children
      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ; 
          child != object->getChildren().end() ;
          ++child)
      {
        onChangedParent(*child,old_parent) ;
      }
     
    }

    void HasChildFormula::addTrait(Object* object,Trait* trait)
    {
      CHECK(object,"HasChildFormula::addTrait no object")
      
      std::set<HasChildFormula*> formulaes = find(trait) ;
      for(std::set<HasChildFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->addedChild(object) ;
      }
    }

    void HasChildFormula::removeTrait(Object* object,Trait* trait)
    {
      
      std::set<HasChildFormula*> formulaes = find(trait) ;
      for(std::set<HasChildFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->removedChild(object) ;
      }
    }

    void HasChildFormula::addedChild(Object* object)
    {
      /*
        Here we use the number of true child formulae on objects to code the 
        number of parents with trait @c trait_name
        
        Direct child just add been added
      */
      // formula is true for current object
      if (isValid(object))
      {
        // update because parent with trait has changed 
        update(object) ;
      }
      else
      {
        becomeTrue(object) ;
      }

      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+1) ;
        
      Object* parent = object->getParent() ;
      if (parent)
      {
        addedChild(parent) ;
      }
    }
    
    void HasChildFormula::removedChild(Object* object)
    {
      /*
        Here we use the number of true child formulae on objects to code the 
        number of parents with trait @c trait_name
        
        Direct parent with trait has changed
        
      */
      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child-1) ;
        
      if (true_child == 1)
      {
        becomeFalse(object) ;
      }
      else
      {
        // still true but child has changed
        update(object) ;
      }
      
      Object* parent = object->getParent() ;
      if (parent)
      {
        removedChild(parent) ;
      }
      
    }

    void HasChildFormula::addedChildren(Object* object, unsigned short number_of_children)
    {
      /*
        Here we use the number of true child formulae on objects to code the 
        number of children with trait @c trait_name
        
        Direct child just add been added
      */
      // formula is true for current object
      if (isValid(object))
      {
        // update because parent with trait has changed 
        DeducedTrait::update(this,object) ;
      }
      else
      {
        becomeTrue(object) ;
      }

      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+number_of_children) ;
        
      Object* parent = object->getParent() ;
      if (parent)
      {
        addedChildren(parent,number_of_children) ;
      }
    }
    
    void HasChildFormula::removedChildren(Object* object, unsigned short number_of_children)
    {
      /*
        Here we use the number of true child formulae on objects to code the 
        number of children with trait @c trait_name
        
        Direct parent with trait has changed
        
      */
      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;

      CHECK(true_child>=number_of_children,"incorrect removed child") ;

      object->setNumberOfTrueChildFormulae(this,true_child-number_of_children) ;
        
      if (true_child == number_of_children)
      {
        becomeFalse(object) ;
      }
      else
      {
        // still true but child has changed
        DeducedTrait::update(this,object) ;
      }
      
      Object* parent = object->getParent() ;
      if (parent)
      {
        removedChildren(parent,number_of_children) ;
      }
      
    }
    
    void HasChildFormula::changeParent(Object* object,Object* old_parent)
    {
      for(std::map<TypeIdentifier,HasChildFormula*>::const_iterator 
          formula = StaticStorage::get()->m_child_traits_formulae.begin() ;
          formula != StaticStorage::get()->m_child_traits_formulae.end() ;
          ++formula)
      {
        formula->second->onChangedParent(object,old_parent) ;
      }
    }
    
    void HasChildFormula::onChangedParent(Object* object,Object* old_parent)
    {
      /* 
        @c object has changed parent : 
        @c old_parent may have changed number of children with m_trait
        also has new parent
        
        @c object cannot have changed status because its children have not moved   
      */  
      

      unsigned int number_of_children = object->getNumberOfChildren(m_trait) ;
      
      if (old_parent && number_of_children > 0)
      {
        removedChildren(old_parent,number_of_children) ;
      }
      Object* parent = object->getParent() ;
      if (parent && number_of_children > 0)
      {
        addedChildren(parent,number_of_children) ;
      }
      
    }
    
    void DeducedTrait::notify(Formula* formula,
                              bool i_validity,
                              Object* object)
    {

      CHECK(formula,"DeducedTrait::notify no formula")
      CHECK(object,"DeducedTrait::notify no object")

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
      CHECK(object,"Formula::addChildTrue no object") ;
      
      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;

      object->setNumberOfTrueChildFormulae(this,true_child+1) ;
      onAddChildTrue(object) ;
    }

    void Formula::addChildFalse(Object* object)
    {
      object->setNumberOfTrueChildFormulae(
        this,object->getNumberOfTrueChildFormulae(this)-1) ;

      onAddChildFalse(object) ;
    }

    void Formula::becomeTrue(Object* object)
    {
      CHECK(object,"Formula::becomeTrue no object")

      if (m_identifier >= 0)
      {
        object->setValidity(this,true) ;
      }
      DeducedTrait::notify(this,true,object) ;
      notifyParentTrue(object) ;
    }

    void Formula::becomeFalse(Object* object)
    {
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
      if (! isValid(object) && 
          object->getNumberOfTrueChildFormulae(this) == m_children.size())
      {
        becomeTrue(object) ;
      }
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

    void HasChildFormula::onAddChildTrue(Object* object) 
    {
      ErrorMessage("HasChildFormula::onAddChildTrue") ;
    }
    
    void HasChildFormula::onAddChildFalse(Object* object) 
    {
      ErrorMessage("HasParentFormula::onAddChildFalse") ;
    }
    
    void TraitFormula::onChildUpdated(Object* object)
    {
      //// error
    }

    void HasParentFormula::onChildUpdated(Object* object)
    {
      // error
    }

    void HasChildFormula::onChildUpdated(Object* object)
    {
      // error
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
  
    void TraitFormula::updateTrait(Object* object,Trait* trait)
    {
      if (!object)
        return ;
      
      std::set<TraitFormula*> formulaes = find(trait) ;
      for(std::set<TraitFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->update(object) ;
      }
    }

    void HasParentFormula::updateTrait(Object* object,Trait* trait)
    {
      if (!object)
        return ;
      
      std::set<HasParentFormula*> formulaes = find(trait) ;
      for(std::set<HasParentFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->update(object) ;
        
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ; 
            child != object->getChildren().end() ;
            ++child)
        {
          (*formula)->updateParentTrait(*child) ;
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

    void HasChildFormula::updateTrait(Object* object,Trait* trait)
    {
      if (!object)
        return ;
      
      std::set<HasChildFormula*> formulaes = find(trait) ;
      for(std::set<HasChildFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->update(object) ;

        Object* parent = object->getParent() ;
        if (parent)
        {
          (*formula)->updateChildTrait(parent) ;
        }
        
      }
    }

    void HasChildFormula::updateChildTrait(Object* object)
    {
      // if object has not the trait...
      if (object->traits.find(m_trait) == object->traits.end())
      {
        update(object) ;
        
        Object* parent = object->getParent() ;
        if (parent)
        {
          updateChildTrait(parent) ;
        }
      }
    }
    
    void Formula::update(Object* object)
    {
      /// notify deduced traits...
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
      std::map<Formula*,TypeIdentifier>::const_iterator destructor ;
      destructor = StaticStorage::get()->m_destructors.find(formula) ;
      if (destructor != StaticStorage::get()->m_destructors.end())
      {
        object->_get(destructor->second)->notify() ;
      }      
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
      TraitFormula::updateTrait(getObject(),this) ;
    }

    void DeducedTrait::addTrait(Object* object,Trait* trait)
    {
      TraitFormula::addTrait(object,trait) ;
      HasParentFormula::addTrait(object,trait) ;
      HasChildFormula::addTrait(object,trait) ;
    }

    void DeducedTrait::updateTrait(Object* object,Trait* trait)
    {
      TraitFormula::updateTrait(object,trait) ;
      HasParentFormula::updateTrait(object,trait) ;
      HasChildFormula::updateTrait(object,trait) ;
    }

    void DeducedTrait::removeTrait(Object* object,Trait* trait)
    {
      TraitFormula::removeTrait(object,trait) ;
      HasParentFormula::removeTrait(object,trait) ;
      HasChildFormula::removeTrait(object,trait) ;
    }
    
  // @}

  }
}
