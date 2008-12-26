/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_TEST_MISSION_H_
#define PU_MODEL_TEST_MISSION_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Test 
    {
            
      /// Test of mission.
      class TestMission : public CppUnit::TestFixture 
      {
      public:
        
        void closeMission() ;
        void loadMission() ;

        void initCustomMission() ;
        void initCustomMissionWithPlayer() ;
        void initCustomMissionShipsHaveTeam() ;
        
        void initCustomMissionShipSpawnAtDistance() ;
        void initCustomMissionShipSpawn() ;
        
        void respawn() ;
        void endOfRespawn() ;
        
      protected:
        // @}
        /*!
          @name Test registration
        */
        // @{      
      
          CPPUNIT_TEST_SUITE(TestMission) ;
        
          CPPUNIT_TEST(closeMission) ;
          CPPUNIT_TEST(loadMission) ;
          CPPUNIT_TEST(initCustomMission) ;
          CPPUNIT_TEST(initCustomMissionWithPlayer) ;
          CPPUNIT_TEST(initCustomMissionShipsHaveTeam) ;
          CPPUNIT_TEST(initCustomMissionShipSpawnAtDistance) ;
          CPPUNIT_TEST(initCustomMissionShipSpawn) ;
          CPPUNIT_TEST(respawn) ;
          CPPUNIT_TEST(endOfRespawn) ;
          
          CPPUNIT_TEST_SUITE_END() ;

      };

    }
  }
}

  #endif /*PU_MODEL_TEST_MISSION_H_*/
