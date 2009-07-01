/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <model/physical_world.h>
#include <model/solid.h>
#include <model/speed.h>
#include <model/mobile.h>
#include <model/oriented.h>
#include <artificial_intelligence/implementation/with_vehicle_controler.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {

      RegisterControler(WithVehicleControler,WithVehicle,AISystem) ;

      void WithVehicleControler::onInit()
      {
        Ogre::Vector3 speed = getSpeed() ;

        m_vehicle.reset(new Vehicle(getPosition(),
                                    getOrientation(),
                                    speed,
                                    speed.length(),
                                    getSize())) ;
      }

      void WithVehicleControler::onClose()
      {
        m_vehicle.reset() ;
      }

      void WithVehicleControler::onUpdate()
      {
        m_vehicle->setPosition(getPosition()) ;
        m_vehicle->setSpeed(getSpeed()) ;
        m_vehicle->setMaxSpeed(std::max(m_vehicle->getMaxSpeed(),m_vehicle->getSpeed().length())) ;
        m_vehicle->setOrientation(getOrientation()) ;
        m_vehicle->setSize(getSize()) ;
      }

      Ogre::Vector3 WithVehicleControler::getPosition() const
      {
        Kernel::Object* physical_world = getObject()->getAncestor<Model::PhysicalWorld>()
                                         ->getObject() ;

        const Model::Position& position =
            getObject()->getTrait<Model::Positionned>()->getPosition(physical_world) ;

        return position.Meter() ;
      }

      Ogre::Vector3 WithVehicleControler::getSpeed() const
      {
        const Model::Speed& speed =
            getObject()->getTrait<Model::Mobile>()->getSpeed() ;

        return speed.MeterPerSecond() ;
      }

      float WithVehicleControler::getSize() const
      {
        Model::Solid* solid = getObject()->getTrait<Model::Solid>() ;
        if (solid)
          return solid->getRadius().Meter() ;
        return 0 ;
      }

      Ogre::Quaternion WithVehicleControler::getOrientation() const
      {
        Kernel::Object* physical_world = getObject()->getAncestor<Model::PhysicalWorld>()
                                         ->getObject() ;

        const Model::Orientation& orientation =
            getObject()->getTrait<Model::Oriented>()->getOrientation(physical_world) ;

        return orientation.getQuaternion() ;
      }

      Vehicle* WithVehicleControler::getVehicle() const
      {
        return m_vehicle.get() ;
      }


    }
  }
}


