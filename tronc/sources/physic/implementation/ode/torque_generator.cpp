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
#include <physic/implementation/ode/torque_generator.h>
#include <kernel/parameters.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {

      DeclareDeducedTrait(TorqueGenerator,And(HasTrait(Model::TorqueGenerator),
                                              HasParent(HasTrait(Implementation::PhysicalObject)))) ;
      namespace Ode
      {

        RegisterControler(TorqueGenerator, 
                          Implementation::TorqueGenerator,
                          PhysicSystem) ;
        
        void TorqueGenerator::prepare()
        {
          /// set a torque on it's body
          if (m_object && m_object->getBody())
          {
            Ogre::Vector3 torque(getTrait<Model::TorqueGenerator>()->NewtonMeter()) ;
            InternalMessage("Physic","Physic::TorqueGenerator::prepare " +
                                      Kernel::toString(getObject()->getIdentifier()) + " torque = " +  
                                      Kernel::toString(torque.x) + "," + 
                                      Kernel::toString(torque.y) + "," +
                                      Kernel::toString(torque.z)) ;

            float length = torque.length() ;
            if (length > Kernel::Parameters::getValue<float>("Physic","Torque.MaxAllowed",10))
            {
              ErrorMessage("TorqueGenerator::prepare() capping torque value") ;
              torque /= length ;
            }

            if (!(finite(torque.x) && finite(torque.y) && finite(torque.z)))
            {
              ErrorMessage("TorqueGenerator::prepare() infinite force") ;
              throw Kernel::ExceptionKernel("Infinite torque in TorqueGenerator::prepare " +
                                            getTrait<Model::TorqueGenerator>()->toString()) ;
            }
            m_object->getBody()->addTorque(torque.x,
                                           torque.y,
                                           torque.z) ;
          }
        }
        
        void TorqueGenerator::onInit()
        {
          m_object = determineObject() ;
        }
        
        PhysicalObject* TorqueGenerator::determineObject() const
        {
          return getControler<PhysicalObject>() ;
        }
      }
    }
  }
}
