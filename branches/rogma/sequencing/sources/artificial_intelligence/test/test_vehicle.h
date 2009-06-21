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
#ifndef PU_AI_TEST_VEHICLE_H_
#define PU_AI_TEST_VEHICLE_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Test {

      /// Test of Vehicle class.
      class TestVehicle : public CppUnit::TestFixture {
      public:

        /// Apply a force to vehicle for simulation.
        static void simulate(Implementation::Vehicle& vehicle,
                             Ogre::Vector3& force) ;

      protected:
      /*!
        @name Tests
      */
      // @{

        /// Simulate with an front steering.
        void testSimulateFront() ;

        /// Simulate with an back steering.
        void testSimulateBack() ;

        /// Simulate with an side steering.
        void testSimulateSide() ;

      // @}
      /*!
        @name Tests registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestVehicle) ;

        CPPUNIT_TEST(testSimulateFront) ;
        CPPUNIT_TEST(testSimulateBack) ;
        CPPUNIT_TEST(testSimulateSide) ;

        CPPUNIT_TEST_SUITE_END() ;
      };

    }
  }
}


#endif /*PU_AI_TEST_VEHICLE_H_*/
