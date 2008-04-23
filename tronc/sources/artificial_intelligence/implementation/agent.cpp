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
#include <OgreStringConverter.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <model/model.h>
#include <model/physical_world.h>
#include <model/with_objectives.h>
#include <model/targeting_system.h>
#include <model/shootable.h>
#include <artificial_intelligence/implementation/behaviour.h>
#include <artificial_intelligence/implementation/steering_behaviour.h>
#include <artificial_intelligence/implementation/agent_vehicle.h>
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
        m_steering(0,0,0),
        m_previous_speed(0,0,0),
        m_previous_X(0),
        m_previous_Y(0),
        m_delta_throttle(0),
        m_max_steering(1,1,1)
      {}

      void Agent::onInit()
      {
        InternalMessage("AI","building Agent") ;
        m_view_point.reset(new AgentViewPoint(this)) ;
        m_view_point->init() ;
        getObject()->getModel()->addManualView(new AgentVehicle(
            Model::getControledShip(getObject())->getTrait<Model::PhysicalObject>(),
            m_view_point.get())) ;
        
        InternalMessage("AI","built Agent") ;
      }
        
      void Agent::onClose()
      {
        m_view_point.reset(NULL) ;
      }

      void Agent::onUpdate()
      {
        // last updated elementary trait will tell us what to update
        const Kernel::TypeIdentifier& latest = getTrait()->getLatestUpdatedTrait() ;
        
        if (latest == getClassTypeIdentifier(Model::WithObjectives))
        {
          // objectives have changed, we must recalculate the behaviours ?
        }
        else
        {
          m_view_point->update() ;
        }
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
            getTargetingSystem()->getTrait<Model::TargetingSystem>()->selectNearestEnemy() ;
          }

          // if enemy selected pursuit it
          if (m_target)
          {
            m_steering += SteeringBehaviour::pursuit(*m_vehicle,*m_target) ;
          }
          
          // if in range shoot
          if (target && target->getTrait<Model::Shootable>())
          {
            getObject()->call("fire") ;
          }
          break ;
        }
        case Model::Objective::Wait:
        {
          break ;
        }
        case Model::Objective::Patrol:
        {
          // apply wander behaviour + containment
          m_steering = SteeringBehaviour::wander(*m_vehicle) ;
          break ;
        }
        }
      }
      
      void Agent::simulate(const float& seconds)
      {
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
        
        // calculate avoidance
        Ogre::Vector3 separate_steering = SteeringBehaviour::separate(*m_vehicle,m_other_vehicles,seconds) ;
        
        if (separate_steering != Ogre::Vector3::ZERO)
        {
          m_steering = separate_steering ;
          InternalMessage("AI","separating") ;
        }

        m_steering = m_previous_orientation.Inverse()*m_steering ;
        
        // get the steering behaviour and apply commands
        InternalMessage("AI","m_steering=" + Ogre::StringConverter::toString(m_steering)) ;

        // Steering calibration
        
        // previous steering in m.s-2
        Ogre::Vector3 real_steering = m_vehicle->getSpeed()-m_previous_speed ; 
        InternalMessage("AI","position=" + Ogre::StringConverter::toString(m_vehicle->getPosition())) ;
        InternalMessage("AI","orientation=" + Ogre::StringConverter::toString(m_vehicle->getOrientation())) ;
        InternalMessage("AI","speed=" + Ogre::StringConverter::toString(m_vehicle->getSpeed())) ;
        InternalMessage("AI","previous speed=" + Ogre::StringConverter::toString(m_previous_speed)) ;
        
        real_steering = m_previous_orientation.Inverse()*real_steering ;
        
        InternalMessage("AI","m_max_steering=" + Ogre::StringConverter::toString(m_max_steering)) ;
        InternalMessage("AI","real_steering=" + Ogre::StringConverter::toString(real_steering)) ;

        InternalMessage("AI","previous Y=" + Kernel::toString(float(m_previous_Y))) ;
        InternalMessage("AI","previous X=" + Kernel::toString(float(m_previous_X))) ;
        InternalMessage("AI","previous thottle=" + Kernel::toString(float(m_delta_throttle))) ;
        
        if (m_previous_X != 0 && real_steering.x != 0)
          m_max_steering.x = fabs(real_steering.x/float(m_previous_X)) ;
        
        if (m_previous_Y != 0 && real_steering.y != 0)
          m_max_steering.y = fabs(real_steering.y/float(m_previous_Y)) ;
        
        if (m_delta_throttle != 0 && real_steering.z != 0)
          m_max_steering.z = fabs(real_steering.z/float(m_delta_throttle)) ;

        InternalMessage("AI","m_max_steering=" + Ogre::StringConverter::toString(m_max_steering)) ;
        
        m_previous_X = -m_steering.x/m_max_steering.x ;
        m_previous_Y = m_steering.y/m_max_steering.y ;
        m_delta_throttle = m_steering.z/m_max_steering.z ;
        m_previous_speed = m_vehicle->getSpeed() ;
        m_previous_orientation = m_vehicle->getOrientation() ;
        
        InternalMessage("AI","applyied Y=" + Kernel::toString(float(m_previous_Y))) ;
        InternalMessage("AI","applyied X=" + Kernel::toString(float(m_previous_X))) ;
        InternalMessage("AI","applyied thottle=" + Kernel::toString(float(m_delta_throttle))) ;
        
        getObject()->call("set_axis_Y",m_previous_Y) ;
        getObject()->call("set_axis_X",m_previous_X) ;
        getObject()->call("Change Throttle",m_delta_throttle) ;
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
