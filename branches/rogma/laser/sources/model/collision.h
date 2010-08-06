/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

#include <kernel/trait.h>
#include <kernel/object_reference.h>
#include <model/energy.h>

namespace ProjetUnivers
{
  namespace Model
  {
    
    /// For collision.
    /*!
      Represents a collision between two objects.
    */
    class Collision : public Kernel::Trait
    {
    public:

      /// Constructs with the two colliding objects.
      Collision(Kernel::Object*,
                Kernel::Object*,
                const Energy&) ;
      
      /// Access to colliding objects.
      Kernel::Object* getObject1() const ;
      Kernel::Object* getObject2() const ;

      const Energy& getEnergy() const ;

    private:
      
      /// Objects involved in the collision.
      Kernel::ObjectReference m_object1 ;
      Kernel::ObjectReference m_object2 ;

      /// Intensity of the collision
      Energy m_energy ;
    };
    
    
  }
}
