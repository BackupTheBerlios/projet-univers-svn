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
#include <artificial_intelligence/test/test_vehicle.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::ArtificialIntelligence::Test::TestVehicle) ;

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

      void TestVehicle::testSimulateFront()
      {
        // A vehicle seeking
        Implementation::Vehicle vehicle ;
        vehicle.setMaxSpeed(10) ;

        // send an impulse toward front
        vehicle.simulate(Ogre::Vector3::NEGATIVE_UNIT_Z,1) ;

        CPPUNIT_ASSERT_EQUAL(Ogre::Vector3::NEGATIVE_UNIT_Z,vehicle.getForward()) ;
        CPPUNIT_ASSERT(vehicle.getPosition().z < 0) ;
        CPPUNIT_ASSERT(vehicle.getPosition().x == 0) ;
        CPPUNIT_ASSERT(vehicle.getPosition().y == 0) ;
      }

      void TestVehicle::testSimulateBack()
      {
        // A vehicle seeking
        Implementation::Vehicle vehicle ;
        vehicle.setMaxSpeed(10) ;
        vehicle.setTurningRate(Ogre::Degree(45)) ;

        vehicle.simulate(Ogre::Vector3::UNIT_Z) ;
        CPPUNIT_ASSERT(vehicle.getForward().x != 0) ;
        CPPUNIT_ASSERT(vehicle.getForward().y == 0) ;

      }

      void TestVehicle::testSimulateSide()
      {
        // A vehicle seeking
        Implementation::Vehicle vehicle ;
        vehicle.setMaxSpeed(10) ;
        vehicle.setTurningRate(Ogre::Degree(45)) ;

        vehicle.simulate(Ogre::Vector3::UNIT_X,1) ;

        CPPUNIT_ASSERT(vehicle.getForward().x > 0) ;
        CPPUNIT_ASSERT(vehicle.getForward().y == 0) ;
      }

      void TestVehicle::testSimulateUp()
      {
        // A vehicle seeking
        Implementation::Vehicle vehicle ;
        vehicle.setMaxSpeed(10) ;
        vehicle.setTurningRate(Ogre::Degree(45)) ;

        vehicle.simulate(Ogre::Vector3::UNIT_Y,1) ;

        CPPUNIT_ASSERT(vehicle.getForward().x == 0) ;
        CPPUNIT_ASSERT(vehicle.getForward().y > 0) ;
      }

    }
  }
}

