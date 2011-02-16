/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2011 Mathieu ROGER                                 *
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
  namespace GUI 
  {
    namespace Test 
    {
            
      /// Test of CustomMission.
      class TestCustomMission : public CppUnit::TestFixture 
      {
      protected:
      /*! 
        @name Tests
      */ 
      // @{
        
        void moveDownTeamWindows() ;
        void moveUpTeamWindows() ;
        void addTeamWindow() ;
        void addTeam() ;
        
        void createFlyingGroup() ;
        void destroyFlyingGroup() ;
        
        void close() ;
        void changeTeamName() ;
        void changeFlyingGroupName() ;
        
        void setInitialNumberOfShips() ;
        void increaseInitialNumberOfShips() ;
        void decreaseInitialNumberOfShips() ;
        void decreaseInitialNumberOfShipsEqualOne() ;

        void setNumberOfSpawn() ;
        void increaseNumberOfSpawn() ;
        void decreaseNumberOfSpawn() ;
        void decreaseNumberOfSpawnEqualOne() ;
        
        void hasPlayer() ;
        void hasNotPlayer() ;
        
      // @}
      /*!
        @name Test registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestCustomMission) ;
      
        CPPUNIT_TEST(moveDownTeamWindows) ;
        CPPUNIT_TEST(moveUpTeamWindows) ;
        CPPUNIT_TEST(addTeamWindow) ;
        CPPUNIT_TEST(addTeam) ;
        CPPUNIT_TEST(createFlyingGroup) ;
        CPPUNIT_TEST(destroyFlyingGroup) ;
        CPPUNIT_TEST(close) ;
        CPPUNIT_TEST(changeTeamName) ;
        CPPUNIT_TEST(changeFlyingGroupName) ;
        CPPUNIT_TEST(setInitialNumberOfShips) ;
        CPPUNIT_TEST(increaseInitialNumberOfShips) ;
        CPPUNIT_TEST(decreaseInitialNumberOfShips) ;
        CPPUNIT_TEST(decreaseInitialNumberOfShipsEqualOne) ;
        CPPUNIT_TEST(setNumberOfSpawn) ;
        CPPUNIT_TEST(increaseNumberOfSpawn) ;
        CPPUNIT_TEST(decreaseNumberOfSpawn) ;
        CPPUNIT_TEST(decreaseNumberOfSpawnEqualOne) ;
        CPPUNIT_TEST(hasPlayer) ;
        CPPUNIT_TEST(hasNotPlayer) ;
        
        CPPUNIT_TEST_SUITE_END() ;
        
      // @}      
      };

    }
  }
}
