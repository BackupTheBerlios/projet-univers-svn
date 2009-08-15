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
#pragma once

/*!
  @file deduced_trait.h

*/

#include <vector>
#include <string>
#include <set>
#include <map>

#include <kernel/helper_macros.h>
#include <kernel/meta.h>
#include <kernel/relation.h>

#include <kernel/trait.h>
#include <kernel/notifiable.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    class Formula ;
    class HasParentFormula ;
    class HasAncestorFormula ;
    class FormulaOr ;

    /// Function type that build a deduced trait.
    typedef boost::function0<DeducedTrait*> DeducedTraitBuilder ;


    /// Declare @c trait as a deduced trait defined by @c formula
    /*!
      @param trait the trait class being defined
      @param formula any combination of And, Or, Not, HasTrait, HasParent,
             HasAncestor, HasChild, IsRelated, IsOnlyRelated. see below.
    */
    #define DeclareDeducedTrait(trait,formula)  \
      namespace PU_MAKE_UNIQUE_NAME(local)      \
      {                                         \
        static                                  \
        Kernel::DeducedTrait* builder()         \
        {                                       \
          return new trait() ;                  \
        }                                       \
                                                \
        static                                  \
        Kernel::DeducedTraitDeclaration temp(   \
          formula::build(),                     \
          &builder,                             \
          getClassTypeIdentifier(trait)) ;      \
      }

    /// Declare @c relation as a deduced relation defined by @c relation_formula
    /*!
      @param relation the deduced relation class being defined
      @param primitive_relation the deduced relation is included into another
                                relation
      @param relation_formula any combination of
             And, Or, Not, IsFrom,
             IsTo. see below.
    */
    #define DeclareDeducedRelation(relation,primitive_relation,relation_formula) \
      namespace PU_MAKE_UNIQUE_NAME(local)                     \
      {                                                        \
        static                                                 \
        Kernel::DeducedRelationDeclaration temp(               \
          relation_formula::build(),                           \
          getClassTypeIdentifier(relation),                    \
          getClassTypeIdentifier(primitive_relation)) ;        \
      }


    /// Conjunction of formulae
    /*!
      Example :
        DeclareDeducedTrait(C,And(HasTrait(A),HasTrait(B))) ;
        C is equivalent to A^B
    */
    #define And(...) \
      Kernel::TemplateAnd< __VA_ARGS__ >

    /// Disjunction of formulae
    #define Or(...) \
      Kernel::TemplateOr< __VA_ARGS__ >

    /// Negation of @c formula.
    #define Not(formula) \
      Kernel::TemplateNot< formula >

    /// Elementary formula true iff object has trait @c trait
    #define HasTrait(trait) \
      Kernel::TemplateHasTrait<trait>

    /// True iff object has parent with @c formula
    /*!
      @remark if object satisfy @c formula then HasParent(formula) is true.
      Notably, HasParent(HasTrait(T)), @see object::getParent<T>().
    */
    #define HasParent(formula) \
      Kernel::TemplateHasParent< formula >

    /// Elementary formula true iff object has ancestor with true @c formula
    /*!
      @see object::getAncestor().
    */
    #define HasAncestor(formula) \
      Kernel::TemplateHasAncestor< formula >

    /// Elementary formula true iff object has child trait @c trait
    /*!
      @remark if object has @c trait then formula is true, @see
      object::getChildren().
    */
    #define HasChild(formula) \
      Kernel::TemplateHasChild< formula >

    /// True iff object is related to a @c formula object through @c relation.
    /*!
      This formula is true for an object o iff :
      exist x, relation(o,x) and formula(x)
    */
    #define IsRelated(relation,formula) \
      Kernel::TemplateIsRelated< relation,formula >

    /// True iff object is only related to @c formula objects through @c relation.
    /*!
      This formula is true for an object o iff :
      for all x, relation(o,x) => formula(x)
    */
    #define IsOnlyRelated(relation,formula) \
      Kernel::TemplateIsOnlyRelated< relation,formula >

    /// True iff a relation goes from an object satisfying formula.
    #define IsFrom(formula) \
      Kernel::TemplateIsFrom< formula >

    /// True iff a relation goes to an object satisfying formula.
    #define IsTo(formula) \
      Kernel::TemplateIsTo< formula >

    /// Abstract class for traits that are deduced.
    /*!
      Each object :
      - gain a deduced trait when its associated formula is true
      - loose it when formula is false

      As a trait :
      - onInit, onClose are called as usual (in that particular case they are
        called when formula validity changes)
      - onChangeParent is treated as usual
      - onUpdate is framed depending on formula type :
        - Not formula : never
        - And formula : whenever a child update event occurs
        - Or formula : whenever a true child update event occurs or a new
          true child appear
        - HasParent formula : whenever the return value of getParent<T> changes,
          i.e., the parent that makes the formula true is not the same as before
        - HasAncestor : same as HasParent
        - HasChild :
    */
    class DeducedTrait : public Trait
    {
    public:

      /// Register @c builder as the builder of @c formula.
      /*!
        @param trait_name is the deduced trait type
      */
      static void registerTrait(Formula*              formula,
                                DeducedTraitBuilder   builder,
                                const TypeIdentifier& trait_name) ;


      /// Called when @c object gained @c trait
      static void addTrait(Object* object,Trait* trait) ;

      /// Object trait has been updated
      static void updateTrait(Object* object,Trait* trait) ;

      /// Called when @c object loosed @c trait
      static void removeTrait(Object* object,Trait* trait) ;

      /// Called when @c object changed parent.
      static void changeParent(Object* object,Object* old_parent) ;

      /// Called when @c relation has been added
      static void addRelation(const Relation& relation) ;

      /// Called when @c relation has been removed
      static void removeRelation(const Relation& relation) ;

      /// Calculate initial value.
      static void evaluateInitial(Object* object) ;

      /// Identify the latest updated trait.
      const TypeIdentifier& getLatestUpdatedTrait() const ;

      /// Abstract class means virtual destructor.
      virtual ~DeducedTrait() ;

      /// Print all the registered deduced traits.
      static std::string printDeclarations() ;

      /// Access to formula of the deduced trait.
      Formula* getFormula() const ;

      /// Access to formula of the deduced trait.
      static Formula* getFormula(const TypeIdentifier&) ;

      /// Return false because the trait is deduced.
      virtual bool isPrimitive() const ;

    protected:

      /// Abstract class means protected constructor.
      DeducedTrait() ;

      Formula* m_formula ;

      /// Tells the views the trait has changed.
      virtual void notify() ;

      /// Notify that @c formula has gained @c validity on @c object
      static void notify(Formula* formula,
                         bool     validity,
                         Object*  object) ;

      /// Notify that @c formula is updated on @c object
      static void update(Formula* formula,
                         Object*  object) ;

      /// Objects that are updating, to avoid loops in weird cases.
      std::set<Notifiable*> m_updating ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        /// map formula to deduced trait builders for construction.
        std::map<Formula*,DeducedTraitBuilder> m_builders ;

        /// map formula to deduced trait names for destruction.
        std::map<Formula*,TypeIdentifier> m_destructors ;

        std::map<TypeIdentifier,Formula*> m_formulae ;

        /// Caching for getDependentNotifiables
        std::map<TypeIdentifier,std::set<TypeIdentifier> > m_dependent_traits ;

      private:

        StaticStorage()
        {}
      };

      friend class Formula ;
      friend class HasParentFormula ;
      friend class HasAncestorFormula ;
      friend class HasChildFormula ;
      friend class Trait ;
      friend class FormulaOr ;

    };

    /// Class for deduced relations
    class DeducedRelation : public Relation
    {
    public:

      /// Register that @c relation is associated with @c formula.
      static void registerRelation(const TypeIdentifier& relation,
                                   const TypeIdentifier& primitive_relation,
                                   Formula*              formula) ;

      /// Relation has been updated
      static void updateRelation(const Relation&) ;


      /// Notify that @c formula has gained @c validity on @c relation
      static void notify(Formula*          formula,
                         bool              validity,
                         const ObjectPair& relation) ;

      /// Notify that @c formula is updated on @c relation
      static void update(Formula*          formula,
                         const ObjectPair& relation) ;

      /// Notify that a relation link has been added
      static void onAddRelation(const Relation&) ;

      /// Notify that a relation link has been removed
      static void onRemoveRelation(const Relation&) ;

    private:

      /// Type identifier associated with the formula
      /*!
        @returns VoidTypeIdentifier if the formula is not associated with a deduced relation
      */
      static TypeIdentifier get(Formula*) ;

      /// Primitive relation associated with a deduced one.
      static TypeIdentifier getPrimitive(const TypeIdentifier&) ;

      /// Get the formulae that applies to @c primitive_relation.
      static std::set<Formula*> getFormulae(const TypeIdentifier& primitive_relation) ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        /// map formula to deduced relation type name.
        std::map<Formula*,TypeIdentifier> m_deduced_relations ;

        /// Map primitive relation to formulae
        std::multimap<TypeIdentifier,Formula*> m_primitive_relation_to_formulae ;

        /// Associate a deduced relation with its primitive relation
        std::map<TypeIdentifier,TypeIdentifier> m_deduced_to_primitive_relation ;

      private:

        StaticStorage()
        {}
      };

      friend class Formula ;
    };


  }
}

#include <kernel/implementation/deduced_trait.cxx>

