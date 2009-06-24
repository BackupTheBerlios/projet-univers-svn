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
#include <iostream>
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/deduced_trait.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

  /*!
    @ Static storage
  */
  // @{

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

    HasAncestorFormula::StaticStorage* HasAncestorFormula::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

    RelationFormula::StaticStorage* RelationFormula::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

  // @}
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

    const std::set<TraitFormula*>& TraitFormula::find(Trait* i_trait)
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

      return StaticStorage::get()->m_impacted_formulae[type] = result ;
    }

    int Formula::getDepth() const
    {
      return m_depth ;
    }

    Formula* DeducedTrait::getFormula() const
    {
      return m_formula ;
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

    const std::set<HasParentFormula*>& HasParentFormula::find(Trait* i_trait)
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
      return StaticStorage::get()->m_impacted_formulae[type] = result ;
    }

    HasAncestorFormula* HasAncestorFormula::get(const TypeIdentifier& trait_name)
    {
      std::map<TypeIdentifier,HasAncestorFormula*>::iterator trait ;
      trait = StaticStorage::get()->m_ancestor_traits_formulae.find(trait_name) ;
      if (trait != StaticStorage::get()->m_ancestor_traits_formulae.end())
      {
        return trait->second ;
      }

      return NULL ;
    }

    const std::set<HasAncestorFormula*>& HasAncestorFormula::find(Trait* i_trait)
    {
      TypeIdentifier type(getObjectTypeIdentifier(i_trait)) ;

      std::map<TypeIdentifier,std::set<HasAncestorFormula*> >::const_iterator finder =
        StaticStorage::get()->m_impacted_formulae.find(type) ;

      if (finder != StaticStorage::get()->m_impacted_formulae.end())

        return finder->second ;

      std::set<HasAncestorFormula*> result ;

      for(std::map<TypeIdentifier,HasAncestorFormula*>::const_iterator trait = StaticStorage::get()->m_ancestor_traits_formulae.begin() ;
          trait != StaticStorage::get()->m_ancestor_traits_formulae.end() ;
          ++trait)
      {
        if (trait->first.isInstance(i_trait))
        {
          result.insert(trait->second) ;
        }
      }
      return StaticStorage::get()->m_impacted_formulae[type] = result ;
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

    const std::set<HasChildFormula*>& HasChildFormula::find(Trait* i_trait)
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

      return StaticStorage::get()->m_impacted_formulae[type] = result ;
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

    HasAncestorFormula* HasAncestorFormula::build(const TypeIdentifier& trait_name)
    {
      HasAncestorFormula* result = get(trait_name) ;
      if (! result)
      {
        result = new HasAncestorFormula(trait_name) ;
        StaticStorage::get()->m_ancestor_traits_formulae[trait_name] = result ;
      }

      return result ;
    }

    HasAncestorFormula::HasAncestorFormula(const TypeIdentifier& trait_name)
    : Formula(),
      m_trait(trait_name)
    {
      generateIdentifier() ;
      CHECK((m_depth==0),"HasAncestorFormula::HasAncestorFormula invalid depth") ;
    }

    std::string HasAncestorFormula::internalPrint() const
    {
      return "HasAncestorFormula(" + m_trait.toString() + ")" ;
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

    std::string IsRelatedFormula::internalPrint() const
    {
      std::string result = "IsRelated(" + m_relation.fullName() + "," ;
      std::string children ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ; child != m_children.end() ; ++child)
      {
        if(!children.empty())
          children += "," ;
        children += (*child)->print() ;
      }

      return result + children + ")" ;
    }

    RelationFormula::RelationFormula(const TypeIdentifier& relation)
    : m_relation(relation)
    {
      generateIdentifier() ;
      StaticStorage::get()->m_formulae[relation].insert(this) ;
    }

    IsRelatedFormula::IsRelatedFormula(const TypeIdentifier& relation)
    : RelationFormula(relation)
    {}

    std::string IsOnlyRelatedFormula::internalPrint() const
    {
      std::string result = "IsOnlyRelated(" + m_relation.fullName() + "," ;
      std::string children ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ; child != m_children.end() ; ++child)
      {
        if(!children.empty())
          children += "," ;
        children += (*child)->print() ;
      }

      return result + children + ")" ;
    }

    IsOnlyRelatedFormula::IsOnlyRelatedFormula(const TypeIdentifier& relation)
    : RelationFormula(relation)
    {}


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
    : m_formula(NULL)
    {}

    std::set<TypeIdentifier> Formula::getDependentTraitTypes() const
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
        std::set<TypeIdentifier> temp((*parent)->getDependentTraitTypes()) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }

    std::set<Trait*> Formula::getDependentTraits(Object* object) const
    {
      std::set<Trait*> result ;

      std::map<Formula*,TypeIdentifier>::const_iterator finder =  DeducedTrait::StaticStorage::get()->m_destructors.find(const_cast<Formula*>(this)) ;
      if (finder != DeducedTrait::StaticStorage::get()->m_destructors.end())
      {
        result.insert(object->getTrait(finder->second)) ;
      }

      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ; parent != m_parents.end() ; ++parent)
      {
        std::set<Trait*> temp((*parent)->getDependentTraits(object)) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }

    const std::set<TypeIdentifier>& DeducedTrait::getDependentTraitTypes(Trait* trait)
    {
      TypeIdentifier type(getObjectTypeIdentifier(trait)) ;

      std::map<TypeIdentifier,std::set<TypeIdentifier> >::iterator finder =
        StaticStorage::get()->m_dependent_traits.find(type) ;

      if (finder != StaticStorage::get()->m_dependent_traits.end())
      {
        return finder->second ;
      }

      std::set<TypeIdentifier> result(TraitFormula::getDependentTraitTypes(trait)) ;
      std::set<TypeIdentifier> temp1(HasParentFormula::getDependentTraitTypes(trait)) ;
      std::set<TypeIdentifier> temp2(HasChildFormula::getDependentTraitTypes(trait)) ;
      result.insert(temp1.begin(),temp1.end()) ;
      result.insert(temp2.begin(),temp2.end()) ;
      return StaticStorage::get()->m_dependent_traits[type] = result ;
    }

    std::set<TypeIdentifier> TraitFormula::getDependentTraitTypes(Trait* trait)
    {

      std::set<TypeIdentifier> result ;
      const std::set<TraitFormula*>& formulae = find(trait) ;
      for(std::set<TraitFormula*>::const_iterator formula = formulae.begin() ;
          formula != formulae.end() ;
          ++formula)
      {
        std::set<TypeIdentifier> temp(((Formula*)*formula)->getDependentTraitTypes()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<TypeIdentifier> HasParentFormula::getDependentTraitTypes(Trait* trait)
    {
      std::set<TypeIdentifier> result ;
      const std::set<HasParentFormula*>& formulae = find(trait) ;
      for(std::set<HasParentFormula*>::const_iterator formula = formulae.begin() ;
          formula != formulae.end() ;
          ++formula)
      {
        std::set<TypeIdentifier> temp(((Formula*)*formula)->getDependentTraitTypes()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<TypeIdentifier> HasAncestorFormula::getDependentTraitTypes(Trait* trait)
    {
      std::set<TypeIdentifier> result ;
      const std::set<HasAncestorFormula*>& formulae = find(trait) ;
      for(std::set<HasAncestorFormula*>::const_iterator formula = formulae.begin() ;
          formula != formulae.end() ;
          ++formula)
      {
        std::set<TypeIdentifier> temp(((Formula*)*formula)->getDependentTraitTypes()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<TypeIdentifier> HasChildFormula::getDependentTraitTypes(Trait* trait)
    {
      std::set<TypeIdentifier> result ;
      const std::set<HasChildFormula*> formulae = find(trait) ;
      for(std::set<HasChildFormula*>::const_iterator formula = formulae.begin() ;
          formula != formulae.end() ;
          ++formula)
      {
        std::set<TypeIdentifier> temp(((Formula*)*formula)->getDependentTraitTypes()) ;
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

    void HasAncestorFormula::eval(Object* object)
    {
      unsigned int number_of_ancestors = object->getNumberOfAncestor(m_trait) ;
      object->setNumberOfTrueChildFormulae(this,number_of_ancestors) ;
      object->setValidity(this,number_of_ancestors > 0) ;
    }

    void HasChildFormula::eval(Object* object)
    {
      unsigned int number_of_children = object->getNumberOfChildren(m_trait) ;
      object->setNumberOfTrueChildFormulae(this,number_of_children) ;
      object->setValidity(this,number_of_children > 0) ;
    }

    void IsRelatedFormula::eval(Object* object)
    {
      Formula* formula = *m_children.begin() ;
      std::set<Object*> related(object->getModel()->getRelations(m_relation,object)) ;
      unsigned int number_of_true_related = 0 ;
      for(std::set<Object*>::iterator related_object = related.begin() ; related_object != related.end() ; ++ related_object)
      {
        if (formula->isValid(*related_object))
          ++number_of_true_related ;
      }

      object->setNumberOfTrueChildFormulae(this,number_of_true_related) ;
      object->setValidity(this,number_of_true_related > 0) ;
    }

    void IsOnlyRelatedFormula::eval(Object* object)
    {
      Formula* formula = *m_children.begin() ;
      std::set<Object*> related(object->getModel()->getRelations(m_relation,object)) ;
      unsigned int number_of_true_related = 0 ;
      for(std::set<Object*>::iterator related_object = related.begin() ; related_object != related.end() ; ++ related_object)
      {
        if (formula->isValid(*related_object))
          ++number_of_true_related ;
      }

      object->setNumberOfTrueChildFormulae(this,number_of_true_related) ;
      object->setValidity(this,number_of_true_related > 0 && number_of_true_related == related.size()) ;
    }

  // @}
  /*!
    @name Continuous evaluation
  */
  // @{


    void TraitFormula::addTrait(Object* object,Trait* trait)
    {
      const std::set<TraitFormula*>& formulaes = find(trait) ;
      for(std::set<TraitFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->becomeTrue(object) ;
      }
    }

    void TraitFormula::removeTrait(Object* object,Trait* trait)
    {

      const std::set<TraitFormula*>& formulaes = find(trait) ;
      for(std::set<TraitFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->becomeFalse(object) ;
      }
    }

    void HasParentFormula::addTrait(Object* object,Trait* trait)
    {
      Log::Block temp("Deduction",std::string("addTrait ") +
                                  toString(object->getIdentifier()) + " " +
                                  getObjectTypeIdentifier(trait).className()) ;

      const std::set<HasParentFormula*>& formulaes = find(trait) ;
      for(std::set<HasParentFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->addParent(object,trait) ;
      }
    }

    void HasParentFormula::addParent(Object* object,Trait* trait)
    {
      Log::Block temp("Deduction",std::string("addParent ") +
                                  toString(object->getIdentifier()) + " " +
                                  getObjectTypeIdentifier(trait).className() +
                                  " number of brothers " +
                                  toString(object->getParent()?
                                      object->getParent()->getChildren().size():0)) ;
      /*
        Here we use the number of true child formulae on objects to code the
        number of parents with trait @c trait_name

        Direct parent just add been added
      */
      if (isValid(object))
      {
        /*
           formula was already true for current object
           update because parent with trait has changed
           -->
           -# m_trait(object) is no longer dependent on xxx
           -# m_trait(object) is dependent of trait
        */
        update(object) ;

        // Update trait dependencies

        Trait* old_updater = trait->getObject()->getAncestor(m_trait) ;
        std::set<Trait*> dependents = getDependentTraits(object) ;
        for(std::set<Trait*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          /// @todo remove that test
          if (old_updater)
          {
            /*
              We may have added objects under the element...
            */
            old_updater->removeDependentTrait((DeducedTrait*)*dependent) ;
            trait->addDependentTrait((DeducedTrait*)*dependent) ;
          }
        }
      }
      else
      {
        becomeTrue(object) ;
      }

      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+1) ;

      std::set<Object*> children(object->getChildren()) ;

      for(std::set<Object*>::const_iterator child = children.begin() ; child != children.end() ; ++child)
      {
        addParent(*child,trait) ;
      }
    }

    void HasParentFormula::removeTrait(Object* object,Trait* trait)
    {
      const std::set<HasParentFormula*>& formulaes = find(trait) ;
      for(std::set<HasParentFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->removedParent(object,trait) ;
      }
    }

    void HasParentFormula::removedParent(Object* object,Trait* trait)
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
        // still true but parent has changed
        update(object) ;

        Trait* new_updater = trait->getObject()->getAncestor(m_trait) ;
        std::set<Trait*> dependents = this->getDependentTraits(object) ;
        for(std::set<Trait*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          /// @todo remove that test
          if (new_updater)
          {
            // useless but left for clarity
            trait->removeDependentTrait((DeducedTrait*)*dependent) ;
            new_updater->addDependentTrait((DeducedTrait*)*dependent) ;
          }
        }

      }

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        removedParent(*child,trait) ;
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

        Trait* old_updater = old_parent->getParent(m_trait) ;
        Trait* new_updater = object->getParent(m_trait) ;
        std::set<Trait*> dependents = this->getDependentTraits(object) ;
        for(std::set<Trait*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          /// @todo remove that test
          // useless but left for clarity
          if (old_updater)
            old_updater->removeDependentTrait((DeducedTrait*)*dependent) ;
          if (new_updater)
            new_updater->addDependentTrait((DeducedTrait*)*dependent) ;
        }

      }
      else if (old_validity && !new_validity)
      {
        becomeFalse(object) ;
      }
      else if (!old_validity && new_validity)
      {
        becomeTrue(object) ;
      }

      // iterate on object children
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

      const std::set<HasChildFormula*>& formulaes = find(trait) ;
      for(std::set<HasChildFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        (*formula)->addedChild(object) ;
      }
    }

    void HasChildFormula::removeTrait(Object* object,Trait* trait)
    {

      const std::set<HasChildFormula*>& formulaes = find(trait) ;
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

    void HasAncestorFormula::addTrait(Object* object,Trait* trait)
    {
      CHECK(object,"HasAncestorFormula::addTrait no object")

      const std::set<HasAncestorFormula*>& formulaes = find(trait) ;
      for(std::set<HasAncestorFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
            child != object->getChildren().end() ;
            ++child)
        {
          (*formula)->addedAncestor(*child) ;
        }
      }
    }

    void HasAncestorFormula::removeTrait(Object* object,Trait* trait)
    {
      const std::set<HasAncestorFormula*>& formulaes = find(trait) ;
      for(std::set<HasAncestorFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
            child != object->getChildren().end() ;
            ++child)
        {
          (*formula)->removedAncestor(*child) ;
        }
      }
    }

    void HasAncestorFormula::addedAncestor(Object* object)
    {
      /*
        Here we use the number of true child formulae on objects to code the
        number of parents with trait @c trait_name

        Direct parent just add been added
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

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        addedAncestor(*child) ;
      }
    }

    void HasAncestorFormula::removedAncestor(Object* object)
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
        // still true but parent has changed
        update(object) ;
      }

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        removedAncestor(*child) ;
      }

    }

    void HasAncestorFormula::changeParent(Object* object,Object* old_parent)
    {
      for(std::map<TypeIdentifier,HasAncestorFormula*>::const_iterator
            formula = StaticStorage::get()->m_ancestor_traits_formulae.begin() ;
          formula != StaticStorage::get()->m_ancestor_traits_formulae.end() ;
          ++formula)
      {
        formula->second->onChangedParent(object,old_parent) ;
      }
    }

    void HasAncestorFormula::onChangedParent(Object* object,Object* old_parent)
    {
      /*
        @c object has changed parent : its number of parents with m_trait may
        change
      */

      bool old_validity = isValid(object) ;
      unsigned int number_of_parents = 0 ;

      Object* new_parent = object->getParent() ;
      if (new_parent)
      {
        number_of_parents += new_parent->getNumberOfParent(m_trait) ;
      }

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

      // iterate on children
      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        onChangedParent(*child,old_parent) ;
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
        // add the deduced trait
        std::map<Formula*,DeducedTraitBuilder>::const_iterator builder ;
        builder = StaticStorage::get()->m_builders.find(formula) ;
        if (builder != StaticStorage::get()->m_builders.end())
        {
          DeducedTrait* new_trait = (builder->second)() ;
          new_trait->m_formula = formula ;
          // deduced trait added :
          std::set<Trait*> updaters(formula->getUpdaterTraits(object)) ;

          for(std::set<Trait*>::iterator updater = updaters.begin() ;
              updater != updaters.end() ;
              ++updater)
          {
            (*updater)->addDependentTrait(new_trait) ;
          }

          object->addTrait(new_trait) ;
        }
      }
      else
      {
        std::map<Formula*,TypeIdentifier>::const_iterator destructor ;
        destructor = StaticStorage::get()->m_destructors.find(formula) ;
        if (destructor != StaticStorage::get()->m_destructors.end())
        {

          DeducedTrait* removed = (DeducedTrait*)object->getTrait(destructor->second) ;
          // deduced trait removed
          std::set<Trait*> updaters(formula->getUpdaterTraits(object)) ;

          for(std::set<Trait*>::iterator updater = updaters.begin() ;
              updater != updaters.end() ;
              ++updater)
          {
            (*updater)->removeDependentTrait(removed) ;
          }

          object->_remove(destructor->second) ;

        }
      }
    }

    void Formula::addChildFormulaTrue(Object* object)
    {
      CHECK(object,"Formula::addChildTrue no object") ;

      unsigned short true_child = object->getNumberOfTrueChildFormulae(this) ;

      object->setNumberOfTrueChildFormulae(this,true_child+1) ;
      onAddChildFormulaTrue(object) ;
    }

    void Formula::addChildFormulaFalse(Object* object)
    {
      object->setNumberOfTrueChildFormulae(
        this,object->getNumberOfTrueChildFormulae(this)-1) ;

      onAddChildFormulaFalse(object) ;
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
        (*parent)->addChildFormulaTrue(object) ;
      }
    }

    void Formula::notifyParentFalse(Object* object)
    {
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->addChildFormulaFalse(object) ;
      }
    }

    void FormulaAnd::onAddChildFormulaFalse(Object* object)
    {
      if (isValid(object))
      {
        becomeFalse(object) ;
      }
    }

    void FormulaAnd::onAddChildFormulaTrue(Object* object)
    {
      if (! isValid(object) &&
          object->getNumberOfTrueChildFormulae(this) == m_children.size())
      {
        becomeTrue(object) ;
      }
    }

    void FormulaOr::onAddChildFormulaTrue(Object* object)
    {
      if (! isValid(object))
      {
        becomeTrue(object) ;
      }
      else
      {
        update(object) ;

        std::set<Trait*> deduced_traits(getDependentTraits(object)) ;
        std::set<Trait*> new_updatertraits(getUpdaterTraits(object)) ;

        for(std::set<Trait*>::const_iterator deduced_trait = deduced_traits.begin() ; deduced_trait != deduced_traits.end() ; ++deduced_trait)
        {
          for(std::set<Trait*>::const_iterator updater = new_updatertraits.begin() ; updater != new_updatertraits.end() ; ++updater)
          {
            (*updater)->addDependentTrait((DeducedTrait*)(*deduced_trait)) ;
          }
        }

      }
    }

    void FormulaOr::onAddChildFormulaFalse(Object* object)
    {
      if (isValid(object) &&
          object->getNumberOfTrueChildFormulae(this) == 0)
      {
        becomeFalse(object) ;
      }
    }

    void TraitFormula::onAddChildFormulaTrue(Object* object)
    {
      ErrorMessage("TraitFormula::onAddChildFormulaTrue") ;
    }

    void TraitFormula::onAddChildFormulaFalse(Object* object)
    {
      ErrorMessage("TraitFormula::onAddChildFormulaFalse") ;
    }

    void HasParentFormula::onAddChildFormulaTrue(Object* object)
    {
      ErrorMessage("HasParentFormula::onAddChildFormulaTrue") ;
    }

    void HasParentFormula::onAddChildFormulaFalse(Object* object)
    {
      ErrorMessage("HasParentFormula::onAddChildFormulaFalse") ;
    }

    void HasAncestorFormula::onAddChildFormulaTrue(Object* object)
    {
      ErrorMessage("HasAncestorFormula::onAddChildFormulaTrue") ;
    }

    void HasAncestorFormula::onAddChildFormulaFalse(Object* object)
    {
      ErrorMessage("HasAncestorFormula::onAddChildFormulaFalse") ;
    }

    void HasChildFormula::onAddChildFormulaTrue(Object* object)
    {
      ErrorMessage("HasChildFormula::onAddChildFormulaTrue") ;
    }

    void HasChildFormula::onAddChildFormulaFalse(Object* object)
    {
      ErrorMessage("HasParentFormula::onAddChildFormulaFalse") ;
    }

    void TraitFormula::onChildFormulaUpdated(Object* object)
    {
      //// error
    }

    void HasParentFormula::onChildFormulaUpdated(Object* object)
    {
      // error
    }

    void HasAncestorFormula::onChildFormulaUpdated(Object* object)
    {
      // error
    }

    void HasChildFormula::onChildFormulaUpdated(Object* object)
    {
      // error
    }

    void FormulaNot::onAddChildFormulaTrue(Object* object)
    {
      if (isValid(object))
      {
        becomeFalse(object) ;
      }
    }

    void FormulaNot::onAddChildFormulaFalse(Object* object)
    {
      if (! isValid(object))
      {
        becomeTrue(object) ;
      }
    }

    void RelationFormula::addChildFormulaTrue(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        unsigned short true_related = (*related)->getNumberOfTrueChildFormulae(this) ;
        (*related)->setNumberOfTrueChildFormulae(this,true_related+1) ;
        onAddChildFormulaTrue(*related) ;
      }
    }

    void RelationFormula::addChildFormulaFalse(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        unsigned short true_related = (*related)->getNumberOfTrueChildFormulae(this) ;
        (*related)->setNumberOfTrueChildFormulae(this,true_related-1) ;
        onAddChildFormulaFalse(*related) ;
      }
    }

    void IsRelatedFormula::onAddChildFormulaTrue(Object* object)
    {
      if (object->getNumberOfTrueChildFormulae(this) == 1)
        becomeTrue(object) ;
      else
        update(object) ;
    }

    void IsRelatedFormula::onAddChildFormulaFalse(Object* object)
    {
      if (object->getNumberOfTrueChildFormulae(this) == 0)
        becomeFalse(object) ;
      else
        update(object) ;
    }

    void IsRelatedFormula::onChildFormulaUpdated(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        update(*related) ;
      }
    }

    void IsOnlyRelatedFormula::onAddChildFormulaTrue(Object* object)
    {
      if (object->getNumberOfTrueChildFormulae(this) ==
          object->getModel()->getRelations(m_relation,object).size())
        becomeTrue(object) ;
    }

    void IsOnlyRelatedFormula::onAddChildFormulaFalse(Object* object)
    {
      becomeFalse(object) ;
    }

    void IsOnlyRelatedFormula::onChildFormulaUpdated(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        update(*related) ;
      }
    }

    void RelationFormula::onAddRelation(const Relation& relation)
    {
      std::map<TypeIdentifier,std::set<RelationFormula*> >::const_iterator finder =
        StaticStorage::get()->m_formulae.find(relation.getType()) ;

      if (finder != StaticStorage::get()->m_formulae.end())
      {
        const std::set<RelationFormula*>& formulae = finder->second ;

        for(std::set<RelationFormula*>::iterator formula = formulae.begin() ; formula != formulae.end() ; ++formula)
        {
          Formula* child_formula = *((*formula)->m_children.begin()) ;

          if (child_formula->isValid(relation.getObject2()))
          {
            unsigned short true_related = relation.getObject1()->getNumberOfTrueChildFormulae(*formula) ;
            relation.getObject1()->setNumberOfTrueChildFormulae(*formula,true_related+1) ;
            (*formula)->onAddChildFormulaTrue(relation.getObject1()) ;
          }
        }
      }
    }

    void RelationFormula::onRemoveRelation(const Relation& relation)
    {
      std::map<TypeIdentifier,std::set<RelationFormula*> >::const_iterator finder =
        StaticStorage::get()->m_formulae.find(relation.getType()) ;

      if (finder != StaticStorage::get()->m_formulae.end())
      {
        const std::set<RelationFormula*>& formulae = finder->second ;

        for(std::set<RelationFormula*>::iterator formula = formulae.begin() ; formula != formulae.end() ; ++formula)
        {
          Formula* child_formula = *((*formula)->m_children.begin()) ;

          if (child_formula->isValid(relation.getObject2()))
          {
            unsigned short true_related = relation.getObject1()->getNumberOfTrueChildFormulae(*formula) ;
            relation.getObject1()->setNumberOfTrueChildFormulae(*formula,true_related-1) ;
            (*formula)->onAddChildFormulaFalse(relation.getObject1()) ;
          }
        }
      }
    }

  // @}
  /*!
    Trait udate propagation
  */
  // @{

    std::set<Trait*> TraitFormula::getUpdaterTraits(Object* object) const
    {
      std::set<Trait*> result ;
      Trait* trait = object->getTrait(m_trait) ;
      if (trait)
        result.insert(trait) ;
      return result ;
    }

    std::set<Trait*> HasChildFormula::getUpdaterTraits(Object* object) const
    {
      return object->getDirectChildren(m_trait) ;
    }

    std::set<Trait*> FormulaHasDescendant::getUpdaterTraits(Object* object) const
    {
      // not implemented
      return std::set<Trait*>() ;
    }

    std::set<Trait*> HasAncestorFormula::getUpdaterTraits(Object* object) const
    {
      std::set<Trait*> result ;
      Trait* trait = object->getAncestor(m_trait) ;
      if (trait)
        result.insert(trait) ;
      return result ;
    }

    std::set<Trait*> HasParentFormula::getUpdaterTraits(Object* object) const
    {
      std::set<Trait*> result ;
      Trait* trait = object->getParent(m_trait) ;
      if (trait)
        result.insert(trait) ;
      return result ;
    }

    std::set<Trait*> FormulaAnd::getUpdaterTraits(Object* object) const
    {
      std::set<Trait*> result ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        std::set<Trait*> temp((*child)->getUpdaterTraits(object)) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<Trait*> FormulaOr::getUpdaterTraits(Object* object) const
    {
      std::set<Trait*> result ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        std::set<Trait*> temp((*child)->getUpdaterTraits(object)) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<Trait*> FormulaNot::getUpdaterTraits(Object* object) const
    {
      return std::set<Trait*>() ;
    }

    std::set<Trait*> RelationFormula::getUpdaterTraits(Object* object) const
    {
      std::set<Trait*> result ;
      Formula* formula = *m_children.begin() ;
      Model* model = object->getModel() ;
      std::set<Object*> objects(model->getRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        if (formula->isValid(*related))
        {
          std::set<Trait*> temp(formula->getUpdaterTraits(*related)) ;
          result.insert(temp.begin(),temp.end()) ;
        }
      }
      return result ;
    }

    void TraitFormula::updateTrait(Object* object,Trait* trait)
    {
      if (!object)
        return ;

      const std::set<TraitFormula*>& formulaes = find(trait) ;
      if (formulaes.empty())
        return ;
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

      const std::set<HasParentFormula*>& formulaes = find(trait) ;
      if (formulaes.empty())
        return ;
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
      // if object has the trait we should stop udpating down
      if (!object->_getDeducedTrait(m_trait))
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

    void HasAncestorFormula::updateTrait(Object* object,Trait* trait)
    {
      if (!object)
        return ;

      const std::set<HasAncestorFormula*>& formulaes = find(trait) ;
      if (formulaes.empty())
        return ;
      for(std::set<HasAncestorFormula*>::const_iterator formula = formulaes.begin() ;
          formula != formulaes.end() ;
          ++formula)
      {
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
            child != object->getChildren().end() ;
            ++child)
        {
          if ((*formula)->isValid(*child))
          {
            (*formula)->updateAncestorTrait(*child) ;
          }
        }

      }
    }

    void HasAncestorFormula::updateAncestorTrait(Object* object)
    {
      update(object) ;

      // if object has not the trait...
      if (!object->_getDeducedTrait(m_trait))
      {
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
            child != object->getChildren().end() ;
            ++child)
        {
          updateAncestorTrait(*child) ;
        }
      }
    }

    void HasChildFormula::updateTrait(Object* object,Trait* trait)
    {
      if (!object)
        return ;

      const std::set<HasChildFormula*>& formulaes = find(trait) ;
      if (formulaes.empty())
        return ;
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
      if (!object->_getDeducedTrait(m_trait))
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
        // if this formula defines a deduced trait, it acts as a notify() on it
        DeducedTrait::update(this,object) ;
        /// @todo optim 50% du temps sur un update
        for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
            parent != m_parents.end() ;
            ++parent)
        {
          (*parent)->onChildFormulaUpdated(object) ;
        }
      }
    }

    void DeducedTrait::update(Formula* formula,
                              Object* object)
    {
      std::map<Formula*,TypeIdentifier>::const_iterator destructor ;
      destructor = StaticStorage::get()->m_destructors.find(formula) ;
      if (destructor != StaticStorage::get()->m_destructors.end())
      {
        object->_getDeducedTrait(destructor->second)->notify() ;
      }
    }

    const TypeIdentifier& DeducedTrait::getLatestUpdatedTrait() const
    {
      return Trait::m_latest_updated_trait.top() ;
    }

    void FormulaOr::onChildFormulaUpdated(Object* object)
    {
      update(object) ;
    }

    void FormulaAnd::onChildFormulaUpdated(Object* object)
    {
      update(object) ;
    }

    void FormulaNot::onChildFormulaUpdated(Object* object)
    {
      /// nothing
    }

    void DeducedTrait::notify()
    {
      lock() ;
      _updated() ;
      DeducedTrait::updateTrait(getObject(),this) ;
      unlock() ;
    }

  // @}
  /*!
    @name Global treatments
  */
  // @{

    void DeducedTrait::addTrait(Object* object,Trait* trait)
    {
      TraitFormula::addTrait(object,trait) ;
      HasParentFormula::addTrait(object,trait) ;
      HasAncestorFormula::addTrait(object,trait) ;
      HasChildFormula::addTrait(object,trait) ;
    }

    void DeducedTrait::updateTrait(Object* object,Trait* trait)
    {
      /*
        valgrind indicates that following functions take the same time on
        basic performance tests (tests without parent formulae)

        problem is that it takes 75% of time without parent/ancestor/child formulae
      */
      TraitFormula::updateTrait(object,trait) ;
      /// @todo optim 50% du temps sur un système sans formules de parentés !!
      HasParentFormula::updateTrait(object,trait) ;
      HasAncestorFormula::updateTrait(object,trait) ;
      HasChildFormula::updateTrait(object,trait) ;
    }

    void DeducedTrait::removeTrait(Object* object,Trait* trait)
    {
      TraitFormula::removeTrait(object,trait) ;
      HasParentFormula::removeTrait(object,trait) ;
      HasAncestorFormula::removeTrait(object,trait) ;
      HasChildFormula::removeTrait(object,trait) ;
    }

    void DeducedTrait::changeParent(Object* object,Object* old_parent)
    {
      /*
        @remark nothing to do for TraitFormula because that cannot change
        the validity ;)
      */
      HasParentFormula::changeParent(object,old_parent) ;
      HasAncestorFormula::changeParent(object,old_parent) ;
      HasChildFormula::changeParent(object,old_parent) ;
    }

    void DeducedTrait::addRelation(const Relation& relation)
    {
      RelationFormula::onAddRelation(relation) ;
    }

    void DeducedTrait::removeRelation(const Relation& relation)
    {
      RelationFormula::onRemoveRelation(relation) ;
    }

    bool DeducedTrait::isPrimitive() const
    {
      return false ;
    }

  // @}

  }
}
