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
#ifndef PU_MODEL_COLLISION_H_
#define PU_MODEL_COLLISION_H_

#include <kernel/trait.h>
#include <kernel/object.h>

#include <model/position.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// For collision.
    /*!
      Represents a collision between two objects.
    */
    class Collision : public Kernel::Trait
    {
    public:

      /// Constructs with the two colliding objects and the collision position.
      Collision(Kernel::Object*,
                Kernel::Object*,
                const Model::Position&) ;
      
      /// Access to collisionning objects.
      Kernel::Object* getObject1() const ;
      Kernel::Object* getObject2() const ;
      
    private:
      
      /// Objects involved in the collision.
      Kernel::Object* m_object1 ;
      Kernel::Object* m_object2 ;
      
      /// Average position of the collision. 
      Model::Position m_position ;

    };
    
    
  }
}

#endif /*PU_MODEL_COLLISION_H_*/
