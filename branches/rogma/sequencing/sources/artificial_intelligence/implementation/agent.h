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
#ifndef PU_AI_IMPLEMENTATION_AGENT_H_
#define PU_AI_IMPLEMENTATION_AGENT_H_

#include <kernel/controler.h>
#include <kernel/percentage.h>

#include <model/objective.h>
#include <artificial_intelligence/implementation/vehicle.h>
#include <artificial_intelligence/implementation/ai_system.h>
#include <artificial_intelligence/implementation/autonomous_agent.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Test
    {
      class TestModelControler ;
    }

    namespace Implementation
    {

      class Behaviour ;
      class AgentViewPoint ;
      class AgentVehicleViewPoint ;

      /// An autonomous agent controler
      class Agent : public Kernel::Controler<AutonomousAgent,AISystem>
      {
      public:

        /// Constructor.
        Agent(AutonomousAgent*,AISystem*) ;

        /// Build the associated vehicle and behaviors.
        virtual void onInit() ;

        virtual void onClose() ;

        virtual void onUpdate() ;

        /// Simulate agent during a certain duration.
        virtual void simulate(const float& seconds) ;

        /// Add a vehicle to the set of other vehicles.
        void addVehicle(Vehicle*) ;

        /// Remove a vehicle to the set of other vehicles.
        void removeVehicle(Vehicle*) ;

        /// Change the current target.
        void setTarget(Vehicle* vehicle) ;

        /// Set the agent vehicle.
        void setVehicle(Vehicle*) ;

        /// Access to vehicles.
        const std::set<Vehicle*>& getVehicles() const ;

        /// Access to current target.
        Vehicle* getTarget() const ;

        /// Access to agent vehicle.
        Vehicle* getVehicle() const ;

        /// Access to the targeting system.
        Kernel::Object* getTargetingSystem() const ;

      private:

        /// Agent's vehicle
        Vehicle*               m_vehicle ;

        /// Other vehicles
        std::set<Vehicle*>     m_other_vehicles ;

        /// Current target.
        Vehicle*               m_target ;

        /// A view point for detection data
        AgentViewPoint*        m_view_point ;

        /// A view point for its vehicle
        AgentVehicleViewPoint* m_vehicle_view_point ;

        bool m_added_view ;

        /// Execute the given objective.
        /*!
          Either send direct command to object or calculate m_steering.
        */
        void applyObjective(const Model::Objective& objective,
                            Kernel::Object* agent,
                            const float& seconds) ;

        /// Calculate the steering commands.
        Ogre::Vector3 calculateSteeringCommands(const float& seconds_since_last_frame) ;

        /// Calculate maximum steering "forces".
        /*!
          Determine how much we have turn, advanced since last frame and
          deduce max turning rate.
          Assume that yaw and pitch turning rates is quite constant (which is
          the case due to physic representation)
        */
        void calibrateSteering(const float& seconds_since_last_frame) ;

        /// Steering to apply this turn.
        Ogre::Vector3      m_steering ;

        /// Agent speed at previous frame.
        /*!
          For steering calibration purpose
        */
        Ogre::Vector3      m_previous_speed ;

        /// Agent orientation at previous frame.
        Ogre::Quaternion   m_previous_orientation ;

        /// Commands send previous frame
        Kernel::Percentage m_previous_X ;
        Kernel::Percentage m_previous_Y ;

        /// Difference of throttle value sent previous frame
        Kernel::Percentage m_delta_throttle ;

        /// Deduced maximum steering.
        Ogre::Vector3      m_max_steering ;

        /// Maximum turning rate in radian per seconds per unit of turning command
        Ogre::Degree       m_max_steering_X ;
        Ogre::Degree       m_max_steering_Y ;

        /// Maximum acceleration in meter per square seconds per unit of throttle
        float              m_max_steering_speed ;

        friend class ::ProjetUnivers::ArtificialIntelligence::Test::TestModelControler ;
      };

    }
  }
}

#endif /*PU_AI_IMPLEMENTATION_AGENT_H_*/
