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
#ifndef PU_PHYSIC_IMPLEMENTATION_ODE_TORQUE_GENERATOR_H_
#define PU_PHYSIC_IMPLEMENTATION_ODE_TORQUE_GENERATOR_H_

#include <kernel/controler.h>
#include <kernel/object.h>

#include <model/torque_generator.h>

#include <physic/implementation/ode/physic_system.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
        
        class PhysicalObject ;
              
        /// Apply torque to a PhysicalObject.
        /*!
          @see Model::TorqueGenerator
        */
        class TorqueGenerator : public Kernel::Controler<Model::TorqueGenerator,
                                                         PhysicSystem>
        {
        public:

          /// constructor.
          TorqueGenerator(Model::TorqueGenerator*,PhysicSystem*) ;
          
          /// simulation
          virtual void prepare() ;
          
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

          /// Calculate the object on which this torque applies. 
          PhysicalObject* determineObject() const ;

          PhysicalObject* m_object ;
        };
      }
    }
  }
}

#endif /*PU_PHYSIC_IMPLEMENTATION_ODE_TORQUE_GENERATOR_H_*/
