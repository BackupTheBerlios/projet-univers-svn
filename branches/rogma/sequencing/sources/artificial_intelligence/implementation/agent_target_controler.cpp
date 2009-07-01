/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <model/model.h>
#include <model/detection_data.h>
#include <artificial_intelligence/implementation/agent.h>
#include <artificial_intelligence/implementation/with_vehicle.h>
#include <artificial_intelligence/implementation/with_vehicle_controler.h>

#include <artificial_intelligence/implementation/agent_target_controler.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {

      RegisterRelationControler(AgentTargetControler,AgentTarget,AISystem) ;

      void AgentTargetControler::onInit()
      {
        getAgent()->setTarget(getTarget()) ;
      }

      void AgentTargetControler::onClose()
      {
        getAgent()->setTarget(NULL) ;
      }

      Agent* AgentTargetControler::getAgent() const
      {
        Kernel::Object* ship = Model::getShip(getObjectFrom()) ;
        if (ship)
        {
          // @todo : find a better way (add a relation Pilot)
          std::set<AutonomousAgent*> agents = ship->getChildren<AutonomousAgent>() ;
          if (agents.empty())
          {
            ErrorMessage("AgentTargetControler::getAgent()") ;
            return NULL ;
          }
          return (*agents.begin())->getControler<Agent>(getControlerSet()) ;
        }
        ErrorMessage("AgentTargetControler::getAgent()") ;
        return NULL ;
      }

      Vehicle* AgentTargetControler::getTarget() const
      {
        Kernel::Object* detected = getObjectTo()->getTrait<Model::DetectionData>()->m_detected ;
        WithVehicle* with_vehicle = detected->getTrait<WithVehicle>() ;
        if (!with_vehicle)
        {
          ErrorMessage("AgentTargetControler::getTarget()") ;
          return NULL ;
        }

        return with_vehicle->getControler<WithVehicleControler>(getControlerSet())->getVehicle() ;
      }


    }
  }
}
