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
#ifndef PU_GAME_IMPLEMENTATION_CONTROLER_GAME_CONTROLER_SET_H_
#define PU_GAME_IMPLEMENTATION_CONTROLER_GAME_CONTROLER_SET_H_

#include <game/game_state.h>
#include <kernel/controler_set.h>

namespace ProjetUnivers {
  namespace Game {
    namespace Implementation {
      
      /// Controls a game
      namespace Controler {
        
        class GameControlerSet : public Kernel::ControlerSet
        {
        public:
          
          /// Construction.
          GameControlerSet(Kernel::Model*) ;
          
          /// Set the current game state
          void setGameState(GameState*) ;
          
          /// Tells the game state to quit.
          void quit() ;

        protected:
            
          virtual void onClose() ;
          
        private:
          
          GameState* m_game_state ;
        };
        
      }
    }
  }
}

#endif /*PU_GAME_IMPLEMENTATION_CONTROLER_GAME_CONTROLER_SET_H_*/
