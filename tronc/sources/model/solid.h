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

#include <kernel/reader.h>
#include <model/mesh.h>
#include <model/sized.h>
#include <model/orientation.h>

namespace ProjetUnivers
{
  namespace Model
  {


    /// For objects that are solid.
    class Solid : public Sized 
    {
    public:

      /// Constructor.
      Solid(const Mesh& _volume) ;

      /// Read a Solid trait.
      /*!
        stored as 
        @code
          <Solid>
            <Mesh .../>
          </Solid>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Access to 3D model.
      Mesh getMesh() const ;

      /// Calculate the drag coefficient for the solid.
      /*!
        @see : 
          http://en.wikipedia.org/wiki/Drag_coefficient
      */
      float getDragCoefficient(const Orientation&) const ;
      
    private:
      
      /// The radius of an containing sphere.
      Distance getBoundingSphereRadius() const ;      

      /// Volume and texture properties.
      Mesh m_mesh ;
    };
  }
}
