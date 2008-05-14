/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_PHYSIC_IMPLEMENTATION_ODE_COLLIDEABLE_H_
#define PU_PHYSIC_IMPLEMENTATION_ODE_COLLIDEABLE_H_

#include <ode/ode.h>
#include <kernel/base_controler.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
        
        /// Common part of all collideable objects
        class Collideable
        {
        public:
          
          enum
          {
            /// The geom is a solid
            Solid = 0,
            /// The geom an approximated solid
            ApproximatedSolid = 1,
            /// The geom is a laser
            Laser = 2
          };
          
          
          
          /// Construction.
          void onInitCollideable() ;

          /// Termination.
          void onCloseCollideable() ;

          /// Access to controler.
          virtual const Kernel::BaseControler* getControler() const = 0 ;
          
          /// Check whether @c this is collideable with another Collideable.
          /*!
            Allow to forbid LaserBeam/LaserBeam collisions.
          */
          virtual bool isCollideableWith(const Collideable*) const = 0 ;
          
          /// Tell if two geoms can collide.
          static bool canCollide(const dGeomID&,const dGeomID&) ;
          
          /// Abstract class means virtual destructor.
          virtual ~Collideable() ;

        protected:

          /// Abstract class means protected constructor.
          Collideable() ;

          /// Create the associated geom.
          virtual void createGeometry(const dSpaceID& i_space) = 0 ;

          /// Internal creation of an appximated geometry.
          virtual void createApproximatedGeometry(const dSpaceID& space) = 0 ;
          
          /// ODE Collision object
          dGeomID  m_geometry1 ;
          dGeomID  m_geometry2 ;

          /// To place m_geometry relatively to parent body.
          dGeomID  m_geometry_placeable ;
        };
      }
    }
  }
}


#endif /*PU_PHYSIC_IMPLEMENTATION_ODE_COLLIDEABLE_H_*/
