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

#include <kernel/trait.h>

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
      @param formula any combination of And, Or, Not HasTrait, HasParent,
             HasAncestor, HasChild. see below.
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

    /// Conjunction of formulaes
    /*!
      Example :
        DeclareDeducedTrait(C,And(HasTrait(A),HasTrait(B))) ;
        C is equivalent to A^B
    */
    #define And(...) \
      Kernel::TemplateAnd< __VA_ARGS__ >

    /// Disjunction of formulaes
    #define Or(...) \
      Kernel::TemplateOr< __VA_ARGS__ >

    /// Negation of @c formula.
    #define Not(formula) \
      Kernel::TemplateNot<formula>

    /// Elementary formula true iff object has trait @c trait
    #define HasTrait(trait) \
      Kernel::TemplateHasTrait<trait>

    /// Elementary formula true iff object has parent trait @c trait
    /*!
      @remark if object has @c trait then formula is true, @see
      object::getParent().
    */
    #define HasParent(trait) \
      Kernel::TemplateHasParent<trait>

    /// Elementary formula true iff object has ancestor trait @c trait
    /*!
      @see object::getAncestor().
    */
    #define HasAncestor(trait) \
      Kernel::TemplateHasAncestor<trait>

    /// Elementary formula true iff object has child trait @c trait
    /*!
      @remark if object has @c trait then formula is true, @see
      object::getChildren().
    */
    #define HasChild(trait) \
      Kernel::TemplateHasChild<trait>

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
        - HasAncestor : idem as HasParent
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

      /// Calculate initial value.
      static void evaluateInitial(Object* object) ;

      /// Identify the latest updated trait.
      const TypeIdentifier& getLatestUpdatedTrait() const ;

      /// Abstract class means virtual destructor.
      virtual ~DeducedTrait() ;

      /// Print all the registered deducedtrait.
      static std::string printDeclarations() ;

      /// Gives the traits directly depending on @c trait.
      static const std::set<TypeIdentifier>& getDependentTraitTypes(Trait* trait) ;

      /// Access to formula of the deduced trait.
      Formula* getFormula() const ;

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

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        /// map formula to deduced trait builders for construction.
        std::map<Formula*,DeducedTraitBuilder> m_builders ;

        /// map formula to deduced trait names for destruction.
        std::map<Formula*,TypeIdentifier> m_destructors ;

        /// Caching for getDependentTraits
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


  }
}

#include <kernel/implementation/deduced_trait.cxx>

