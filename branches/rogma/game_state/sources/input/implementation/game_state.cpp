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
#include <model/player_configuration.h>
#include <input/implementation/keyboard.h>
#include <input/implementation/input_internal.h>
#include <input/implementation/game_state.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      
      RegisterControler(GameState,Model::GameState,InputControlerSet) ;

      GameState::GameState(Model::GameState* player,InputControlerSet* input)
      : Kernel::Controler<Model::GameState,InputControlerSet>(player,input)
      {}
        
      void GameState::simulate(const float& seconds)
      {
        InternalMessage("Input","GameState::simulate entering") ;
        // intended hard coded behaviour : escape produces quit
        
        const std::set<Model::PlayerConfiguration::InputEvent>& events = 
          getKeyboard()->getEvents() ;
        if (events.find(Model::PlayerConfiguration::InputEvent::key(OIS::KC_ESCAPE)) !=
            events.end())
        {
          getObject()->call("quit") ;
        }
        
        InternalMessage("Input","GameState::simulate leaving") ;
      }
      
    }
  }
}
