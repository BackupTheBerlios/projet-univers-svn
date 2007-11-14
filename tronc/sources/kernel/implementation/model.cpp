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
#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/exception_kernel.h>

#include <kernel/object.h>
#include <kernel/object_reference.h>
#include <kernel/trait.h>
#include <kernel/view_point.h>
#include <kernel/controler_set.h>
#include <kernel/model.h>

#include <typeinfo>


namespace ProjetUnivers {
  namespace Kernel {
    
    namespace
    {
      int next_number = 0 ;
    }

    /// create a unique object name.
    std::string getUniqueName()
    {
      return "PU::Kernel::Name" + toString(next_number++) ;
    }

    Object* Model::getObject(const std::string& i_name)
    {
      if (m_objects_dictionnary.find(i_name)!= m_objects_dictionnary.end())
      {
        return m_objects_dictionnary[i_name] ;
      }
      else
      {
        return NULL ;
      }
    }

    Object* Model::getObject(const int& identifier) const
    {
      std::map<int,Object*>::const_iterator finder 
        = m_objects_by_identifier.find(identifier) ;
      if (finder != m_objects_by_identifier.end())
      {
        return finder->second ;
      }
      else
      {
        return NULL ;
      }
    }

    Object* Model::createObject(const std::string& i_name) 
    {
      if (m_objects_dictionnary.find(i_name) == m_objects_dictionnary.end())
      {
        Object* result = new Object(this,i_name) ;
        m_objects.insert(result) ;
        m_objects_dictionnary[i_name] = result ;
        m_objects_by_identifier[result->getIdentifier()] = result ;
        return result ;
      }
      return NULL ;
    }
      
    /// Creates a new Object with name.
    Object* Model::createObject(const std::string& i_name,
                                Object* i_parent)
    {
      CHECK(i_parent,ExceptionKernel("Model::createObject no parent")) ;
      
      if (m_objects_dictionnary.find(i_name) == m_objects_dictionnary.end())
      {
        Object* result = new Object(this,i_name) ;
        i_parent->_add(result) ;
        m_objects_dictionnary[i_name] = result ;
        m_objects_by_identifier[result->getIdentifier()] = result ;
        
        return result ;
      }
      
      return NULL ;
      
    }

    Object* Model::createObject() 
    {
      return createObject(getUniqueName()) ;
    }
      
    /// Creates a new Object with name.
    Object* Model::createObject(Object* i_parent)
    {
      return createObject(getUniqueName(),i_parent) ;
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
      CHECK(i_object,ExceptionKernel("Model::destroyObject no object")) ;
      
      i_object->_close() ;

      m_objects_dictionnary.erase(i_object->getName()) ;
      m_objects_by_identifier.erase(i_object->getIdentifier()) ;
      
      if (i_object->getParent() == NULL)
      {
        /// a top object
        m_objects.erase(i_object) ;
        delete i_object ;  /// model is the contener of the root m_objects
      } 
      else
      {
        /// a sub object
        i_object->getParent()->_remove(i_object) ;
      }
      
    }

    /// Changes parent of a given Object.
    void Model::changeParent(Object* i_object, 
                             Object* i_new_parent)
    {
      CHECK(i_object,ExceptionKernel("Model::changeParent no object")) ;
      CHECK(i_new_parent,ExceptionKernel("Model::changeParent no new parent")) ;
      
      Object* old_parent = i_object->getParent() ;
      
      if (i_object->getParent() == NULL)
      {
        /// a top object
        m_objects.erase(i_object) ;

      }
      else
      {
        i_object->getParent()->_detach(i_object) ;
      }

      i_new_parent->_add(i_object) ;
      i_object->_changed_parent(old_parent) ;

    }

    /// Adds a new trait to an Object.
    void Model::addTrait(Object* i_object, 
                         Trait* i_new_trait)
    {
      CHECK(i_object,ExceptionKernel("Model::destroyTrait no object")) ;
      CHECK(i_new_trait,ExceptionKernel("Model::destroyTrait no new trait")) ;
      
      i_object->_add(i_new_trait) ;
      
    }

    /// Destroy an Object's trait.
    void Model::destroyTrait(Object* i_object, 
                            Trait* i_trait)
    {
      CHECK(i_object,ExceptionKernel("Model::destroyTrait no object")) ;
      CHECK(i_trait,ExceptionKernel("Model::destroyTrait no trait")) ;

      i_object->_remove(i_trait) ;
    }
    
    Model::~Model()
    {
      InternalMessage("Kernel::Model::~Model entering") ;
      
      for(std::set<ObjectReference*>::iterator reference = m_references.begin() ;
          reference != m_references.end() ;
          ++reference)
      {
        (*reference)->_setModel(NULL) ;
      }
      
      /// 1. close all view points
      for(std::set<ViewPoint*>::iterator viewpoint = m_viewpoints.begin() ;
          viewpoint != m_viewpoints.end() ;
          ++viewpoint)
      {
        _close(*viewpoint) ;
        /// notify viewpoint it has no longer a model
        (*viewpoint)->setModel(NULL) ;
      }
      
      /// 1. close all controler sets
      for(std::set<ControlerSet*>::iterator controler_set = m_controler_sets.begin() ;
          controler_set != m_controler_sets.end() ;
          ++controler_set)
      {
        _close(*controler_set) ;
        /// notify controler_set it has no longer a model
        (*controler_set)->setModel(NULL) ;
      }
      
      
      /// 2. destroy m_objects 
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        delete *object ;
      }
      
      InternalMessage("Kernel::Model::~Model Leaving") ;
    }
    
    Model::Model(const std::string& i_name)
    : m_name(i_name)
    {}

    void Model::_register(ViewPoint* i_viewpoint)
    {
      m_viewpoints.insert(i_viewpoint) ;

      InternalMessage(
        (std::string("Model::_register") + typeid(*i_viewpoint).name()).c_str()) ;

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_create_views(i_viewpoint) ;
      }      
    }

    void Model::_unregister(ViewPoint* i_viewpoint)
    {
      m_viewpoints.erase(i_viewpoint) ;

      InternalMessage(
        (std::string("Model::_unregister") + typeid(*i_viewpoint).name()).c_str()) ;
    }

    void Model::_register(ControlerSet* i_controler_set)
    {
      m_controler_sets.insert(i_controler_set) ;

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_create_controlers(i_controler_set) ;
      }      
    }

    void Model::_unregister(ControlerSet* i_controler_set)
    {
      m_controler_sets.erase(i_controler_set) ;
    }
    
    void Model::_init(ViewPoint* i_viewpoint)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_init(i_viewpoint) ;
      }      
    }
  
    void Model::_close(ViewPoint* i_viewpoint)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(i_viewpoint) ;
      }      
    }

    void Model::_init(ControlerSet* i_controler_set)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_init(i_controler_set) ;
      }      
    }

    void Model::_close(ControlerSet* i_controler_set)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(i_controler_set) ;
      }      
    }

    std::set<Object*> Model::getRoots() const
    {
      return m_objects ;
    }

    void Model::_registerReference(ObjectReference* reference)
    {
      m_references.insert(reference) ;
    }

    void Model::_unregisterReference(ObjectReference* reference)
    {
      m_references.erase(reference) ;
    }

  }
}


