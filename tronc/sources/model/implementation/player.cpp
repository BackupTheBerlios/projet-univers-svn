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
#include <model/player.h>

namespace ProjetUnivers
{
  namespace Model
  {
  
    Player::Player()
    {}

    void Player::connect(Kernel::Object* player,Kernel::Object* configuration)
    {
      Player* player_trait = player->getTrait<Player>() ;
      if (player_trait)
      {
        player_trait->m_configuration = configuration ;
        player_trait->notify() ;
      }
    }
    
    void Player::setName(const std::string& name)
    {
      m_name = name ;
      notify() ;
    }

    Kernel::Object* Player::getConfiguration() const
    {
      return m_configuration ;
    }
    
    const std::string& Player::getName() const
    {
      return m_name ;
    }

  }
}
