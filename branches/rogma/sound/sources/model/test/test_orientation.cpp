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
#include <OgreVector3.h>
#include <model/orientation.h>

#include <model/test/test_orientation.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Model::Test::TestOrientation) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      void TestOrientation::rigthHandedAntiClockWise()
      {
        /*
          turing of 90° around up is anticlockwise
        */
        Orientation orientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y)) ;

        CPPUNIT_ASSERT(orientation.getQuaternion().zAxis().positionEquals(Ogre::Vector3(1,0,0),1e-4)) ;
        CPPUNIT_ASSERT(orientation.getQuaternion().yAxis().positionEquals(Ogre::Vector3(0,1,0),1e-4)) ;
        CPPUNIT_ASSERT(orientation.getQuaternion().xAxis().positionEquals(Ogre::Vector3(0,0,-1),1e-4)) ;
      }

      void TestOrientation::composeOrientation()
      {
        Orientation orientation1(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y)) ;
        Orientation orientation2(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Z)) ;
        
        Orientation orientation = orientation2*orientation1 ;
          
        CPPUNIT_ASSERT(orientation.getQuaternion().zAxis().positionEquals(Ogre::Vector3(0,1,0),1e-4)) ;
        CPPUNIT_ASSERT(orientation.getQuaternion().yAxis().positionEquals(Ogre::Vector3(-1,0,0),1e-4)) ;
        CPPUNIT_ASSERT(orientation.getQuaternion().xAxis().positionEquals(Ogre::Vector3(0,0,-1),1e-4)) ;
      }
      
      void TestOrientation::setUp() 
      {
      }
      
      void TestOrientation::tearDown() 
      {
      }
      

    }
  }
}

