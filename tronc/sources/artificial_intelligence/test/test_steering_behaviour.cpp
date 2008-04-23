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
#include <iostream>
#include <kernel/log.h>
#include <kernel/string.h>
#include <artificial_intelligence/implementation/vehicle.h>
#include <artificial_intelligence/implementation/steering_behaviour.h>
#include <artificial_intelligence/test/test_steering_behaviour.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::ArtificialIntelligence::Test::TestSteeringBehaviour) ;

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Test {

      namespace
      {
        /// Acceptable variable for comparison 
        const float delta = 1e-4 ;

        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }
      }
      
      void TestSteeringBehaviour::testSeek()
      {
        // A vehicle to seek
        Implementation::Vehicle target(Ogre::Vector3(0,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(0,0,0),
                                       5) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(0,0,0),
                                       10) ;
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 1000 ; ++i)
        {
          Ogre::Vector3 steering = Implementation::SteeringBehaviour::seek(seeker,target) ;
          seeker.simulate(steering) ;
        }
        
        // check that seeker position is almost zero
        /*
          @remark only valid because max_force >= max_speed so seek == arrival
        */
        CPPUNIT_ASSERT(equal(seeker.getPosition().x,0)) ;
        CPPUNIT_ASSERT(equal(seeker.getPosition().y,0)) ;
        CPPUNIT_ASSERT(equal(seeker.getPosition().z,0)) ;
      }
      
      void TestSteeringBehaviour::testPursuitLinear()
      {
        // A vehicle to seek (not too speedy to be able to catch it)
        Implementation::Vehicle target(Ogre::Vector3(100,50,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(5,0,0),
                                       5) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(0,0,0),
                                       10) ;
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 1000 ; ++i)
        {
          target.simulate(Ogre::Vector3::ZERO) ;
          Ogre::Vector3 steering = Implementation::SteeringBehaviour::pursuit(seeker,target) ;
          seeker.simulate(steering) ;
        }
        
        // check that both objects nearly have same position
        Ogre::Vector3 offset = target.getPosition()  - seeker.getPosition() ;
        
        CPPUNIT_ASSERT(offset.length() < seeker.getMaxSpeed()) ;
      }

      void TestSteeringBehaviour::testPursuitPlannar()
      {
        // A vehicle to seek (not too speedy to be able to catch it)
        Implementation::Vehicle target(Ogre::Vector3(100,150,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(5,0,0),
                                       5) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,50,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(-5,0,0),
                                       10) ;
        
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 1000 ; ++i)
        {
          target.simulate(Ogre::Vector3::ZERO) ;
          Ogre::Vector3 steering = Implementation::SteeringBehaviour::pursuit(seeker,target) ;
          seeker.simulate(steering) ;
        }
        
        // check that both objects nearly have same position
        Ogre::Vector3 offset = target.getPosition()  - seeker.getPosition() ;
        
        CPPUNIT_ASSERT(offset.length() < seeker.getMaxSpeed()) ;
      }

      void TestSteeringBehaviour::testPursuitTargetBehind()
      {
        InternalMessage("AI","Entering TestSteeringBehaviour::testPursuitTargetBehind" ) ;
        // A vehicle to seek (not too speedy to be able to catch it)
        Implementation::Vehicle target(Ogre::Vector3(100,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(5,0,0),
                                       5) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(-5,0,0),
                                       10) ;
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 1000 ; ++i)
        {
          target.simulate(Ogre::Vector3::ZERO) ;
          Ogre::Vector3 steering = Implementation::SteeringBehaviour::pursuit(seeker,target) ;
          seeker.simulate(steering) ;
        }
        
        // check that both objects nearly have same position
        Ogre::Vector3 offset = target.getPosition()  - seeker.getPosition() ;
        
        CPPUNIT_ASSERT(offset.length() < seeker.getMaxSpeed()) ;

        InternalMessage("AI","Leaving TestSteeringBehaviour::testPursuitTargetBehind" ) ;
      }

      void TestSteeringBehaviour::testOffsetPursuitTargetBehind()
      {
        InternalMessage("AI","Entering TestSteeringBehaviour::testOffsetPursuitTargetBehind" ) ;
        // A vehicle to seek (not too speedy to be able to catch it)
        Implementation::Vehicle target(Ogre::Vector3(100,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(5,0,0),
                                       5) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(-5,0,0),
                                       10) ;
        
        Ogre::Vector3 local_offset(-10,0,0) ;
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 1000 ; ++i)
        {
          target.simulate(Ogre::Vector3::ZERO) ;
          Ogre::Vector3 steering 
            = Implementation::SteeringBehaviour::offsetPursuit(seeker,target,local_offset) ;
          seeker.simulate(steering) ;
        }
        
        // check that both objects nearly have same position
        Ogre::Vector3 offset = target.getPosition() + target.getOrientation()*local_offset - seeker.getPosition() ;
        
        CPPUNIT_ASSERT(offset.length() < seeker.getMaxSpeed()) ;

        InternalMessage("AI","Leaving TestSteeringBehaviour::testOffsetPursuitTargetBehind" ) ;
      }

      void TestSteeringBehaviour::testOffsetPursuitTargetSide()
      {
        InternalMessage("AI","Entering TestSteeringBehaviour::testOffsetPursuitTargetSide" ) ;
        // A vehicle to seek (not too speedy to be able to catch it)
        Implementation::Vehicle target(Ogre::Vector3(100,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(5,0,0),
                                       5) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(-5,0,0),
                                       10) ;
        
        Ogre::Vector3 local_offset(0,10,0) ;
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 1000 ; ++i)
        {
          target.simulate(Ogre::Vector3::ZERO) ;
          Ogre::Vector3 steering 
            = Implementation::SteeringBehaviour::offsetPursuit(seeker,target,local_offset) ;
          seeker.simulate(steering) ;
        }

        // check that both objects nearly have same position
        Ogre::Vector3 offset = target.getPosition() + target.getOrientation()*local_offset - seeker.getPosition() ;
        CPPUNIT_ASSERT(offset.length() < seeker.getMaxSpeed()) ;

        InternalMessage("AI","Leaving TestSteeringBehaviour::testOffsetPursuitTargetSide" ) ;
      }

      void TestSteeringBehaviour::pursuitWanderingTarget()
      {
        InternalMessage("AI","Entering TestSteeringBehaviour::pursuitWanderingTarget" ) ;
        // A vehicle to seek (not too speedy to be able to catch it)
        Implementation::Vehicle target(Ogre::Vector3(100,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(5,0,0),
                                       5,
                                       10) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(-5,0,0),
                                       10,
                                       10) ;
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 1000 ; ++i)
        {
          Ogre::Vector3 target_steering = Implementation::SteeringBehaviour::wander(target) ;
          target.simulate(target_steering) ;
          Ogre::Vector3 steering = Implementation::SteeringBehaviour::pursuit(seeker,target) ;
          seeker.simulate(steering) ;
        }
        
        // check that both objects nearly have same position
        CPPUNIT_ASSERT((target.getPosition() - seeker.getPosition()).length() < seeker.getMaxSpeed()) ;

        InternalMessage("AI","Leaving TestSteeringBehaviour::pursuitWanderingTarget" ) ;
      }

      void TestSteeringBehaviour::evadeNearTarget()
      {
        InternalMessage("AI","Entering TestSteeringBehaviour::evadeNearTarget" ) ;
        // A vehicle to seek (not too speedy to be able to catch it)
        Implementation::Vehicle target(Ogre::Vector3(0,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(5,0,0),
                                       8) ;
        
        // A vehicle seeking
        Implementation::Vehicle seeker(Ogre::Vector3(10,0,0),
                                       Ogre::Quaternion(),
                                       Ogre::Vector3(-5,0,0),
                                       10) ;
        
        // A "simulation" loop : calculate steering and apply it 
        for(int i = 1 ; i <= 100 ; ++i)
        {
          Ogre::Vector3 target_steering = Implementation::SteeringBehaviour::evade(target,seeker) ;
          target.simulate(target_steering) ;
          Ogre::Vector3 steering = Implementation::SteeringBehaviour::pursuit(seeker,target) ;
          seeker.simulate(steering) ;
        }
        
        // check that both objects nearly have same position
        Ogre::Vector3 offset = target.getPosition()  - seeker.getPosition() ;
        
        CPPUNIT_ASSERT(equal(target.getSpeed().length(),target.getMaxSpeed())) ;
        CPPUNIT_ASSERT(offset.length() < seeker.getMaxSpeed()) ;

        InternalMessage("AI","Leaving TestSteeringBehaviour::evadeNearTarget" ) ;
      }
      
      void TestSteeringBehaviour::setUp() 
      {
      }
      
      void TestSteeringBehaviour::tearDown() 
      {
      }

    }
  }
}

