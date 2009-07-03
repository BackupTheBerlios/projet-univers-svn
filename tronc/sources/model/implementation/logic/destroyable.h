/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <model/destroyable.h>
#include <model/implementation/logic/logic_system.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Implementation
    {
      namespace Logic
      {

        /// Manage deletion of destroyable objects.
        class Destroyable : public Kernel::Controler<Model::Destroyable,
                                                     LogicSystem>
        {
        public:
        
          virtual void onInit() ;

          /// Destroy object if life is zero.
          void simulate(const float& i_seconds) ;
        
        private:
        
          /// used to destroy only once an object.
          bool m_marked_to_destroy ;
        };
      }
    }
  }
}
