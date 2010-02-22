/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Mathieu ROGER                                 *
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

#include <ode/ode.h>
#include <kernel/base_controler.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      namespace Ode
      {
        
        /// Common part of all collideable objects
        class Collideable
        {
        public:
          
          enum
          {
            /// The geometry is a solid
            Solid = 0,
            /// The geometry an approximated solid
            ApproximatedSolid = 1,
            /// The geometry is a laser beam
            Laser = 2
          };
          
          
          
          /// Construction.
          void onInitCollideable() ;

          /// Termination.
          void onCloseCollideable() ;

          /// Access to controller.
          virtual const Kernel::BaseControler* getControler() const = 0 ;
          
          /// Check whether @c this is collideable with another Collideable.
          /*!
            Allow to forbid LaserBeam/LaserBeam collisions.
          */
          virtual bool isCollideableWith(const Collideable*) const = 0 ;
          
          /// Tell if two geometries can collide.
          static bool canCollide(const dGeomID&,const dGeomID&) ;
          
          /// contact parameter.
          static float getContactSoftConstraintForceMixing(const dGeomID&,const dGeomID&) ;

          /// Abstract class means virtual destructor.
          virtual ~Collideable() ;

        protected:

          /// Abstract class means protected constructor.
          Collideable() ;

          /// Create the associated geometry.
          virtual void createGeometry(const dSpaceID& i_space) = 0 ;

          /// Internal creation of an approximated geometry.
          virtual void createApproximatedGeometry(const dSpaceID& space) = 0 ;
          
          /// ODE Collision object
          dGeomID  m_geometry1 ;
          dGeomID  m_geometry2 ;

        };
      }
    }
  }
}
