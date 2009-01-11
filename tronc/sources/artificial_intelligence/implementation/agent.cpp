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
#include <algorithm>
#include <OgreStringConverter.h>
#include <kernel/command_delegator.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <model/model.h>
#include <model/physical_world.h>
#include <model/with_objectives.h>
#include <model/targeting_system.h>
#include <model/shootable.h>
#include <artificial_intelligence/implementation/steering_behaviour.h>
#include <artificial_intelligence/implementation/agent_vehicle.h>
#include <artificial_intelligence/implementation/agent_vehicle_view_point.h>
#include <artificial_intelligence/implementation/agent_view_point.h>
#include <artificial_intelligence/implementation/agent.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Implementation {

      RegisterControler(Agent,AutonomousAgent,AISystem) ;
      
      Agent::Agent(AutonomousAgent* agent,AISystem* system)
      : Kernel::Controler<AutonomousAgent,AISystem>(agent,system),
        m_vehicle(NULL),
        m_target(NULL),
        m_view_point(NULL),
        m_vehicle_view_point(NULL),
        m_added_view(false),
        m_steering(0,0,0),
        m_previous_speed(0,0,0),
        m_previous_X(0),
        m_previous_Y(0),
        m_delta_throttle(0),
        m_max_steering(1,1,1),
        m_max_steering_X(1),
        m_max_steering_Y(1),
        m_max_steering_speed(0)
      {}

      void Agent::onInit()
      {
        InternalMessage("AI","building Agent") ;
        m_view_point = new AgentViewPoint(this) ;
        m_view_point->init() ;
        m_vehicle_view_point = new AgentVehicleViewPoint(this) ;
        m_vehicle_view_point->init() ;
        
        Kernel::Object* ship = Model::getControledShip(getObject()) ;
        if (ship)
        {
          getObject()->getModel()->addManualView(new AgentVehicle(
              ship->getTrait<Model::PhysicalObject>(),
              m_vehicle_view_point)) ;
          m_added_view = true ;
        }
        
        InternalMessage("AI","built Agent") ;
      }
        
      void Agent::onClose()
      {
//        m_view_point->close() ;
//        m_vehicle_view_point->close() ;
        m_view_point= NULL ;
        m_vehicle_view_point = NULL ;
      }

      void Agent::onUpdate()
      {
        // last updated elementary trait will tell us what to update
        const Kernel::TypeIdentifier& latest = getTrait()->getLatestUpdatedTrait() ;
        
        if (latest == getClassTypeIdentifier(Model::WithObjectives))
        {
          // objectives have changed, we must recalculate the behaviours ?
        }
        else if (latest == getClassTypeIdentifier(Kernel::CommandDelegator))
        {
          Kernel::Object* ship = Model::getControledShip(getObject()) ;
          if (ship && ! m_added_view)
          {
            getObject()->getModel()->addManualView(new AgentVehicle(
                ship->getTrait<Model::PhysicalObject>(),
                m_vehicle_view_point)) ;
            m_added_view = true ;
          }
          
        }
        m_view_point->update() ;
      }

      void Agent::setTarget(Vehicle* vehicle)
      {
        m_target = vehicle ;
      }
      
      void Agent::addVehicle(Vehicle* vehicle)
      {
        m_other_vehicles.insert(vehicle) ;
      }
      
      void Agent::removeVehicle(Vehicle* vehicle) 
      {
        m_other_vehicles.erase(vehicle) ;
        
        if (m_target == vehicle)
          m_target = NULL ;
      }
      
      const std::set<Vehicle*>& Agent::getVehicles() const
      {
        return m_other_vehicles ;
      }
      
      Vehicle* Agent::getTarget() const
      {
        return m_target ;
      }

      void Agent::setVehicle(Vehicle* vehicle)
      {
        m_vehicle = vehicle ;
      }
      
      Vehicle* Agent::getVehicle() const
      {
        return m_vehicle ;
      }

      void Agent::applyObjective(
          const Model::Objective& objective,
          Kernel::Object*         agent, 
          const float&            seconds)
      {
        switch(objective.getKind())
        {
          case Model::Objective::AttackAllEnemies:
          { 
            Kernel::Object* target 
              = getTargetingSystem()->getTrait<Model::TargetingSystem>()->getTarget() ;
  
            // if no enemy selected select one
            if (!target)
            {
              InternalMessage("Agent","selecting new enemy") ;
              getTargetingSystem()->getTrait<Model::TargetingSystem>()->selectNearestEnemy() ;
            }
  
            // if enemy selected pursuit it
            if (m_target)
            {
              m_steering += SteeringBehaviour::offsetPursuit(*m_vehicle,*m_target,m_target->getRadius()*2) ;
            }
            else
            {
              m_steering += SteeringBehaviour::idle(*m_vehicle) ;
            }
            
            // if in range shoot
            if (target && target->getTrait<Model::Shootable>())
            {
              InternalMessage("Agent","fire") ;
              getObject()->call("fire") ;
            }
            break ;
          }
          case Model::Objective::Wait:
          {
            m_steering = SteeringBehaviour::idle(*m_vehicle) ;
            break ;
          }
          case Model::Objective::Patrol:
          {
            // apply wander behaviour + @todo containment 
            m_steering = SteeringBehaviour::wander(*m_vehicle) ;
            break ;
          }
          case Model::Objective::GoTo:
          {
            Kernel::ObjectReference destination = objective.getDestination() ;
            
            /*
              we need to build a vehicle from the destination : its the relative 
              position of destination from the PhysicalWorld parent of agent 
            */
  //          m_steering = SteeringBehaviour::seek(*m_vehicle,) ;
            
          }
        }
      }

      Ogre::Vector3 Agent::calculateSteeringCommands(const float& seconds_since_last_frame)
      {
        InternalMessage("Agent","m_steering=" + Ogre::StringConverter::toString(m_steering)) ;
        InternalMessage("Agent","seconds_since_last_frame=" + Kernel::toString(seconds_since_last_frame)) ;
        
        // calibration : calculate previous steering 
        calibrateSteering(seconds_since_last_frame) ;
        
        // angle between front and desired velocity
        Ogre::Vector3 aim_speed_local_space 
          = m_vehicle->getOrientation().Inverse()*(m_vehicle->getSpeed() + m_steering) ;
        
        InternalMessage("Agent","aim_speed_local_space=" + Ogre::StringConverter::toString(aim_speed_local_space)) ;
        
        Ogre::Quaternion rotation = Ogre::Vector3::UNIT_Z.getRotationTo(aim_speed_local_space) ;
        rotation.normalise() ;
        
        InternalMessage("Agent","rotation yaw=" + Kernel::toString(rotation.getYaw().valueDegrees())) ;
        InternalMessage("Agent","rotation pitch=" + Kernel::toString(rotation.getPitch().valueDegrees())) ;

        InternalMessage("Agent","divider yaw=" + Kernel::toString((m_max_steering_X*seconds_since_last_frame).valueDegrees())) ;
        
        // x part 
        Kernel::Percentage X = 
          float(rotation.getYaw().valueDegrees()/
              fabs((m_max_steering_X*seconds_since_last_frame).valueDegrees())) ;
        
        // Y part
        Kernel::Percentage Y = 
          float(rotation.getPitch().valueDegrees()/
              fabs((m_max_steering_Y*seconds_since_last_frame).valueDegrees())) ;
        
        // throttle part
        float delta_speed = aim_speed_local_space.length()-m_vehicle->getSpeed().length() ;
        
        Kernel::Percentage throttle = 
          delta_speed / (m_max_steering_speed*seconds_since_last_frame) ;
        
        /// @todo : inverse Y and throttle
        return Ogre::Vector3(-int(X),int(Y),int(throttle)) ;
      }

      void Agent::calibrateSteering(const float& seconds_since_last_frame)
      {
        // previous_orientation then delta == current_orientation
//        Ogre::Quaternion delta = m_vehicle->getOrientation()*(m_previous_orientation.Inverse()) ; 
        
        Ogre::Quaternion delta = m_previous_orientation.zAxis().getRotationTo(m_vehicle->getOrientation().zAxis()) ;
        delta.normalise() ;
        
        InternalMessage("Agent","calibrateSteering::delta=" + Ogre::StringConverter::toString(delta)) ;
        
        InternalMessage("Agent","calibrateSteering::delta yaw=" + Kernel::toString(delta.getYaw().valueDegrees())) ;
        InternalMessage("Agent","calibrateSteering::delta pitch=" + Kernel::toString(delta.getPitch().valueDegrees())) ;

        if (int(m_previous_X) != 0)
        {
          m_max_steering_X = (delta.getYaw()/float(m_previous_X))/seconds_since_last_frame ;
        }
        
        if (int(m_previous_Y) != 0)
        {
          m_max_steering_Y = (delta.getPitch()/float(m_previous_Y))/seconds_since_last_frame ;
        }

        if (m_max_steering_X.valueRadians() == 0)
          m_max_steering_X = Ogre::Degree(1) ;
          
        if (m_max_steering_Y.valueRadians() == 0)
          m_max_steering_Y = Ogre::Degree(1) ;
        
        m_vehicle->setTurningRate(std::max(m_max_steering_X,m_max_steering_Y)) ;
        
        // 
        float delta_speed = m_previous_speed.length()-m_vehicle->getSpeed().length() ;
        
        if(int(m_delta_throttle) != 0)
        {
          m_max_steering_speed = fabs((delta_speed/float(m_delta_throttle))/seconds_since_last_frame) ;
        }
        
        if (m_max_steering_speed == 0 || !finite(m_max_steering_speed))
          m_max_steering_speed = 1 ;
        
        InternalMessage("Agent","calibration m_max_steering_X=" + Kernel::toString(m_max_steering_X.valueDegrees())) ;
        InternalMessage("Agent","calibration m_max_steering_Y=" + Kernel::toString(m_max_steering_Y.valueDegrees())) ;
        InternalMessage("Agent","calibration m_max_steering_speed=" + Kernel::toString(m_max_steering_speed)) ;
      }
      
      void Agent::simulate(const float& seconds)
      {
        if (seconds == 0)
          return ;
        
        // re-init the steering behaviour
        m_steering = Ogre::Vector3::ZERO ;
        
        const std::set<Model::Objective>& objectives = 
          getObject()->getTrait<Model::WithObjectives>()->getObjectives() ;
        
        for(std::set<Model::Objective>::const_iterator objective = objectives.begin() ; 
            objective != objectives.end() ;
            ++objective)
        {
          applyObjective(*objective,getObject(),seconds) ;
        }

        Ogre::Vector3 commands = calculateSteeringCommands(seconds) ;
        
        m_previous_X = int(commands.x) ;
        m_previous_Y = int(commands.y) ;
        m_delta_throttle = int(commands.z) ;
        m_previous_speed = m_vehicle->getSpeed() ;
        m_previous_orientation = m_vehicle->getOrientation() ;

        if(m_target)
        {
          InternalMessage("Agent","target position=" + Ogre::StringConverter::toString(m_target->getPosition())) ;
        }

        InternalMessage("Agent","agent position=" + Ogre::StringConverter::toString(m_vehicle->getPosition())) ;
        
        InternalMessage("Agent","applyied X=" + Kernel::toString(float(m_previous_X))) ;
        InternalMessage("Agent","applyied Y=" + Kernel::toString(float(m_previous_Y))) ;
        InternalMessage("Agent","applyied thottle=" + Kernel::toString(float(m_delta_throttle))) ;
        
        getObject()->call("Yaw",int(m_previous_X)) ;
        getObject()->call("Pitch",int(m_previous_Y)) ;
        getObject()->call("Change Throttle",int(m_delta_throttle)) ;
      }

      Kernel::Object* Agent::getTargetingSystem() const
      {
        Kernel::Object* ship = Model::getControledShip(getObject()) ;
        if (!ship)
          return NULL ;
        
        std::set<Model::TargetingSystem*> systems = ship->getChildren<Model::TargetingSystem>() ;
        if (systems.size() != 1)
          return NULL ;
        return (*(systems.begin()))->getObject() ;
      }
      
    }
  }
}
