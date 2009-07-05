/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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

      /// Test of Model::Implementation::Logic classes.
      class TestLogic : public CppUnit::TestFixture
      {
      protected:
      /*!
        @name Tests
      */
      // @{

        /// Tests that laser beams disappear after some time.
        void testLaserBeamDisappearing() ;

        /// A destroyable object disappears when it takes too much damage.
        void testDestroyable() ;

        /// A LaserBeam/Destroyable collision produce damage.
        void testLaserBeamDestroyableCollision() ;

        /// A Shot disappear just after creation.
        void testShotDisappearing() ;

        void endOfSimulation() ;

      // @}
      /*!
        @name Tests registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestLogic) ;

        CPPUNIT_TEST(testLaserBeamDisappearing) ;
        CPPUNIT_TEST(testDestroyable) ;
        CPPUNIT_TEST(testLaserBeamDestroyableCollision) ;
        CPPUNIT_TEST(testShotDisappearing) ;
        CPPUNIT_TEST(endOfSimulation) ;

        CPPUNIT_TEST_SUITE_END() ;

      public:

      // @}
      /*!
        @name Init/close methods
      */
      // @{

        /// Initialisation du test
        void setUp() ;

      // @}
      };

    }
  }
}

