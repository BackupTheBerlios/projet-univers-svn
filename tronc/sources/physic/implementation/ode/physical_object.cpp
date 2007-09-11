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

#include <model/massive.h>
#include <model/mobile.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/physical_world.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        RegisterControler(PhysicalObject, 
                          Model::PhysicalObject, 
                          PhysicSystem) ;


        PhysicalObject::PhysicalObject(Model::PhysicalObject* i_object,
                                       PhysicSystem*          i_physic)
        : Kernel::Controler<Model::PhysicalObject,
                            PhysicSystem>(i_object,i_physic),
          m_body(NULL),
          m_collision_space(NULL)
        {}
        
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
          InternalMessage("PhysicalObject::onInit entering " + getObject()->getName()) ;
          
          PhysicalWorld* world = getPhysicalWorld(this) ; 
          if (world)
          {
            m_body = new dBody() ;
            m_body->create(world->getWorld()->id()) ;
  
            /// set the inital values :
            updatePositionned() ;          
            updateMobile() ;
            updateMassive() ;
            
            // an object is a space in the world's space.
            m_collision_space = new dSimpleSpace(world->getCollisionSpace()->id()) ;
          }
          else
          {
            InternalMessage("PhysicalObject::onInit could not build ode object " + getObject()->getName()) ;
          }
          InternalMessage("PhysicalObject::onInit leaving " + getObject()->getName()) ;

        }

        void PhysicalObject::onClose()
        {
          InternalMessage("Ode::PhysicalObject::onClose entering " + getObject()->getName()) ;

          if (m_body)
          {
            delete m_body ;
            m_body = NULL ;
          }
          InternalMessage("Ode::PhysicalObject::onClose leaving " + getObject()->getName()) ;
        }

        void PhysicalObject::onChangeParent(Kernel::Object* i_old_parent)
        {
          /// 1. remove body from old parent
          
          
          /// 2. onInit
          onInit() ;
        }

        void PhysicalObject::onUpdate()
        {
          InternalMessage("Physic::PhysicalObject::onUpdate Entering " +getObject()->getName()) ; 
          if (! m_is_being_updated && m_body)
          {
            /*!
              Somehow brutal...
            */ 
            
            updatePositionned() ;          
            updateMobile() ;
            updateMassive() ;
          }
          InternalMessage("Physic::PhysicalObject::onUpdate Leaving " +getObject()->getName()) ; 
        }

        void PhysicalObject::updateMobile()
        {
          Model::Mobile* mobile = getObject()->getTrait<Model::Mobile>() ;

          Ogre::Vector3 speed = mobile->getSpeed().MeterPerSecond() ;
          
          InternalMessage("PhysicalObject::updateMobile initial speed=" 
                                       + Kernel::toString(speed[0]) + ","
                                       + Kernel::toString(speed[1]) + ","
                                       + Kernel::toString(speed[2])) ;

          m_body->setLinearVel(speed[0],speed[1],speed[2]) ;

          Ogre::Vector3 angularSpeed = mobile->getAngularSpeed().RadianPerSecond() ;
          InternalMessage("PhysicalObject::updateMobile angular speed="
                          + Kernel::toString(angularSpeed[0]) + "," 
                          + Kernel::toString(angularSpeed[1]) + "," 
                          + Kernel::toString(angularSpeed[2])); 

          m_body->setAngularVel(angularSpeed[0],angularSpeed[1],angularSpeed[2]) ;
        }
        
        void PhysicalObject::updateMassive()
        {
          Model::Massive* massive = getObject()->getTrait<Model::Massive>() ;
          check(massive,"PhysicalObject::updateMassive no Massive trait") ;
          Model::Mass mass = massive->getMass() ;
          
//          dMass ode_mass ;
//          m_body->getMass(&ode_mass) ;
//          
//          std::cout << "mass = " << ode_mass.mass << std::endl ;
          
          //m_body->setMass(mass.Kilogram())
          
        }
        
        void PhysicalObject::updatePositionned()
        {
          
          /// have to take the position relatively to the physical_world parent 
          PhysicalWorld* world = getPhysicalWorld(this) ;
          if (world)
          {
            Model::Positionned* positionned = getObject()->getTrait<Model::Positionned>() ;
          
            Ogre::Vector3 position = positionned->getPosition(world->getObject()).Meter() ;
            m_body->setPosition((dReal)position.x,
                                (dReal)position.y,
                                (dReal)position.z) ;

            Model::Oriented* oriented = 
              getObject()->getTrait<Model::Oriented>() ;
            if (oriented)
            {
              Ogre::Quaternion orientation = 
                oriented->getOrientation(world->getObject()).getQuaternion() ;
              
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
          InternalMessage("Ode::PhysicalObject::simulate " + getObject()->getName() + " entering") ;
          updateModelPositionned() ;
          updateModelMobile() ;
          InternalMessage("Ode::PhysicalObject::simulate " + getObject()->getName() + " leaving") ;
        }

        void PhysicalObject::updateModelPositionned()
        {
          m_is_being_updated = true ;
          
          /*!
            Very brutal
            
            if the object has not moved, there is no reason to change position
            
          */
          Model::Positionned* 
              positionned = getObject()->getTrait<Model::Positionned>() ;

          PhysicalWorld* world = getPhysicalWorld(this) ;
          if (world)
          {
          
            /*! 
              the position of the body is relative to the position of the world
              in general, the world will be the direct parent of the body but 
              it may be different in the future
            */
            const dReal* ode_position = m_body->getPosition() ;

            InternalMessage("Ode::PhysicalObject::updateModelPositionned "
                            + getObject()->getName() + " position="
                            + Kernel::toString(ode_position[0]) + "," 
                            + Kernel::toString(ode_position[1]) + "," 
                            + Kernel::toString(ode_position[2])) ; 
                                
            positionned->setPosition(Model::Position::Meter(
                                       ode_position[0],
                                       ode_position[1],
                                       ode_position[2]),
                                     world->getObject()) ;
  
            Model::Oriented* oriented = 
              getObject()->getTrait<Model::Oriented>() ;
            if (oriented)
            {
              const dReal* ode_orientation = m_body->getQuaternion() ;
    
              InternalMessage("Ode::PhysicalObject::updateModelPositionned "
                              + getObject()->getName() + " orientation="
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
                                       world->getObject()) ;
            }
                        
          }          
          m_is_being_updated = false ;
          
        }
      
        void PhysicalObject::updateModelMobile()
        {
          m_is_being_updated = true ;

          Model::Mobile* 
              mobile = getObject()->getTrait<Model::Mobile>() ;

          PhysicalWorld* world = getPhysicalWorld(this) ;
          if (world)
          {
            const dReal* speed = m_body->getLinearVel() ;

            InformationMessage("Ode::PhysicalObject::updateModelMobile new linear speed=" 
                            + Kernel::toString(speed[0]) + "," 
                            + Kernel::toString(speed[1]) + "," 
                            + Kernel::toString(speed[2])) ; 

            mobile->setSpeed(Model::Speed::MeterPerSecond(
                                  speed[0],speed[1],speed[2])) ;
            
            const dReal* angular_speed = m_body->getAngularVel() ;
            
            
            mobile->setAngularSpeed(Model::AngularSpeed::RadianPerSecond(
                                        angular_speed[0],
                                        angular_speed[1],
                                        angular_speed[2])) ;
            
          }
          
          m_is_being_updated = false ;
        }
      }
    }
  }
}
