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
#ifndef PU_KERNEL_MODEL_H_
#define PU_KERNEL_MODEL_H_

#include <boost/function.hpp>
#include <set>
#include <map>
#include <string>

namespace ProjetUnivers {
  namespace Kernel {
    
    class ViewPoint ;
    class Object ;
    class Trait ;
    class ControlerSet ;
    
    /// A set of Objects.
    class Model
    {
    public:
    
      /// Builds a new model.
      Model(const std::string& i_name = "") ;

      /// Get an object.
      Object* getObject(const std::string& i_name) ;
        
      /// Creates a new Object with name.
      Object* createObject(const std::string& i_name) ; 
  
      /// Creates a new Object with name and given parent.
      Object* createObject(const std::string& i_name, 
                           Object* i_parent) ; 

      /// Creates a new Object.
      Object* createObject() ; 
  
      /// Creates a new Object with given parent.
      Object* createObject(Object* i_parent) ; 
  
      /// Destroy an Object of given name.
      void destroyObject(const std::string& i_name) ;
  
      /// Destroy a given Object.
      void destroyObject(Object* i_object) ;
  
      /// Changes parent of a given Object.
      void changeParent(Object* i_object, 
                        Object* i_new_parent) ;
  
      /// Adds a new trait to an Object.
      void addTrait(Object* i_object, 
                    Trait* i_new_trait) ;
  
      /// Destroy an Object's trait.
      void destroyTrait(Object* i_object, 
                        Trait* i_trait) ;
      
    
      ~Model() ;
    
    private:
    
      /// root objects @composite
      std::set<Object*>             m_objects ;
      std::map<std::string,Object*> m_objects_dictionnary ;

      /// Register a view point.
      void _register(ViewPoint* i_viewpoint) ;

      /// Unregister a view point.
      void _unregister(ViewPoint* i_viewpoint) ;

      /// Register a controler set.
      void _register(ControlerSet* i_controler_set) ;

      /// Unregister a controler set.
      void _unregister(ControlerSet* i_controler_set) ;
      
      /// Init objects according to a viewpoint
      void _init(ViewPoint* i_viewpoint) ;

      /// Close objects according to a viewpoint
      void _close(ViewPoint* i_viewpoint) ;

      /// Init objects according to a controler set
      void _init(ControlerSet* i_controler_set) ;

      /// Close objects according to a controler set
      void _close(ControlerSet* i_controler_set) ;

      
      std::set<ViewPoint*>        m_viewpoints ;
      std::set<ControlerSet*>     m_controler_sets ;
      
      friend class ViewPoint ;
      friend class Trait ;
      friend class Object ;
      friend class ControlerSet ;
      
      template <class _View>
      friend void forAll(ViewPoint*                    i_viewpoint,
                         boost::function1<void,_View*> i_operation) ;

    };
    
  }
}

#endif

