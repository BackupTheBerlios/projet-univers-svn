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

#include <kernel/controler.h>
#include <kernel/deduced_trait.h>

#include <model/physical_object.h>
#include <model/physical_world.h>
#include <model/speed.h>
#include <model/position.h>

#include <physic/implementation/ode/physic_system.h>
#include <physic/implementation/ode/physical_world.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      class PhysicalObject : public Kernel::DeducedTrait
      {} ;

      namespace Ode
      {
      
        class Solid ;
        
        /// ODE's representation of a physical object.
        /*!
          @see Model::PhysicalWorld
        */
        class PhysicalObject : public Kernel::Controler<Implementation::PhysicalObject,
                                                        PhysicSystem>
        {
        public:
          
          /// Access to ODE implementation.
          dBody* getBody() const ;

          /// Access to ODE collision space. 
          dSpace* getCollisionSpace() const ;
          
          /// Updates model according to simulation.
          void simulate(const float&) ;
          
          /// Get the speed at a given point.
          /*!
            @param position position relative to the world
          */
          Model::Speed getSpeedAt(const Model::Position& position) const ;

        protected:
        
          /// Called after the view is created on a initialized viewpoint.
          virtual void onInit() ;
          
          /// Called just before the view is destroyed.
          virtual void onClose() ;
    
          /// Called when parent changed.
          virtual void onChangeParent(Kernel::Object* old_parent) ;
          
          /// Called when the model trait has changed.
          virtual void onUpdate() ;
        
        private:

          
          /// Set ODE position and orientation from Model.
          void updatePositioned() ;
          /// Set ODE mass from Model.
          void updateMassive() ;
          /// Set ODE speeds from Model.
          void updateMobile() ;
          
          /// Modify model position/orientation. 
          void updateModelPositioned() ;

          /// Modify model speed. 
          void updateModelMobile() ;
          
          /// ode's body
          dBody* m_body ;
          
          /// Used to avoid that changeModelPosition triggers onUpdate.
          bool m_is_being_updated ;
          
          /// ODE collision space
          dSpace* m_collision_space ;
          
          /// Store world for speed up.
          PhysicalWorld* m_world ;

          friend class Solid ;
        };

      }
    }
  }
}
