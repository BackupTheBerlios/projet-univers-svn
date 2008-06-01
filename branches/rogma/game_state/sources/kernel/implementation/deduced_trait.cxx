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
namespace ProjetUnivers {
  namespace Kernel {

    class Object ;
    
    /// Formula over traits.
    /*!
      Formula are stored statically and destroyed at the end of the program.
      
      Complex formula have identifier, while elementary formula (for now 
      TraitFormula) have no need to have an internal identifier.
      
      Globbally speaking : validity value for each formula are stored in the 
      objects (because we expect to have a variable number of objects with a 
      constant number of formula). Elementary changes are propagated in a 
      network, possibly changing the evaluation of complex formulas. 
      
      For example in a state where an object statisfy "A^B^C" : 
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
      bool isValid(Object* object) const ;      
      
      /// Acces to formula identifier.
      int getIdentifier() const ;
      
      /// Calculate initial state.
      static void evaluateInitial(Object* object) ;
      
      /// Abstract class means virtual destrutor.
      virtual ~Formula() ;
      
      /// Print the formula.
      std::string print() const ;
      
    protected:
      

      /// Print the formula.
      virtual std::string internalPrint() const = 0 ;
      
      /// The distance to elementary formula
      int getDepth() const ;
      void setDepth(int i_depth) ;
      
    /*!
      @name Construct.
    */
    // @{

      /// Add a parent formula.
      void addParent(Formula* formula) ;
      
      /// Abstract class means protected construtor.
      Formula() ;
      
      void generateIdentifier() ;
      
    // @}
    /*!
      @name Value calculus.
    */
    // @{

      /// Initial value.
      virtual void eval(Object* object) = 0 ;
      
      /// Declare that a child formula has became true.
      void addChildTrue(Object* object) ;

      /// Declare that a child formula has became false.
      void addChildFalse(Object* object) ;

      /// Callback on child changing state.
      virtual void onAddChildTrue(Object* object) = 0 ;

      /// Callback on child changing state.
      virtual void onAddChildFalse(Object* object) = 0 ;

      /// Tells the parents the formula changed state.      
      void notifyParentTrue(Object* object) ;

      /// Tells the parents the formula changed state.      
      void notifyParentFalse(Object* object) ;

      /// Make the formula become true.
      void becomeTrue(Object* object) ;

      /// Make the formula become false.
      void becomeFalse(Object* object) ;

    // @}
    /*!
      @name Updates.
    */
    // @{
      
      /// The formula has been modified.
      void update(Object* object) ;

      virtual void onChildUpdated(Object* object) = 0 ;
      
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
    
      // Notify that @c object has gained @c trait_name.
      static void addTrait(Object* object,const TypeIdentifier& trait_name) ;
      
      // Notify that @c object has lost @c trait_name.
      static void removeTrait(Object* object,const TypeIdentifier& trait_name) ;
      
      // Notify that @c trait_name has been updated for @c object.
      static void updateTrait(Object* object,const TypeIdentifier& trait_name) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;
      
      virtual void onAddChildTrue(Object* object) ;
      virtual void onAddChildFalse(Object* object) ;
      virtual void onChildUpdated(Object* object) ;

    private:
        
      /// A trait is an atomic formula
      TraitFormula(const TypeIdentifier& trait_name) ;
    
      TypeIdentifier m_trait ;
      
      /// Find the trait formula associated with @c trait_name.
      /*!
        @return NULL if not found.
      */
      static TraitFormula* get(const TypeIdentifier& trait_name) ;
      
      class StaticStorage
      {
      public:
        
        /// Access to singleton.
        static StaticStorage* get() ;
      
        std::map<TypeIdentifier,TraitFormula*> m_traits_formulae ;
        
      private:
        
        StaticStorage()
        {}
      };      


    };
    
    /// Conjunction of its child formulae.
    /*
    */
    class FormulaAnd : public Formula
    {
    public:
    
      /// Constructs.
      FormulaAnd() ;
    
      /// Print the formula.
      virtual std::string internalPrint() const ;
      
    private:  

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildTrue(Object* object) ;
      virtual void onAddChildFalse(Object* object) ;
      virtual void onChildUpdated(Object* object) ;
      
    };

    /// Disjunction of its child formulae.
    /*
    */
    class FormulaOr : public Formula
    {
    public:
    
      /// Constructs.
      FormulaOr() ;

      /// Print the formula.
      virtual std::string internalPrint() const ;
      
    private:  

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildTrue(Object* object) ;
      virtual void onAddChildFalse(Object* object) ;
      virtual void onChildUpdated(Object* object) ;
      
    };
    
    /// Negation of its child formula.
    /*
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
      
    private:  

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildTrue(Object*  object) ;
      virtual void onAddChildFalse(Object* object) ;
      virtual void onChildUpdated(Object*  object) ;
      
    };

    /// True iff child formula is true on a descendant.
    class FormulaHasDescendant : public Formula
    {
    public:
    
      /// Constructs.
      FormulaHasDescendant() ;

      /// Add a child formula.
      virtual void addChild(Formula* formula) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;
      
    private:  

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildTrue(Object*  object) ;
      virtual void onAddChildFalse(Object* object) ;
      virtual void onChildUpdated(Object*  object) ;
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
      
      /// Constructs.
      HasAncestorFormula() ;

      /// Add a child formula.
      virtual void addChild(Formula* formula) ;

      /// Print the formula.
      virtual std::string internalPrint() const ;
      
    private:  

      /// Initial value.
      virtual void eval(Object* object) ;

      virtual void onAddChildTrue(Object*  object) ;
      virtual void onAddChildFalse(Object* object) ;
      virtual void onChildUpdated(Object*  object) ;
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

      // Notify that @c object has gained @c trait_name.
      static void addTrait(Object* object,const TypeIdentifier& trait_name) ;
      
      // Notify that @c object has lost @c trait_name.
      static void removeTrait(Object* object,const TypeIdentifier& trait_name) ;
      
      // Notify that @c trait_name has been updated for @c object.
      static void updateTrait(Object* object,const TypeIdentifier& trait_name) ;

      /// Notify that @c object has changed parent.
      static void changeParent(Object* object,Object* old_parent) ;
      
      /// Print the formula.
      virtual std::string internalPrint() const ;

    protected:

      /// Initial value.
      virtual void eval(Object* object) ;
      
      virtual void onAddChildTrue(Object* object) ;
      virtual void onAddChildFalse(Object* object) ;
      virtual void onChildUpdated(Object* object) ;

      /// Declare that the trait has been added to parent's object 
      void addParent(Object* object) ;

      /// Declare that the trait has been removed to parent's object 
      void removedParent(Object* object) ;

      /// Parent trait has been updated.
      void updateParentTrait(Object* object) ;

      /// Notify that @c object has changed parent.
      void onChangedParent(Object* object,Object* old_parent) ;
      
    private:

      /// Constructor 
      HasParentFormula(const TypeIdentifier& trait_name) ;
    
      TypeIdentifier m_trait ;
      
      /// Find the parent trait formula associated with @c trait_name.
      /*!
        @return NULL if not found.
      */
      static HasParentFormula* get(const TypeIdentifier& trait_name) ;
      
      class StaticStorage
      {
      public:
        
        /// Access to singleton.
        static StaticStorage* get() ;
      
        std::map<TypeIdentifier,HasParentFormula*> m_parent_traits_formulae ;
        
      private:
        
        StaticStorage()
        {}
      };      
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
  }
}
