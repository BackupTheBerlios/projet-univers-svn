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
#include <kernel/log.h>
#include <model/flying_group.h>
#include <model/mission.h>
#include <model/played.h>
#include <model/universe.h>
#include <model/implementation/logic/activated_mission.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {


        RegisterControler(ActivatedMission, 
                          Implementation::ActivatedMission, 
                          LogicSystem) ;

        ActivatedMission::ActivatedMission(Implementation::ActivatedMission* mission,
                                           LogicSystem*                      system)
        : Kernel::Controler<Implementation::ActivatedMission,
                            LogicSystem>(mission,system)
        {
          InternalMessage("Mission","ActivatedMission::ActivatedMission") ;
        }
        
        void ActivatedMission::onInit()
        {
          getTrait<Mission>()->load() ;
          getObject()->getModel()->resetStatistics() ;
        }

        void ActivatedMission::onClose()
        {
          InternalMessage("Mission","Destroying mission content") ;
          std::set<Universe*> universes = getObject()->getChildren<Universe>() ;
          for(std::set<Universe*>::const_iterator child = universes.begin() ; 
              child != universes.end() ;
              ++child)
          {
            (*child)->getObject()->destroyObject() ;
          }
          getObject()->getModel()->printStatistics() ;
        }

        void ActivatedMission::indicateGroupHasNoMoreSpawn(Kernel::Object* group)
        {
          if (group->getTrait<FlyingGroup>()->hasPlayer())
          {
            getObject()->call("quit") ;
          }
        }
        
      }
    }
  }
}

