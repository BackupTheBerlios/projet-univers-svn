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
#ifndef PU_AI_TEST_STEERING_BEHAVIOUR_H_
#define PU_AI_TEST_STEERING_BEHAVIOUR_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Test {

      /// Test of SteeringBehaviour.
      class TestSteeringBehaviour : public CppUnit::TestFixture {
      public:
        
        /// Apply a force to vehicle for simulation.
        static void simulate(Implementation::Vehicle& vehicle,
                             Ogre::Vector3& force) ;

      protected:
      /*! 
        @name Tests 
      */
      // @{
        
        /// Test the seek behaviour.
        void testSeek() ;

        /// Test the pursuit behaviour.
        void testPursuitLinear() ;

        /// Test the pursuit behaviour.
        void testPursuitPlannar() ;
        
        /// Test the pursuit behaviour.
        void testPursuitTargetBehind() ;

        /// Test the offsetPursuit behaviour.
        void testOffsetPursuitTargetBehind() ;
        
        /// Test the offsetPursuit behaviour.
        void testOffsetPursuitTargetSide() ;

        /// Pursuit of a wandering target.
        void pursuitWanderingTarget() ;

        /// Test the evade behaviour when target is near.
        /*!
          check that even iff pursuing object is near, the evading speed is 
          maximal.
        */
        void evadeNearTarget() ;
        
        /*!
          @todo add a test for a complex behaviour combining pursuit and avoiding
        */
        
      // @}
      /*! 
        @name Tests registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestSteeringBehaviour) ;
      
        CPPUNIT_TEST(testSeek) ;
        CPPUNIT_TEST(testPursuitLinear) ;
        CPPUNIT_TEST(testPursuitPlannar) ;
        CPPUNIT_TEST(testPursuitTargetBehind) ;
        CPPUNIT_TEST(testOffsetPursuitTargetBehind) ;
        CPPUNIT_TEST(testOffsetPursuitTargetSide) ;
        CPPUNIT_TEST(pursuitWanderingTarget) ;
        CPPUNIT_TEST(evadeNearTarget) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      public:
        
      // @}
        /*! 
          @name Mandatory methods
        */
      // @{

      
        /// Initialisation du test
        void setUp() ;
      
        /// Desinitialisation du test
        void tearDown() ;
      
      // @}      
                
       
      
      };

    }
  }
}


#endif /*PU_AI_TEST_STEERING_BEHAVIOUR_H_*/
