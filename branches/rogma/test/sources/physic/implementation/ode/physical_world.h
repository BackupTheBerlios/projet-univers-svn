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
#ifndef PU_PHYSIC_IMPLEMENTATION_ODE_PHYSICAL_WORLD_H_
#define PU_PHYSIC_IMPLEMENTATION_ODE_PHYSICAL_WORLD_H_

#include <set>
#include <ode/ode.h>

#include <kernel/controler.h>

#include <model/physical_world.h>
#include <model/duration.h>
#include <physic/implementation/ode/physic_system.h>

class dWorld ;

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
        
        class Solid ;
        class PhysicalObject ;
        
        /// ODE's representation of a physical world
        /*!
          @see Model::PhysicalWorld
        */
        class PhysicalWorld : public Kernel::Controler<Model::PhysicalWorld,
                                                       PhysicSystem>
        {
        public:

          /// Constructor.
          PhysicalWorld(Model::PhysicalWorld*,PhysicSystem*) ;
          
          /// Simulate world during a certain duration and notify positions.
          void simulate(const float& i_duration) ;
          
          /// Access to ODE world. 
          dWorld* getWorld() const ;

          /// Access to ODE collision space. 
          dSpace* getCollisionSpace() const ;
          
        protected:
        
          /// Called after the view is created on a initialised viewpoint.
          virtual void onInit() ;
          
          /// Called just before the view is destroyed.
          virtual void onClose() ;
    
          /// Called when parent changed.
          virtual void onChangeParent(Kernel::Object* i_old_parent) ;
          
          /// Called when the model trait has changed.
          virtual void onUpdate() ;
        
          /// Called when two spaces collide.
          static void onSpaceCollision(void*   i_world,
                                       dGeomID i_space1,
                                       dGeomID i_space2) ;

          /// Called when two geometries collide.
          static void onGeometryCollision(void*   i_world,
                                          dGeomID i_geometry1,
                                          dGeomID i_geometry2) ;
        
        private:
          
          
          /// ODE's world
          dWorld* m_world ;
          
          /// ODE collision space
          dSpace* m_collision_space ;
          
          /// For solid retrieval.
          std::map<dGeomID,Solid*> m_solid_of_geometry ;

          /// Group for the contact joints.
          dJointGroupID m_contact_group ;
          
        };

      }
    }
  }
}


#endif /*PU_PHYSIC_IMPLEMENTATION_ODE_PHYSICAL_WORLD_H_*/
