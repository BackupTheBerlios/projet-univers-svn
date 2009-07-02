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
// ----------------------------------------------------------------------------
//
//
// OpenSteer -- Steering Behaviors for Autonomous Characters
//
// Copyright (c) 2002-2003, Sony Computer Entertainment America
// Original author: Craig Reynolds <craig_reynolds@playstation.sony.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
#include <cstdlib>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/algorithm.h>
#include <artificial_intelligence/implementation/vehicle.h>
#include <artificial_intelligence/implementation/steering_behaviour.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {
      namespace SteeringBehaviour
      {

        float WanderSide = 0 ;
        float WanderUp = 0 ;
        
        Ogre::Vector3 seek(const Vehicle& agent,const Vehicle& target)
        {
          Ogre::Vector3 desiredVelocity = target.getPosition()-agent.getPosition() ;
          agent.normalizeSpeed(desiredVelocity) ;
          return desiredVelocity-agent.getSpeed() ;
        }
  
        /// classify a value relative to the interval between two bounds:
        /*!     
          @returns -1 when below the lower bound
          @returns  0 when between the bounds (inside the interval)
          @returns +1 when above the upper bound
        */
        int intervalComparison(float x, float lowerBound, float upperBound)
        {
            if (x < lowerBound) return -1;
            if (x > upperBound) return +1;
            return 0;
        }
        
        Ogre::Vector3 pursuit(const Vehicle& agent,const Vehicle& target)
        {
          return offsetPursuit(agent,target,Ogre::Vector3(0,0,0)) ;
        }
  
        Ogre::Vector3 offsetPursuit(const Vehicle& agent,
                                    const Vehicle& target,
                                    const Ogre::Vector3& local_space_target_offset)
        {
          
          InternalMessage("AI","agent.getPosition() =" + 
                                      Kernel::toString(agent.getPosition().x) + 
                                "," + Kernel::toString(agent.getPosition().y) + 
                                "," + Kernel::toString(agent.getPosition().z)) ;
          
          InternalMessage("AI","target.getPosition() =" + 
                                      Kernel::toString(target.getPosition().x) + 
                                "," + Kernel::toString(target.getPosition().y) + 
                                "," + Kernel::toString(target.getPosition().z)) ;
          
          Ogre::Vector3 offset = target.getPosition() + 
                                 target.getOrientation()*local_space_target_offset -
                                 agent.getPosition() ;
          
          InternalMessage("AI","offset =" + 
                                      Kernel::toString(offset.x) + 
                                "," + Kernel::toString(offset.y) + 
                                "," + Kernel::toString(offset.z)) ;
          
          // calculate interception time
          std::pair<bool,float> reachable_time = 
            Kernel::Algorithm::calculateInterceptionTime(offset,
                                                         target.getSpeed(),
                                                         agent.getMaxSpeed()) ;
          
          if (! reachable_time.first)
          {
            InternalMessage("AI","offsetPursuit unreachable") ; 
            return Ogre::Vector3::ZERO ;
          }
          else
          {
            InternalMessage("AI","time =" + Kernel::toString(reachable_time.second)) ; 
            
            if (!finite(reachable_time.second))
            {
              reachable_time.second = 0 ;
            }
            
            const Ogre::Vector3 seeking_position = 
              target.predictFuturePosition(reachable_time.second) + 
              target.getOrientation()*local_space_target_offset ;
            
            InternalMessage("AI","seeking_position =" + 
                                        Kernel::toString(seeking_position.x) + 
                                  "," + Kernel::toString(seeking_position.y) + 
                                  "," + Kernel::toString(seeking_position.z)) ;
            
            Ogre::Vector3 desiredVelocity  = seeking_position - agent.getPosition() ;
            agent.normalizeSpeed(desiredVelocity) ;
            
            Ogre::Vector3 result = desiredVelocity-agent.getSpeed() ;
            
            InternalMessage("AI","result =" + 
                                        Kernel::toString(result.x) + 
                                  "," + Kernel::toString(result.y) + 
                                  "," + Kernel::toString(result.z)) ;
            
            return result ;
            
          }
        }
  
        
        Ogre::Vector3 offsetPursuit(const Vehicle& agent,
                                    const Vehicle& target,
                                    const float&   distance)
        {
          
          InternalMessage("AI","agent.getPosition() =" + 
                                      Kernel::toString(agent.getPosition().x) + 
                                "," + Kernel::toString(agent.getPosition().y) + 
                                "," + Kernel::toString(agent.getPosition().z)) ;
          
          InternalMessage("AI","target.getPosition() =" + 
                                      Kernel::toString(target.getPosition().x) + 
                                "," + Kernel::toString(target.getPosition().y) + 
                                "," + Kernel::toString(target.getPosition().z)) ;
          
          Ogre::Vector3 offset = target.getPosition() -
                                 agent.getPosition() ;
          
          InternalMessage("AI","offset =" + 
                                      Kernel::toString(offset.x) + 
                                "," + Kernel::toString(offset.y) + 
                                "," + Kernel::toString(offset.z)) ;
          
          // calculate interception time
          std::pair<bool,float> reachable_time = 
            Kernel::Algorithm::calculateInterceptionTime(offset,
                                                         target.getSpeed(),
                                                         agent.getMaxSpeed()) ;
          
          if (! reachable_time.first)
          {
            InternalMessage("AI","offsetPursuit unreachable") ; 
            agent.normalizeSpeed(offset) ;
            return offset-agent.getSpeed() ;
          }
          else
          {
            InternalMessage("AI","time =" + Kernel::toString(reachable_time.second)) ; 
            
            if (!finite(reachable_time.second))
            {
              reachable_time.second = 0 ;
            }
            
            const Ogre::Vector3 seeking_position = 
              target.predictFuturePosition(reachable_time.second) ;
            
            InternalMessage("AI","seeking_position =" + 
                                        Kernel::toString(seeking_position.x) + 
                                  "," + Kernel::toString(seeking_position.y) + 
                                  "," + Kernel::toString(seeking_position.z)) ;
            
            Ogre::Vector3 desiredVelocity  = seeking_position - agent.getPosition() ;
            
            Ogre::Vector3 delta = desiredVelocity ;
            delta.normalise() ;
            desiredVelocity = desiredVelocity - delta*distance ;
            
            agent.normalizeSpeed(desiredVelocity) ;
            
            Ogre::Vector3 result = desiredVelocity-agent.getSpeed() ;
            
            InternalMessage("AI","result =" + 
                                        Kernel::toString(result.x) + 
                                  "," + Kernel::toString(result.y) + 
                                  "," + Kernel::toString(result.z)) ;
            
            return result ;
            
          }
        }
  
        
        /// Returns a float randomly distributed between 0 and 1
        float frandom01 (void)
        {
            return (((float) rand ()) / ((float) RAND_MAX));
        }
        
        float scalarRandomWalk(const float initial,const float walkspeed,
                               const float min,const float max)
        {
            const float next = initial + (((frandom01() * 2) - 1) * walkspeed);
            if (next < min) return min;
            if (next > max) return max;
            return next;
        }
        
        Ogre::Vector3 wander(const Vehicle& agent)
        {
          // random walk WanderSide and WanderUp between -1 and +1
          const float speed = agent.getSpeed().length() ;
          WanderSide = scalarRandomWalk (WanderSide, speed, -1, +1) ;
          WanderUp   = scalarRandomWalk (WanderUp,   speed, -1, +1) ;
  
          // return a pure lateral steering vector: (+/-Side) + (+/-Up)
          return agent.getSide()*WanderSide + agent.getUp()*WanderUp ;
          
        }
        
        Ogre::Vector3 flee(const Vehicle& agent,const Vehicle& target)
        {
          Ogre::Vector3 desiredVelocity = agent.getPosition() - target.getPosition() ;
          agent.normalizeSpeed(desiredVelocity) ;
          return desiredVelocity-agent.getSpeed() ;
        }
  
        Ogre::Vector3 evade(const Vehicle& agent,const Vehicle& target)
        {
          // a parameter
          const float maxPredictionTime = 2 ;
          
          Ogre::Vector3 offset = target.getPosition()-agent.getPosition() ;
          const float distance = offset.length() ;
          
          // may be equal to zero when target has reached agent 
          const float roughTime = distance / target.getSpeed().length() ;
  
          const float predictionTime = ((roughTime > maxPredictionTime) ?
                                        maxPredictionTime :
                                        roughTime);
      
          const Ogre::Vector3 menace_position = target.predictFuturePosition(predictionTime) ;
          
          Ogre::Vector3 desiredVelocity = agent.getPosition() - menace_position ;
          const float desiredSpeed =  desiredVelocity.normalise() ;
  
          if (desiredSpeed == 0)
          {
            desiredVelocity = agent.getForward() ;
            desiredVelocity.normalise() ;
          }
          
          // we should evade with maximum speed 
          desiredVelocity = desiredVelocity*agent.getMaxSpeed() ;
          agent.normalizeSpeed(desiredVelocity) ;
  
          return desiredVelocity-agent.getSpeed() ;
        }
  
        Ogre::Vector3 separate(const Vehicle& agent,
                               const std::set<Vehicle*>& neighbours,
                               const float simulation_time)
        {
          Ogre::Vector3 result(Ogre::Vector3::ZERO) ;
          
          for(std::set<Vehicle*>::const_iterator neighbour = neighbours.begin() ;
              neighbour != neighbours.end() ;
              ++neighbour)
          {
            // test proximity
            const float sumOfRadii = agent.getRadius() + (*neighbour)->getRadius() ;
            const float minCenterToCenter = sumOfRadii;
  
            Ogre::Vector3 offset = (*neighbour)->predictFuturePosition(simulation_time)-
                                   agent.predictFuturePosition(simulation_time) ;
            const float futureDistance = offset.length() ;
            InternalMessage("AI","SteeringBehaviour::separate offset=" + 
                                        Kernel::toString(offset.x) + 
                                  "," + Kernel::toString(offset.y) + 
                                  "," + Kernel::toString(offset.z)) ;
            
            if (futureDistance < minCenterToCenter)
            {
              result += offset / (futureDistance*futureDistance) ;
            }
            InternalMessage("AI","SteeringBehaviour::futureDistance =" + Kernel::toString(futureDistance)) ;
          }
          InternalMessage("AI","SteeringBehaviour::separate =" + 
                                      Kernel::toString(result.x) + 
                                "," + Kernel::toString(result.y) + 
                                "," + Kernel::toString(result.z)) ;
          return result ;
        }
        
        Ogre::Vector3 obstacleAvoidance(const Vehicle& agent,
                                        const std::set<Vehicle*>& obstacles)
        {
          Ogre::Vector3 result(Ogre::Vector3::ZERO) ;
          
          // 1. distance (and time) to look ahead
          // it depends on the turning rate and speed
          float agent_speed = agent.getSpeed().length() ;
          float radius_of_turn = agent_speed/agent.getTurningRate().valueRadians() ;
          float radius = agent.getRadius() ;
          
          InternalMessage("AI","radius_of_turn=" + Kernel::toString(radius_of_turn)) ;
          InternalMessage("AI","radius=" + Kernel::toString(radius)) ;
          
          
          if (radius > radius_of_turn || agent_speed == 0)
            return result ;
          
          float lookahead_distance = agent.getRadius()+radius_of_turn*sqrt(1-((radius_of_turn-radius)/radius_of_turn)) ;

//          float lookahead_distance = agent.getRadius()+4*agent_speed ;
          float lookahead_time = lookahead_distance/agent_speed ;

          InternalMessage("AI","agent_speed=" + Kernel::toString(agent_speed)) ;
          InternalMessage("AI","lookahead_distance=" + Kernel::toString(lookahead_distance)) ;
          InternalMessage("AI","lookahead_time=" + Kernel::toString(lookahead_time)) ;
          
          for(std::set<Vehicle*>::const_iterator obstacle = obstacles.begin() ;
              obstacle != obstacles.end() ;
              ++obstacle)
          {
          
            // 2. nearest point of obstacle center and direction
            Ogre::Vector3 relative_position = (*obstacle)->getPosition()-agent.getPosition() ;
            Ogre::Vector3 direction = agent.getForward() ;
            Ogre::Vector3 relative_nearest_point = (relative_position.dotProduct(direction))*direction ;
            float collision_distance = (relative_nearest_point - relative_position).length() ;
            float nearest_point_distance = relative_nearest_point.length() ;
            
            if (nearest_point_distance < lookahead_distance && 
                collision_distance < (agent.getRadius()*1.5+(*obstacle)->getRadius()))
            {
              InternalMessage("AI","menace") ;
              
              if (collision_distance == 0)
                result = agent.getSide()*agent.getMaxSpeed() ;
              else
              {
                result = relative_nearest_point - relative_position ;
                result.normalise() ;
                result *= agent.getMaxSpeed() ;
              }

              // in order to get the nearest menace
              lookahead_distance = nearest_point_distance ;
            }
            
          }
          
          InternalMessage("AI","SteeringBehaviour::obstacleAvoidance =" + 
                                      Kernel::toString(result.x) + 
                                "," + Kernel::toString(result.y) + 
                                "," + Kernel::toString(result.z)) ;
          return result ;
        }
        
        Ogre::Vector3 idle(const Vehicle& agent)
        {
          return -agent.getSpeed() ;
        }
      }
    }    
  }
}
