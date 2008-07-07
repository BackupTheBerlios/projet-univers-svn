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
#ifndef PU_PHYSIC_IMPLEMENTATION_ODE_LASER_BEAM_H_
#define PU_PHYSIC_IMPLEMENTATION_ODE_LASER_BEAM_H_

#include <ode/ode.h>

#include <kernel/controler.h>
#include <physic/implementation/laser_beam.h>
#include <physic/implementation/ode/collideable.h>
#include <physic/implementation/ode/physic_system.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
        
        /// ODE laser beam view
        /*!
        */
        class LaserBeam : public Kernel::Controler<Implementation::LaserBeam,
                                                   PhysicSystem>,
                          public Collideable
        {
        public:

          /// constructor.
          LaserBeam(Implementation::LaserBeam*,PhysicSystem*) ;

          /// Check whether @c this is collideable with another Collideable.
          virtual bool isCollideableWith(const Collideable*) const ;

        protected:
        
          /// Called after the view is created on a initialised viewpoint.
          virtual void onInit() ;
          
          /// Called just before the view is destroyed.
          virtual void onClose() ;
    
          /// Called when parent changed.
          virtual void onChangeParent(Kernel::Object* i_old_parent) ;
          
          /// Called when the model trait has changed.
          virtual void onUpdate() ;
        
        private:
          
          /// Internal creation of a trimesh geometry.
          virtual void createGeometry(const dSpaceID& i_space) ;

          /// Internal creation of an appximated geometry.
          virtual void createApproximatedGeometry(const dSpaceID& space) ;
          
          /// Access to controler.
          virtual const Kernel::BaseControler* getControler() const ;
        };

      }
    }
  }
}

#endif /*PU_PHYSIC_IMPLEMENTATION_ODE_LASER_BEAM_H_*/
