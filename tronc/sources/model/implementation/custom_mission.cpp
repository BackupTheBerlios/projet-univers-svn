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
#include <kernel/object.h>
#include <model/positionned.h>
#include <model/stellar_system.h>
#include <model/universe.h>
#include <model/custom_mission.h>

namespace ProjetUnivers {
  namespace Model {
  
    CustomMission::CustomMission(const std::string& name,
                                 Kernel::Object* player_configuration,
                                 Kernel::Object* main_menu)
    : Mission(name,player_configuration,main_menu)
    {}
      
    Duration CustomMission::getMissionTotalDuration() const
    {
      return m_mission_duration ;
    }

    void CustomMission::load()
    {
      // setup the system 
      Kernel::Object* universe = getObject()->createObject() ;
      universe->addTrait(new Universe()) ;
      universe->addTrait(new Positionned()) ;
      
      m_system = universe->createObject() ;
      m_system->addTrait(new StellarSystem()) ;
      m_system->addTrait(new Positionned()) ;
    }
    
  }
}
