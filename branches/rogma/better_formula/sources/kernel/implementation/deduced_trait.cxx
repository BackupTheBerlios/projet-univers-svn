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
namespace ProjetUnivers
{
  namespace Kernel
  {

    class Object ;

    /// Formula over traits.
    /*!
      Formula are stored statically and destroyed at the end of the program.

      Complex formula have identifier, while elementary formula (for now
      TraitFormula) have no need to have an internal identifier.

      Globally speaking : validity value for each formula are stored in the
      objects (because we expect to have a variable number of objects with a
      constant number of formula). Elementary changes are propagated in a
      network, possibly changing the evaluation of complex formulas.

      For example in a state where an object satisfy "A^B^C" :
      removing C, will leave formula "A^B^C" with only 2 true children thus
      it is no longer valid and propagate it new false-ness to formulas using
      it.

      In the future, equivalent formula should be shared in order to speed up
      the propagation calculus. Any sharing could be calculated at startup.
    */
    class Formula
    {
    public:

      /// Add a child formula.
      virtual void addChild(Formula* formula) ;

      /// True iff the formula is valid.
      virtual bool isValid(Object* object) const ;

      /// True iff the formula is valid.
      virtual bool isValid(const ObjectPair& relation) const ;

      /// Acces to formula identifier.
      int getIdentifier() const ;

      /// Calculate initial state.
      static void evaluateInitial(Object* object) ;
      /// Calculate initial state.
      virtual void evaluateInitial(const ObjectPair& relation) ;

      /// Abstract class means virtual destructor.
      virtual ~Formula() ;

      /// Print the formula.
      std::string print() const ;

      /// Gives the traits types directly depending on formula.
      /*!
        This trait types are those that use this formula for their calculation
      */
      std::set<TypeIdentifier> getDependentTraitTypes() const ;

      /// Access to the traits that trigger update for this formula.
      /*!
        These are all the traits instance whose presence makes the formula true.

        Calculated by browsing the formula down.
      */
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const = 0 ;

      /// Gives the @c objects' traits directly depending on formula.
      /*!
        These are the traits instances that should be updated when the formula
        is updated.

        Calculated by browsing the formula up.
      */
      std::set<Trait*> getDependentTraits(Object* object) const ;

    protected:


      /// Print the formula.
      virtual std::string internalPrint() const = 0 ;

      /// The distance to elementary formula
      /*!
        We need a lattice, the depth acts as a stratification.
      */
      int getDepth() const ;
      void setDepth(int i_depth) ;

    /*!
      @name Construct.
    */
    // @{

      /// Add a parent formula.
      void addParent(Formula* formula) ;

      /// Abstract class means protected constructor.
      Formula() ;

      /// Generate a unique identifier
      void generateIdentifier() ;

    // @}
    /*!
      @name Value calculus.
    */
    // @{

      /// Initial value.
      virtual void eval(Object* object) = 0 ;
      /// Initial value.
      virtual void eval(const ObjectPair& relation) ;

      /// Declare that a child formula has became true.
      virtual void addChildFormulaTrue(Object* object) ;

      /// Declare that a child formula has became false.
      virtual void addChildFormulaFalse(Object* object) ;

      /// Callback on child changing state.
      virtual void onAddChildFormulaTrue(Object* object) = 0 ;

      /// Callback on child changing state.
      virtual void onAddChildFormulaFalse(Object* object) = 0 ;

      /// Declare that a child formula has became true.
      virtual void addChildFormulaTrue(const ObjectPair& pair) ;

      /// Declare that a child formula has became false.
      virtual void addChildFormulaFalse(const ObjectPair& pair) ;

      /// Callback on child changing state.
      virtual void onAddChildFormulaTrue(const ObjectPair& pair) ;

      /// Callback on child changing state.
      virtual void onAddChildFormulaFalse(const ObjectPair& pair) ;

      /// Tells the parents formula the formula changed state.
      /*!
        Used for continuous evaluation
      */
      void notifyParentTrue(Object* object) ;

      /// Tells the parents the formula changed state.
      /*!
        Used for continuous evaluation
      */
      void notifyParentFalse(Object* object) ;

      /// Make the formula become true.
      void becomeTrue(Object* object) ;

      /// Make the formula become false.
      void becomeFalse(Object* object) ;

