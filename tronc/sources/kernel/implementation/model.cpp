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
#include <kernel/base_trait_view.h>
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

    Object* Model::getObject(const std::string& name)
    {
      if (m_objects_dictionnary.find(name)!= m_objects_dictionnary.end())
      {
        return m_objects_dictionnary[name] ;
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

    Object* Model::createObject(const std::string& name) 
    {
      if (m_objects_dictionnary.find(name) == m_objects_dictionnary.end())
      {
        Object* result = new Object(this,name) ;
        m_objects.insert(result) ;
        m_objects_dictionnary[name] = result ;
        m_objects_by_identifier[result->getIdentifier()] = result ;
        return result ;
      }
      return NULL ;
    }
      
    /// Creates a new Object with name.
    Object* Model::createObject(const std::string& name,
                                Object* parent)
    {
      CHECK(parent,ExceptionKernel("Model::createObject no parent")) ;
      
      if (m_objects_dictionnary.find(name) == m_objects_dictionnary.end())
      {
        Object* result = new Object(this,name) ;
        parent->_add(result) ;
        m_objects_dictionnary[name] = result ;
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
    Object* Model::createObject(Object* parent)
    {
      return createObject(getUniqueName(),parent) ;
    }

    /// Destroy an Object of given name.
    void Model::destroyObject(const std::string& name)
    {
      Object* object = getObject(name) ;
      if (object)
      {
        destroyObject(object) ;
      }
    }

    /// Destroy a given Object.
    void Model::destroyObject(Object* object)
    {
      CHECK(object,ExceptionKernel("Model::destroyObject no object")) ;
      
      object->_close() ;

      m_objects_dictionnary.erase(object->getName()) ;
      m_objects_by_identifier.erase(object->getIdentifier()) ;
      
      if (object->getParent() == NULL)
      {
        /// a top object
        m_objects.erase(object) ;
        delete object ;  /// model is the contener of the root m_objects
      } 
      else
      {
        /// a sub object
        object->getParent()->_remove(object) ;
      }
      
    }

    /// Changes parent of a given Object.
    void Model::changeParent(Object* object, 
                             Object* new_parent)
    {
      CHECK(object,ExceptionKernel("Model::changeParent no object")) ;
      CHECK(new_parent,ExceptionKernel("Model::changeParent no new parent")) ;
      
      Object* old_parent = object->getParent() ;
      
      if (object->getParent() == NULL)
      {
        /// a top object
        m_objects.erase(object) ;

      }
      else
      {
        object->getParent()->_detach(object) ;
      }

      new_parent->_add(object) ;
      object->_changed_parent(old_parent) ;

    }

    /// Adds a new trait to an Object.
    void Model::addTrait(Object* object, 
                         Trait* new_trait)
    {
      CHECK(object,ExceptionKernel("Model::destroyTrait no object")) ;
      CHECK(new_trait,ExceptionKernel("Model::destroyTrait no new trait")) ;
      
      object->_add(new_trait) ;
      
    }

    /// Destroy an Object's trait.
    void Model::destroyTrait(Object* object, 
                            Trait* trait)
    {
      CHECK(object,ExceptionKernel("Model::destroyTrait no object")) ;
      CHECK(trait,ExceptionKernel("Model::destroyTrait no trait")) ;

      object->_remove(trait) ;
    }
    
    Model::~Model()
    {
      InternalMessage("Kernel","Kernel::Model::~Model entering") ;
      
      for(std::set<ObjectReference*>::iterator reference = m_references.begin() ;
          reference != m_references.end() ;
          ++reference)
      {
        (*reference)->_setModel(NULL) ;
      }
      
      /// 1. close all view points
      InternalMessage("Kernel","Kernel::Model::~Model closing viewpoints") ;
      for(std::set<ViewPoint*>::iterator viewpoint = m_viewpoints.begin() ;
          viewpoint != m_viewpoints.end() ;
          ++viewpoint)
      {
        _close(*viewpoint) ;
        /// notify viewpoint it has no longer a model
        (*viewpoint)->m_model = NULL ;
      }
      
      /// 1. close all controler sets
      InternalMessage("Kernel","Kernel::Model::~Model closing controler sets") ;
      for(std::set<ControlerSet*>::iterator controler_set = m_controler_sets.begin() ;
          controler_set != m_controler_sets.end() ;
          ++controler_set)
      {
        _close(*controler_set) ;
        /// notify controler_set it has no longer a model
        (*controler_set)->m_model = NULL ;
      }
      
      
      /// 2. destroy m_objects 
      InternalMessage("Kernel","Kernel::Model::~Model destroying objects") ;
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        delete *object ;
      }
      
      InternalMessage("Kernel","Kernel::Model::~Model Leaving") ;
    }
    
    Model::Model(const std::string& name)
    : m_name(name)
    {}

    void Model::_register(ViewPoint* viewpoint)
    {
      m_viewpoints.insert(viewpoint) ;

      InternalMessage("Kernel",
        (std::string("Model::_register") + typeid(*viewpoint).name()).c_str()) ;

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_create_views(viewpoint) ;
      }      
    }

    void Model::_unregister(ViewPoint* viewpoint)
    {
      m_viewpoints.erase(viewpoint) ;

      InternalMessage("Kernel",
        (std::string("Model::_unregister") + typeid(*viewpoint).name()).c_str()) ;
    }

    void Model::_register(ControlerSet* controler_set)
    {
      m_controler_sets.insert(controler_set) ;

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_create_controlers(controler_set) ;
      }      
    }

    void Model::_unregister(ControlerSet* controler_set)
    {
      m_controler_sets.erase(controler_set) ;
    }
    
    void Model::_init(ViewPoint* viewpoint)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_init(viewpoint) ;
      }      
    }
  
    void Model::_close(ViewPoint* viewpoint)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(viewpoint) ;
      }
    }

    void Model::_init(ControlerSet* controler_set)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_init(controler_set) ;
      }      
    }

    void Model::_close(ControlerSet* controler_set)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(controler_set) ;
      }      
    }

    const std::set<Object*>& Model::getRoots() const
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

    void Model::addManualView(BaseTraitView* view)
    {
      view->getTrait()->addView(view->m_viewpoint,view) ;
    }
  }
}


