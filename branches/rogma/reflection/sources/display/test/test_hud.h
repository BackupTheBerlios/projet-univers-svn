/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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

#include <display/test/display_test_fixture.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Test
    {
      /// Test HUD displays
      class TestHUD : public DisplayTestFixture
      {
      protected:
      /*!
        @name Tests
      */
      // @{

        /// When player's ship is taken as a target, display an alert indicator
        void targetedIndicatorIndicatesEnemyTargetting() ;
        void targetedIndicatorIndicatesSeveralEnemyTargetting() ;
        void targetedIndicatorDoesNotIndicateFriendTargetting() ;
        /// Display life point on hud
        void displayHullLifePoint() ;
        void displayShipData() ;
        void displayTargetSpeed() ;

      // @}
        /*!
          @name Tests registration
        */
      // @{

        CPPUNIT_TEST_SUITE(TestHUD) ;

        CPPUNIT_TEST(targetedIndicatorIndicatesEnemyTargetting) ;
        CPPUNIT_TEST(targetedIndicatorIndicatesSeveralEnemyTargetting) ;
        CPPUNIT_TEST(targetedIndicatorDoesNotIndicateFriendTargetting) ;
        CPPUNIT_TEST(displayHullLifePoint) ;
        CPPUNIT_TEST(displayShipData) ;
        CPPUNIT_TEST(displayTargetSpeed) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      };

    }
  }
}
