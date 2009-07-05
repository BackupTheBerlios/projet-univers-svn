/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

    WithRelationFormula::StaticStorage* WithRelationFormula::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

    DeducedRelation::StaticStorage* DeducedRelation::StaticStorage::get()
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

    bool Formula::isValid(const ObjectPair& relation) const
    {
      return relation.getValidity(this) ;
    }

    Object* Formula::getValidParent(Object* object) const
    {
      if (isValid(object))
        return object ;

      if (!object->getParent())
        return NULL ;

      return getValidParent(object->getParent()) ;
    }

    Object* Formula::getValidAncestor(Object* object) const
    {
      if (!object->getParent())
        return NULL ;

      return getValidParent(object->getParent()) ;
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

    TypeIdentifier DeducedRelation::get(Formula* formula)
    {
      std::map<Formula*,TypeIdentifier>::iterator finder ;
      finder = StaticStorage::get()->m_deduced_relations.find(formula) ;
      if (finder != StaticStorage::get()->m_deduced_relations.end())
        return finder->second ;
      return VoidTypeIdentifier ;
    }

    std::set<Formula*> DeducedRelation::getFormulae(const TypeIdentifier& primitive_relation)
    {
      std::set<Formula*> result ;

      for (std::multimap<TypeIdentifier,Formula*>::iterator
             formula = StaticStorage::get()->m_primitive_relation_to_formulae.lower_bound(primitive_relation),
             last = StaticStorage::get()->m_primitive_relation_to_formulae.upper_bound(primitive_relation) ;

           formula != StaticStorage::get()->m_primitive_relation_to_formulae.end() &&
           formula != last && formula->first == primitive_relation ;
           ++formula)
      {
        result.insert(formula->second) ;
      }

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

    HasParentFormula::HasParentFormula()
    : Formula()
    {
      generateIdentifier() ;
      StaticStorage::get()->m_formulae.insert(this) ;
    }

    std::string HasParentFormula::internalPrint() const
    {
      return "HasParent" ;
    }

    Formula* HasParentFormula::getChildFormula() const
    {
      return *m_children.begin() ;
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

    WithRelationFormula::WithRelationFormula(const TypeIdentifier& relation)
    : m_relation(relation)
    {
      generateIdentifier() ;
      StaticStorage::get()->m_formulae[relation].insert(this) ;
    }

    IsRelatedFormula::IsRelatedFormula(const TypeIdentifier& relation)
    : WithRelationFormula(relation)
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
    : WithRelationFormula(relation)
    {}

    FormulaOnRelation::FormulaOnRelation()
    {}

    IsFromFormula::IsFromFormula()
    {
      generateIdentifier() ;
    }

    IsToFormula::IsToFormula()
    {
      generateIdentifier() ;
    }

    std::string IsFromFormula::internalPrint() const
    {
      std::string result = "IsFrom(" ;
      std::string children ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ; child != m_children.end() ; ++child)
      {
        if(!children.empty())
          children += "," ;
        children += (*child)->print() ;
      }

      return result + children + ")" ;
    }

    std::string IsToFormula::internalPrint() const
    {
      std::string result = "IsTo(" ;
      std::string children ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ; child != m_children.end() ; ++child)
      {
        if(!children.empty())
          children += "," ;
        children += (*child)->print() ;
      }

      return result + children + ")" ;
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
    : m_formula(NULL)
    {}

    void DeducedRelation::registerRelation(const TypeIdentifier& relation,
                                           const TypeIdentifier& primitive_relation,
                                           Formula*              formula)
    {
      StaticStorage::get()->m_deduced_relations[formula] = relation ;
      StaticStorage::get()->m_primitive_relation_to_formulae.insert(std::make_pair(primitive_relation,formula)) ;
    }


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

    std::set<DeducedTrait*> Formula::getDependentDeducedTraits(Object* object) const
    {
      std::set<DeducedTrait*> result ;

      std::map<Formula*,TypeIdentifier>::const_iterator finder =  DeducedTrait::StaticStorage::get()->m_destructors.find(const_cast<Formula*>(this)) ;
      if (finder != DeducedTrait::StaticStorage::get()->m_destructors.end())
      {
        result.insert(object->_getDeducedTrait(finder->second)) ;
      }

      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ; parent != m_parents.end() ; ++parent)
      {
        std::set<DeducedTrait*> temp((*parent)->getDependentDeducedTraits(object)) ;
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
      std::set<TypeIdentifier> temp2(HasChildFormula::getDependentTraitTypes(trait)) ;
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

    void Formula::evaluateInitial(const ObjectPair& relation)
    {
      for(std::set<Formula*>::iterator child = m_children.begin() ; child != m_children.end() ; ++child)
      {
        (*child)->evaluateInitial(relation) ;
      }

      eval(relation) ;
      if (isValid(relation))
        DeducedRelation::notify(this,true,relation) ;
    }

    void Formula::eval(const ObjectPair& relation)
    {
      // default is nop
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

    void FormulaAnd::eval(const ObjectPair& pair)
    {
      bool validity = true ;
      int true_child_number = 0 ;

      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        bool child_validity = (*child)->isValid(pair) ;
        validity &= child_validity ;

        if (child_validity)
        {
          ++true_child_number ;
        }
      }
      pair.setValidity(this,validity) ;
      pair.setNumberOfTrueChildFormulae(this,true_child_number) ;
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

    void FormulaOr::eval(const ObjectPair& pair)
    {
      bool validity = false ;
      int true_child_number = 0 ;

      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        bool child_validity = (*child)->isValid(pair) ;

        validity |= child_validity ;

        if (child_validity)
        {
          ++true_child_number ;
        }
      }

      pair.setValidity(this,validity) ;
      pair.setNumberOfTrueChildFormulae(this,true_child_number) ;
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

    void FormulaNot::eval(const ObjectPair& pair)
    {
      bool validity = false ;
      int true_child_number = 0 ;

      std::set<Formula*>::const_iterator child = m_children.begin() ;

      if ((*child)->isValid(pair))
      {
        validity = false ;
        true_child_number = 1 ;
      }
      else
      {
        validity = true ;
      }

      pair.setValidity(this,validity) ;
      pair.setNumberOfTrueChildFormulae(this,true_child_number) ;
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
      Formula* child_formula = getChildFormula() ;
      unsigned int number_of_parents = object->getNumberOfParent(child_formula) ;
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

    void IsToFormula::eval(Object* object)
    {
      // nop
    }

    void IsFromFormula::eval(Object* object)
    {
      // nop
    }

    void IsFromFormula::evaluateInitial(const ObjectPair& relation)
    {
      eval(relation) ;
      if (isValid(relation))
        DeducedRelation::notify(this,true,relation) ;
    }

    void IsFromFormula::eval(const ObjectPair& relation)
    {
      Formula* child = *m_children.begin() ;
      relation.setValidity(this,child->isValid(relation.getObjectFrom())) ;
    }

    void IsToFormula::evaluateInitial(const ObjectPair& relation)
    {
      eval(relation) ;
    }

    void IsToFormula::eval(const ObjectPair& relation)
    {
      Formula* child = *m_children.begin() ;
      relation.setValidity(this,child->isValid(relation.getObjectTo())) ;
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

    void HasParentFormula::addParent(Object* object,Object* new_parent)
    {
      Log::Block temp("Deduction",std::string("addParent ") +
                                  toString(object->getIdentifier()) +
                                  " number of brothers " +
                                  toString(object->getParent()?
                                      object->getParent()->getChildren().size():0)) ;
      /*
        Direct parent just add been added
      */
      if (isValid(object))
      {
        /*
           formula was already true for current object
           update because parent with formula has changed
        */
        update(object) ;

        // Update trait dependencies
        std::set<Trait*> old_updaters = getChildFormula()->getUpdaterTraits(getChildFormula()->getValidAncestor(new_parent)) ;
        std::set<Trait*> new_updaters = getChildFormula()->getUpdaterTraits(new_parent) ;

        std::set<DeducedTrait*> dependents = getDependentDeducedTraits(object) ;
        for(std::set<DeducedTrait*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          for(std::set<Trait*>::iterator old_updater = old_updaters.begin() ; old_updater != old_updaters.end() ; ++old_updater)
          {
            (*old_updater)->removeDependency(*dependent) ;
          }
          for(std::set<Trait*>::iterator new_updater = new_updaters.begin() ; new_updater != new_updaters.end() ; ++new_updater)
          {
            (*new_updater)->addDependency(*dependent) ;
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
        addParent(*child,new_parent) ;
      }
    }

    void HasParentFormula::removeParent(Object* object,Object* removed_parent)
    {
      /*
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

        std::set<Trait*> new_updaters = getChildFormula()->getUpdaterTraits(getChildFormula()->getValidAncestor(removed_parent)) ;
        std::set<DeducedTrait*> dependents = this->getDependentDeducedTraits(object) ;
        for(std::set<DeducedTrait*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          for(std::set<Trait*>::iterator new_updater = new_updaters.begin() ; new_updater != new_updaters.end() ; ++new_updater)
          {
            (*new_updater)->addDependency(*dependent) ;
          }
        }

      }

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        removeParent(*child,removed_parent) ;
      }

    }

    void HasParentFormula::changeParent(Object* object,Object* old_parent)
    {
      for(std::set<HasParentFormula*>::const_iterator formula = StaticStorage::get()->m_formulae.begin() ;
          formula != StaticStorage::get()->m_formulae.end() ;
          ++formula)
      {
        (*formula)->onChangedParent(object,old_parent) ;
      }
    }

    void HasParentFormula::onChangedParent(Object* object,Object* old_parent)
    {
      /*
        @c object has changed parent : its number of parents with formula may
        change
      */
      bool old_validity = isValid(object) ;
      bool has_formula = getChildFormula()->isValid(object) ;

      unsigned int number_of_parents = 0 ;

      if (has_formula)
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

      if (old_validity && new_validity && ! has_formula)
      {
        // update because parent with trait has changed
        DeducedTrait::update(this,object) ;

        std::set<Trait*> old_updaters = getChildFormula()->getUpdaterTraits(getChildFormula()->getValidParent(old_parent)) ;
        std::set<Trait*> new_updaters = getChildFormula()->getUpdaterTraits(getChildFormula()->getValidParent(object)) ;

        std::set<DeducedTrait*> dependents = this->getDependentDeducedTraits(object) ;
        for(std::set<DeducedTrait*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          for(std::set<Trait*>::iterator old_updater = old_updaters.begin() ; old_updater != old_updaters.end() ; ++old_updater)
          {
            (*old_updater)->removeDependency(*dependent) ;
          }
          for(std::set<Trait*>::iterator new_updater = new_updaters.begin() ; new_updater != new_updaters.end() ; ++new_updater)
          {
            (*new_updater)->addDependency(*dependent) ;
          }
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
            (*updater)->addDependency(new_trait) ;
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
            (*updater)->removeDependency(removed) ;
          }

          object->_remove(destructor->second) ;

        }
      }
    }

    void DeducedRelation::notify(Formula*          formula,
                                 bool              validity,
                                 const ObjectPair& pair)
    {
      TypeIdentifier relation = get(formula) ;

      if (relation != VoidTypeIdentifier)
      {
        if (validity)
        {
          // add a link
          Relation::createLink(relation,pair.getObjectFrom(),pair.getObjectTo()) ;
        }
        else
        {
          // remove a link
          Relation::destroyLink(relation,pair.getObjectFrom(),pair.getObjectTo()) ;
        }
      }
    }

    void Formula::addChildFormulaTrue(Object* object)
    {
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

    void Formula::addChildFormulaTrue(const ObjectPair& pair)
    {
      unsigned short true_child = pair.getNumberOfTrueChildFormulae(this) ;

      pair.setNumberOfTrueChildFormulae(this,true_child+1) ;
      onAddChildFormulaTrue(pair) ;
    }

    void Formula::addChildFormulaFalse(const ObjectPair& pair)
    {
      pair.setNumberOfTrueChildFormulae(
        this,pair.getNumberOfTrueChildFormulae(this)-1) ;

      onAddChildFormulaFalse(pair) ;
    }

    void Formula::onAddChildFormulaTrue(const ObjectPair&)
    {
      // default is nop
    }

    void Formula::onAddChildFormulaFalse(const ObjectPair&)
    {
      // default is nop
    }

    void Formula::becomeTrue(Object* object)
    {
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

    void Formula::becomeTrue(const ObjectPair& pair)
    {
      if (m_identifier >= 0)
      {
        pair.setValidity(this,true) ;
      }
      DeducedRelation::notify(this,true,pair) ;
      notifyParentTrue(pair) ;
    }

    void Formula::becomeFalse(const ObjectPair& pair)
    {
      if (m_identifier >= 0)
      {
        pair.setValidity(this,false) ;
      }
      DeducedRelation::notify(this,false,pair) ;
      notifyParentFalse(pair) ;
    }

    void Formula::notifyParentTrue(const ObjectPair& pair)
    {
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->addChildFormulaTrue(pair) ;
      }
    }

    void Formula::notifyParentFalse(const ObjectPair& pair)
    {
      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
          parent != m_parents.end() ;
          ++parent)
      {
        (*parent)->addChildFormulaFalse(pair) ;
      }
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

    void FormulaAnd::onAddChildFormulaFalse(const ObjectPair& pair)
    {
      if (isValid(pair))
      {
        becomeFalse(pair) ;
      }
    }

    void FormulaAnd::onAddChildFormulaTrue(const ObjectPair& pair)
    {
      if (! isValid(pair) &&
          pair.getNumberOfTrueChildFormulae(this) == m_children.size())
      {
        becomeTrue(pair) ;
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

        std::set<DeducedTrait*> deduced_traits(getDependentDeducedTraits(object)) ;
        std::set<Trait*> new_updatertraits(getUpdaterTraits(object)) ;

        for(std::set<DeducedTrait*>::const_iterator deduced_trait = deduced_traits.begin() ; deduced_trait != deduced_traits.end() ; ++deduced_trait)
        {
          for(std::set<Trait*>::const_iterator updater = new_updatertraits.begin() ; updater != new_updatertraits.end() ; ++updater)
          {
            (*updater)->addDependency(*deduced_trait) ;
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
      /// @todo handle dependent traits
    }

    void FormulaOr::onAddChildFormulaTrue(const ObjectPair& pair)
    {
      if (! isValid(pair))
      {
        becomeTrue(pair) ;
      }
    }

    void FormulaOr::onAddChildFormulaFalse(const ObjectPair& pair)
    {
      if (isValid(pair) &&
          pair.getNumberOfTrueChildFormulae(this) == 0)
      {
        becomeFalse(pair) ;
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
      addParent(object,object) ;
    }

    void HasParentFormula::onAddChildFormulaFalse(Object* object)
    {
      removeParent(object,object) ;
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
      ErrorMessage("HasChildFormula::onAddChildFormulaFalse") ;
    }

    void TraitFormula::onChildFormulaUpdated(Object* object)
    {
      // error
    }

    void HasParentFormula::onChildFormulaUpdated(Object* object)
    {
      update(object) ;

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        updateChildrenObjects(*child) ;
      }

    }

    void HasParentFormula::updateChildrenObjects(Object* object)
    {
      Formula* child_formula = getChildFormula() ;

      // if the object has the formula we should stop going down
      if (! child_formula->isValid(object))
      {
        update(object) ;

        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
            child != object->getChildren().end() ;
            ++child)
        {
          updateChildrenObjects(*child) ;
        }
      }
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

    void FormulaNot::onAddChildFormulaTrue(const ObjectPair& pair)
    {
      if (isValid(pair))
      {
        becomeFalse(pair) ;
      }
    }

    void FormulaNot::onAddChildFormulaFalse(const ObjectPair& pair)
    {
      if (! isValid(pair))
      {
        becomeTrue(pair) ;
      }
    }

    void WithRelationFormula::addChildFormulaTrue(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        unsigned short true_related = (*related)->getNumberOfTrueChildFormulae(this) ;
        (*related)->setNumberOfTrueChildFormulae(this,true_related+1) ;
        onAddChildFormulaTrue(*related) ;
      }
    }

    void WithRelationFormula::addChildFormulaFalse(Object* object)
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

    void WithRelationFormula::onAddRelation(const Relation& relation)
    {
      std::map<TypeIdentifier,std::set<WithRelationFormula*> >::const_iterator finder =
        StaticStorage::get()->m_formulae.find(relation.getType()) ;

      if (finder != StaticStorage::get()->m_formulae.end())
      {
        const std::set<WithRelationFormula*>& formulae = finder->second ;

        for(std::set<WithRelationFormula*>::iterator formula = formulae.begin() ; formula != formulae.end() ; ++formula)
        {
          Formula* child_formula = *((*formula)->m_children.begin()) ;

          if (child_formula->isValid(relation.getObjectTo()))
          {
            unsigned short true_related = relation.getObjectFrom()->getNumberOfTrueChildFormulae(*formula) ;
            relation.getObjectFrom()->setNumberOfTrueChildFormulae(*formula,true_related+1) ;
            (*formula)->onAddChildFormulaTrue(relation.getObjectFrom()) ;
          }
        }
      }
    }

    void WithRelationFormula::onRemoveRelation(const Relation& relation)
    {
      std::map<TypeIdentifier,std::set<WithRelationFormula*> >::const_iterator finder =
        StaticStorage::get()->m_formulae.find(relation.getType()) ;

      if (finder != StaticStorage::get()->m_formulae.end())
      {
        const std::set<WithRelationFormula*>& formulae = finder->second ;

        for(std::set<WithRelationFormula*>::iterator formula = formulae.begin() ; formula != formulae.end() ; ++formula)
        {
          Formula* child_formula = *((*formula)->m_children.begin()) ;

          if (child_formula->isValid(relation.getObjectTo()))
          {
            unsigned short true_related = relation.getObjectFrom()->getNumberOfTrueChildFormulae(*formula) ;
            relation.getObjectFrom()->setNumberOfTrueChildFormulae(*formula,true_related-1) ;
            (*formula)->onAddChildFormulaFalse(relation.getObjectFrom()) ;
          }
        }
      }
    }

    void DeducedRelation::onAddRelation(const Relation& relation)
    {
      std::set<Formula*> formulae(getFormulae(relation.getType())) ;
      for (std::set<Formula*>::iterator formula = formulae.begin() ; formula != formulae.end() ; ++formula)
      {
        (*formula)->evaluateInitial(relation) ;
      }
    }

    void DeducedRelation::onRemoveRelation(const Relation& relation)
    {
      std::set<Formula*> formulae(getFormulae(relation.getType())) ;
      for (std::set<Formula*>::iterator formula = formulae.begin() ; formula != formulae.end() ; ++formula)
      {
        (*formula)->becomeFalse(relation) ;
      }
    }

    void IsFromFormula::onAddChildFormulaTrue(Object* object)
    {
      /*
        Here we should say that the formula has gained a true children
        for all ObjectPair (object,x) which is prohibitive
        Same applies for
        * IsFromFormula::onAddChildFormulaFalse
        * IsToFormula::onAddChildFormulaTrue
        * IsToFormula::onAddChildFormulaFalse

        So we limit ourselves to the object pairs taken from existing links
      */

      std::set<Object*> objects(Relation::_getLinked(object)) ;
      for(std::set<Object*>::iterator to = objects.begin() ; to != objects.end() ; ++to)
      {
        becomeTrue(ObjectPair(object,*to)) ;
      }
    }

    void IsFromFormula::onAddChildFormulaFalse(Object* object)
    {
      // all links going from object became false
      std::set<Object*> objects(Relation::_getLinked(object)) ;
      for(std::set<Object*>::iterator to = objects.begin() ; to != objects.end() ; ++to)
      {
        becomeFalse(ObjectPair(object,*to)) ;
      }
    }

    void IsToFormula::onAddChildFormulaTrue(Object* object)
    {
      // all links going to object became true
      std::set<Object*> objects(Relation::_getInversedLinked(object)) ;
      for(std::set<Object*>::iterator from = objects.begin() ; from != objects.end() ; ++from)
      {
        becomeTrue(ObjectPair(*from,object)) ;
      }
    }

    void IsToFormula::onAddChildFormulaFalse(Object* object)
    {
      // all links going to object became false
      std::set<Object*> objects(Relation::_getInversedLinked(object)) ;
      for(std::set<Object*>::iterator from = objects.begin() ; from != objects.end() ; ++from)
      {
        becomeFalse(ObjectPair(*from,object)) ;
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

      Formula* formula = getChildFormula() ;

      Object* valid_parent = formula->getValidParent(object) ;

      if (!valid_parent)
        return result ;

      return formula->getUpdaterTraits(valid_parent) ;
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
      // empty on purpose
      return std::set<Trait*>() ;
    }

    std::set<Trait*> WithRelationFormula::getUpdaterTraits(Object* object) const
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

    std::set<Trait*> IsFromFormula::getUpdaterTraits(Object* object) const
    {
      Formula* formula = *m_children.begin() ;
      return formula->getUpdaterTraits(object) ;
    }

    std::set<Trait*> IsToFormula::getUpdaterTraits(Object* object) const
    {
      Formula* formula = *m_children.begin() ;
      return formula->getUpdaterTraits(object) ;
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
        /// @todo optimize 50% of time on an update
        for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
            parent != m_parents.end() ;
            ++parent)
        {
          (*parent)->onChildFormulaUpdated(object) ;
        }
      }
    }

    void Formula::update(const ObjectPair& pair)
    {
      /// notify deduced relations...
      if (isValid(pair))
      {
        // if this formula defines a deduced relation, it acts as a notify() on it
        DeducedRelation::update(this,pair) ;
        for(std::set<Formula*>::const_iterator parent = m_parents.begin() ;
            parent != m_parents.end() ;
            ++parent)
        {
          (*parent)->onChildFormulaUpdated(pair) ;
        }
      }
    }

    void Formula::onChildFormulaUpdated(const ObjectPair& pair)
    {
      // default implementation is error
      ErrorMessage("Formula::onChildFormulaUpdated(const ObjectPair& pair)") ;
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

    void DeducedRelation::update(Formula*          formula,
                                 const ObjectPair& relation)
    {
      TypeIdentifier deduced_relation(get(formula)) ;
      if (deduced_relation != VoidTypeIdentifier)
      {
        Relation observed(deduced_relation,relation.getObjectFrom(),relation.getObjectTo()) ;
        observed.notify() ;
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

    void FormulaOr::onChildFormulaUpdated(const ObjectPair& pair)
    {
      update(pair) ;
    }

    void FormulaAnd::onChildFormulaUpdated(Object* object)
    {
      update(object) ;
    }

    void FormulaAnd::onChildFormulaUpdated(const ObjectPair& pair)
    {
      update(pair) ;
    }

    void FormulaNot::onChildFormulaUpdated(Object* object)
    {
      /// nothing (on purpose)
    }

    void IsFromFormula::onChildFormulaUpdated(Object* object)
    {
      std::set<Object*> objects(Relation::_getLinked(object)) ;
      for(std::set<Object*>::iterator to = objects.begin() ; to != objects.end() ; ++to)
      {
        update(ObjectPair(object,*to)) ;
      }
    }

    void IsToFormula::onChildFormulaUpdated(Object* object)
    {
      // all links going to object must be updated
      std::set<Object*> objects(Relation::_getInversedLinked(object)) ;
      for(std::set<Object*>::iterator from = objects.begin() ; from != objects.end() ; ++from)
      {
        update(ObjectPair(*from,object)) ;
      }
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
      /// @todo optim 50% du temps sur un syst�me sans formules de parent�s !!
      HasAncestorFormula::updateTrait(object,trait) ;
      HasChildFormula::updateTrait(object,trait) ;
    }

    void DeducedTrait::removeTrait(Object* object,Trait* trait)
    {
      TraitFormula::removeTrait(object,trait) ;
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
      DeducedRelation::onAddRelation(relation) ;
      WithRelationFormula::onAddRelation(relation) ;
    }

    void DeducedTrait::removeRelation(const Relation& relation)
    {
      DeducedRelation::onRemoveRelation(relation) ;
      WithRelationFormula::onRemoveRelation(relation) ;
    }

    bool DeducedTrait::isPrimitive() const
    {
      return false ;
    }

  // @}

  }
}
