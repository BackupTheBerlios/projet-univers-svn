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
#include <input/implementation/input_internal.h>
#include <input/implementation/player.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      
      RegisterControler(Player,Model::Player,InputControlerSet) ;

      Player::Player(Model::Player* player,InputControlerSet* input)
      : Kernel::Controler<Model::Player,InputControlerSet>(player,input)
      {}
        
      void Player::simulate(const float& seconds)
      {
        InternalMessage("Input","Player::simulate entering") ;
        Kernel::Object* object = getTrait()->getConfiguration() ;
        if (object)
        {
          Model::PlayerConfiguration* configuration = object->getTrait<Model::PlayerConfiguration>() ;
          
          if (configuration)
          {
            InternalMessage("Input","Player::simulate applying") ;
            Input::apply(configuration,getObject()) ;
          }
        }
        InternalMessage("Input","Player::simulate leaving") ;
      }
      
    }
  }
}
