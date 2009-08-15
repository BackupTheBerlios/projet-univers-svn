/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
  namespace Physic
  {
    namespace Test
    {

      /// Collision tests.
      class TestCollision : public CppUnit::TestFixture {
      protected:
      /*!
        @name Test methods
      */
      // @{

        /// A basic test.
        void basicTest() ;

        /// Test the bug for laser beams touching their own ship.
        void testBugLaser() ;

        /// Test LaserBeam/Solid collision.
        void testLaserBeamSolidCollision() ;

        /// Test that LaserBeam/LaserBeam does not collide.
        void testLaserBeamLaserBeamNoCollision() ;

        /// Fire a beam against a ship
        void testFire() ;

      // @}
      /*!
        @name Test registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestCollision) ;

        CPPUNIT_TEST(basicTest) ;
        CPPUNIT_TEST(testBugLaser) ;
        CPPUNIT_TEST(testLaserBeamSolidCollision) ;
        CPPUNIT_TEST(testLaserBeamLaserBeamNoCollision) ;
        CPPUNIT_TEST(testFire) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      };

    }
  }
}
