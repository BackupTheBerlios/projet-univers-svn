/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/exception_kernel.h>

#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/view_point.h>
#include <kernel/model.h>

#include <typeinfo>


namespace ProjetUnivers {
  namespace Kernel {
    

    Object* Model::getObject(const std::string& i_name)
    {
      if (objects_dictionnary.find(i_name)!= objects_dictionnary.end())
      {
        return objects_dictionnary[i_name] ;
      }
      else
      {
        return NULL ;
      }
    }


    Object* Model::createObject(const std::string& i_name) 
    {
      if (objects_dictionnary.find(i_name) == objects_dictionnary.end())
      {
        Object* result = new Object(this,i_name) ;
        objects.insert(result) ;
        objects_dictionnary[i_name] = result ;
        return result ;
      }
      return NULL ;
    }
      
    /// Creates a new Object with name.
    Object* Model::createObject(const std::string& i_name,
                                Object* i_parent)
    {
      check(i_parent,ExceptionKernel("Model::createObject no parent")) ;
      
      if (objects_dictionnary.find(i_name) == objects_dictionnary.end())
      {
        Object* result = new Object(this,i_name) ;
        i_parent->_add(result) ;
        objects_dictionnary[i_name] = result ;
        
        return result ;
      }
      
      return NULL ;
      
    }


    /// Destroy an Object of given name.
    void Model::destroyObject(const std::string& i_name)
    {
      Object* object = getObject(i_name) ;
      if (object)
      {
        destroyObject(object) ;
      }
    }

    /// Destroy a given Object.
    void Model::destroyObject(Object* i_object)
    {
      check(i_object,ExceptionKernel("Model::destroyObject no object")) ;
      
      i_object->_close() ;

      objects_dictionnary.erase(i_object->getName()) ;
      
      if (i_object->parent == NULL)
      {
        /// a top object
        objects.erase(i_object) ;
        delete i_object ;  /// model is the contener of the root objects
      } 
      else
      {
        /// a sub object
        i_object->parent->_remove(i_object) ;
      }
      
    }

    /// Changes parent of a given Object.
    void Model::changeParent(Object* i_object, 
                             Object* i_new_parent)
    {
      check(i_object,ExceptionKernel("Model::changeParent no object")) ;
      check(i_new_parent,ExceptionKernel("Model::changeParent no new parent")) ;
      
      Object* old_parent = i_object->parent ;
      
      if (i_object->parent == NULL)
      {
        /// a top object
        objects.erase(i_object) ;

      }
      else
      {
        i_object->parent->_release(i_object) ;
      }

      i_new_parent->_add(i_object) ;
      i_object->_changed_parent(old_parent) ;

    }

    /// Adds a new trait to an Object.
    void Model::addTrait(Object* i_object, 
                         Trait* i_new_trait)
    {
      check(i_object,ExceptionKernel("Model::destroyTrait no object")) ;
      check(i_new_trait,ExceptionKernel("Model::destroyTrait no new trait")) ;
      
      i_object->_add(i_new_trait) ;
      
    }

    /// Destroy an Object's trait.
    void Model::destroyTrait(Object* i_object, 
                            Trait* i_trait)
    {
      check(i_object,ExceptionKernel("Model::destroyTrait no object")) ;
      check(i_trait,ExceptionKernel("Model::destroyTrait no trait")) ;

      i_object->_remove(i_trait) ;
    }


    
    Model::~Model()
    {
      for(std::set<Object*>::iterator object = objects.begin() ;
          object != objects.end() ;
          ++object)
      {
        delete *object ;
      }
      
    }
    
    Model::Model(const std::string& i_name)
    {}

    void Model::_register(ViewPoint* i_viewpoint)
    {
      viewpoints.insert(i_viewpoint) ;

      Log::InternalMessage(
        (std::string("Model::_register") + typeid(*i_viewpoint).name()).c_str()) ;

      for(std::set<Object*>::iterator object = objects.begin() ;
          object != objects.end() ;
          ++object)
      {
        (*object)->_create_views(i_viewpoint) ;
      }      
    }
    
    void Model::_init(ViewPoint* i_viewpoint)
    {
      for(std::set<Object*>::iterator object = objects.begin() ;
          object != objects.end() ;
          ++object)
      {
        (*object)->_init(i_viewpoint) ;
      }      
    }
  
    void Model::_close(ViewPoint* i_viewpoint)
    {
      for(std::set<Object*>::iterator object = objects.begin() ;
          object != objects.end() ;
          ++object)
      {
        (*object)->_close(i_viewpoint) ;
      }      
      
    }
  }
}


