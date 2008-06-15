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
#ifndef PU_GAME_GAME_STATE_H_
#define PU_GAME_GAME_STATE_H_

#include <memory>
#include <string>
#include <kernel/model.h>

namespace ProjetUnivers {
  namespace Game {
    
    class Game ;
    
    /// Represents a game state.
    /*!
      @see http://gamedevgeek.com/tutorials/managing-game-states-in-c/
    */
    class GameState
    {
    public:
      
      /// Constructs
      GameState(const std::string& name) ;
    
      /// Set the GameState activated after desactivation.
      void setNextState(GameState*) ;
      
      /// Load a scene in the associated model.
      void load(const std::string& scene_name) ;
      
      /// Make the state active.
      void activate() ;
      
      /// Make the state inactive.
      void desactivate() ;
      
      /// Access to model.
      Kernel::Model* getModel() const ;
      
      /// Update the state during @c seconds.
      void update(const float& seconds) ;
      
    private:  
    
      void setGame(Game* game) ;
      
      std::string m_name ;
      
      /// True iff active
      bool m_is_active ;
      
      /// State activated after this close.
      GameState* m_next_state ;
      
      Game* m_game ;
      
      /// Store the state.
      std::auto_ptr<Kernel::Model> m_model ;
      
      friend class Game ;
    };
    
  }
}

#endif /*PU_GAME_GAME_STATE_H_*/
