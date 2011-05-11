/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2009 Mathieu ROGER                                 *
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
#include <kernel/trait.h>

#include <model/objective.h>

namespace ProjetUnivers 
{
  namespace Model 
  {

    /// Represents a FlyingGroup.
    /*!
    */
    class FlyingGroup : public Kernel::Trait
    {
    public:

      /// Constructs with a name.
      FlyingGroup(const std::string& name) ;
      
      /// Change group's name.
      void setName(const std::string& name) ;

      /// Change ship's name
      void setShipName(const std::string& name) ;
      
      /// Change the number of ships.
      void setInitialNumberOfShips(const unsigned int&) ;
      
      /// Set the number of creations.
      void setNumberOfSpawn(const unsigned int&) ;
      
      /// A ship was removed.
      void removeShip(Kernel::Object*) ;

      /// A ship was added.
      void addShip(Kernel::Object*) ;
      
      /// Access to name.
      const std::string& getName() const ;

      /// Access to ship's name.
      const std::string& getShipName() const ;
      
      /// Access to maximum number of ships.
      const unsigned int& getInitialNumberOfShips() const ;

      /// Access to actual number of ships.
      unsigned int getNumberOfShips() const ;

      /// Access to number of lives.
      const unsigned int& getNumberOfSpawn() const ;
      
      /// True iff it has current player in it.
      /*!
      @deprecated
      */
      bool hasPlayer() const ;
      
      /// Objective of the group
      const Objective& getObjective() const ;
      
      /// Get an AI piloted ship.
      Kernel::Object* getAIShip() const ;
      
      /// Access to all current ships of group
      std::set<Kernel::ObjectReference> getShips() const ;
      
    private:

      /// Group name.
      std::string m_name ;
      
      /// True if it has the player in it.
      bool m_has_player ;
      
      /// Initial number of ships in the group
      unsigned int m_initial_number_of_ships ;

      /// Ship model name.
      std::string m_ship_name ;
      
      /// Objective of the group
      /*!
        @todo We should have a more complex structure with primary objectives,
        secondary etc...
        Difficulty is for AI...
      */
      Objective m_objective ;
      
      /// Number of times the group is created (at least one)
      unsigned int m_number_of_spawn ;
      
    };

  }
}
