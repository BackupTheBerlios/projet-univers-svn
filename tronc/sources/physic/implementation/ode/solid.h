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
#ifndef PU_PHYSIC_IMPLEMENTATION_ODE_SOLID_H_
#define PU_PHYSIC_IMPLEMENTATION_ODE_SOLID_H_

#include <kernel/controler.h>
#include <model/solid.h>
#include <physic/implementation/ode/physic_system.h>

class dGeom ;

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
        
        /// ODE solid view
        /*!
          @todo 
            probably rename
            its a view on Solid and Positionned, i.e PhysicalVolume
        */
        class Solid : public Kernel::Controler<Model::Solid,
                                               PhysicSystem>
        {
        public:

          /// constructor.
          Solid(Model::Solid*,PhysicSystem*) ;

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
          
          /// ODE Collision object
          dGeom*          m_geometry ;
          /// To place m_geometry relatively to parent body.
          dGeomTransform* m_geometry_placeable ;
        };

      }
    }
  }
}

#endif /*PU_PHYSIC_IMPLEMENTATION_ODE_SOLID_H_*/
