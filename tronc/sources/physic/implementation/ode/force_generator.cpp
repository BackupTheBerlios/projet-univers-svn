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
#include <kernel/string.h>
#include <kernel/trait_view.h>

#include <model/physical_world.h>
#include <model/physical_object.h>

#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/force_generator.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
        
        // control registration
        RegisterControler(ForceGenerator, 
                          Model::ForceGenerator, 
                          PhysicSystem) ;

      
        ForceGenerator::ForceGenerator(
            Model::ForceGenerator* i_object,
            PhysicSystem*          i_system)
        : Kernel::Controler<Model::ForceGenerator,
                            PhysicSystem>(i_object,i_system),
          m_object(NULL)
        {}
        
        void ForceGenerator::prepare()
        {
          /// set a force on it's body
          if (m_object)
          {
            Ogre::Vector3 force = getModel()->getAppliedForce().Newton() ;

            InternalMessage("Physic::ForceGenerator::prepare " +
                            getObject()->getName() 
                            + " force = " +  
                            Kernel::toString(force.x) + "," + 
                            Kernel::toString(force.y) + "," +
                            Kernel::toString(force.z)
                            + " applied on object " + m_object->getObject()->getName()) ;
             
            m_object->getBody()->addForce((dReal)(force.x),
                                          (dReal)(force.y),
                                          (dReal)(force.z)) ;
          }
        }
        
        void ForceGenerator::onInit()
        {
          m_object = determineObject() ;
        }
        
        void ForceGenerator::onClose()
        {
        }
  
        void ForceGenerator::onChangeParent(Kernel::Object* i_old_parent)
        {
          onClose() ;
        }
        
        void ForceGenerator::onUpdate()
        {
        }
        
        PhysicalObject* ForceGenerator::determineObject() const
        {
          Model::PhysicalObject* physical_object = 
              getObject()->getParent<Model::PhysicalObject>() ;

          if (physical_object)
          {
//            InformationMessage(getObject()->getName() +  " has physical object : " 
//                               + physical_object->getObject()->getName()) ; 
            
            return physical_object->getControler<PhysicalObject>(getControlerSet()) ;
          }           
          return NULL ;
        }
      }
    }
  }
}
