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
#ifndef PU_MODEL_CUSTOM_MISSION_H_
#define PU_MODEL_CUSTOM_MISSION_H_

#include <kernel/trait.h>

#include <model/distance.h>
#include <model/duration.h>

namespace ProjetUnivers {
  namespace Model {
  
    /// Represents a basic configurable mission.
    /*!
      # CustomMission
      ## Team
      ### Group
      ### Group
      ## Team
    */
    class CustomMission : public Kernel::Trait
    {
    public:
      
      /// Constructor.
      CustomMission() ;
      
      /// Access to minimal distance of respawn.
      Distance getStartingDistance() const ;
      
      /// Total mission duration.
      Duration getMissionTotalDuration() const ;
      
    private:
      
      /// Minimum distance when respawning a group.
      Distance m_starting_distance ;
      
      /// Duration of the mission.
      Duration m_mission_duration ;
      
      /// Name
      std::string m_name ;
    };
  }
}

#endif /*PU_MODEL_CUSTOM_MISSION_H_*/
