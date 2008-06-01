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
#ifndef PU_AI_IMPLEMENTATION_AGENT_VIEW_POINT_H_
#define PU_AI_IMPLEMENTATION_AGENT_VIEW_POINT_H_

#include <kernel/view_point.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Implementation {

      class Vehicle ;
      class Agent ;
      
      /// A particular view point on an agent's detection data.
      class AgentViewPoint : public Kernel::ViewPoint
      {
      public:
      
        /// Constructor.
        /*!
          @pre agent must be a AutonomousAgent.
        */
        AgentViewPoint(Agent* agent) ;
        
        /// When system may change computer or other things.
        void update() ;

        /// Add a vehicle to the set of agent's other vehicles. 
        void addVehicle(Vehicle*) ;

        /// Remove a vehicle to the set of agent's other vehicles. 
        void removeVehicle(Vehicle*) ;
        
        /// Change the current target.
        void setTarget(Vehicle*) ;
        
        /// Set the agent vehicle.
        void setVehicle(Vehicle*) ;
        
        /// Access to agent object.
        Kernel::Object* getAgent() const ;
        
        /// Access to the targeting system.
        Kernel::Object* getTargetingSystem() const ;
        
      private:
        
        Agent* m_agent ;
      };
      
    }
  }
}

#endif /*PU_AI_IMPLEMENTATION_AGENT_VIEW_POINT_H_*/
