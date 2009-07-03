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
#pragma once

#include <kernel/controler.h>
#include <model/position.h>
#include <model/implementation/activated_flying_group.h>
#include <model/implementation/logic/logic_system.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Implementation 
    {
      namespace Logic 
      {

        /// Handle respawn of the flying group.
        class FlyingGroup : public Kernel::Controler<Implementation::ActivatedFlyingGroup,
                                                     LogicSystem>
        {
        public:
        
          /// Respawn the player in an AI.
          void respawnPlayer() ;
          
        protected:
          
          /// Populate the group.
          virtual void onInit() ;

          /// Handle respawn.
          virtual void onUpdate() ;
          
          void spawn() ;

          /// Calculate the spawning position.
          Position getStartingPosition() const ;
          
        private:
          
          unsigned int m_number_of_spawn ;
        };
      }
    }
  }
}
