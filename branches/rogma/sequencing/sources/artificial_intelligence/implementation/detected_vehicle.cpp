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
#include <model/model.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/mobile.h>
#include <model/physical_world.h>
#include <model/computer.h>
#include <model/detection_data.h>
#include <artificial_intelligence/implementation/detected_vehicle.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Implementation {

      RegisterView(DetectedVehicle,Target,AgentViewPoint) ;

      DetectedVehicle::DetectedVehicle(Target* data,AgentViewPoint* viewpoint)
      : Kernel::TraitView<Target,AgentViewPoint>(data,viewpoint),
        m_vehicle(NULL)
      {}

      void DetectedVehicle::onInit()
      {
        InternalMessage("AI","entering DetectedVehicle::onInit") ;
        Ogre::Vector3 speed = getSpeed() ;

        m_vehicle.reset(new Vehicle(getPosition(),
                                    getOrientation(),
                                    speed,
                                    speed.length(),
                                    getSize())) ;
        getViewPoint()->addVehicle(m_vehicle.get()) ;
        InternalMessage("AI","leaving DetectedVehicle::onInit") ;
      }

      void DetectedVehicle::onClose()
      {
        getViewPoint()->removeVehicle(m_vehicle.get()) ;
        m_vehicle.reset(NULL) ;
      }

      void DetectedVehicle::onUpdate()
      {
//        // last updated elementary trait will tell us what to update
//        const Kernel::TypeIdentifier& latest = getTrait()->getLatestUpdatedTrait() ;
//
//        InternalMessage("AI","DetectedVehicle::onUpdate " + latest.toString()) ;
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

      Ogre::Vector3 DetectedVehicle::getPosition() const
      {
        Kernel::Object* agent =  getViewPoint()->getAgent() ;
        Kernel::Object* ship = Model::getControledShip(agent) ;

        Model::Computer* computer = getObject()->getTrait<Model::DetectionData>()
                                    ->getComputer()->getTrait<Model::Computer>() ;

        Kernel::Object* physical_world = ship->getAncestor<Model::PhysicalWorld>()
                                         ->getObject() ;

        InternalMessage("AI",Ogre::StringConverter::toString(getObject()->getTrait<Model::Positionned>()->getPosition().Meter())) ;

        Model::Position position
          = computer->getDataPosition(getObject(),physical_world) ;

        return position.Meter() ;
      }

      Ogre::Vector3 DetectedVehicle::getSpeed() const
      {
        const Model::Speed& speed =
            getObject()->getTrait<Model::Mobile>()->getSpeed() ;

        return speed.MeterPerSecond() ;
      }

      float DetectedVehicle::getSize() const
      {
        return getObject()->getTrait<Model::Solid>()->getRadius().Meter() ;
      }

      Vehicle* DetectedVehicle::getVehicle() const
      {
        return m_vehicle.get() ;
      }

      Ogre::Quaternion DetectedVehicle::getOrientation() const
      {
        Ogre::Vector3 speed = getSpeed() ;

        Ogre::Vector3 side(-speed.y,speed.x,-speed.z) ;
        side.normalise() ;
        Ogre::Vector3 forward = speed ;
        forward.normalise() ;
        Ogre::Vector3 up = forward.crossProduct(side) ;
        up.normalise() ;

        return Ogre::Quaternion(side,up,forward) ;
      }

    }
  }
}
