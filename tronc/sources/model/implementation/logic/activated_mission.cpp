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
#include <model/mission.h>
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
        {}
        
        void ActivatedMission::onInit()
        {
          getObject()->getTrait<Mission>()->load() ;
        }

        void ActivatedMission::onClose()
        {
          InternalMessage("Model","Destroying mission content") ;
          const std::set<Kernel::Object*>& children = getTrait()->getObject()
                                                      ->getChildren() ;
          for(std::set<Kernel::Object*>::const_iterator child = children.begin() ; 
              child != children.end() ;
              ++child)
          {
            getControlerSet()->addObjectToDestroy(*child) ;
          }
        }

      }
    }
  }
}

