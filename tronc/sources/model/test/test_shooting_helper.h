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
  namespace Model
  {
    namespace Test
    {
      /// Test for the Model::ShootingHelper and associated logic.
      class TestShootingHelper : public CppUnit::TestFixture
      {
      protected:
      /*!
        @name Test methods
      */
      // @{

        /// A basic functional test.
        /*!
          Aiming a static target.
        */
        void basicTest() ;

        /// Test an object flying away from the shot.
        void testMovingFront() ;

        /// Test an object flying away from the shot and untouchable.
        void testMovingUnshootable() ;

        void movingFastToFiringShipShouldBeShootable() ;

        /// Test an object moving in orthogonal direction of the shot.
        void testMovingLateral() ;

        /// Test an object moving in orthogonal direction of the shot.
        void testMovingLateralWithRotation() ;

        /// Test a Computer destruction.
        void destroyComputer() ;

        /// Test a Laser destruction.
        void destroyLaser() ;

        /// Test a Computer deconnection.
        /*!
          We deconnect the computer and the ideal target does not exist anymore
        */
        void deconnectComputer() ;

        /// A target in front.
        void testShootable() ;

        /// A target in front all system rotated 45 degrees.
        void testShootableWithRotation() ;

        /// Same as previous but where detecting ship is not at origin (showed a bug).
        void shootableWithRotationIsInvariantByTranslation() ;

        /// A target aligned but behind.
        void testNotShootableBehind() ;

        /// A target in front but offset on the side.
        void testNotShootableOnTheSide() ;

        /// A target in front and offset on the side, shoot it in the back.
        void testShootableOnTheSide() ;

        void idealTargetIsInvariantByRotation() ;
        void idealTargetIsInvariantByTranslation() ;

      // @}
      /*!
        @name Test registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestShootingHelper) ;

         CPPUNIT_TEST(basicTest) ;
         CPPUNIT_TEST(testMovingFront) ;
         CPPUNIT_TEST(testMovingUnshootable) ;
         CPPUNIT_TEST(movingFastToFiringShipShouldBeShootable) ;
         CPPUNIT_TEST(testMovingLateral) ;
         CPPUNIT_TEST(testMovingLateralWithRotation) ;
         CPPUNIT_TEST(destroyComputer) ;
         CPPUNIT_TEST(destroyLaser) ;
         CPPUNIT_TEST(deconnectComputer) ;
         CPPUNIT_TEST(testShootable) ;
         CPPUNIT_TEST(testShootableWithRotation) ;
         CPPUNIT_TEST(shootableWithRotationIsInvariantByTranslation) ;
         CPPUNIT_TEST(testNotShootableBehind) ;
         CPPUNIT_TEST(testNotShootableOnTheSide) ;
         CPPUNIT_TEST(testShootableOnTheSide) ;
         CPPUNIT_TEST(idealTargetIsInvariantByRotation) ;
         CPPUNIT_TEST(idealTargetIsInvariantByTranslation) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      private:

        Kernel::Object* createDetectingShip(Kernel::Object* parent) ;
        Kernel::Object* createDetectedShip(Kernel::Object* parent) ;
        Kernel::Object* getIdealTarget(Kernel::Object* ship) ;
      };
    }
  }
}

