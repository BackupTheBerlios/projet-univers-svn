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
#include <model/model.h>
#include <model/computer.h>
#include <model/targeting_system.h>
#include <artificial_intelligence/implementation/agent.h>
#include <artificial_intelligence/implementation/agent_view_point.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Implementation {
      
      AgentViewPoint::AgentViewPoint(Agent* agent)
      : Kernel::ViewPoint(NULL),
        m_agent(agent)
      {
        InternalMessage("AI","building AgentViewPoint::AgentViewPoint") ;
        update() ;
        InternalMessage("AI","built AgentViewPoint::AgentViewPoint") ;
      }
      
      void AgentViewPoint::update()
      {
        InternalMessage("AI","entering AgentViewPoint::update") ;
        if (! m_agent)
          return ;
        
        Kernel::Object* ship = Model::getControledShip(m_agent->getObject()) ;
        if (!ship)
          return ;
        
        std::set<Model::Computer*> computers = ship->getChildren<Model::Computer>() ;
        if (computers.size() != 1)
          return ;
        Model::Computer* computer = *(computers.begin()) ;
        
        setModel(computer->getMemoryModel()) ;
        InternalMessage("AI","leaving AgentViewPoint::update") ;
      }

      void AgentViewPoint::addVehicle(Vehicle* vehicle)
      {
        m_agent->addVehicle(vehicle) ;
      }
      
      void AgentViewPoint::removeVehicle(Vehicle* vehicle) 
      {
        m_agent->removeVehicle(vehicle) ;
      }
      
      void AgentViewPoint::setTarget(Vehicle* vehicle)
      {
        m_agent->setTarget(vehicle) ;
      }
      
      Kernel::Object* AgentViewPoint::getAgent() const
      {
        return m_agent->getObject() ;
      }
      
      Kernel::Object* AgentViewPoint::getTargetingSystem() const
      {
        if (! m_agent)
          return NULL ;
        return m_agent->getTargetingSystem() ;
      }

      void AgentViewPoint::setVehicle(Vehicle* vehicle)
      {
        m_agent->setVehicle(vehicle) ;
      }
      
      
    }
  }
}
