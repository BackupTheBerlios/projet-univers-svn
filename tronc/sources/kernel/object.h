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
#ifndef PU_KERNEL_OBJECT_H_
#define PU_KERNEL_OBJECT_H_

#include <set>
#include <map>
#include <vector>
#include <typeinfo>

#include <kernel/meta.h>
#include <kernel/exception_kernel.h>
#include <kernel/error.h>
#include <kernel/string.h>
#include <kernel/log.h>
#include <kernel/inherits.h>

#include <kernel/trait.h>


namespace ProjetUnivers {
  namespace Kernel {

    class Trait ;
    class Model ;
    class ViewPoint ;
    class ControlerSet ;
    class Formula ;
    class FormulaAnd ;
    class FormulaOr ;
    class TraitFormula ;
    class FormulaNot ;
    
    /// A model object.
    /*!
      An object has traits and eventually sub-objects. When an object is 
      destroyed, his traits and sub objects are also destroyed.
      
      Trait can be added. Only one trait having class T can be added on 
      the same object.
    */
    class Object 
    {
    public:

    /*!
      @name Construction
    */
    //@{

      /// Constructor.
      Object(Model* i_model,const std::string& i_name = "") ;

      /// Destructs the objects and the traits.
      ~Object() ;
    
    //@}
    /*!
      @name Access methods
    */
    //@{
    
      /// Get object's name.
      std::string getName() const ;

      // Access to parent.
      Object* getParent() const ;
      
      /// Get top most ancestor.
      Object* getRoot() const ;

      /// Acces to model.
      Model* getModel() const ;

      /// Access to trait of type T if exists.
      template <class T> T* getTrait() ;

      /// Access to trait's view of type _View if exists.
      /*!
        @remark 
          It may exist several @c _View on that object (mainly because 
          the view may be attached to a base trait whose several subtraits are
          attached to this object) : in that case, it returns one of the view 
          in an unspecified manner. 
          Note that in that case one can obtain exactly the desired view through 
          Trait::getView after choosing the correct trait.     
      */
      template <class _View> _View* getView(ViewPoint* i_viewpoint) ;

      /// Top most ancestor with T trait.
      template <class T> T* getRoot() const ;

      /// First ancestor (including @c this) with trait T.
      template <class T> T* getParent() const ;
      
      /// First ancestor (excluding @c this) with trait T.
      template <class T> T* getAncestor() const ;
      
      /// First ancestor (including @c this) with trait T and not up to @c i_object.
      /*!
        @returns NULL 
          if no object has T trait between this and @c i_object
          or @c i_object is not ancestor of this.
      */
      template <class T> T* getParentUpTo(Object* i_object) const ;

      /// Get all the descendant (excluding @c this) with trait T.
      template <class T> std::set<T*> getDescendants() const ;

      /// call a void command returns true iff succedeed.
      /*!
        Try first on object traits then on sub-objects...??
      */
      bool call(const std::string& i_command) ;

      /// call an int command returns true iff succedeed.
      bool call(const std::string& i_command, const int&) ;
      
      /// Access to all commands understood be the object.
      std::set<std::string> getCommands() const ;
      
      /// Access to all children.
      std::set<Object*> getChildren() const ;
      
    //@}
    /*!
      @name Apply methods
    */
    //@{

      /// Apply @c i_operation on all _View.
      /*!
        @deprecated
      */
      template <class _View>
      void apply(const TypeIdentifier& i_trait_name,
                 ViewPoint* i_viewpoint,
                 boost::function1<void,_View*> i_operation) ;

      /// Apply @c i_operation on all controlers of @c i_controler_set.
      void applyTopDown
                (ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

      /// Apply @c i_operation on all controlers of @c i_controler_set.
      void applyBottomUp
                (ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

    //@}

    private:

    /*!
      @name Internal construction
      
      @see Model for public construction methods.
    */    
    //@{
    
      /// Add a sub-object
      Object* _add(Object* i_child) ;

      /// Remove a sub-object.
      void _remove(Object* i_child) ;
    
      /// Detach a sub-object.
      Object* _release(Object* i_child) ;

      /// Add a trait.
      void _add(Trait* i_trait) ;

      /// Remove a trait.
      void _remove(Trait* i_trait) ;

      /// Remove a trait by trait name.
      void _remove(const TypeIdentifier& i_trait_name) ;

      /// Retreive the trait named @c i_trait_name.
      Trait* _get(const TypeIdentifier& i_trait_name) const ;

      /// update the views for a change_parent. 
      void _changed_parent(Object* i_old_parent) ;
      
      /// update the views.
      void _updated() ;
      
      /// init after construction.
      void _init() ;

      /// init the views after construction.
      void _init(ViewPoint* i_viewpoint) ;

      /// init the controlers after construction.
      void _init(ControlerSet* i_controler_set) ;

      /// closes before destruction.
      void _close() ;

      /// close the views before viewpoint closing.
      void _close(ViewPoint* i_viewpoint) ;

      /// close the controlers before controler set closing.
      void _close(ControlerSet* i_controler_set) ;

      /// recursivelly create views for a viewpoint.
      void _create_views(ViewPoint* i_viewpoint) ;

      /// recursivelly create controlers for a controler set.
      void _create_controlers(ControlerSet* i_controler_set) ;

    /*!
      @name Deduction access
    */    
    //@{
    
      bool getValidity(const Formula* i_formula) const ;
      
      void setValidity(const Formula* i_formula,bool i_validity) ;

      unsigned short getNumberOfTrueChildFormulae(const Formula* i_formula) const ;
      
      void setNumberOfTrueChildFormulae(const Formula* i_formula,
                                        unsigned short i_number) ;
                                        
    // @}
    /*!
      @name attributes
    */    
    // @{
    
      std::string name ;
      /// @composite
      std::map<TypeIdentifier, Trait*> traits ;
      Object* parent ;
      /// @composite
      std::set<Object*> children ;
      
      /// Model of the object.
      Model*            m_model ;
      
      /// Validities for each formula
      std::vector<bool> m_validities ;

      /// Number of true chid formulae indexed by formulae.       
      std::vector<unsigned short> m_number_of_true_child_formulae ;

    // @}

      friend class Trait ;    
      friend class Model ;
      friend class Formula ;
      friend class FormulaAnd ;
      friend class FormulaOr ;
      friend class FormulaNot ;
      friend class TraitFormula ;
      friend class DeducedTrait ;
      
    };
  }
}      

#include <kernel/implementation/object.cxx>

#endif /*PU_KERNEL_OBJECT_H_*/
