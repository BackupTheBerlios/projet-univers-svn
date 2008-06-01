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
#ifndef PU_GAME_TEST_GAME_STATE_H_
#define PU_GAME_TEST_GAME_STATE_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Game {
    namespace Test {


      ///  Tests for GameState.
      class TestGameState : public CppUnit::TestFixture {
      public:

        /// Test suite init.
        void setUp() ;

        /// Test suite close.
        void tearDown() ;

      protected:

      /// @name Tests methods
      // @{  

        /// Build a game state an run it.
        void basicTest() ;
       
        /// A two state game : splash screen wecome and spash screen goodby.
        void twoStateGame() ;
        
      // @}


        CPPUNIT_TEST_SUITE(TestGameState) ;

        CPPUNIT_TEST(basicTest) ;
        CPPUNIT_TEST(twoStateGame) ;

        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif /*PU_GAME_TEST_GAME_STATE_H_*/
