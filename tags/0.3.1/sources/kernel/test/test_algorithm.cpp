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

#include <kernel/algorithm.h>

#include <kernel/test/test_algorithm.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestAlgorithm) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

      
      void TestAlgorithm::testFindAfterBeforeOnSmallSet()
      {
          std::set<int> ensemble ;
          ensemble.insert(10) ;
          ensemble.insert(20) ;
          // 10 20
          
          CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,25)==20) ;
          CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,25)==10) ;
        
          CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,20)==10) ;
          CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,20)==10) ;
        
          CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,10)==20) ;
          CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,10)==20) ;
          
          CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,5)==20) ;
          CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,5)==10) ;
      
          CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,40)==20) ;
          CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,40)==10) ;
        
          CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,45)==20) ;
          CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,45)==10) ;
      }

      void TestAlgorithm::testFindAfterBeforeOnBigSet()
      {
        std::set<int> ensemble ;
        ensemble.insert(10) ;
        ensemble.insert(20) ;
        ensemble.insert(15) ;
        ensemble.insert(30) ;
        ensemble.insert(40) ;
        // 10 15 20 30 40
        
        CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,25)==20) ;
        CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,25)==30) ;
      
        CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,20)==15) ;
        CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,20)==30) ;
      
        CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,10)==40) ;
        CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,10)==15) ;
      
        CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,5)==40) ;
        CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,5)==10) ;
      
        CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,40)==30) ;
        CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,40)==10) ;
      
        CPPUNIT_ASSERT(Algorithm::findBefore<int>(ensemble,45)==40) ;
        CPPUNIT_ASSERT(Algorithm::findAfter<int>(ensemble,45)==10) ;
      }

      void TestAlgorithm::calculateInterceptionTime()
      {
        Ogre::Vector3 target_position(150,150,0) ;
        Ogre::Vector3 target_speed(5,0,0) ;
        float interceptor_speed = 10 ;
        
        std::pair<bool,float> reachable_time = 
          Algorithm::calculateInterceptionTime(target_position,target_speed,interceptor_speed) ;
        
        CPPUNIT_ASSERT(reachable_time.first) ;
        CPPUNIT_ASSERT(reachable_time.second > 0) ;
        
      }
      
	  void TestAlgorithm::infiniteInterceptionTime()
	  {
        Ogre::Vector3 target_position(150,150,0) ;
        Ogre::Vector3 target_speed(5,0,0) ;
        float interceptor_speed = 5 ;
        
        std::pair<bool,float> reachable_time = 
          Algorithm::calculateInterceptionTime(target_position,target_speed,interceptor_speed) ;

        CPPUNIT_ASSERT(!reachable_time.first) ;
	  }
	  

      void TestAlgorithm::setUp()
      {
      }

      void TestAlgorithm::tearDown()
      {
      }
    }
  }
}
