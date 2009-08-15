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

      /// Direct tests on ODE.
      /*!
        To check properties of ODE.
      */
      class TestODE : public CppUnit::TestFixture {
      protected:


      /*!
        @name Test methods
      */
      // @{

        /// Test a simulation of two worlds.
        void testTwoWorlds() ;

        /// Test trimesh collision.
        void testTrimesh() ;

        /// Test trimesh inertia calculus.
        void testTrimeshInertia() ;

        /// Test cube/cube collision.
        void testCubeCubeCollision() ;

        /// Test trimesh collision against a cube.
        /*!
          ODE's bug submitted as :
          http://sourceforge.net/tracker/index.php?func=detail&aid=1905353&group_id=24884&atid=382799
          Marked as CPPUNIT_TEST_FAIL to get a clear result but test is KO.
        */
        void testTrimeshCubeCollision() ;

        /// Test trimesh collision against a cube.
        void testTrimeshCubeCollisionBasic() ;

      // @}
      /*!
        @name Test registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestODE) ;

        CPPUNIT_TEST(testTwoWorlds) ;
        CPPUNIT_TEST(testTrimesh) ;
        CPPUNIT_TEST(testTrimeshInertia) ;
        CPPUNIT_TEST(testCubeCubeCollision) ;
        CPPUNIT_TEST_FAIL(testTrimeshCubeCollision) ;
        CPPUNIT_TEST(testTrimeshCubeCollisionBasic) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      };

    }
  }
}
