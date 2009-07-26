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

    std::set<Object*> Formula::getDirectChildren(Object* object)
    {
      std::set<Object*> result ;
      if (isValid(object))
      {
        result.insert(object) ;
        return result ;
      }

      for(std::set<Object*>::iterator child = object->getChildren().begin() ; child != object->getChildren().end() ; ++child)
      {
        std::set<Object*> temp(getDirectChildren(*child)) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }

    std::set<Object*> Formula::getDirectDescendants(Object*object)
    {
      std::set<Object*> result ;

      for(std::set<Object*>::iterator child = object->getChildren().begin() ; child != object->getChildren().end() ; ++child)
      {
        std::set<Object*> temp(getDirectChildren(*child)) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
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

    Formula* DeducedTrait::getFormula(const TypeIdentifier& name)
    {
      return StaticStorage::get()->m_formulae[name] ;
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

    std::set<Notifiable*> Formula::getUpdaterNotifiables(const std::set<Object*> objects) const
    {
      std::set<Notifiable*> result ;
      for(std::set<Object*>::iterator object = objects.begin() ; object != objects.end() ; ++object)
      {
        std::set<Notifiable*> temp(getUpdaterNotifiables(*object)) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
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
      return "HasTrait(" + m_trait.fullName() + ")" ;
    }

    HasParentFormula::HasParentFormula()
    {
      generateIdentifier() ;
      StaticStorage::get()->m_formulae.insert(this) ;
    }

    std::string HasParentFormula::internalPrint() const
    {
      return "HasParent" ;
    }

    HasAncestorFormula::HasAncestorFormula()
    {
      generateIdentifier() ;
      StaticStorage::get()->m_formulae.insert(this) ;
    }

    std::string HasAncestorFormula::internalPrint() const
    {
      return "HasAncestorFormula" ;
    }

    HasChildFormula::HasChildFormula()
    {
      generateIdentifier() ;
      StaticStorage::get()->m_formulae.insert(this) ;
    }

    std::string HasChildFormula::internalPrint() const
    {
      return "HasChild" ;
    }

    Formula* ParentshipFormula::getChildFormula() const
    {
      return *m_children.begin() ;
    }

    Formula* WithRelationFormula::getChildFormula() const
    {
      return *m_children.begin() ;
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

    void DeducedTrait::registerTrait(Formula* formula,
                                     DeducedTraitBuilder builder,
                                     const TypeIdentifier& trait_name)
    {
      StaticStorage::get()->m_builders[formula] = builder ;
      StaticStorage::get()->m_destructors.insert(std::pair<Formula*,TypeIdentifier>(formula,trait_name)) ;
      StaticStorage::get()->m_formulae[trait_name] = formula ;
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

    std::set<Notifiable*> Formula::getDependentNotifiables(Object* object) const
    {
      std::set<Notifiable*> result ;

      std::map<Formula*,TypeIdentifier>::const_iterator deduced_trait =
          DeducedTrait::StaticStorage::get()->m_destructors.find(const_cast<Formula*>(this)) ;
      if (deduced_trait != DeducedTrait::StaticStorage::get()->m_destructors.end())
      {
        DeducedTrait* temp = object->_getDeducedTrait(deduced_trait->second) ;
        if (temp)
          result.insert(temp) ;
      }

      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ; parent != m_parents.end() ; ++parent)
      {
        std::set<Notifiable*> temp((*parent)->getDependentNotifiables(object)) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }

    std::set<Notifiable*> Formula::getDependentNotifiables(const ObjectPair& pair) const
    {
      std::set<Notifiable*> result ;

      std::map<Formula*,TypeIdentifier>::const_iterator deduced_relation =
          DeducedRelation::StaticStorage::get()->m_deduced_relations.find(const_cast<Formula*>(this)) ;
      if (deduced_relation != DeducedRelation::StaticStorage::get()->m_deduced_relations.end())
      {
        if (Relation::_areLinked(deduced_relation->second,pair.getObjectFrom(),pair.getObjectTo()))
          result.insert(Relation::getRelation(deduced_relation->second,pair.getObjectFrom(),pair.getObjectTo())) ;
      }

      for(std::set<Formula*>::const_iterator parent = m_parents.begin() ; parent != m_parents.end() ; ++parent)
      {
        std::set<Notifiable*> temp((*parent)->getDependentNotifiables(pair)) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }

    void Formula::maintainDependencies(Object* object,
                                       Formula* formula,
                                       std::set<Object*> new_sources,
                                       std::set<Object*> old_sources) const
    {
      std::set<Notifiable*> dependents(getDependentNotifiables(object)) ;

      std::set<Notifiable*> new_updaters(formula->getUpdaterNotifiables(new_sources)) ;
      std::set<Notifiable*> old_updaters(formula->getUpdaterNotifiables(old_sources)) ;

      for(std::set<Notifiable*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
      {
        for(std::set<Notifiable*>::iterator old_updater = old_updaters.begin() ; old_updater != old_updaters.end() ; ++old_updater)
        {
          (*old_updater)->removeDependency(*dependent) ;
        }
        for(std::set<Notifiable*>::iterator new_updater = new_updaters.begin() ; new_updater != new_updaters.end() ; ++new_updater)
        {
          (*new_updater)->addDependency(*dependent) ;
        }
      }

    }

    void Formula::maintainDependencies(Object* object,
                                       Formula* formula,
                                       std::set<Object*> new_sources,
                                       Object* old_source) const
    {
      std::set<Object*> old_sources ;
      if (old_source)
        old_sources.insert(old_source) ;

      maintainDependencies(object,formula,new_sources,old_sources) ;
    }

    void Formula::maintainDependencies(Object* object,
                                       Formula* formula,
                                       Object* new_source,
                                       std::set<Object*> old_sources) const
    {
      std::set<Object*> new_sources ;
      if (new_source)
        new_sources.insert(new_source) ;

      maintainDependencies(object,formula,new_sources,old_sources) ;
    }

    void Formula::maintainDependencies(Object* object,
                                       Formula* formula,
                                       Object* new_source,
                                       Object* old_source) const
    {
      std::set<Object*> old_sources ;
      if (old_source)
        old_sources.insert(old_source) ;

      std::set<Object*> new_sources ;
      if (new_source)
        new_sources.insert(new_source) ;

      maintainDependencies(object,formula,new_sources,old_sources) ;
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

    void Formula::eval(const ObjectPair&)
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

    void TraitFormula::eval(Object*)
    {
      // nothing to do : its false...
    }

    bool TraitFormula::isValid(Object* object) const
    {
      return object->getTrait(m_trait) ;
    }

    void HasParentFormula::eval(Object* object)
    {
      unsigned int number_of_parents = object->getNumberOfParent(getChildFormula()) ;
      object->setNumberOfTrueChildFormulae(this,number_of_parents) ;
      object->setValidity(this,number_of_parents > 0) ;
    }

    void HasAncestorFormula::eval(Object* object)
    {
      unsigned int number_of_ancestors = object->getNumberOfAncestor(getChildFormula()) ;
      object->setNumberOfTrueChildFormulae(this,number_of_ancestors) ;
      object->setValidity(this,number_of_ancestors > 0) ;
    }

    void HasChildFormula::eval(Object* object)
    {
      unsigned int number_of_children = object->getNumberOfChildren(getChildFormula()) ;
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

    void IsToFormula::eval(Object*)
    {
      // nop
    }

    void IsFromFormula::eval(Object*)
    {
      // nop
    }

    void IsFromFormula::eval(const ObjectPair& relation)
    {
      Formula* child = *m_children.begin() ;
      relation.setValidity(this,child->isValid(relation.getObjectFrom())) ;
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

    void HasParentFormula::addParent(Object* object,Object* new_parent,const bool& may_update)
    {
      Log::Block temp("Deduction",std::string("addParent ") +
                                  toString(object->getIdentifier()) +
                                  " number of brothers " +
                                  toString(object->getParent()?
                                      object->getParent()->getChildren().size():0)) ;
      /*
        Direct parent just add been added
      */

      bool local_may_update = !getChildFormula()->isValid(object) || object == new_parent ;

      if (may_update && isValid(object) && local_may_update)
      {
        /*
           formula was already true for current object
           update because parent with formula has changed
        */
        update(object) ;

        // Update trait dependencies
        maintainDependencies(object,
                             getChildFormula(),
                             new_parent,
                             getChildFormula()->getValidAncestor(new_parent)) ;
      }
      else if (!isValid(object))
      {
        becomeTrue(object) ;
      }

      short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+1) ;

      std::set<Object*> children(object->getChildren()) ;

      for(std::set<Object*>::const_iterator child = children.begin() ; child != children.end() ; ++child)
      {
        addParent(*child,new_parent,local_may_update) ;
      }
    }

    void HasParentFormula::removeParent(Object* object,Object* removed_parent,const bool& may_update)
    {
      if( removed_parent->isDeleting())
        // no need to go further all child traits have been closed
        return ;
      /*
        Direct parent with trait has changed
      */
      short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child-1) ;

      bool local_may_update = may_update && ( !getChildFormula()->isValid(object) || object == removed_parent) ;

      if (true_child <= 0)
      {
        throw ExceptionKernel("HasParentFormula::removeParent") ;
      }

      if (true_child == 1)
      {
        becomeFalse(object) ;
      }
      else if (true_child > 1 && local_may_update)
      {
        // still true but parent has changed
        update(object) ;

        maintainDependencies(object,
                             getChildFormula(),
                             getChildFormula()->getValidAncestor(removed_parent),
                             NULL) ;
      }

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        removeParent(*child,removed_parent,local_may_update) ;
      }

    }

    void HasParentFormula::changeParent(Object* object,Object* old_parent)
    {
      for(std::set<HasParentFormula*>::const_iterator formula = StaticStorage::get()->m_formulae.begin() ;
          formula != StaticStorage::get()->m_formulae.end() ;
          ++formula)
      {
        (*formula)->onChangedParent(object,old_parent,true) ;
      }
    }

    void HasParentFormula::onChangedParent(Object* object,Object* old_parent,const bool& may_update)
    {
      /*
        an @c object ancestor has changed parent : its number of parents with
        formula may change
      */
      bool old_validity = isValid(object) ;
      bool has_formula = getChildFormula()->isValid(object) ;

      short number_of_parents = 0 ;

      bool local_may_upate = may_update && !has_formula ;

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

      if (old_validity && new_validity && local_may_upate)
      {
        // update because parent with trait has changed
        update(object) ;

        maintainDependencies(object,
                             getChildFormula(),
                             getChildFormula()->getValidParent(object),
                             getChildFormula()->getValidParent(old_parent)) ;
      }
      else if (old_validity && !new_validity)
      {
        becomeFalse(object) ;
      }
      else if (!old_validity && new_validity)
      {
        becomeTrue(object) ;
      }

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        onChangedParent(*child,old_parent,local_may_upate) ;
      }
    }

    void HasChildFormula::addedChild(Object* object,Object* new_child,const bool& may_update)
    {
      bool local_may_update = may_update ;

      // formula is true for current object
      if (may_update && isValid(object) && !getChildFormula()->isValid(object))
      {
        update(object) ;
        local_may_update = false ;

        maintainDependencies(object,
                             getChildFormula(),
                             new_child,
                             getChildFormula()->getDirectDescendants(new_child)) ;
      }
      else if (!isValid(object))
      {
        becomeTrue(object) ;
      }
      else if (getChildFormula()->isValid(object) && object != new_child)
      {
        local_may_update = false ;
      }

      short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+1) ;

      Object* parent = object->getParent() ;
      if (parent)
      {
        addedChild(parent,new_child,local_may_update) ;
      }
    }

    void HasChildFormula::removedChild(Object* object,Object* removed_child,const bool& may_update)
    {
      short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child-1) ;

      bool local_may_update = may_update && !(getChildFormula()->isValid(object) && object != removed_child) ;

      if (true_child == 1)
      {
        becomeFalse(object) ;
      }
      else if (local_may_update)
      {
        // still true but child has changed
        update(object) ;

        maintainDependencies(object,
                             getChildFormula(),
                             getChildFormula()->getDirectDescendants(removed_child),
                             removed_child) ;
      }

      Object* parent = object->getParent() ;
      if (parent)
      {
        removedChild(parent,removed_child,local_may_update) ;
      }
    }

    void HasChildFormula::addedChildren(Object* object, short number_of_children)
    {
      /*
        Here we use the number of true child formulae on objects to code the
        number of children with trait @c trait_name

        Direct child just add been added

        @todo maintain dependencies

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

      short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+number_of_children) ;

      Object* parent = object->getParent() ;
      if (parent)
      {
        addedChildren(parent,number_of_children) ;
      }
    }

    void HasChildFormula::removedChildren(Object* object, short number_of_children)
    {
      /*
        Here we use the number of true child formulae on objects to code the
        number of children with trait @c trait_name

        Direct parent with trait has changed
        @todo maintain dependencies

      */
      short true_child = object->getNumberOfTrueChildFormulae(this) ;

      CHECK(true_child>=number_of_children,"incorrect removed child") ;

      object->setNumberOfTrueChildFormulae(this,true_child-number_of_children) ;

      if (true_child == number_of_children)
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
        removedChildren(parent,number_of_children) ;
      }

    }

    void HasChildFormula::changeParent(Object* object,Object* old_parent)
    {
      for(std::set<HasChildFormula*>::const_iterator
          formula = StaticStorage::get()->m_formulae.begin() ;
          formula != StaticStorage::get()->m_formulae.end() ;
          ++formula)
      {
        (*formula)->onChangedParent(object,old_parent) ;
      }
    }

    void HasChildFormula::onChangedParent(Object* object,Object* old_parent)
    {
      /*
        @c object has changed parent :
        @c old_parent may have changed number of children with m_trait
        also has new parent

        @c object cannot have changed status because its children have not moved

        @todo maintain dependencies
      */

      unsigned int number_of_children = object->getNumberOfChildren(getChildFormula()) ;

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

    void HasAncestorFormula::addAncestor(Object* object,Object* new_ancestor,const bool& may_update)
    {
      /*
        Ancestor just add been added

        important to go down first because of recursive case... it will induce
        updates in case of Or(HasAncestor(HasTrait(RecursivePos)),HasTrait(Pos))
        @see Kernel::Test::TestModelView::addingParentUpdateHasAncestor.
      */

      bool local_may_update = may_update ;

      if (may_update && getChildFormula()->isValid(object))
      {
        local_may_update = false ;
      }

      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        addAncestor(*child,new_ancestor,local_may_update) ;
      }

      // formula is true for current object
      if (may_update && isValid(object))
      {
        // update because parent with trait has changed
        update(object) ;

        // Update trait dependencies
        maintainDependencies(object,
                             getChildFormula(),
                             new_ancestor,
                             getChildFormula()->getValidAncestor(new_ancestor)) ;
      }
      else if (!isValid(object))
      {
        becomeTrue(object) ;
      }

      short true_child = object->getNumberOfTrueChildFormulae(this) ;
      object->setNumberOfTrueChildFormulae(this,true_child+1) ;


    }

    void HasAncestorFormula::removeAncestor(Object* object,Object* removed_ancestor,const bool& may_update)
    {
      if (removed_ancestor->isDeleting())
        // no need to go further, all traits have been closed
        return ;
      /*
        a true ancestor has been removed
      */
      short true_child = object->getNumberOfTrueChildFormulae(this) ;

      bool local_may_update = !getChildFormula()->isValid(object) ;

      if (true_child <= 0)
      {
        throw ExceptionKernel("HasAncestorFormula::removeAncestor") ;
      }

      object->setNumberOfTrueChildFormulae(this,true_child-1) ;

      if (true_child == 1)
      {
        becomeFalse(object) ;
      }
      else if (true_child > 1 && may_update)
      {
        // still true but parent has changed
        update(object) ;

        // Update trait dependencies
        maintainDependencies(object,
                             getChildFormula(),
                             getChildFormula()->getValidAncestor(removed_ancestor),
                             NULL) ;
      }
      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        removeAncestor(*child,removed_ancestor,local_may_update) ;
      }
    }

    void HasAncestorFormula::changeParent(Object* object,Object* old_parent)
    {
      for(std::set<HasAncestorFormula*>::const_iterator formula = StaticStorage::get()->m_formulae.begin() ;
          formula != StaticStorage::get()->m_formulae.end() ;
          ++formula)
      {
        (*formula)->onChangedParent(object,old_parent,true) ;
      }
    }

    void HasAncestorFormula::onChangedParent(Object* object,Object* old_parent,const bool& may_update)
    {
      /*
        @c object has changed parent : its number of parents with formula may
        change
      */

      bool old_validity = isValid(object) ;
      unsigned int number_of_parents = 0 ;

      bool local_may_update = may_update && !getChildFormula()->isValid(object) ;

      Object* new_parent = object->getParent() ;
      if (new_parent)
      {
        number_of_parents += new_parent->getNumberOfParent(getChildFormula()) ;
      }

      object->setNumberOfTrueChildFormulae(this,number_of_parents) ;

      bool new_validity = number_of_parents != 0 ;

      if (old_validity && new_validity && may_update)
      {
        // update because parent with trait has changed
        update(object) ;

        // Update trait dependencies
        maintainDependencies(object,
                             getChildFormula(),
                             getChildFormula()->getValidAncestor(object),
                             getChildFormula()->getValidParent(old_parent)) ;
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
        onChangedParent(*child,old_parent,local_may_update) ;
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
          std::set<Notifiable*> updaters(formula->getUpdaterNotifiables(object)) ;

          for(std::set<Notifiable*>::iterator updater = updaters.begin() ;
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
          std::set<Notifiable*> updaters(formula->getUpdaterNotifiables(object)) ;

          for(std::set<Notifiable*>::iterator updater = updaters.begin() ;
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
          Relation* new_relation(Relation::createLink(relation,pair.getObjectFrom(),pair.getObjectTo())) ;

          std::set<Notifiable*> updaters(formula->getUpdaterNotifiables(pair)) ;

          for(std::set<Notifiable*>::iterator updater = updaters.begin() ;
              updater != updaters.end() ;
              ++updater)
          {
            (*updater)->addDependency(new_relation) ;
          }
        }
        else
        {
          // remove a link
          Relation::destroyLink(relation,pair.getObjectFrom(),pair.getObjectTo()) ;

          //  (no need to change updaters destruction will take care of it) ?
        }
      }
    }

    void Formula::addChildFormulaTrue(Object* object)
    {
      short true_child = object->getNumberOfTrueChildFormulae(this) ;

      object->setNumberOfTrueChildFormulae(this,true_child+1) ;
      onAddChildFormulaTrue(object) ;
    }

    void Formula::addChildFormulaFalse(Object* object)
    {
      object->setNumberOfTrueChildFormulae(
        this,object->getNumberOfTrueChildFormulae(this)-1) ;

      onAddChildFormulaFalse(object) ;
    }

    void ParentshipFormula::addChildFormulaTrue(Object* object)
    {
      onAddChildFormulaTrue(object) ;
    }

    void ParentshipFormula::addChildFormulaFalse(Object* object)
    {
      onAddChildFormulaFalse(object) ;
    }

    void Formula::addChildFormulaTrue(const ObjectPair& pair)
    {
      short true_child = pair.getNumberOfTrueChildFormulae(this) ;

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
          (unsigned int)object->getNumberOfTrueChildFormulae(this) == m_children.size())
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
          (unsigned int)pair.getNumberOfTrueChildFormulae(this) == m_children.size())
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

        std::set<Notifiable*> deduced_traits(getDependentNotifiables(object)) ;
        std::set<Notifiable*> new_updaters(getUpdaterNotifiables(object)) ;

        for(std::set<Notifiable*>::const_iterator deduced_trait = deduced_traits.begin() ; deduced_trait != deduced_traits.end() ; ++deduced_trait)
        {
          for(std::set<Notifiable*>::const_iterator updater = new_updaters.begin() ; updater != new_updaters.end() ; ++updater)
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
      /// @todo
    }

    void FormulaOr::onAddChildFormulaTrue(const ObjectPair& pair)
    {
      if (! isValid(pair))
      {
        becomeTrue(pair) ;
      }
      else
      {
        update(pair) ;

        std::set<Notifiable*> deduced_traits(getDependentNotifiables(pair)) ;

        std::set<Notifiable*> new_updaters(getUpdaterNotifiables(pair)) ;

        for(std::set<Notifiable*>::const_iterator deduced_trait = deduced_traits.begin() ; deduced_trait != deduced_traits.end() ; ++deduced_trait)
        {
          for(std::set<Notifiable*>::const_iterator updater = new_updaters.begin() ; updater != new_updaters.end() ; ++updater)
          {
            (*updater)->addDependency(*deduced_trait) ;
          }
        }
      }
    }

    void FormulaOr::onAddChildFormulaFalse(const ObjectPair& pair)
    {
      if (isValid(pair) &&
          pair.getNumberOfTrueChildFormulae(this) == 0)
      {
        becomeFalse(pair) ;
      }
      else
      {
        // @todo maintain dependencies...
        update(pair) ;
      }
    }

    void TraitFormula::onAddChildFormulaTrue(Object*)
    {
      ErrorMessage("TraitFormula::onAddChildFormulaTrue") ;
    }

    void TraitFormula::onAddChildFormulaFalse(Object*)
    {
      ErrorMessage("TraitFormula::onAddChildFormulaFalse") ;
    }

    void HasParentFormula::onAddChildFormulaTrue(Object* object)
    {
      addParent(object,object,true) ;
    }

    void HasParentFormula::onAddChildFormulaFalse(Object* object)
    {
      removeParent(object,object,true) ;
    }

    void HasAncestorFormula::onAddChildFormulaTrue(Object* object)
    {
      for(std::set<Object*>::iterator child = object->getChildren().begin() ; child != object->getChildren().end() ; ++child)
      {
        addAncestor(*child,object,true) ;
      }
    }

    void HasAncestorFormula::onAddChildFormulaFalse(Object* object)
    {
      for(std::set<Object*>::iterator child = object->getChildren().begin() ; child != object->getChildren().end() ; ++child)
      {
        removeAncestor(*child,object,true) ;
      }
    }

    void HasChildFormula::onAddChildFormulaTrue(Object* object)
    {
      addedChild(object,object,true) ;
    }

    void HasChildFormula::onAddChildFormulaFalse(Object* object)
    {
      removedChild(object,object,true) ;
    }

    void TraitFormula::onChildFormulaUpdated(Object*)
    {
      ErrorMessage("TraitFormula::onChildFormulaUpdated") ;
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
      // if the object has the formula we should stop going down
      if (! getChildFormula()->isValid(object))
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
      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        updateDescendentObject(*child) ;
      }
    }

    void HasChildFormula::onChildFormulaUpdated(Object* object)
    {
      update(object) ;

      Object* parent = object->getParent() ;
      if (parent)
      {
        updateSubFormulaOnChild(parent) ;
      }
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
      onAddChildFormulaTrue(object) ;
    }

    void WithRelationFormula::onAddChildFormulaTrue(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        short true_related = (*related)->getNumberOfTrueChildFormulae(this) ;
        (*related)->setNumberOfTrueChildFormulae(this,true_related+1) ;
        onAddTrueRelated(*related,object) ;
      }
    }

    void WithRelationFormula::addChildFormulaFalse(Object* object)
    {
      onAddChildFormulaFalse(object) ;
    }

    void WithRelationFormula::onAddChildFormulaFalse(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        short true_related = (*related)->getNumberOfTrueChildFormulae(this) ;
        (*related)->setNumberOfTrueChildFormulae(this,true_related-1) ;
        onAddFalseRelated(*related,object) ;
      }
    }

    void IsRelatedFormula::onAddTrueRelated(Object* from,Object* new_to)
    {
      if (from->getNumberOfTrueChildFormulae(this) == 1)
        becomeTrue(from) ;
      else
      {
        update(from) ;

        std::set<Notifiable*> dependents = getDependentNotifiables(from) ;
        std::set<Notifiable*> new_updaters = getChildFormula()->getUpdaterNotifiables(new_to) ;
        for(std::set<Notifiable*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          for(std::set<Notifiable*>::iterator new_updater = new_updaters.begin() ; new_updater != new_updaters.end() ; ++new_updater)
          {
            (*new_updater)->addDependency(*dependent) ;
          }
        }

      }
    }

    void IsRelatedFormula::onAddFalseRelated(Object* from,Object* old_to)
    {
      if (from->getNumberOfTrueChildFormulae(this) == 0)
        becomeFalse(from) ;
      else
      {
        update(from) ;

        std::set<Notifiable*> dependents = getDependentNotifiables(from) ;
        std::set<Notifiable*> old_updaters = getChildFormula()->getUpdaterNotifiables(old_to) ;
        for(std::set<Notifiable*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
        {
          for(std::set<Notifiable*>::iterator old_updater = old_updaters.begin() ; old_updater != old_updaters.end() ; ++old_updater)
          {
            (*old_updater)->removeDependency(*dependent) ;
          }
        }

      }
    }

    void WithRelationFormula::onChildFormulaUpdated(Object* object)
    {
      std::set<Object*> objects(object->getModel()->getInverseRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        update(*related) ;
      }
    }

    void IsOnlyRelatedFormula::onAddTrueRelated(Object* from,Object* new_to)
    {
      if ((unsigned int)from->getNumberOfTrueChildFormulae(this) ==
          from->getModel()->getRelations(m_relation,from).size())

      {
        if (!isValid(from))
          becomeTrue(from) ;
        else
        {
          // a new true related...
          update(from) ;

          std::set<Notifiable*> dependents = getDependentNotifiables(from) ;
          std::set<Notifiable*> new_updaters = getChildFormula()->getUpdaterNotifiables(new_to) ;
          for(std::set<Notifiable*>::iterator dependent = dependents.begin() ; dependent != dependents.end() ; ++dependent)
          {
            for(std::set<Notifiable*>::iterator new_updater = new_updaters.begin() ; new_updater != new_updaters.end() ; ++new_updater)
            {
              (*new_updater)->addDependency(*dependent) ;
            }
          }
        }
      }

    }

    void IsOnlyRelatedFormula::onAddFalseRelated(Object* from,Object*)
    {
      if (isValid(from))
        becomeFalse(from) ;
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
            short true_related = relation.getObjectFrom()->getNumberOfTrueChildFormulae(*formula) ;
            relation.getObjectFrom()->setNumberOfTrueChildFormulae(*formula,true_related+1) ;
            (*formula)->onAddTrueRelated(relation.getObjectFrom(),relation.getObjectTo()) ;
          }
          else if ((*formula)->isValid(relation.getObjectFrom()))
          {
            (*formula)->onAddFalseRelated(relation.getObjectFrom(),relation.getObjectTo()) ;
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
            short true_related = relation.getObjectFrom()->getNumberOfTrueChildFormulae(*formula) ;
            relation.getObjectFrom()->setNumberOfTrueChildFormulae(*formula,true_related-1) ;
            (*formula)->onAddFalseRelated(relation.getObjectFrom(),relation.getObjectTo()) ;
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

    std::set<Notifiable*> TraitFormula::getUpdaterNotifiables(const DeductionElement& element) const
    {
      std::set<Notifiable*> result ;

      if (!element.isObject())
        return result ;

      Object* object = element.getObject() ;

      if (!object)
        throw ExceptionKernel("TraitFormula::getUpdaterNotifiables") ;

      Trait* trait = object->getTrait(m_trait) ;
      if (trait)
        result.insert(trait) ;
      return result ;
    }

    std::set<Notifiable*> HasChildFormula::getUpdaterNotifiables(const DeductionElement& element) const
    {
      std::set<Notifiable*> result ;

      if (!element.isObject())
        return result ;

      Object* object = element.getObject() ;

      std::set<Object*> true_children(getChildFormula()->getDirectChildren(object)) ;
      for(std::set<Object*>::iterator true_child = true_children.begin() ; true_child != true_children.end() ; ++true_child)
      {
        std::set<Notifiable*> temp(getChildFormula()->getUpdaterNotifiables(*true_child)) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<Notifiable*> FormulaHasDescendant::getUpdaterNotifiables(const DeductionElement&) const
    {
      // not implemented
      return std::set<Notifiable*>() ;
    }

    std::set<Notifiable*> HasAncestorFormula::getUpdaterNotifiables(const DeductionElement& element) const
    {
      std::set<Notifiable*> result ;

      if (!element.isObject())
        return result ;

      Object* object = element.getObject() ;

      Object* valid_ancestor = getChildFormula()->getValidAncestor(object) ;

      if (!valid_ancestor)
        return result ;

      return getChildFormula()->getUpdaterNotifiables(valid_ancestor) ;
    }


    std::set<Notifiable*> HasParentFormula::getUpdaterNotifiables(const DeductionElement& element) const
    {
      std::set<Notifiable*> result ;

      if (!element.isObject())
        return result ;

      Object* object = element.getObject() ;

      Object* valid_parent = getChildFormula()->getValidParent(object) ;

      if (!valid_parent)
        return result ;

      return getChildFormula()->getUpdaterNotifiables(valid_parent) ;
    }

    std::set<Notifiable*> FormulaAnd::getUpdaterNotifiables(const DeductionElement& object) const
    {
      std::set<Notifiable*> result ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        std::set<Notifiable*> temp((*child)->getUpdaterNotifiables(object)) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<Notifiable*> FormulaOr::getUpdaterNotifiables(const DeductionElement& object) const
    {
      std::set<Notifiable*> result ;
      for(std::set<Formula*>::const_iterator child = m_children.begin() ;
          child != m_children.end() ;
          ++child)
      {
        std::set<Notifiable*> temp((*child)->getUpdaterNotifiables(object)) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }

    std::set<Notifiable*> FormulaNot::getUpdaterNotifiables(const DeductionElement&) const
    {
      // empty on purpose
      return std::set<Notifiable*>() ;
    }

    std::set<Notifiable*> WithRelationFormula::getUpdaterNotifiables(const DeductionElement& element) const
    {
      std::set<Notifiable*> result ;

      if (!element.isObject())
        return result ;

      Object* object = element.getObject() ;

      Formula* formula = *m_children.begin() ;
      Model* model = object->getModel() ;
      std::set<Object*> objects(model->getRelations(m_relation,object)) ;
      for(std::set<Object*>::iterator related = objects.begin() ; related != objects.end() ; ++related)
      {
        if (formula->isValid(*related))
        {
          std::set<Notifiable*> temp(formula->getUpdaterNotifiables(*related)) ;
          result.insert(temp.begin(),temp.end()) ;
        }
      }
      return result ;
    }

    std::set<Notifiable*> IsFromFormula::getUpdaterNotifiables(const DeductionElement& element) const
    {
      std::set<Notifiable*> result ;

      if (element.isObject())
        return result ;

      Formula* formula = *m_children.begin() ;
      return formula->getUpdaterNotifiables(element.getObjectFrom()) ;
    }

    std::set<Notifiable*> IsToFormula::getUpdaterNotifiables(const DeductionElement& element) const
    {
      std::set<Notifiable*> result ;

      if (element.isObject())
        return result ;

      Formula* formula = *m_children.begin() ;
      return formula->getUpdaterNotifiables(element.getObjectTo()) ;
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

    void HasAncestorFormula::updateDescendentObject(Object* object)
    {
      update(object) ;

      // if object has not the formula...
      if (!getChildFormula()->isValid(object))
      {
        for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
            child != object->getChildren().end() ;
            ++child)
        {
          updateDescendentObject(*child) ;
        }
      }
    }

    void HasChildFormula::updateSubFormulaOnChild(Object* object)
    {
      // if object is not valid
      if (!getChildFormula()->isValid(object))
      {
        update(object) ;

        Object* parent = object->getParent() ;
        if (parent)
        {
          updateSubFormulaOnChild(parent) ;
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

    void Formula::onChildFormulaUpdated(const ObjectPair&)
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

    void FormulaNot::onChildFormulaUpdated(Object*)
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
      if (m_updating.find(this) != m_updating.end())
        return ;
      m_updating.insert(this) ;
      lock() ;
      _updated() ;
      DeducedTrait::updateTrait(getObject(),this) ;
      unlock() ;
      m_updating.erase(this) ;
    }

  // @}
  /*!
    @name Global treatments
  */
  // @{

    void DeducedTrait::addTrait(Object* object,Trait* trait)
    {
      TraitFormula::addTrait(object,trait) ;
    }

    void DeducedTrait::updateTrait(Object*,Trait* trait)
    {
      for(std::set<Notifiable*>::iterator dependent = trait->getDependentNotifiables().begin() ; dependent != trait->getDependentNotifiables().end() ; ++dependent)
      {
        (*dependent)->notify() ;
      }

      /*
        valgrind indicates that following functions take the same time on
        basic performance tests (tests without parent formulae)

        problem is that it takes 75% of time without parent/ancestor/child formulae
      */
//      TraitFormula::updateTrait(object,trait) ;
    }

    void DeducedRelation::updateRelation(const Relation& relation)
    {
      std::set<Formula*> formulae(getFormulae(relation.getType())) ;
      for(std::set<Formula*>::const_iterator formula = formulae.begin() ; formula != formulae.end() ; ++formula)
      {
        TypeIdentifier deduced_relation_type(get(*formula)) ;
        if (deduced_relation_type != VoidTypeIdentifier && Relation::_areLinked(deduced_relation_type,relation.getObjectFrom(),relation.getObjectTo()))
        {
          Relation(deduced_relation_type,relation.getObjectFrom(),relation.getObjectTo()).notify() ;
        }
      }
    }

    void DeducedTrait::removeTrait(Object* object,Trait* trait)
    {
      TraitFormula::removeTrait(object,trait) ;
    }

    void DeducedTrait::changeParent(Object* object,Object* old_parent)
    {
      /*
        We only need to deal with formula on parentship.

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
