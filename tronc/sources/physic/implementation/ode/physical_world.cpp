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

#include <OgreStringConverter.h>

#include <kernel/log.h>
#include <kernel/parameters.h>
#include <kernel/exception.h>

#include <model/collision.h>
#include <model/positioned.h>

#include <physic/implementation/ode/solid.h>
#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/collideable.h>
#include <physic/implementation/ode/physical_world.h>
#include <model/mobile.h>
#include <model/energy.h>
#include <model/massive.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      namespace Ode
      {

        RegisterControler(PhysicalWorld,
                          Model::PhysicalWorld,
                          PhysicSystem) ;


        void PhysicalWorld::onInit()
        {
          InternalMessage("Physic","Physic::PhysicalWorld::onInit entering " +
                                   Kernel::toString(getObject()->getIdentifier())) ;

          Kernel::Log::Block temp("Physic","PhysicalWorld::onInit") ;
          m_world = new dWorld() ;

          dWorldSetCFM(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldCFM")) ;
          dWorldSetERP(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldERP")) ;
          dWorldSetContactSurfaceLayer(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldContactSurfaceLayer")) ;
//          dWorldSetContactMaxCorrectingVel(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldContactMaxCorrectingVelocity")) ;

          m_collision_space = new dSimpleSpace(0) ;

          m_contact_group = dJointGroupCreate(0) ;
        }

        void PhysicalWorld::onClose()
        {
          InternalMessage("Physic","Physic::PhysicalWorld::onClose entering " +
                                   Kernel::toString(getObject()->getIdentifier())) ;

          if (m_world)
          {
            delete m_world ;
          }

          if (m_collision_space)
          {
            delete m_collision_space ;
          }

          InternalMessage("Physic","Physic::PhysicalWorld::onClose leaving " +
                                   Kernel::toString(getObject()->getIdentifier())) ;
        }

        void PhysicalWorld::onChangeParent(Kernel::Object* i_old_parent)
        {
        }

        void PhysicalWorld::onUpdate()
        {
        }

        dWorld* PhysicalWorld::getWorld() const
        {
          return m_world ;
        }

        dSpace* PhysicalWorld::getCollisionSpace() const
        {
          return m_collision_space ;
        }

        void PhysicalWorld::onSpaceCollision(void*   world,
                                             dGeomID space1,
                                             dGeomID space2)
        {
          // due to organization space1 and space2 are spaces.
          dSpaceCollide2(space1,
                         space2,
                         world,
                         PhysicalWorld::onGeometryCollision) ;
        }

        void PhysicalWorld::onGeometryCollision(void*   parameter,
                                                dGeomID geometry1,
                                                dGeomID geometry2)
        {
          // due to organization geometry1 and geometry2 are not spaces.
          InternalMessage("Physic","PhysicalWorld::onGeometryCollision entering") ;

          if (! Collideable::canCollide(geometry1,geometry2))
            return ;

          // parameter is in fact a world.
          PhysicalWorld* world = static_cast<PhysicalWorld*>(parameter) ;

          if (!world)
          {
            return ;
          }

          // Retrieve useful objects
          Collideable* collideable1 = static_cast<Collideable*>(dGeomGetData(geometry1)) ;
          Collideable* collideable2 = static_cast<Collideable*>(dGeomGetData(geometry2)) ;
          PhysicalObject* object1 = collideable1 ? collideable1->getControler()->getControler<PhysicalObject>()
                                                 : NULL ;
          PhysicalObject* object2 = collideable2 ? collideable2->getControler()->getControler<PhysicalObject>()
                                                 : NULL ;

          InternalMessage("Physic","PhysicalWorld::onGeometryCollision "
                          + (object1 ? Kernel::toString(object1->getObject()->getIdentifier()) : "no object1")
                          + " "
                          + (object2 ? Kernel::toString(object2->getObject()->getIdentifier()) : "no object2")
                          + (collideable1->isCollideableWith(collideable2) ? " collideable" : "not collideable")
                          ) ;

          if (object1 && object2)
          {
            // object positions
            Ogre::Vector3 object1_position ;
            Ogre::Vector3 object2_position ;

            const dReal* temp_position ;
            temp_position = dBodyGetPosition(object1->getBody()->id()) ;
            object1_position.x = temp_position[0] ;
            object1_position.y = temp_position[1] ;
            object1_position.z = temp_position[2] ;

            temp_position = dBodyGetPosition(object2->getBody()->id()) ;
            object2_position.x = temp_position[0] ;
            object2_position.y = temp_position[1] ;
            object2_position.z = temp_position[2] ;

            InternalMessage("Physic","PhysicalWorld::onGeometryCollision object positions "
                            + Ogre::StringConverter::toString(object1_position)
                            + ";"
                            + Ogre::StringConverter::toString(object2_position)) ;


            // calculate contact points
            int number_of_contacts = dCollide(geometry1,
                                              geometry2,
                                              maximum_contact_points,
                                              contact_points,
                                              sizeof(dContactGeom)) ;

            InformationMessage("Physic","number of contact points = " + Kernel::toString(number_of_contacts)) ;

            Ogre::Vector3 result(0,0,0) ;

            int real_number_of_contact_points = 0 ;
            Ogre::Vector3 average_contact_point(0,0,0) ;

            for (int contact_index = 0 ;
                 contact_index < number_of_contacts ;
                 ++contact_index)
            {

              // create contact joint
              dContact contact ;
              contact.surface.mode = dContactSoftCFM|dContactSoftERP|dContactBounce|dContactSlip1|dContactSlip2 ;
              contact.surface.mu = Kernel::Parameters::getValue<float>("Physic","ContactMu") ;
              contact.surface.mu2 = 0 ;
              contact.surface.bounce = Kernel::Parameters::getValue<float>("Physic","ContactBounce") ;
              contact.surface.bounce_vel = Kernel::Parameters::getValue<float>("Physic","ContactBounceVelocity") ;
              contact.surface.soft_erp = 0.5 ;
              contact.surface.soft_cfm = 0.5 ;
              contact.surface.motion1 = 0 ;
              contact.surface.motion2 = 0 ;
              contact.surface.slip1 = 0.5 ;
              contact.surface.slip2 = 0.5 ;
              contact.geom = contact_points[contact_index] ;

              Ogre::Vector3 contact_point(contact_points[contact_index].pos[0],
                                          contact_points[contact_index].pos[1],
                                          contact_points[contact_index].pos[2]) ;
              Ogre::Vector3 v1 = contact_point - object1_position ;

              Ogre::Vector3 normal(contact_points[contact_index].normal[0],
                                   contact_points[contact_index].normal[1],
                                   contact_points[contact_index].normal[2]) ;

              float dot1 = v1.dotProduct(normal) ;

              // magic ... to avoid contacts points that stick objects together
              /*
                Not symmetric
              */
              if (dot1 < 0)
              {
                average_contact_point += contact_point ;

                dJointID joint_id = dJointCreateContact(world->m_world->id(),
                                                        world->m_contact_group,
                                                        &contact) ;

                dJointAttach(joint_id,
                             object1->getBody()->id(),
                             object2->getBody()->id()) ;

                ++real_number_of_contact_points ;
              }
            }


            if (real_number_of_contact_points != 0)
            {
              average_contact_point = average_contact_point / real_number_of_contact_points ;

              Model::Position contact_point(Model::Position::Meter(average_contact_point.x,
                                                                   average_contact_point.y,
                                                                   average_contact_point.z)) ;
              // calculate energy of collision
              // get the relative speed at collision point
              Model::Speed relative_speed(object1->getSpeedAt(contact_point)-object2->getSpeedAt(contact_point)) ;
              // energy is 1/2 (m1+m2) v²
              Model::Energy collision_energy(object1->getTrait<Model::Massive>()->getMass()+object2->getTrait<Model::Massive>()->getMass(),relative_speed) ;

              // create a collision object
              Kernel::Object* collision_object = world->getObject()->createObject() ;
              collision_object->addTrait(new Model::Collision(
                                     collideable1->getControler()->getObject(),
                                     collideable2->getControler()->getObject(),
                                     collision_energy)) ;
              collision_object->addTrait(new Model::Positioned(contact_point)) ;
            }

          }
        }

        void PhysicalWorld::prepare()
        {
          m_has_been_simulated = false ;
        }

        void PhysicalWorld::simulate(const float& seconds)
        {
          InternalMessage("Physic","Physic::PhysicalWorld::simulate " +
                                   Kernel::toString(getObject()->getIdentifier()) +
                                   " Entering") ;

          if (!m_collision_space)
          {
            ErrorMessage("Physic::PhysicalWorld no collision space") ;
            throw Kernel::Exception("no collision space") ;
          }
          /// simulate
          /*
            collision detection
          */
          if (Kernel::Parameters::getValue<bool>("Physic","ActivateCollision"))
          {
            dSpaceCollide(m_collision_space->id(),this,PhysicalWorld::onSpaceCollision) ;
          }

          InternalMessage("Physic","Physic::PhysicalWorld::simulate " +
                                   Kernel::toString(getObject()->getIdentifier()) +
                                   " trace#1") ;

          // physical part
          if (m_world)
          {
            dWorldStep(m_world->id(),seconds) ;
          }

          dJointGroupEmpty(m_contact_group) ;

          m_has_been_simulated = true ;

          InternalMessage("Physic","PhysicalWorld::simulate " +
                                   Kernel::toString(getObject()->getIdentifier()) +
                                   " Leaving") ;
        }

      }
    }
  }
}
