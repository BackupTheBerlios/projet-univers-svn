/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#ifndef PU_MODEL_MISSION_H_
#define PU_MODEL_MISSION_H_

#include <kernel/object_reference.h>
#include <kernel/trait.h>
#include <model/distance.h>

namespace ProjetUnivers {
  namespace Model {
  
    /// Represents a basic loadable mission.
    class Mission : public Kernel::Trait
    {
    public:
      
      /// Constructor.
      Mission(const std::string& name,
              Kernel::Object* player_configuration,
              Kernel::Object* main_menu) ;

      /// Set the starting distance.
      void setStartingDistance(const Distance&) ;
      
      /// Load the misison.
      virtual void load() ;
      
      /// Access to minimal distance of respawn.
      Distance getStartingDistance() const ;
      
      /// Access to system where we play.
      Kernel::Object* getSystem() const ;

      /// Access to the player configuration.
      Kernel::Object* getPlayerConfiguration() const ;
      
      
    protected:
      
      /// Name
      std::string m_name ;
      
      Kernel::ObjectReference m_player_configuration ;
      Kernel::ObjectReference m_main_menu ;

      /// The system in which we play
      Kernel::ObjectReference m_system ;

      /// Minimum distance when respawning a group.
      Distance m_starting_distance ;
      
    };
  }
}

#endif /*PU_MODEL_MISSION_H_*/
