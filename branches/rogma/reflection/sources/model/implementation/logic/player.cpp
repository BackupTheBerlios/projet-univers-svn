/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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
#include <model/implementation/with_flying_group.h>
#include <model/implementation/logic/flying_group.h>
#include <model/implementation/logic/player.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Implementation 
    {
      namespace Logic 
      {
        
        RegisterControler(Player,PlayerInActivatedFlyingGroup,LogicSystem) ;
        
        void Player::onClose()
        {
          Kernel::Object* group = getObject()
                                  ->getParent<Implementation::WithFlyingGroup>()
                                  ->getFlyingGroup() ;
          if (group)
          {
            Implementation::ActivatedFlyingGroup* activated_flying_group = 
              group->getTrait<Implementation::ActivatedFlyingGroup>() ;
            if (activated_flying_group)
            {
              activated_flying_group->getControler<Logic::FlyingGroup>(getControlerSet())
                                    ->respawnPlayer() ;
            }
          }
        }
        
      }
    }
  }
}
