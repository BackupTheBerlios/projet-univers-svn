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
#include <kernel/log.h>
#include <kernel/timer.h>
#include <game/game_state.h>
#include <game/game.h>

namespace ProjetUnivers {
  namespace Game {

    Game::Game()
    : m_running(false)
    {}
    
    void Game::run()
    {
      m_running = true ;
      bool exist_active_state = true ;

      InternalMessage("Game","Game::run iniotialisation of starting states") ;
      for(std::set<GameState*>::const_iterator state = m_active_states.begin() ;
          state != m_active_states.end() ;
          ++state)
      {
        (*state)->init() ;
      }
      
      
      Kernel::Timer timer ;
      // main loop
      InternalMessage("Game","Game::run starting main loop") ;
      while (exist_active_state)
      {
        float seconds = timer.getSecond() ;
        if (seconds > 0)
        {
          InternalMessage("Game","Game::run loop") ;
          timer.reset() ;
          exist_active_state = false ;
          
          m_active_states_addition.clear() ;
          m_active_states_removal.clear() ;
          
          for(std::set<GameState*>::const_iterator state = m_active_states.begin() ;
              state != m_active_states.end() ;
              ++state)
          {
            InternalMessage("Game","Game::run updating active state") ;
            
            (*state)->update(seconds) ;
            exist_active_state = true  ;
          }
          for(std::set<GameState*>::const_iterator state = m_active_states_removal.begin() ;
              state != m_active_states_removal.end() ;
              ++state)
          {
            InternalMessage("Game","Game::run closing an active state") ;
            (*state)->getModel()->close() ;
            m_active_states.erase(*state) ;
          }
          for(std::set<GameState*>::const_iterator state = m_active_states_addition.begin() ;
              state != m_active_states_addition.end() ;
              ++state)
          {
            InternalMessage("Game","Game::run adding an active state") ;
            (*state)->init() ;
            m_active_states.insert(*state) ;
          }
                    
          InternalMessage("Game","Game::run end loop") ;
        }
      }
      InternalMessage("Game","Game::run ending") ;
      m_running = false ;
    }
    
    GameState* Game::addState(GameState* state)
    {
      m_states.insert(state) ;
      state->setGame(this) ;
      return state ;
    }
    
    Game::~Game()
    {
      for(std::set<GameState*>::const_iterator state = m_states.begin() ;
          state != m_states.end() ;
          ++state)
      {
        delete *state ;
      }
    }

    void Game::removeActiveState(GameState* state)
    {
      m_active_states_removal.insert(state) ;
    }
   
    void Game::addActiveState(GameState* state)
    {
      if (! m_running)
        m_active_states.insert(state) ;
      else
        m_active_states_addition.insert(state) ;
    }
    
  }
}
