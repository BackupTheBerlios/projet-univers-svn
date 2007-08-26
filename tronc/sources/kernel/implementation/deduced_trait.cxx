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
      
      In the furture, equivalent formula should be shared in order to speed up 
      the propagation calculus. Any sharing could be calculated at startup. 
    */
    class Formula 
    {
    public:

      /// Add a child formula.
      virtual void addChild(Formula* i_formula) ;
      
      /// True iff the formula is valid.
      bool isValid(Object* i_object) const ;      
      
      /// Acces to formula identifier.
      int getIdentifier() const ;
      
      /// Calculate initial state.
      static void evaluateInitial(Object* i_object) ;
      
      /// Abstract class means virtual destrutor.
      virtual ~Formula() ;

    protected:

      /// The distance to elementary formula
      int getDepth() const ;
      void setDepth(int i_depth) ;
      
    /*!
      @name Construct.
    */
    // @{

      /// Add a parent formula.
      void addParent(Formula* i_formula) ;
      
      /// Abstract class means protected construtor.
      Formula() ;
      
      void generateIdentifier() ;
      
    // @}
    /*!
      @name Value calculus.
    */
    // @{

      /// Initial value.
      virtual void eval(Object* i_object) = 0 ;
      
      /// Declare that a child formula has became true.
      void addChildTrue(Object* i_object) ;

      /// Declare that a child formula has became false.
      void addChildFalse(Object* i_object) ;

      /// Callback on child changing state.
      virtual void onAddChildTrue(Object* i_object) = 0 ;

      /// Callback on child changing state.
      virtual void onAddChildFalse(Object* i_object) = 0 ;

      /// Tells the parents the formula changed state.      
      void notifyParentTrue(Object* i_object) ;

      /// Tells the parents the formula changed state.      
      void notifyParentFalse(Object* i_object) ;

      /// Make the formula become true.
      void becomeTrue(Object* i_object) ;

      /// Make the formula become false.
      void becomeFalse(Object* i_object) ;

    // @}
    /*!
      @name Updates.
    */
    // @{
      
      /// The formula has been modified.
      void update(Object* i_object) ;

      virtual void onChildUpdated(Object* i_object) = 0 ;
      
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
      
      /// next identifier to assign.
      static int m_next_identifier ;    

      /// Distance to elementary formula. 
      int        m_depth ;
      
      /// Formulas sorted by depth. 
      static std::map<int,std::set<Formula*> > m_stratification ;
      
      /// maximum formula depth.
      static int m_maximum_depth ;
      
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
      static TraitFormula* build(const TypeIdentifier& i_trait_name) ;
    
      // Notify that @c i_object has gained @c i_trait_name.
      static void addTrait(Object* i_object,const TypeIdentifier& i_trait_name) ;
      
      // Notify that @c i_object has lost @c i_trait_name.
      static void removeTrait(Object* i_object,const TypeIdentifier& i_trait_name) ;
      
      // Notify that @c i_trait_name has been updated for @c i_object.
      static void updateTrait(Object* i_object,const TypeIdentifier& i_trait_name) ;
      
    protected:

      /// Initial value.
      virtual void eval(Object* i_object) ;
      
      virtual void onAddChildTrue(Object* i_object) ;
      virtual void onAddChildFalse(Object* i_object) ;
      virtual void onChildUpdated(Object* i_object) ;

    private:
        
      /// A trait is an atomic formula
      TraitFormula(const TypeIdentifier& i_trait_name) ;
      
      /// Find the traitformula associaited with @c i_trait_name.
      /*!
        Return NULL if not found.
      */
      static TraitFormula* get(const TypeIdentifier& i_trait_name) ;
    
      static std::map<TypeIdentifier,TraitFormula*> m_traits_formulae ;
    };
    
    /// Conjunction of its child formulae.
    /*
    */
    class FormulaAnd : public Formula
    {
    public:
    
      /// Constructs.
      FormulaAnd() ;
    
      
    private:  

      /// Initial value.
      virtual void eval(Object* i_object) ;

      virtual void onAddChildTrue(Object* i_object) ;
      virtual void onAddChildFalse(Object* i_object) ;
      virtual void onChildUpdated(Object* i_object) ;
      
    };

    /// Disjunction of its child formulae.
    /*
    */
    class FormulaOr : public Formula
    {
    public:
    
      /// Constructs.
      FormulaOr() ;
      
    private:  

      /// Initial value.
      virtual void eval(Object* i_object) ;

      virtual void onAddChildTrue(Object* i_object) ;
      virtual void onAddChildFalse(Object* i_object) ;
      virtual void onChildUpdated(Object* i_object) ;
      
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
      virtual void addChild(Formula* i_formula) ;
      
    private:  

      /// Initial value.
      virtual void eval(Object* i_object) ;

      virtual void onAddChildTrue(Object* i_object) ;
      virtual void onAddChildFalse(Object* i_object) ;
      virtual void onChildUpdated(Object* i_object) ;
      
    };

    /// Function type that build a deduced trait.
    typedef boost::function0<DeducedTrait*> DeducedTraitBuilder ;

    /// Abstract class for traits that are deduced.
    /*!
      Each object :
      - has a deduced trait when its associated formula is true
      - does not have it when formula is false 

      As a trait : 
      - onInit, onClose are treated as usual (in that particular case they are 
      also callbacks for validity change of the formula)
      - onChangeParent is treated as usual
      - onUpdate is framed depending on formula type :
        - Not formula : never 
        - And formula : whenever a child update event occurs 
        - Or formula : whenever a true child update event occurs or a new 
          true child appear
    */
    class DeducedTrait : public Trait
    {
    public:

      /// Register @c i_builder as the builder of @c i_formula.
      static void registerTrait(Formula*            i_formula,
                                DeducedTraitBuilder i_builder,
                                const TypeIdentifier&  i_trait_name) ;
      
      /// Calculate initial value.
      /*!
        @todo calculate the object vector once for all...
      */
      static void evaluateInitial(Object* i_object) ;

      /// Abstract class means virtual destructor.
      virtual ~DeducedTrait() ;

    protected: 
    
      /// Abstract class means protected constructor.
      DeducedTrait() ;
      
      /// Notify that @c i_formula has gained @c i_validity on @c i_object
      static void notify(Formula* i_formula,
                         bool i_validity,
                         Object* i_object) ;
      
      /// Notify that @c i_formula is updated on @c i_object
      static void update(Formula* i_formula,
                         Object* i_object) ;

      /// map formula to deduced trait builders for construction.
      static std::map<Formula*,DeducedTraitBuilder> m_builders ;

      /// map formula to deduced trait names for destruction.
      static std::map<Formula*,TypeIdentifier> m_destructors ;
      
      friend class Formula ;
      
    }; 

    /// A deduced trait declaration.    
    class DeducedTraitDeclaration
    {
    public:

      DeducedTraitDeclaration(Formula*            i_formula,
                              DeducedTraitBuilder i_builder,
                              const TypeIdentifier&  i_trait_name)
      {
        DeducedTrait::registerTrait(i_formula,i_builder,i_trait_name) ;
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
