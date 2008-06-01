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

#include <game/game.h>
#include <game/game_state.h>
#include <game/test/test_game_state.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Game::Test::TestGameState) ;

namespace ProjetUnivers {
  namespace Game {
    namespace Test {

      void TestGameState::basicTest()
      {
        GameState state("level") ;
        state.load("TestDemonstration") ;
        state.activate() ;
        state.update(0.1) ;
      }

      void TestGameState::twoStateGame()
      {
        Game game ;
        
        game.addState(new GameState("welcome")) ;
        game.addState(new GameState("goodbye")) ;
        
        
      }
      
      void TestGameState::setUp()
      {}

      void TestGameState::tearDown()
      {}

      
    }
  }
}
