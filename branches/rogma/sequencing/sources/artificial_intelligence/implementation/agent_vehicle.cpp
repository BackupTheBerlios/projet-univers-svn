/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <kernel/log.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/mobile.h>
#include <model/physical_world.h>
#include <artificial_intelligence/implementation/vehicle.h>
#include <artificial_intelligence/implementation/agent_vehicle.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {


      void AgentVehicle::onInit()
      {
        InternalMessage("AI","entering AgentVehicle::onInit") ;
        Ogre::Vector3 speed = getSpeed() ;

        m_vehicle.reset(new Vehicle(getPosition(),
                                    getOrientation(),
                                    speed,
                                    speed.length(),
                                    getSize())) ;
        getViewPoint()->setVehicle(m_vehicle.get()) ;
        InternalMessage("AI","leaving AgentVehicle::onInit") ;
      }

      void AgentVehicle::onClose()
      {
        getViewPoint()->setVehicle(NULL) ;
        m_vehicle.reset(NULL) ;
      }

      void AgentVehicle::onUpdate()
      {
        // last updated elementary trait will tell us what to update
//        const Kernel::TypeIdentifier& latest = getTrait()->getLatestUpdatedTrait() ;
//
//        if (latest == getClassTypeIdentifier(Model::Positionned))
//        {
          m_vehicle->setPosition(getPosition()) ;
//        }
//        else if (latest == getClassTypeIdentifier(Model::Mobile))
//        {
          m_vehicle->setSpeed(getSpeed()) ;
          m_vehicle->setMaxSpeed(std::max(m_vehicle->getMaxSpeed(),m_vehicle->getSpeed().length())) ;
          m_vehicle->setOrientation(getOrientation()) ;
//        }
//        else if (latest == getClassTypeIdentifier(Model::Solid))
//        {
          m_vehicle->setSize(getSize()) ;
//        }
      }

      Ogre::Vector3 AgentVehicle::getPosition() const
      {
        Kernel::Object* physical_world = getObject()->getAncestor<Model::PhysicalWorld>()
                                         ->getObject() ;

        const Model::Position& position =
            getObject()->getTrait<Model::Positionned>()->getPosition(physical_world) ;

        return position.Meter() ;
      }

      Ogre::Vector3 AgentVehicle::getSpeed() const
      {
        const Model::Speed& speed =
            getObject()->getTrait<Model::Mobile>()->getSpeed() ;

        return speed.MeterPerSecond() ;
      }

      float AgentVehicle::getSize() const
      {
        Model::Solid* solid = getObject()->getTrait<Model::Solid>() ;
        if (solid)
          return solid->getRadius().Meter() ;
        return 0 ;
      }

      Ogre::Quaternion AgentVehicle::getOrientation() const
      {
        Kernel::Object* physical_world = getObject()->getAncestor<Model::PhysicalWorld>()
                                         ->getObject() ;

        const Model::Orientation& orientation =
            getObject()->getTrait<Model::Oriented>()->getOrientation(physical_world) ;

        return orientation.getQuaternion() ;
      }

    }
  }
}
