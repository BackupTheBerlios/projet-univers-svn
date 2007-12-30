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
#include <ode/ode.h>

#include <kernel/log.h>
#include <kernel/trait_view.h>

#include <model/physical_world.h>
#include <model/physical_object.h>

#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/torque_generator.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        RegisterControler(TorqueGenerator, 
                          Model::TorqueGenerator, 
                          PhysicSystem) ;
      
        TorqueGenerator::TorqueGenerator(
            Model::TorqueGenerator* i_object,
            PhysicSystem*           i_system)
        : Kernel::Controler<Model::TorqueGenerator,
                            PhysicSystem>(i_object,i_system),
          m_object(NULL)
        {}
        
        void TorqueGenerator::prepare()
        {
          /// set a torque on it's body
          if (m_object)
          {
            Ogre::Vector3 torque(getTrait()->NewtonMeter()) ;
            InternalMessage("Physic","Physic::TorqueGenerator::prepare " +
                            getObject()->getName() + " torque = " +  
                                          Kernel::toString(torque.x) + "," + 
                                          Kernel::toString(torque.y) + "," +
                                          Kernel::toString(torque.z)) ;
             
            m_object->getBody()->addTorque(torque.x,
                                           torque.y,
                                           torque.z) ;
          }
        }
        
        void TorqueGenerator::onInit()
        {
          m_object = determineObject() ;
        }
        
        void TorqueGenerator::onClose()
        {
        }
  
        void TorqueGenerator::onChangeParent(Kernel::Object* i_old_parent)
        {
          onClose() ;
        }
        
        void TorqueGenerator::onUpdate()
        {
        }
        
        PhysicalObject* TorqueGenerator::determineObject() const
        {
          Model::PhysicalObject* physical_object = 
              getObject()->getParent<Model::PhysicalObject>() ;

          if (physical_object)
          {
//            InformationMessage("Physic",getObject()->getName() +  " has physical object : " 
//                               + physical_object->getObject()->getName()) ; 
            
            return physical_object->getControler<PhysicalObject>(getControlerSet()) ;
          }           
          return NULL ;
        }
      }
    }
  }
}
