/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef PU_PHYSIC_IMPLEMENTATION_ODE_PHYSICAL_OBJECT_H_
#define PU_PHYSIC_IMPLEMENTATION_ODE_PHYSICAL_OBJECT_H_

#include <kernel/trait_view.h>

#include <model/physical_object.h>
#include <model/physical_world.h>

#include <physic/implementation/ode/real_world_view_point.h>

class dBody ;

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
      
        /// ODE's representation of a physical object.
        /*!
          @see Model::PhysicalWorld
        */
        class PhysicalObject : public Kernel::TraitView<Model::PhysicalObject,
                                                        RealWorldViewPoint>
        {
        public:

          /// constructor.
          PhysicalObject(Model::PhysicalObject*,RealWorldViewPoint*) ;

          dBody* getBody() const ;
          
          /// Updates model according to simulation.
          void updateModel() ;

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

          
          /// Set ODE position and orientation from Model.
          void updatePositionned() ;
          /// Set ODE mass from Model.
          void updateMassive() ;
          /// Set ODE speeds from Model.
          void updateMobile() ;
          
          /// Calculate the world object of this body. 
          Model::PhysicalWorld* determineWorld() const ;

          /// Modify model position/orientation. 
          void updateModelPositionned() ;

          /// Modify model speed. 
          void updateModelMobile() ;
          
          /// ode's body
          dBody* m_body ;
          
          /// Used to avoid that changeModelPosition triggers onUpdate.
          bool m_is_being_updated ;
        };

      }
    }
  }
}

#endif /*PU_PHYSIC_IMPLEMENTATION_ODE_PHYSICAL_OBJECT_H_*/
