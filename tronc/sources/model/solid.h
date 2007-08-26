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
#ifndef PU_MODEL_SOLID_H_
#define PU_MODEL_SOLID_H_

#include <kernel/trait.h>
#include <model/mesh.h>
#include <model/orientation.h>

namespace ProjetUnivers {
  namespace Model {


    /// For objects that ar solid.
    class Solid : public Kernel::Trait 
    {
    public:

      /// Constructor.
      Solid(const Mesh& _volume) ;
      
      /// Access to 3D model.
      Mesh getMesh() const ;

      /// Calculate the drag coefficient for the solid.
      /*!
        @see : 
          http://en.wikipedia.org/wiki/Drag_coefficient
      */
      float getDragCoefficient(const Orientation&) const ;      

    private:
      
      /// Volume and texture properties.
      Mesh m_mesh ;
    };
  }
}
#endif
