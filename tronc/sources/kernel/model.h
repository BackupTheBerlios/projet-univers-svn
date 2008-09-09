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
#ifndef PU_KERNEL_MODEL_H_
#define PU_KERNEL_MODEL_H_

#include <boost/function.hpp>
#include <set>
#include <map>
#include <string>

#include <kernel/object.h>

namespace ProjetUnivers {
  namespace Kernel {
    
    class ViewPoint ;
    class Trait ;
    class ControlerSet ;
    class ObjectReference ;
    class BaseTraitView ;
    class Reader ;
    
    /// A set of Objects.
    class Model
    {
    public:
    
      /// Builds a new model.
      Model(const std::string& name = "") ;

      /// Destroy all objects, views and controlers. 
      ~Model() ;

      
      /// Creates a new Object.
      Object* createObject() ; 
  
      /// Destroy a given Object.
      void destroyObject(Object* object) ;
  
      /// Manually add a view.
      /*!
        The view already contains a reference to its viewpoint and trait.
      */
      void addManualView(BaseTraitView*) ;
      
      /// Build all registered viewpoints and controler sets.
      void init() ;

      /// Closes all registered viewpoints and controler sets.
      void close() ;
      
      /// Update the model during @c seconds
      void update(const float& seconds) ;
      
      /// Add a viewpoint.
      ViewPoint* addViewPoint(ViewPoint*) ;
      
      /// Add a controler set.
      ControlerSet* addControlerSet(ControlerSet*) ;
      
      /// Get an object by identifier.
      Object* getObject(const int& identifier) const ;
      
      /// Access to root objects.
      const std::set<Object*>& getRoots() const ;
      /// return a controler set of type @c T.
      template <class T> T* getControlerSet() const ;
      
      /// return a viewpoint of type @c T.
      template <class T> T* getViewPoint() const ;
      
    private:
      
      /// Creates a new Object with given parent.
      Object* createObject(Object* parent) ; 

      /// Changes parent of a given Object.
      void changeParent(Object* object, 
                        Object* new_parent) ;
  
      /// Adds a new trait to an Object.
      void addTrait(Object* object, 
                    Trait* new_trait) ;
  
      /// Destroy an Object's trait.
      void destroyTrait(Object* object, 
                        Trait* trait) ;

      /// Access to viewpoints.
      const std::set<ViewPoint*>& getViewPoints() const ;

      /// Access to controler sets.
      const std::set<ControlerSet*>& getControlerSets() const ;
      
      std::string                   m_name ;
    
      /// root objects @composite
      std::set<Object*>             m_objects ;
      
      /// Remove the mapping between an identifier and an object.
      /*!
        Used during object destruction.
      */
      void _removeObjectIdentifier(const int& identifier) ;
      
      /// Identify objects.
      std::map<int,Object*>         m_objects_by_identifier ;

      /// true during destruction.
      bool                          m_destroying ;
      
      /// Register a view point.
      void _register(ViewPoint* viewpoint) ;

      /// Unregister a view point.
      void _unregister(ViewPoint* viewpoint) ;

      /// Register a controler set.
      void _register(ControlerSet* controler_set) ;

      /// Unregister a controler set.
      void _unregister(ControlerSet* controler_set) ;
      
      /// Init objects according to a viewpoint
      void _init(ViewPoint* viewpoint) ;

      /// Close objects according to a viewpoint
      void _close(ViewPoint* viewpoint) ;

      /// Init objects according to a controler set
      void _init(ControlerSet* controler_set) ;

      /// Close objects according to a controler set
      void _close(ControlerSet* controler_set) ;

      std::set<ViewPoint*>        m_viewpoints ;
      std::set<ControlerSet*>     m_controler_sets ;

    /*!
      @name Back reference handling
      
      Reference to object need to be "cleared" when model is destroyed. 
    */
          
      void _registerReference(ObjectReference*) ;

      void _unregisterReference(ObjectReference*) ;
      
      std::set<ObjectReference*>  m_references ;
      
      friend class ViewPoint ;
      friend class Trait ;
      friend class Object ;
      friend class ControlerSet ;
      friend class Reader ;
      
      template <class _View>
      friend void forAll(ViewPoint*                    viewpoint,
                         boost::function1<void,_View*> operation) ;

      friend class ObjectReference ;
    };
    
  }
}

#include <kernel/implementation/model.cxx>

#endif

