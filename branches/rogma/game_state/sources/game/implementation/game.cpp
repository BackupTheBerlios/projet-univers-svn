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
#include <kernel/timer.h>
#include <game/game_state.h>
#include <game/game.h>

namespace ProjetUnivers {
  namespace Game {

    void Game::run()
    {
      bool exist_active_state = true ;

      Kernel::Timer timer ;
      
      // main loop
      while (exist_active_state)
      {
        float seconds = timer.getSecond() ;
        if (seconds > 0)
        {
          timer.reset() ;
          exist_active_state = false ;
          for(std::set<GameState*>::const_iterator state = m_states.begin() ;
              state != m_states.end() ;
              ++state)
          {
            (*state)->update(seconds) ;
            exist_active_state |= (*state)->isActive() ;
          }
        }
      }
    }
    
    void Game::addState(GameState* state)
    {
      m_states.insert(state) ;
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
    
  }
}
