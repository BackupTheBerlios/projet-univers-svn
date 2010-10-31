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
#pragma once

#include <string>
#include <list>
#include <model/duration.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Object ;
    class Trait ;
    class Model ;
  }
   
  /// Game data model.
  /*!
  @par Introduction
  
    Model part of Model/View/Control. Functional core.
    
    This module contains all data about manipulated objects in the game 
    regardless of displaying and events that triggers modifications.
    
  */ 
  namespace Model 
  {

    /// Start the module.
    void start() ;

    /// Load a model from disk.
    void load(const std::string& name,Kernel::Model* model) ;
    
    /// Load and initialize external resources.
    void initRessources() ;
    
    /// Unload and close external resources.
    void closeRessources() ;

  //@}
  /*!
    @name Specialized Modification Interface
    
  */
  // @{
    
    /// Create a ship under @c parent.
    Kernel::Object* createShip(Kernel::Object* parent) ;
    
    /// Load a ship file by name.
    /*!
      Ship files are ending by ".ship".
    */
    Kernel::Object* loadShip(const std::string&,Kernel::Object* parent) ;
    
    /// Create a autonomous agent controling @c ship and inside it.
    Kernel::Object* createAI(Kernel::Object* ship) ;
    
    /// Create a default player configuration.
    Kernel::Object* createDefaultPlayerConfiguration(Kernel::Object* parent) ;

    void savePlayerConfiguration(Kernel::Object* configuration) ;
    
    /// Return the ship controled by @c agent.
    /*!
      @return NULL if not exist
    */
    Kernel::Object* getControledShip(Kernel::Object* agent) ;
    
    /// Return the ship of an object
    Kernel::Object* getShip(Kernel::Object* object) ;

    /// Get the available ships.
    std::list<std::string> getAvailableShipNames() ;
    
  //@}
  
  }
}
