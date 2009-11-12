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
#include <ode/ode.h>

#include <kernel/log.h>
#include <kernel/string.h>

#include <model/massive.h>
#include <model/mobile.h>
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/physical_world.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      DeclareDeducedTrait(PhysicalObject,And(HasTrait(Model::PhysicalObject),
                                             HasAncestor(HasTrait(Model::PhysicalWorld))))

      namespace Ode
      {


        RegisterControler(PhysicalObject,
                          Implementation::PhysicalObject,
                          PhysicSystem) ;

        dBody* PhysicalObject::getBody() const
        {
          return m_body ;
        }

        dSpace* PhysicalObject::getCollisionSpace() const
        {
          return m_collision_space ;
        }

        void PhysicalObject::onInit()
        {
          Kernel::Log::Block temp("Physic","PhysicalObject::onInit " + Kernel::toString(getObject()->getIdentifier())) ;

          m_is_being_updated = false ;
          m_body = NULL ;
          m_collision_space = NULL ;

          m_world = getAncestorControler<PhysicalWorld>() ;
          if (m_world)
          {
            m_body = new dBody() ;
            m_body->create(m_world->getWorld()->id()) ;

            /// set the initial values :
            updatePositioned() ;
            updateMobile() ;
            updateMassive() ;

            // an object is a space in the world's space.
            m_collision_space = new dSimpleSpace(m_world->getCollisionSpace()->id()) ;
          }
          else
          {
            InternalMessage("Physic","PhysicalObject::onInit could not build ode object " +
                                     Kernel::toString(getObject()->getIdentifier())) ;
          }
          InternalMessage("Physic","PhysicalObject::onInit leaving " +
                                    Kernel::toString(getObject()->getIdentifier())) ;

        }

        void PhysicalObject::onClose()
        {
          InternalMessage("Physic","Ode::PhysicalObject::onClose entering " +
                                    Kernel::toString(getObject()->getIdentifier())) ;

          if (m_body)
          {
            delete m_body ;
            m_body = NULL ;
          }
          if (m_collision_space)
          {
            delete m_collision_space ;
            m_collision_space = NULL ;
          }

          m_world = NULL ;

          InternalMessage("Physic","Ode::PhysicalObject::onClose leaving " +
                                   Kernel::toString(getObject()->getIdentifier())) ;
        }

        void PhysicalObject::onChangeParent(Kernel::Object* i_old_parent)
        {
          /// 1. remove body from old parent


          /// 2. onInit
          onInit() ;
        }

        void PhysicalObject::onUpdate()
        {
          InternalMessage("Physic","Physic::PhysicalObject::onUpdate Entering " +
                                   Kernel::toString(getObject()->getIdentifier())) ;
          if (! m_is_being_updated && m_body)
          {
            /*!
              Somehow brutal...
            */
            m_world = getAncestorControler<PhysicalWorld>() ;
            updatePositioned() ;
            updateMobile() ;
            updateMassive() ;
          }
          InternalMessage("Physic","Physic::PhysicalObject::onUpdate Leaving " +
                                   Kernel::toString(getObject()->getIdentifier())) ;
        }

        void PhysicalObject::updateMobile()
        {
          Model::Mobile* mobile = getObject()->getTrait<Model::Mobile>() ;

          Ogre::Vector3 speed = mobile->getSpeed().MeterPerSecond() ;

          InternalMessage("Physic","PhysicalObject::updateMobile initial speed="
                                       + Kernel::toString(speed[0]) + ","
                                       + Kernel::toString(speed[1]) + ","
                                       + Kernel::toString(speed[2])) ;

          m_body->setLinearVel(speed[0],speed[1],speed[2]) ;

          Ogre::Vector3 angularSpeed = mobile->getAngularSpeed().RadianPerSecond() ;
          InternalMessage("Physic","PhysicalObject::updateMobile angular speed="
                          + Kernel::toString(angularSpeed[0]) + ","
                          + Kernel::toString(angularSpeed[1]) + ","
                          + Kernel::toString(angularSpeed[2]));

          m_body->setAngularVel(angularSpeed[0],angularSpeed[1],angularSpeed[2]) ;
        }

        void PhysicalObject::updateMassive()
        {
          Model::Massive* massive = getObject()->getTrait<Model::Massive>() ;
          Model::Mass mass = massive->getMass() ;

          InternalMessage("Physic","PhysicalObject::updateMassive mass="
                                       + Kernel::toString(mass.Kilogram())) ;

          if (mass.Kilogram() < 0)
          {
            ErrorMessage("PhysicalObject::updateMassive") ;
            throw std::exception() ;
          }

          dMass ode_mass ;
          dMassSetSphereTotal(&ode_mass,1,1) ;
          m_body->setMass(&ode_mass) ;
        }

        void PhysicalObject::updatePositioned()
        {
          /// have to take the position relatively to the physical_world parent
          if (m_world)
          {
            Model::Positioned* positioned = getObject()->getTrait<Model::Positioned>() ;

            Ogre::Vector3 position = positioned->getPosition(m_world->getObject()).Meter() ;
            m_body->setPosition((dReal)position.x,
                                (dReal)position.y,
                                (dReal)position.z) ;

            Model::Oriented* oriented = getObject()->getTrait<Model::Oriented>() ;
            if (oriented)
            {
              Ogre::Quaternion orientation = oriented->getOrientation(m_world->getObject()).getQuaternion() ;

              dQuaternion ode_quaternion ;
              ode_quaternion[0] = (dReal)orientation.w ;
              ode_quaternion[1] = (dReal)orientation.x ;
              ode_quaternion[2] = (dReal)orientation.y ;
              ode_quaternion[3] = (dReal)orientation.z ;

              m_body->setQuaternion(ode_quaternion) ;
            }

          }
        }

        /*!
          @name Active part
          Modify the model according to physic simulation
        */
        void PhysicalObject::simulate(const float&)
        {
          InternalMessage("Physic","Ode::PhysicalObject::simulate " +
                                   Kernel::toString(getObject()->getIdentifier()) +
                                   " entering") ;

          if (!m_world->m_has_been_simulated)
            InternalMessage("Physic","Ode::PhysicalObject::simulate error") ;

          updateModelPositioned() ;
          updateModelMobile() ;
          InternalMessage("Physic","Ode::PhysicalObject::simulate " +
                                   Kernel::toString(getObject()->getIdentifier()) +
                                   " leaving") ;
        }

        void PhysicalObject::updateModelPositioned()
        {
          m_is_being_updated = true ;

          /*!
            Very brutal

            if the object has not moved, there is no reason to change position

          */
          Model::Positioned*
              positioned = getObject()->getTrait<Model::Positioned>() ;

          if (m_world)
          {

            /*!
              the position of the body is relative to the position of the world
              in general, the world will be the direct parent of the body but
              it may be different in the future
            */
            const dReal* ode_position = m_body->getPosition() ;

            InternalMessage("Physic","Ode::PhysicalObject::updateModelPositioned "
                            + Kernel::toString(getObject()->getIdentifier()) + " position="
                            + Kernel::toString(ode_position[0]) + ","
                            + Kernel::toString(ode_position[1]) + ","
                            + Kernel::toString(ode_position[2])) ;

            positioned->setPosition(Model::Position::Meter(
                                       ode_position[0],
                                       ode_position[1],
                                       ode_position[2]),
                                       m_world->getObject()) ;

            Model::Oriented* oriented = getObject()->getTrait<Model::Oriented>() ;
            if (oriented)
            {
              const dReal* ode_orientation = m_body->getQuaternion() ;

              InternalMessage("Physic","Ode::PhysicalObject::updateModelPositioned "
                              + Kernel::toString(getObject()->getIdentifier()) + " orientation="
                              + Kernel::toString(ode_orientation[0]) + ","
                              + Kernel::toString(ode_orientation[1]) + ","
                              + Kernel::toString(ode_orientation[2]) + ","
                              + Kernel::toString(ode_orientation[3])) ;

              oriented->setOrientation(Model::Orientation(
                                            Ogre::Quaternion(
                                               ode_orientation[0],
                                               ode_orientation[1],
                                               ode_orientation[2],
                                               ode_orientation[3])),
                                       m_world->getObject()) ;
            }

          }
          m_is_being_updated = false ;
        }

        void PhysicalObject::updateModelMobile()
        {
          m_is_being_updated = true ;

          Model::Mobile*
              mobile = getObject()->getTrait<Model::Mobile>() ;

          if (m_world)
          {
            const dReal* speed = m_body->getLinearVel() ;

            InformationMessage("Physic","Ode::PhysicalObject::updateModelMobile new linear speed="
                            + Kernel::toString(speed[0]) + ","
                            + Kernel::toString(speed[1]) + ","
                            + Kernel::toString(speed[2])) ;

            mobile->setSpeed(Model::Speed::MeterPerSecond(
                                  (float)speed[0],(float)speed[1],(float)speed[2])) ;

            const dReal* angular_speed = m_body->getAngularVel() ;


            mobile->setAngularSpeed(Model::AngularSpeed::RadianPerSecond(
                                        (float)angular_speed[0],
                                        (float)angular_speed[1],
                                        (float)angular_speed[2])) ;

          }

          m_is_being_updated = false ;
        }

        Model::Speed PhysicalObject::getSpeedAt(const Model::Position& position) const
        {
          dVector3 velocity_meter_per_second ;
          dBodyGetPointVel(getBody()->id(),
                           position.Meter().x,
                           position.Meter().y,
                           position.Meter().z,
                           velocity_meter_per_second) ;

          return Model::Speed::MeterPerSecond(velocity_meter_per_second[0],velocity_meter_per_second[1],velocity_meter_per_second[2]) ;

        }

      }
    }
  }
}
