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

#include <kernel/view_point.h>
#include <kernel/trait_view.h>

#include <model/game_state.h>
#include <model/with_lifetime.h>
#include <model/model.h>

#include <game/game.h>
#include <game/game_state.h>
#include <game/test/test_game_state.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Game::Test::TestGameState) ;

namespace ProjetUnivers {
  namespace Game {
    namespace Test {

      namespace
      {
        /// A viewpoint for testing
        class TestGameStateViewPoint : public Kernel::ViewPoint
        {
        public:
          
          TestGameStateViewPoint(Kernel::Model* model)
          : Kernel::ViewPoint(model)
          {}
          
          static std::list<Kernel::Model*> m_activated_states ;
          
        protected:
          
          virtual void onInit()
          {
            m_activated_states.push_back(getModel()) ;
          }

          virtual void onClose()
          {
            
          }
        };
        
        std::list<Kernel::Model*> TestGameStateViewPoint::m_activated_states ;
        
        RegisterViewPoint(TestGameStateViewPoint) ;
        
      }
      
      void TestGameState::basicTest()
      {
        GameState state("level") ;
        state.load("TestDemonstration") ;
        state.activate() ;
        state.init() ;
        state.update(0.1) ;
      }

      void TestGameState::twoStateGame()
      {
        
        TestGameStateViewPoint::m_activated_states.clear() ;
        
        /*
          A game with two states : 
          a welcome during 2 seconds
          a goodbye during 2 seconds
        */
        Game game ;
        GameState* welcome = game.addState(new GameState("welcome")) ;
        Kernel::Object* welcome_model = welcome->getRoot() ;
        welcome_model->addTrait(new Model::WithLifetime(Model::Duration::Second(2))) ;
        
        GameState* goodbye = game.addState(new GameState("goodbye")) ;
        Kernel::Object* goodbye_model = goodbye->getRoot() ;
        goodbye_model->addTrait(new Model::WithLifetime(Model::Duration::Second(2))) ;
        
        welcome->setNextState(goodbye) ;
        welcome->activate() ;
        game.run() ;
        CPPUNIT_ASSERT(TestGameStateViewPoint::m_activated_states.size()==2) ;
      }
      
      void TestGameState::demonstration()
      {
        Game game ;
        GameState* state = game.addState(new GameState("TestPilot")) ;
        state->load("TestPilot") ;
        state->activate() ;
        game.run() ;
      }
      
      void TestGameState::setUp()
      {
      }

      void TestGameState::tearDown()
      {}

      
    }
  }
}
