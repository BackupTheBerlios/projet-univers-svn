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
#ifndef PU_IMPLEMENTATION_STEERING_BEHAVIOUR_H_
#define PU_IMPLEMENTATION_STEERING_BEHAVIOUR_H_

#include <set>
#include <OgreVector3.h>
#include <artificial_intelligence/implementation/behaviour.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Implementation {
    
      class Vehicle ;
      
      /// Abstract class for all steering behaviours.
      class SteeringBehaviour : public Behaviour
      {
      public:
        
        /// Apply the behaviour.
        virtual void apply(Kernel::Object*) ;

        /*!
          @name Utility functions for steering behaviour
          
          adapted from code by OpenSteer @see http://opensteer.sourceforge.net/
        */
        // @{
          
          /// Calculate steering for seeking target.
          static Ogre::Vector3 seek(const Vehicle& agent,const Vehicle& target) ;

          /// Calculate steering for pursuing target.
          /*!
            @warning when pursuing a target, the agent will ram into it if 
            possible
          */
          static Ogre::Vector3 pursuit(const Vehicle& agent,const Vehicle& target) ;
          
          /// Calculate steering for fleeing target.
          static Ogre::Vector3 flee(const Vehicle& agent,const Vehicle& target) ;
          
          /// Calculate steering for evading target.
          static Ogre::Vector3 evade(const Vehicle& agent,const Vehicle& target) ;
          
          /// Calculate steering for offset pursuing target.
          /*
            The targetted point is a point placed at an offset in the target space.
            Usefull for "docking", moving to a particular point of a sized target, 
            heading for "behind" a target...  
          */
          static Ogre::Vector3 offsetPursuit(const Vehicle& agent,
                                             const Vehicle& target,
                                             const Ogre::Vector3& local_space_target_offset) ;

          /// Calculate steering for wandering behaviour.
          static Ogre::Vector3 wander(const Vehicle& agent) ;
          
          /// Calculate steering for separating @c agent from @c neighbours.
          /*!
            @todo make it work ...
          */
          static Ogre::Vector3 separate(const Vehicle& agent, 
                                        const std::set<Vehicle*>& neighbours,
                                        const float simulation_time) ;
          
        // @}
        
        /// Abstract classes have virtual destructors.
        virtual ~SteeringBehaviour() ;

      protected:
        
        /// Abstract classes have protected constructors.
        SteeringBehaviour() ;
        
        // Wander behavior
        static float WanderSide ;
        static float WanderUp ;
      };
    }    
  }
}

#endif //PU_IMPLEMENTATION_STEERING_BEHAVIOUR_H_
