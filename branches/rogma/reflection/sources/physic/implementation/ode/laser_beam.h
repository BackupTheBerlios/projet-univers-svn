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
#pragma once

#include <ode/ode.h>

#include <kernel/controler.h>
#include <physic/implementation/ode/collideable.h>
#include <physic/implementation/ode/physic_system.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      class LaserBeam : public Kernel::DeducedTrait
      {};

      namespace Ode
      {
        
        /// ODE laser beam view
        class LaserBeam : public Kernel::Controler<Implementation::LaserBeam,
                                                   PhysicSystem>,
                          public Collideable
        {
        public:

          /// Check whether @c this is collideable with another Collideable.
          virtual bool isCollideableWith(const Collideable*) const ;

        protected:
        
          /// Called after the view is created on a initialised viewpoint.
          virtual void onInit() ;
          
          /// Called just before the view is destroyed.
          virtual void onClose() ;
    
        private:
          
          /// Internal creation of a trimesh geometry.
          virtual void createGeometry(const dSpaceID& space) ;

          /// Internal creation of an approximated geometry.
          virtual void createApproximatedGeometry(const dSpaceID& space) ;
          
          /// Access to controller.
          virtual const Kernel::BaseControler* getControler() const ;

          dGeomID m_ray ;
        };

      }
    }
  }
}
