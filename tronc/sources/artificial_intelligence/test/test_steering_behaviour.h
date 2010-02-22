/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2010 Mathieu ROGER                                 *
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
#pragma once

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Test
    {

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

        /// Test the seek behavior.
        void testSeek() ;

        /// Test the pursuit behavior.
        void testPursuitLinear() ;
        void pursuitStaticTarget() ;

        /// Test the pursuit behavior.
        void testPursuitPlannar() ;

        /// Test the pursuit behavior.
        void testPursuitTargetBehind() ;

        /// Test the offsetPursuit behavior.
        void testOffsetPursuitTargetBehind() ;
        void offsetPursuitDistanceBehind() ;
        void offsetPursuitStaticTarget() ;

        /// Test the offsetPursuit behavior.
        void testOffsetPursuitTargetSide() ;

        /// Pursuit of a wandering target.
        void pursuitWanderingTarget() ;

        /// Test the evade behavior when target is near.
        /*!
          check that even iff pursuing object is near, the evading speed is
          maximal.
        */
        void evadeNearTarget() ;

        /// Test the obstacleAvoidance behavior.
        void obstacleAvoidance() ;

        /*!
          @todo add a test for a complex behavior combining pursuit and avoiding
        */

      // @}
      /*!
        @name Tests registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestSteeringBehaviour) ;

        CPPUNIT_TEST(testSeek) ;
        CPPUNIT_TEST(testPursuitLinear) ;
        CPPUNIT_TEST(pursuitStaticTarget) ;
        CPPUNIT_TEST(testPursuitPlannar) ;
        CPPUNIT_TEST(testPursuitTargetBehind) ;
        CPPUNIT_TEST(testOffsetPursuitTargetBehind) ;
        CPPUNIT_TEST(offsetPursuitDistanceBehind) ;
        CPPUNIT_TEST(offsetPursuitStaticTarget) ;
        CPPUNIT_TEST(testOffsetPursuitTargetSide) ;
        CPPUNIT_TEST(pursuitWanderingTarget) ;
        CPPUNIT_TEST(evadeNearTarget) ;
        CPPUNIT_TEST(obstacleAvoidance) ;

        CPPUNIT_TEST_SUITE_END() ;
      };

    }
  }
}
