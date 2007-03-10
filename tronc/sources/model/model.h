/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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

#ifndef PU_MODEL_MODEL_H_
#define PU_MODEL_MODEL_H_

#include <string>


namespace ProjetUnivers {
  
  namespace Kernel {
    class Object ;
    class Kernel::Trait ;
  }
   
  /// Game data model.
  /*!
  @par Introduction
  
    Model part of Model/View/Control. Functionnal core.
    
    This module contains all data about manipulated objects in the game 
    regardless of displaying and events that triggers modifications.
    
  */ 
  namespace Model 
  {
    
  
  /*!
    @name Init/Close.
  */
  //@{        
    
    /// Starts the module.
    void init() ;

    /// Closes le module.
    void close() ;

    /// Load a model from disk.
    void load(const std::string& _name) ;
    
  //@}
  /*!
    @name Interface
    
  */
  // @{

    /// Get an object.
    Kernel::Object* getObject(const std::string& i_name) ;
      
    /// Creates a new Kernel::Object with name.
    Kernel::Object* createObject(const std::string& i_name) ; 

    /// Creates a new Kernel::Object with name and given parent.
    Kernel::Object* createObject(const std::string& i_name, 
                                 Kernel::Object* i_parent) ; 

    /// Destroy an Kernel::Object of given name.
    void destroyObject(const std::string& i_name) ;

    /// Destroy a given Kernel::Object.
    void destroyObject(Kernel::Object* i_object) ;

    /// Changes parent of a given Kernel::Object.
    void changeParent(Kernel::Object* i_object, 
                      Kernel::Object* i_new_parent) ;

    /// Adds a new trait to an Kernel::Object.
    void addTrait(Kernel::Object* i_object, 
                  Kernel::Trait* i_new_trait) ;

    /// Destroy an Kernel::Object's trait.
    void destroyTrait(Kernel::Object* i_object, 
                      Kernel::Trait* i_trait) ;

  //@}

    /// Access to real world model. 
    Kernel::Model* getRealWorlModel() ;
    
  }
  
}

#endif

