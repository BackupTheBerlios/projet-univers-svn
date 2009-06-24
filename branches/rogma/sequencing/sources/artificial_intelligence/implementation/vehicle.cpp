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
#include <OgreStringConverter.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <artificial_intelligence/implementation/vehicle.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Implementation {

      Vehicle::Vehicle()
      : m_position(0,0,0),
        m_speed(0,0,0),
        m_orientation(),
        m_max_speed(0),
        m_radius(0),
        m_turning_rate(Ogre::Degree(30))
      {}

      Vehicle::Vehicle(
              const Ogre::Vector3& position,
              const Ogre::Quaternion& orientation,
              const Ogre::Vector3& speed,
              float max_speed,
              float radius)
      : m_position(position),
        m_speed(speed),
        m_orientation(orientation),
        m_max_speed(max_speed),
        m_radius(radius),
        m_turning_rate(Ogre::Degree(30))
      {}

      void Vehicle::setPosition(const Ogre::Vector3& position)
      {
        m_position = position ;
      }

      void Vehicle::setOrientation(const Ogre::Quaternion& orientation)
      {
        m_orientation = orientation ;
      }

      void Vehicle::setSpeed(const Ogre::Vector3& speed)
      {
        m_speed = speed ;
      }

      void Vehicle::setSize(const float& size)
      {
        m_radius = size ;
      }

      void Vehicle::setMaxSpeed(const float& max_speed)
      {
        m_max_speed = max_speed ;
      }

      void Vehicle::setTurningRate(const Ogre::Degree& turning_rate)
      {
        m_turning_rate = turning_rate ;
      }

      const Ogre::Vector3& Vehicle::getPosition() const
      {
        return m_position ;
      }

      const Ogre::Vector3& Vehicle::getSpeed() const
      {
        return m_speed ;
      }

      const Ogre::Quaternion& Vehicle::getOrientation() const
      {
        return m_orientation ;
      }

      Ogre::Vector3 Vehicle::getForward() const
      {
        return -(m_orientation.zAxis()) ;
      }

      Ogre::Vector3 Vehicle::getUp() const
      {
        return m_orientation.yAxis() ;
      }

      Ogre::Vector3 Vehicle::getSide() const
      {
        return m_orientation.xAxis() ;
      }

      Ogre::Vector3 Vehicle::predictFuturePosition(const float& time) const
      {
        return m_position + time * m_speed ;
      }

      /// maximize a speed to max_speed
      void Vehicle::normalizeSpeed(Ogre::Vector3& speed) const
      {
        if (speed.length() > m_max_speed && m_max_speed != 0)
        {
          speed.normalise() ;
          speed *= m_max_speed ;
        }
      }

      // max force for tests
      static const float max_force = 10 ;

      /// maximize a force to max_force
      void normalizeForce(Ogre::Vector3& force)
      {
        if (force.length() > max_force && max_force != 0)
        {
          force.normalise() ;
          force *= max_force ;
        }
      }

      /// Simualtion time step
      static const float timestep = 0.1 ;

      void Vehicle::simulate(const Ogre::Vector3& force,const int mode)
      {
        switch(mode)
        {
        case 0:
          simulateClassic(force) ;
          break ;
        case 1:
          simulateNew(force) ;
          break ;
        }
      }

      void Vehicle::simulateNew(const Ogre::Vector3& force)
      {
        InternalMessage("TestDisplay","force=" + Ogre::StringConverter::toString(force)) ;
        Ogre::Vector3 local = force ;
        normalizeForce(local) ;
        local = m_orientation.Inverse()*local ;
        InternalMessage("TestDisplay","local force=" + Ogre::StringConverter::toString(local)) ;
        InternalMessage("TestDisplay","front=" + Ogre::StringConverter::toString(getForward())) ;

        Ogre::Degree side_turn = m_turning_rate*local.x/max_force ;

        if (local.x == 0 && local.z > 0)
        {
          side_turn = m_turning_rate ;
        }

        side_turn *= timestep ;
        Ogre::Quaternion side(-side_turn,Ogre::Vector3::UNIT_Y) ;

        InternalMessage("TestDisplay","side_turn=" + Kernel::toString(side_turn.valueDegrees())) ;

        Ogre::Degree up_turn = m_turning_rate*local.y/max_force ;

        if (local.y == 0 && local.z > 0)
        {
          up_turn = m_turning_rate ;
        }

        up_turn *= timestep ;
        Ogre::Quaternion up(up_turn,Ogre::Vector3::UNIT_X) ;

        InternalMessage("TestDisplay","up_turn=" + Kernel::toString(up_turn.valueDegrees())) ;
        InternalMessage("TestDisplay","local force=" + Ogre::StringConverter::toString(local)) ;

        float speed_value = getSpeed().length() - local.z ;

        InternalMessage("TestDisplay","speed_value=" + Kernel::toString(speed_value)) ;
        if (speed_value <= 0)
          speed_value = m_max_speed/3 ;
        if (speed_value > m_max_speed)
          speed_value = m_max_speed ;

        Ogre::Vector3 speed = getForward() ;
        InternalMessage("TestDisplay","result speed=" + Ogre::StringConverter::toString(speed)) ;
        speed = side*speed ;
        speed = up*speed ;
        Ogre::Vector3 front = speed ;
        InternalMessage("TestDisplay","result speed=" + Ogre::StringConverter::toString(speed)) ;
        speed = speed_value*speed ;
        InternalMessage("TestDisplay","result speed=" + Ogre::StringConverter::toString(speed)) ;
        normalizeSpeed(speed) ;
        InternalMessage("TestDisplay","result speed=" + Ogre::StringConverter::toString(speed)) ;

        // apply changes to vehicle
        setPosition(getPosition()+timestep*speed) ;
        setSpeed(speed) ;

        // change direction
        {
          if (front.length() == 0)
            front = getForward() ;
          front.normalise() ;
          front = -front ;
          Ogre::Vector3 rigth = Ogre::Vector3::UNIT_Y.crossProduct(front) ;
          rigth.normalise() ;
          setOrientation(Ogre::Quaternion(rigth,Ogre::Vector3::UNIT_Y,front)) ;
        }
      }

      void Vehicle::simulateClassic(const Ogre::Vector3& force)
      {
        Ogre::Vector3 local = force ;
        normalizeForce(local) ;

        Ogre::Vector3 speed = getSpeed() + force ;
        normalizeSpeed(speed) ;

        // apply changes to vehicle
        setPosition(getPosition()+timestep*speed) ;
        setSpeed(speed) ;

        if (speed.length() != 0)
        {
          Ogre::Vector3 side(-speed.y,speed.x,-speed.z) ;
          Ogre::Vector3 forward = speed ;
          side.normalise() ;
          forward.normalise() ;
          Ogre::Vector3 up = forward.crossProduct(side) ;
          up.normalise() ;
          setOrientation(Ogre::Quaternion(side,up,forward)) ;
        }
      }


      float Vehicle::getMaxSpeed() const
      {
        return m_max_speed ;
      }

      float Vehicle::getRadius() const
      {
        return m_radius ;
      }

      const Ogre::Radian& Vehicle::getTurningRate() const
      {
        return m_turning_rate ;
      }

    }
  }
}
