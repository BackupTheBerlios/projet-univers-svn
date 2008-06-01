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
#ifndef PU_GAME_GAME_H_
#define PU_GAME_GAME_H_

#include <set>

namespace ProjetUnivers {
  
  /// High level game concepts and main loop.
  namespace Game {

    class GameState ;
    
    /// Represents a whole game.
    class Game
    {
    public:
      
      /// Run the game.
      void run() ;
      
      /// Add a new game state.
      void addState(GameState*) ;
      
      /// Destroy all states.
      ~Game() ;
      
    private:
      
      /// Component game states.
      std::set<GameState*> m_states ;
    };
      
    
  }
}
#endif /*PU_GAME_GAME_H_*/
