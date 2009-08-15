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
#include <artificial_intelligence/implementation/steering_behaviour.h>
#include <artificial_intelligence/implementation/agent.h>
#include <artificial_intelligence/implementation/with_vehicle_controler.h>
#include <model/has_in_line_of_sight.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {

      RegisterControler(Agent,AutonomousAgent,AISystem) ;

      void Agent::onInit()
      {
        InternalMessage("AI","building Agent") ;

        m_target = NULL ;
        m_steering = Ogre::Vector3(0,0,0) ;
        m_previous_speed = Ogre::Vector3(0,0,0) ;
        m_previous_X = 0 ;
        m_previous_Y = 0 ;
        m_delta_throttle = 0 ;
        m_max_steering= Ogre::Vector3(1,1,1) ;
        m_max_steering_X = 1 ;
        m_max_steering_Y = 1 ;
        m_max_steering_speed = 0 ;

        InternalMessage("AI","built Agent") ;
      }

      void Agent::setTarget(WithVehicleControler* vehicle)
      {
        m_target = vehicle ;
      }

      Vehicle* Agent::getTarget() const
      {
        return m_target?m_target->getVehicle():NULL ;
      }

      Vehicle* Agent::getVehicle() const
      {
        /*
          lookup

          @todo We should find the vehicle really piloted by the agent
        */
        WithVehicleControler* vehicle_controler = getAncestorControler<WithVehicleControler>() ;
        if (vehicle_controler)
        {
          return vehicle_controler->getVehicle() ;
        }
        return NULL ;
      }

      void Agent::simulate(const float& seconds)
      {
        if (seconds == 0)
          return ;

        // re-init the steering behaviour
        m_steering = Ogre::Vector3::ZERO ;

        applyObjectives(seconds) ;

        applyCommands(calculateSteeringCommands(seconds)) ;
      }

      void Agent::applyObjectives(const float& seconds)
      {
        const std::set<Model::Objective>& objectives =
          getObject()->getTrait<Model::WithObjectives>()->getObjectives() ;

        for(std::set<Model::Objective>::const_iterator objective = objectives.begin() ;
            objective != objectives.end() ;
            ++objective)
        {
          applyObjective(*objective,getObject(),seconds) ;
        }
      }

      bool Agent::isTargetedByTarget() const
      {
        if (!m_target)
          return false ;

        Kernel::Object* ship = Model::getControledShip(getObject()) ;

        m_target->getChild<Model::TargetingSystem>() ;

        return false ;
      }

      void Agent::applyObjective(const Model::Objective& objective,
                                 Kernel::Object*         agent,
                                 const float&            seconds)
      {
        switch(objective.getKind())
        {
          case Model::Objective::AttackAllEnemies:
          {
            // if no enemy selected select one
            if (!m_target)
            {
              InternalMessage("Agent","selecting new enemy") ;
              getObject()->call(Model::TargetingSystem::SelectNearestEnemy) ;
            }

            // if enemy selected pursuit it
            if (m_target)
            {
              m_steering += SteeringBehaviour::offsetPursuit(*getVehicle(),*getTarget(),getTarget()->getRadius()*2) ;
            }
            else
            {
              m_steering += SteeringBehaviour::idle(*getVehicle()) ;
            }

            // if in range shoot
            if (m_target && isShootable(m_target->getObject()))
            {
              InternalMessage("Agent","fire") ;
              getObject()->call("fire") ;
            }
            break ;
          }
          case Model::Objective::Wait:
          {
            m_steering = SteeringBehaviour::idle(*getVehicle()) ;
            break ;
          }
          case Model::Objective::Patrol:
          {
            // apply wander behaviour + @todo containment
            m_steering = SteeringBehaviour::wander(*getVehicle()) ;
            break ;
          }
          case Model::Objective::GoTo:
          {
            Kernel::ObjectReference destination = objective.getDestination() ;

            /*
              we need to build a vehicle from the destination : its the relative
              position of destination from the PhysicalWorld parent of agent
            */
  //          m_steering = SteeringBehaviour::seek(*getVehicle(),) ;

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
          = getVehicle()->getOrientation().Inverse()*(getVehicle()->getSpeed() + m_steering) ;

        InternalMessage("Agent","aim_speed_local_space=" + Ogre::StringConverter::toString(aim_speed_local_space)) ;

        Ogre::Quaternion rotation = Ogre::Vector3::UNIT_Z.getRotationTo(aim_speed_local_space) ;
        rotation.normalise() ;

        Ogre::Vector3 local_aim_direction(aim_speed_local_space) ;
        local_aim_direction.normalise() ;

        Kernel::Percentage X ;
        Kernel::Percentage Y ;
        Kernel::Percentage throttle ;

        // if nearly full back
        if (local_aim_direction.directionEquals(Ogre::Vector3::UNIT_Z,Ogre::Degree(5)))
        {
          X = float(1.0) ;
        }
        else
        {
          InternalMessage("Agent","rotation yaw=" + Kernel::toString(rotation.getYaw().valueDegrees())) ;
          InternalMessage("Agent","rotation pitch=" + Kernel::toString(rotation.getPitch().valueDegrees())) ;

          InternalMessage("Agent","divider yaw=" + Kernel::toString((m_max_steering_X*seconds_since_last_frame).valueDegrees())) ;

          // x part
          X =float(rotation.getYaw().valueDegrees()/
                   fabs((m_max_steering_X*seconds_since_last_frame).valueDegrees())) ;

          // Y part
          Y = float(rotation.getPitch().valueDegrees()/
                    fabs((m_max_steering_Y*seconds_since_last_frame).valueDegrees())) ;
        }
        // throttle part
        float delta_speed = aim_speed_local_space.length()-getVehicle()->getSpeed().length() ;

        throttle = delta_speed/(m_max_steering_speed*seconds_since_last_frame) ;


        return Ogre::Vector3(int(X),int(Y),int(throttle)) ;
      }

      void Agent::calibrateSteering(const float& seconds_since_last_frame)
      {
        // previous_orientation then delta == current_orientation
        Ogre::Quaternion delta = m_previous_orientation.zAxis().getRotationTo(getVehicle()->getOrientation().zAxis()) ;
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

        getVehicle()->setTurningRate(std::max(m_max_steering_X,m_max_steering_Y)) ;

        //
        float delta_speed = m_previous_speed.length()-getVehicle()->getSpeed().length() ;

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

      void Agent::applyCommands(const Ogre::Vector3& commands)
      {
        m_previous_X = int(commands.x) ;
        m_previous_Y = int(commands.y) ;
        m_delta_throttle = int(commands.z) ;
        m_previous_speed = getVehicle()->getSpeed() ;
        m_previous_orientation = getVehicle()->getOrientation() ;

        if(m_target)
        {
          InternalMessage("Agent","target position=" + Ogre::StringConverter::toString(getTarget()->getPosition())) ;
        }

        InternalMessage("Agent","agent position=" + Ogre::StringConverter::toString(getVehicle()->getPosition())) ;

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

      Ogre::Vector3 Agent::getDesiredSpeed() const
      {
        Ogre::Vector3 desired_speed = m_steering + getVehicle()->getSpeed() ;
        desired_speed.normalise() ;
        return desired_speed ;
      }

      bool Agent::isShootable(Kernel::Object* target) const
      {
        return Kernel::Relation::areLinked<Model::HasInLineOfSight>(Model::getControledShip(getObject()),target) ;
      }
    }
  }
}
