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
#include <model/collision.h>

namespace ProjetUnivers {
  namespace Model {
    
      Collision::Collision(Kernel::Object* object1,
                           Kernel::Object* object2,
                           const Model::Position& position)
      : Kernel::Trait(),
        m_object1(object1),
        m_object2(object2),
        m_position(position)
      {}

      Kernel::Object* Collision::getObject1() const
      {
        return m_object1 ;
      }

      Kernel::Object* Collision::getObject2() const
      {
        return m_object2 ;
      }
    
  }
}