      /// Tells the parents formula the formula changed state.
      /*!
        Used for continuous evaluation
      */
      void notifyParentTrue(const ObjectPair& pair) ;

      /// Tells the parents the formula changed state.
      /*!
        Used for continuous evaluation
      */
      void notifyParentFalse(const ObjectPair& pair) ;

      /// Make the formula become true.
      void becomeTrue(const ObjectPair& pair) ;

      /// Make the formula become false.
      void becomeFalse(const ObjectPair& pair) ;

    // @}
    /*!
      @name Updates.
    */
    // @{

      /// Notify propagation
      /*!
        @pre the formula is true for object

      */
      void update(Object* object) ;

      /// A child formula has been updated.
      virtual void onChildFormulaUpdated(Object* object) = 0 ;

      /// Notify propagation
      void update(const ObjectPair& pair) ;

      /// A child formula has been updated.
      virtual void onChildFormulaUpdated(const ObjectPair& pair) ;

    // @}
    /*!
      @name Attributes.
    */
    // @{

      /// empty for top-most formulas.
      std::set<Formula*>  m_parents ;

      /// inverse of m_parents.
      std::set<Formula*>  m_children ;

      /// Formula identifier.
      int        m_identifier ;

      /// Distance to elementary formula.
      int        m_depth ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        /// next identifier to assign.
        int m_next_identifier ;

        /// Formulas sorted by depth.
        std::map<int,std::set<Formula*> > m_stratification ;

        /// maximum formula depth.
        int m_maximum_depth ;

        /// All formulaes.
        std::set<Formula*> m_formulae ;

      private:

        StaticStorage()
        : m_next_identifier(0),
          m_maximum_depth(0)
        {}

        ~StaticStorage()
        {
          for(std::set<Formula*>::iterator formula = m_formulae.begin() ;
              formula != m_formulae.end() ;
              ++formula)
          {
            delete *formula ;
          }
        }
      };

    // @}

      /// Get the total number of formulas.
      static unsigned int getNumberOfFormulae() ;

      friend class Object ;
      friend class Model ;
      friend class DeducedRelation ;
    };

    /// An atomic formula representing the fact "object has trait T".
    class TraitFormula : public Formula
    {
    public:

      /// Special constructor.
      /*!
        Two calls with the same parameter returns the same formula.
      */
      static TraitFormula* build(const TypeIdentifier& trait_name) ;

      /// Notify that @c object has gained @c trait.
      static void addTrait(Object* object,Trait* trait) ;

      /// Notify that @c object has lost @c trait.
      static void removeTrait(Object* object,Trait* trait) ;

      /// Notify that @c trait has been updated for @c object.
      static void updateTrait(Object* object,Trait* trait) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// True iff the formula is valid.
      virtual bool isValid(Object* object) const ;

      /// Gives the traits directly depending on @c trait.
      static std::set<TypeIdentifier> getDependentTraitTypes(Trait* trait) ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;

    private:

      /// A trait is an atomic formula
      TraitFormula(const TypeIdentifier& trait_name) ;

      TypeIdentifier m_trait ;

      /// Find the trait formula associated with @c trait_name.
      /*!
        @return NULL if not found.
      */
      static TraitFormula* get(const TypeIdentifier& trait_name) ;

      /// Find the formulae impacted by trait
      static const std::set<TraitFormula*>& find(Trait* i_trait) ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        std::map<TypeIdentifier,TraitFormula*> m_traits_formulae ;

        /// Caching for find.
        std::map<TypeIdentifier,std::set<TraitFormula*> > m_impacted_formulae ;

      private:

        StaticStorage()
        {}
      };

