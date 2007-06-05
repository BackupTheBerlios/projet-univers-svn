/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
    */
    class Object 
    {
    public:

      /// Constructor.
      Object(Model* i_model,const std::string& i_name = "") ;

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

      /// First ancestor with trait T.
      template <class T> T* getParent() const ;

      /// Apply @c i_operation on all _View.
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

      /// destrucs the traits
      ~Object() ;

    private:
    
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
    // @{
    
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



    template <class _View> _View* Object::getView(ViewPoint* i_viewpoint)
    {
      check(i_viewpoint,ExceptionKernel("Object::getView error")) ;
      InternalMessage(
        "Object::getView for " + getObjectTypeIdentifier(i_viewpoint).toString()) ;
      
      TypeIdentifier trait_type = 
        Trait::getTraitTypeOfView(
                    getClassTypeIdentifier(_View), 
                    getObjectTypeIdentifier(i_viewpoint)) ;
      
      if (trait_type != VoidTypeIdentifier)
      {
        InternalMessage("Object::getView found trait name " + trait_type.toString()) ;

        for(std::map<TypeIdentifier, Trait*>::const_iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          if (trait_type.isInstance(trait->second))
          {
            InternalMessage("Object::getView trait*=" + toString((int)trait->second)) ;
            return trait->second->getView<_View>(i_viewpoint) ;
          }
        }
      }
      
      InternalMessage("Object::getView return NULL") ;
      return NULL ;
    }

    template <class T> T* Object::getTrait() 
    {

      InternalMessage("Object::getTrait()") ;

      /// T doit être une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;

      InternalMessage("Asking trait " + getClassTypeIdentifier(T).toString()) ;
      
      /// if trait exist convert :
      if (traits.find(getClassTypeIdentifier(T)) != traits.end())
      {
        InternalMessage("Trait found") ;
        
        return static_cast<T*>(traits[getClassTypeIdentifier(T)]) ;
      }
      else
      {
        InternalMessage("Trait not found") ;
        return NULL ;
      }
    }

    template <class T> T* Object::getParent() const
    {
      /// T doit être une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      T* trait(iterator->getTrait<T>()) ;
      
      while((! trait) && iterator)
      {
        iterator = iterator->getParent() ;
        if (iterator)
        {
          trait = iterator->getTrait<T>() ;
        }
      }
      
      return trait ;
      
    }

    template <class T> T* Object::getRoot() const
    {
      InternalMessage("Object::getRoot()") ;

      /// T doit être une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      T* highest_trait_found(iterator->getTrait<T>()) ;
      
      while(highest_trait_found && iterator)
      {
        InternalMessage(
          (std::string("highest_trait_found=") 
           + toString((int)highest_trait_found)
           + std::string(" iterator=")
           + toString((int)iterator)).c_str()) ;
          

        highest_trait_found = highest_trait_found ;
        
        iterator = iterator->getParent() ;
        if (iterator)
        {
          highest_trait_found = iterator->getTrait<T>() ;
        }
      }
      
      return highest_trait_found ;
      
    }

    template <class _View>
    void Object::apply(const TypeIdentifier& i_trait_name,
                       ViewPoint* i_viewpoint,
                       boost::function1<void,_View*> i_operation)
    {
      std::map<TypeIdentifier, Trait*>::const_iterator
           trait = traits.find(i_trait_name) ;
      
      if (trait != traits.end())
      {
        _View* view = trait->second->getView<_View>(i_viewpoint) ;
        if (view)
        {
          i_operation(view) ;
        }
      }

      /// recursive
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->apply<_View>(i_trait_name,i_viewpoint,i_operation) ;
      }
      
    }


  }
}      

#endif /*PU_KERNEL_OBJECT_H_*/
