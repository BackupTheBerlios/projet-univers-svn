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
#pragma once

#include <OgreVector3.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {

      /// Something that has a position, orientation and moves.
      /*!
        When doing calculus all position orientations must be in the same space.
        Vehicle objects are generally calculated from Model objects.

        All units are in a coherent system, for example meter and seconds.
      */
      class Vehicle
      {
      public:
      /*!
        @name Construction
      */
      // @{

        /// default constructor.
        Vehicle() ;

        Vehicle(const Ogre::Vector3& position,
                const Ogre::Quaternion& orientation,
                const Ogre::Vector3& speed,
                float max_speed = 10,
                float radius = 10) ;

        /// Change position.
        void setPosition(const Ogre::Vector3& position) ;

        /// Change orientation.
        void setOrientation(const Ogre::Quaternion& orientation) ;

        /// Change speed.
        void setSpeed(const Ogre::Vector3& speed) ;

        /// Change size.
        void setSize(const float& size) ;

        /// Change maximum speed.
        void setMaxSpeed(const float& max_speed) ;

        /// Change the maximum turning rate.
        void setTurningRate(const Ogre::Degree&) ;

        /// Basic physic simulation, used for internal tests only.
        void simulate(const Ogre::Vector3& force,const int mode = 0) ;

        /// @c speed is normalized not to exceed max speed.
        void normalizeSpeed(Ogre::Vector3& speed) const ;

      // @}
      /*!
        @name Access
      */
      // @{

        /// Access to position of vehicle.
        const Ogre::Vector3& getPosition() const ;

        /// Access to speed of vehicle.
        const Ogre::Vector3& getSpeed() const ;

        /// Access to orientation of vehicle.
        const Ogre::Quaternion& getOrientation() const ;

        /// Access to forward direction of vehicle.
        Ogre::Vector3 getForward() const ;

        /// Access to up direction of vehicle.
        Ogre::Vector3 getUp() const ;

        /// Access to side direction of vehicle.
        Ogre::Vector3 getSide() const ;

        /// Predict the future position of element
        Ogre::Vector3 predictFuturePosition(const float& time) const ;

        /// Access to maximal vehicle speed.
        float getMaxSpeed() const ;

        /// Access to Vehicle size.
        float getRadius() const ;

        /// Access to the turning rate.
        const Ogre::Radian& getTurningRate() const ;

        /// Debug printing
        std::string toString() const ;

      // @}

      private:

        /// Basic physic simulation, used for internal tests only.
        void simulateClassic(const Ogre::Vector3& force) ;

        /// Basic physic simulation, used for internal tests only.
        void simulateNew(const Ogre::Vector3& force) ;


        Ogre::Vector3 m_position ;

        Ogre::Vector3 m_speed ;

        Ogre::Quaternion m_orientation ;

        /// Maximum speed of the vehicle.
        float m_max_speed ;

        /// Radius of the vehicle.
        float m_radius ;

        /// Maximum directional steering, for example in degree per seconds.
        Ogre::Radian m_turning_rate ;

      };
    }
  }
}