      friend class Trait ;
    };

    /// Conjunction of its child formulae.
    class FormulaAnd : public Formula
    {
    public:

      /// Constructs.
      FormulaAnd() ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

    private:

      /// Initial value.
      virtual void eval(Object* object) ;
      /// Initial value.
      virtual void eval(const ObjectPair& relation) ;

      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;
      virtual void onAddChildFormulaTrue(const ObjectPair& pair) ;
      virtual void onAddChildFormulaFalse(const ObjectPair& pair) ;
      /// A child formula has been updated.
      virtual void onChildFormulaUpdated(const ObjectPair& pair) ;

    };

    /// Disjunction of its child formulae.
    class FormulaOr : public Formula
    {
    public:

      /// Constructs.
      FormulaOr() ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

    private:

      /// Initial value.
      virtual void eval(Object* object) ;
      /// Initial value.
      virtual void eval(const ObjectPair& relation) ;

      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;
      virtual void onAddChildFormulaTrue(const ObjectPair& pair) ;
      virtual void onAddChildFormulaFalse(const ObjectPair& pair) ;
      /// A child formula has been updated.
      virtual void onChildFormulaUpdated(const ObjectPair& pair) ;

    };

    /// Negation of its child formula.
    /*!
      Should only have one child.
    */
    class FormulaNot : public Formula
    {
    public:

      /// Constructs.
      FormulaNot() ;

      /// Add a child formula.
      virtual void addChild(Formula* formula) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

    private:

      /// Initial value.
      virtual void eval(Object* object) ;
      /// Initial value.
      virtual void eval(const ObjectPair& relation) ;

      virtual void onAddChildFormulaTrue(Object*  object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object*  object) ;
      virtual void onAddChildFormulaTrue(const ObjectPair& pair) ;
      virtual void onAddChildFormulaFalse(const ObjectPair& pair) ;

    };

    /// True iff child formula is true on a descendant.
    /*!
      Not implemented : it is equivalent to HasChild(F)^~F
    */
    class FormulaHasDescendant : public Formula
    {
    public:

      /// Constructs.
      FormulaHasDescendant() ;

      /// Add a child formula.
      virtual void addChild(Formula* formula) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

    private:

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildFormulaTrue(Object*  object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object*  object) ;
    };

    /// True iff child formula is true on an ancestor.
    class HasAncestorFormula : public Formula
    {
    public:

      /// Special constructor.
      /*!
        Two calls with the same parameter returns the same formula.
      */
      static HasAncestorFormula* build(const TypeIdentifier& trait_name) ;

      /// Notify that @c object has gained @c trait.
      static void addTrait(Object* object,Trait* trait) ;

      /// Notify that @c object has lost @c trai.
      static void removeTrait(Object* object,Trait* trait) ;

      /// Notify that @c trait has been updated for @c object.
      static void updateTrait(Object* object,Trait* trait) ;

      /// Notify that @c object has changed parent.
      static void changeParent(Object* object,Object* old_parent) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// Gives the traits directly depending on @c trait.
      static std::set<TypeIdentifier> getDependentTraitTypes(Trait* trait) ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;

      /// Declare that the trait has been added to an @c object's parent.
      void addedAncestor(Object* object) ;

      /// Declare that the trait has been removed to an @c object's parent.
      void removedAncestor(Object* object) ;

      /// Parent trait has been updated.
      void updateAncestorTrait(Object* object) ;

      /// Notify that @c object has changed parent.
      void onChangedParent(Object* object,Object* old_parent) ;

    private:

      /// Constructor
      HasAncestorFormula(const TypeIdentifier& trait_name) ;

      TypeIdentifier m_trait ;

      /// Find the parent trait formula associated with @c trait_name.
      /*!
        @return NULL if not found.
      */
      static HasAncestorFormula* get(const TypeIdentifier& trait_name) ;

      /// Find the formulae impacted by trait
      static const std::set<HasAncestorFormula*>& find(Trait* i_trait) ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        std::map<TypeIdentifier,HasAncestorFormula*> m_ancestor_traits_formulae ;

        /// Caching for find.
        std::map<TypeIdentifier,std::set<HasAncestorFormula*> > m_impacted_formulae ;

      private:

        StaticStorage()
        {}
      };
    };

    /// True iff child formula is true on a parent or @c this.
    class HasParentFormula : public Formula
    {
    public:

      /// Special constructor.
      /*!
        Two calls with the same parameter returns the same formula.
      */
      static HasParentFormula* build(const TypeIdentifier& trait_name) ;

      /// Notify that @c object has gained @c trait.
      static void addTrait(Object* object,Trait* trait) ;

      /// Notify that @c object has lost @c trai.
      static void removeTrait(Object* object,Trait* trait) ;

      /// Notify that @c trait has been updated for @c object.
      static void updateTrait(Object* object,Trait* trait) ;

      /// Notify that @c object has changed parent.
      static void changeParent(Object* object,Object* old_parent) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// Gives the traits directly depending on @c trait.
      static std::set<TypeIdentifier> getDependentTraitTypes(Trait* trait) ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

      /// Find the parent trait formula associated with @c trait_name.
      /*!
        @return NULL if not found.
      */
      static HasParentFormula* get(const TypeIdentifier& trait_name) ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;

      /// Declare that @c trait has been added to an @c object's parent.
      /*!
       * @param object
       * @param trait of type m_trait
       */
      void addParent(Object* object,Trait* trait) ;

      /// Declare that the trait has been removed to an @c object's parent.
      void removedParent(Object* object,Trait* trait) ;

      /// Parent trait has been updated.
      void updateParentTrait(Object* object) ;

      /// Notify that @c object has changed parent.
      void onChangedParent(Object* object,Object* old_parent) ;

    private:

      /// Constructor
      HasParentFormula(const TypeIdentifier& trait_name) ;

      TypeIdentifier m_trait ;


      /// Find the formulae impacted by trait
      static const std::set<HasParentFormula*>& find(Trait* i_trait) ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        std::map<TypeIdentifier,HasParentFormula*> m_parent_traits_formulae ;

        /// Caching for find.
        std::map<TypeIdentifier,std::set<HasParentFormula*> > m_impacted_formulae ;

      private:

        StaticStorage()
        {}
      };
    };

    /// True iff child formula is true on a child or @c this.
    class HasChildFormula : public Formula
    {
    public:

      /// Special constructor.
      /*!
        Two calls with the same parameter returns the same formula.
      */
      static HasChildFormula* build(const TypeIdentifier& trait_name) ;

      /// Notify that @c object has gained @c trait.
      static void addTrait(Object* object,Trait* trait) ;

      /// Notify that @c object has lost @c trait.
      static void removeTrait(Object* object,Trait* trait) ;

      /// Notify that @c trait has been updated for @c object.
      static void updateTrait(Object* object,Trait* trait) ;

      /// Notify that @c object has changed parent.
      static void changeParent(Object* object,Object* old_parent) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

      /// Gives the traits directly depending on @c trait.
      static std::set<TypeIdentifier> getDependentTraitTypes(Trait* trait) ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;

      /// Declare that the trait has been added to an @c object's child.
      void addedChild(Object* object) ;

      /// Declare that the trait has been removed to an @c object's child.
      void removedChild(Object* object) ;

      /// Declare that the trait has been added to number of @c object's children.
      void addedChildren(Object* object,unsigned short number_of_children) ;

      /// Declare that the trait has been removed to number @c object's children.
      void removedChildren(Object* object,unsigned short number_of_children) ;

      /// Child trait has been updated.
      void updateChildTrait(Object* object) ;

      /// Notify that @c object has changed parent.
      void onChangedParent(Object* object,Object* old_parent) ;

    private:

      /// Constructor
      HasChildFormula(const TypeIdentifier& trait_name) ;

      TypeIdentifier m_trait ;

      /// Find the parent trait formula associated with @c trait_name.
      /*!
        @return NULL if not found.
      */
      static HasChildFormula* get(const TypeIdentifier& trait_name) ;

      /// Find the formulae impacted by trait
      static const std::set<HasChildFormula*>& find(Trait* i_trait) ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        std::map<TypeIdentifier,HasChildFormula*> m_child_traits_formulae ;

        /// Caching for find.
        std::map<TypeIdentifier,std::set<HasChildFormula*> > m_impacted_formulae ;

      private:

        StaticStorage()
        {}
      };
    };

    /// Common part for object formula involving relations
    class WithRelationFormula : public Formula
    {
    public:

      /// Called when a relation has been added.
      static void onAddRelation(const Relation&) ;

      /// Called when a relation has been removed.
      static void onRemoveRelation(const Relation&) ;

    protected:

      WithRelationFormula(const TypeIdentifier& relation) ;

      /// Access to the traits that trigger update for this formula.
      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

      /// Declare that a child formula has became true.
      virtual void addChildFormulaTrue(Object* object) ;

      /// Declare that a child formula has became false.
      virtual void addChildFormulaFalse(Object* object) ;

      TypeIdentifier m_relation ;

      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        /// All the formulae sorted by relation type.
        std::map<TypeIdentifier,std::set<WithRelationFormula*> > m_formulae ;

      private:

        StaticStorage()
        {}
      };

    };

    /// True iff child-formula is true on a related object.
    class IsRelatedFormula : public WithRelationFormula
    {
    public:

      /// Constructor
      IsRelatedFormula(const TypeIdentifier& relation) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;

      /// Continuous evaluation
      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;

    private:

    };

    /// True iff child-formula is true on all related object.
    class IsOnlyRelatedFormula : public WithRelationFormula
    {
    public:

      /// Constructor
      IsOnlyRelatedFormula(const TypeIdentifier& relation) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;

      /// Continuous evaluation
      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;
    };


    /// Common part for all formulae on relation
    class FormulaOnRelation : public Formula
    {
    public:

      /// Called when a relation has been added.
      static void onAddRelation(const Relation&) ;

      /// Called when a relation has been removed.
      static void onRemoveRelation(const Relation&) ;

    protected:

      FormulaOnRelation() ;

    };

    /// True iff link goes from an object satisfying the child formula.
    class IsFromFormula : public FormulaOnRelation
    {
    public:

      IsFromFormula() ;

      /// Initial value.
      virtual void eval(Object* object) ;
      /// Initial value.
      virtual void eval(const ObjectPair& relation) ;
      /// Calculate initial state.
      virtual void evaluateInitial(const ObjectPair& relation) ;

      /// Continuous evaluation
      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;

      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

      /// Print the formula.
      virtual std::string internalPrint() const ;
    };

    /// True iff link goes to an object satisfying the child formula.
    class IsToFormula : public FormulaOnRelation
    {
    public:

      IsToFormula() ;

      /// Initial value.
      virtual void eval(Object* object) ;
      /// Initial value.
      virtual void eval(const ObjectPair& relation) ;
      /// Calculate initial state.
      virtual void evaluateInitial(const ObjectPair& relation) ;

      /// Continuous evaluation
      virtual void onAddChildFormulaTrue(Object* object) ;
      virtual void onAddChildFormulaFalse(Object* object) ;
      virtual void onChildFormulaUpdated(Object* object) ;

      virtual std::set<Trait*> getUpdaterTraits(Object* object) const ;

      /// Print the formula.
      virtual std::string internalPrint() const ;
    };


  // @}
  /*!
    @name Declarations.
  */
  // @{


    /// A deduced trait declaration.
    class DeducedTraitDeclaration
    {
    public:

      DeducedTraitDeclaration(Formula*              formula,
                              DeducedTraitBuilder   builder,
                              const TypeIdentifier& trait_name)
      {
        DeducedTrait::registerTrait(formula,builder,trait_name) ;
      }
    };

    /// A deduced relation declaration.
    class DeducedRelationDeclaration
    {
    public:

      DeducedRelationDeclaration(Formula*              formula,
                                 const TypeIdentifier& relation,
                                 const TypeIdentifier& primitive_relation)
      {
        DeducedRelation::registerRelation(relation,primitive_relation,formula) ;
      }
    };

    /// Elementary formula static declaration.
    template <class T> class TemplateHasTrait
    {
    public:

      static Formula* build()
      {
        return TraitFormula::build(getClassTypeIdentifier(T)) ;
      }
    };

    /// Elementary formula static declaration.
    template <class T> class TemplateHasParent
    {
    public:

      static Formula* build()
      {
        return HasParentFormula::build(getClassTypeIdentifier(T)) ;
      }
    };

    /// Elementary formula static declaration.
    template <class T> class TemplateHasAncestor
    {
    public:

      static Formula* build()
      {
        return HasAncestorFormula::build(getClassTypeIdentifier(T)) ;
      }
    };

    /// Elementary formula static declaration.
    template <class T> class TemplateHasChild
    {
    public:

      static Formula* build()
      {
        return HasChildFormula::build(getClassTypeIdentifier(T)) ;
      }
    };


    /// The default value for templates TemplateAnd TemplateOr
    class EmptyFormula
    {
    public:

      static Formula* build()
      {
        return NULL ;
      }
    };

    /// And formula static declaration.
    template <class F1 = EmptyFormula,
              class F2 = EmptyFormula,
              class F3 = EmptyFormula,
              class F4 = EmptyFormula,
              class F5 = EmptyFormula,
              class F6 = EmptyFormula,
              class F7 = EmptyFormula,
              class F8 = EmptyFormula,
              class F9 = EmptyFormula,
              class F10 = EmptyFormula>
    class TemplateAnd
    {
    public:

      static Formula* build()
      {
        Formula* result = new FormulaAnd() ;

        Formula* formula1 = F1::build() ;
        if (formula1)
        {
          result->addChild(formula1) ;
        }

        Formula* formula2 = F2::build() ;
        if (formula2)
        {
          result->addChild(formula2) ;
        }

        Formula* formula3 = F3::build() ;
        if (formula3)
        {
          result->addChild(formula3) ;
        }

        Formula* formula4 = F4::build() ;
        if (formula4)
        {
          result->addChild(formula4) ;
        }

        Formula* formula5 = F5::build() ;
        if (formula5)
        {
          result->addChild(formula5) ;
        }

        Formula* formula6 = F6::build() ;
        if (formula6)
        {
          result->addChild(formula6) ;
        }

        Formula* formula7 = F7::build() ;
        if (formula7)
        {
          result->addChild(formula7) ;
        }

        Formula* formula8 = F8::build() ;
        if (formula8)
        {
          result->addChild(formula8) ;
        }

        Formula* formula9 = F9::build() ;
        if (formula9)
        {
          result->addChild(formula9) ;
        }

        Formula* formula10 = F10::build() ;
        if (formula10)
        {
          result->addChild(formula10) ;
        }


        return result ;
      }

    };

    /// Or formula static declaration.
    template <class F1 = EmptyFormula,
              class F2 = EmptyFormula,
              class F3 = EmptyFormula,
              class F4 = EmptyFormula,
              class F5 = EmptyFormula,
              class F6 = EmptyFormula,
              class F7 = EmptyFormula,
              class F8 = EmptyFormula,
              class F9 = EmptyFormula,
              class F10 = EmptyFormula>
    class TemplateOr
    {
    public:

      static Formula* build()
      {
        Formula* result = new FormulaOr() ;

        Formula* formula1 = F1::build() ;
        if (formula1)
        {
          result->addChild(formula1) ;
        }

        Formula* formula2 = F2::build() ;
        if (formula2)
        {
          result->addChild(formula2) ;
        }

        Formula* formula3 = F3::build() ;
        if (formula3)
        {
          result->addChild(formula3) ;
        }

        Formula* formula4 = F4::build() ;
        if (formula4)
        {
          result->addChild(formula4) ;
        }

        Formula* formula5 = F5::build() ;
        if (formula5)
        {
          result->addChild(formula5) ;
        }

        Formula* formula6 = F6::build() ;
        if (formula6)
        {
          result->addChild(formula6) ;
        }

        Formula* formula7 = F7::build() ;
        if (formula7)
        {
          result->addChild(formula7) ;
        }

        Formula* formula8 = F8::build() ;
        if (formula8)
        {
          result->addChild(formula8) ;
        }

        Formula* formula9 = F9::build() ;
        if (formula9)
        {
          result->addChild(formula9) ;
        }

        Formula* formula10 = F10::build() ;
        if (formula10)
        {
          result->addChild(formula10) ;
        }


        return result ;
      }

    };

    /// Not formula static declaration.
    template <class F>
    class TemplateNot
    {
    public:

      static Formula* build()
      {
        Formula* result = new FormulaNot() ;
        result->addChild(F::build()) ;
        return result ;
      }
    };

    /// IsRelated static declaration
    template <class _Relation,class _Formula>
    class TemplateIsRelated
    {
    public:

      static Formula* build()
      {
        Formula* result = new IsRelatedFormula(getClassTypeIdentifier(_Relation)) ;
        result->addChild(_Formula::build()) ;
        return result ;
      }
    };

    /// IsOnlyRelated static declaration
    template <class _Relation,class _Formula>
    class TemplateIsOnlyRelated
    {
    public:

      static Formula* build()
      {
        Formula* result = new IsOnlyRelatedFormula(getClassTypeIdentifier(_Relation)) ;
        result->addChild(_Formula::build()) ;
        return result ;
      }
    };

    /// IsFrom static declaration.
    template <class _Formula>
    class TemplateIsFrom
    {
    public:

      static Formula* build()
      {
        Formula* result = new IsFromFormula() ;
        result->addChild(_Formula::build()) ;
        return result ;
      }
    };

    /// IsTo static declaration.
    template <class _Formula>
    class TemplateIsTo
    {
    public:

      static Formula* build()
      {
        Formula* result = new IsToFormula() ;
        result->addChild(_Formula::build()) ;
        return result ;
      }
    };

  }
}
