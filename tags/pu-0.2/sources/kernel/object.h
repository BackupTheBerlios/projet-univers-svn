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
#include <typeinfo>

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

      virtual Object* getParent() const ;
  
      /// Get top most ancestor.
      virtual Object* getRoot() const ;

      /// Access to trait of type T if exists.
      template <class T> T* getTrait() ;

      /// Access to trait's view of type _View if exists.
      template <class _View> _View* getView(ViewPoint* i_viewpoint) ;

      /// Top most ancestor with T trait.
      template <class T> T* getRoot() const ;

      /// First ancestor with trait T.
      template <class T> T* getParent() const ;

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

      /// update the views for a change_parent. 
      void _changed_parent(Object* i_old_parent) ;
      
      /// update the views.
      void _updated() ;
      
      /// init the views after construction.
      void _init() ;

      /// init the views after construction.
      void _init(ViewPoint* i_viewpoint) ;

      /// closes the views before destruction.
      void _close() ;

      /// close the views before viewpoint closing.
      void _close(ViewPoint* i_viewpoint) ;

      
      /// recursivelly create views for a viewpoint.
      void _create_views(ViewPoint* i_viewpoint) ;

    /*!
      @name attributes
    */    
    // @{
    
      std::string name ;
      /// @composite
      std::map<std::string, Trait*> traits ;
      Object* parent ;
      /// @composite
      std::set<Object*> children ;
      Model* model ;
      
    // @}

      friend class Trait ;    
      friend class Model ;
    };

    template <class _View> _View* Object::getView(ViewPoint* i_viewpoint)
    {
      check(i_viewpoint,ExceptionKernel("Object::getView error")) ;
      
      if (Trait::m_trait_of_view.find(std::pair<std::string,std::string>(
                       typeid(_View).name(), typeid(*i_viewpoint).name()))
          != Trait::m_trait_of_view.end()
         )
      {
        std::string trait_class_name =
          Trait::m_trait_of_view[std::pair<std::string,std::string>(
              typeid(_View).name(), typeid(*i_viewpoint).name())] ;
        
        Trait* trait = traits[trait_class_name] ; 
        check(trait,ExceptionKernel("Object::getView error")) ;
        return trait->getView<_View>(i_viewpoint) ;
      }
      
      return NULL ;
    }

    template <class T> T* Object::getTrait() 
    {

      Kernel::Log::InternalMessage("Object::getTrait()") ;

      /// T doit être une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;

      Kernel::Log::InternalMessage("Asking :") ;
      Kernel::Log::InternalMessage(typeid(T).name()) ;
      
      /// if trait exist convert :
      if (traits.find(typeid(T).name()) != traits.end())
      {
        Kernel::Log::InternalMessage("Trait found") ;
        
        return static_cast<T*>(traits[typeid(T).name()]) ;
      }
      else
      {
        Kernel::Log::InternalMessage("Trait not found") ;
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
      Kernel::Log::InternalMessage("Object::getRoot()") ;

      /// T doit être une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      T* highest_trait_found(iterator->getTrait<T>()) ;
      
      while(highest_trait_found && iterator)
      {
        Kernel::Log::InternalMessage(
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


  }
}      

#endif /*PU_KERNEL_OBJECT_H_*/
