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
#include <model/distance.h>

namespace ProjetUnivers
{
  namespace Model
  {

    /// For objects that are laser beams.
    class LaserBeam : public Kernel::Trait
    {
    public:

      /// Constructor.
      LaserBeam(Kernel::Object* ship) ;
      
      /// Constructor.
      LaserBeam(Kernel::Object* ship,const Distance& length,const Distance& radius) ;
      
      /// Get the beam energy.
      /*!
        E = 1/2.mass.speed²
      */
      Energy getEnergy() const ;
      
      /// Ship that fired the beam.
      Kernel::Object* getFiringShip() const ;

      /// Access to the radius of the beam.
      const Distance& getRadius() const ;

      /// Access to the length of the beam.
      const Distance& getLength() const ;

    private:

      /// Ship that fired the beam.
      /*!
        @todo find a way to avoid following issue : beam exists but firing ship
        has been destroyed...
      */
      Kernel::ObjectReference m_ship ;

      /// Size parameter
      Distance    m_length ;
      /// Size parameter
      Distance    m_radius ;

    };

  }
}
