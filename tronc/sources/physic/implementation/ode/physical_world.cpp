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

#include <OgreStringConverter.h>

#include <kernel/log.h>
#include <kernel/parameters.h>

#include <model/model.h>
#include <model/collision.h>

#include <physic/implementation/ode/solid.h>
#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/collideable.h>
#include <physic/implementation/ode/physical_world.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        RegisterControler(PhysicalWorld, 
                          Model::PhysicalWorld, 
                          PhysicSystem) ;


        PhysicalWorld::PhysicalWorld(Model::PhysicalWorld* i_object,
                                     PhysicSystem*         i_physic)
        : Kernel::Controler<Model::PhysicalWorld,
                            PhysicSystem>(i_object,i_physic),
          m_world(NULL),
          m_collision_space(NULL)
        {}

        void PhysicalWorld::onInit()
        {
          InternalMessage("PhysicalWorld::onInit entering") ;
          if (m_world)
          {
            delete m_world ;
          }
          m_world = new dWorld() ;

          dWorldSetCFM(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldCFM")) ;
          dWorldSetERP(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldERP")) ;
          dWorldSetContactSurfaceLayer(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldContactSurfaceLayer")) ;
          dWorldSetContactMaxCorrectingVel(m_world->id(),Kernel::Parameters::getValue<float>("Physic","WorldContactMaxCorrectingVelocity")) ;
           
          if (m_collision_space)
          {
            delete m_collision_space ;
          }
          
          m_collision_space = new dSimpleSpace(0) ;

          m_contact_group = dJointGroupCreate(0) ;
                    
          InternalMessage("PhysicalWorld::onInit leaving") ;
        }

        void PhysicalWorld::onClose()
        {
          InternalMessage("Physic::PhysicalWorld::onClose entering " + getObject()->getName()) ;

          if (m_world)
          {
            delete m_world ;
          }

          if (m_collision_space)
          {
            delete m_collision_space ;
          }
          
          InternalMessage("Physic::PhysicalWorld::onClose leaving " + getObject()->getName()) ;
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
        
        void PhysicalWorld::onSpaceCollision(void*   i_world,
                                             dGeomID i_space1,
                                             dGeomID i_space2)
        {
          // due to organisation i_space1 and i_space2 are spaces.
//          std::cout << "collision between two spaces" << std::endl ;
          
          dSpaceCollide2(i_space1,
                         i_space2,
                         i_world,
                         PhysicalWorld::onGeometryCollision) ;
        }

        void PhysicalWorld::onGeometryCollision(void*   i_world,
                                                dGeomID i_geometry1,
                                                dGeomID i_geometry2)
        {
          // due to organisation i_geometry1 and i_geometry2 are not spaces.
//          std::cout << "soupscon de collision" << std::endl ;
          InternalMessage("PhysicalWorld::onGeometryCollision entering") ;
          
          // i_world is in fact a world.
          PhysicalWorld* world = static_cast<PhysicalWorld*>(i_world) ;
          
          if (!world)
          {
            return ;
          }
          
          // retreive usefull objects
          Collideable* collideable1 
            = static_cast<Collideable*>(dGeomGetData(i_geometry1)) ;  
          Collideable* collideable2 
            = static_cast<Collideable*>(dGeomGetData(i_geometry2)) ;  
          PhysicalObject* object1 
            = collideable1 ? getPhysicalObject(collideable1->getControler()) 
                           : NULL ;
          PhysicalObject* object2 
            = collideable2 ? getPhysicalObject(collideable2->getControler()) 
                           : NULL ;

          InternalMessage("PhysicalWorld::onGeometryCollision "
                          + (object1 ? object1->getObject()->getName() : "no object1")
                          + " " 
                          + (object2 ? object2->getObject()->getName() : "no object2")
                          + (collideable1->isCollideableWith(collideable2) ? " collideable" : "not collideable")
                          ) ;

          if (object1 && object2 
              && collideable1->isCollideableWith(collideable2))
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
            
            InternalMessage("PhysicalWorld::onGeometryCollision object positions " 
                            + Ogre::StringConverter::toString(object1_position)
                            + ";"
                            + Ogre::StringConverter::toString(object2_position)) ;
                            
            
            // calculate contact points
            int number_of_contacts = dCollide(i_geometry1,
                                              i_geometry2,
                                              maximum_contact_points,
                                              contact_points,
                                              sizeof(dContactGeom)) ;

            InformationMessage("number of contact points = " + Kernel::toString(number_of_contacts)) ;

            Ogre::Vector3 result(0,0,0) ;
            
            int real_number_of_contact_points = 0 ;
            Ogre::Vector3 average_contact_point(0,0,0) ;
            
            for (int contact_index = 0 ; 
                 contact_index < number_of_contacts ; 
                 ++contact_index)
            {
             
              // create contact joint
              dContact contact ;
              contact.surface.mode = dContactSoftCFM|dContactSoftERP ;
              contact.surface.mu = Kernel::Parameters::getValue<float>("Physic","ContactMu") ;
              contact.surface.mu2 = 0 ;
              contact.surface.bounce = Kernel::Parameters::getValue<float>("Physic","ContactBounce") ;
              contact.surface.bounce_vel = Kernel::Parameters::getValue<float>("Physic","ContactBounceVelocity") ;
              contact.surface.soft_erp = 1 ;
              contact.surface.soft_cfm = 1 ;
              contact.surface.motion1 = 0 ;
              contact.surface.motion2 = 0 ;
              contact.surface.slip1 = 0 ;
              contact.surface.slip2 = 0 ;
              contact.geom = contact_points[contact_index] ;
              contact.fdir1[0] = 0 ;
              contact.fdir1[1] = 0 ;
              contact.fdir1[2] = 0 ;
              contact.fdir1[3] = 0 ;

              Ogre::Vector3 point(contact_points[contact_index].pos[0],
                                  contact_points[contact_index].pos[1],
                                  contact_points[contact_index].pos[2]) ;
              Ogre::Vector3 v1 = point - object1_position ;
              

              Ogre::Vector3 normal(contact_points[contact_index].normal[0],
                                   contact_points[contact_index].normal[1],
                                   contact_points[contact_index].normal[2]) ;
              
              float dot1 = v1.dotProduct(normal) ;
              
              if (dot1 < 0)
              {
                average_contact_point += point ; 
                
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
          
              // create a collision object
              Kernel::Object* collision_object = Model::createObject(world->getObject()) ;
              
              Model::Collision* collision_trait = 
                new Model::Collision(collideable1->getControler()->getObject(),
                                     collideable2->getControler()->getObject(),
                                     Model::Position::Meter(average_contact_point.x,
                                                            average_contact_point.y,
                                                            average_contact_point.z)) ;
              Model::addTrait(collision_object,collision_trait) ;
            }
          
          }          
        }
        
        void PhysicalWorld::simulate(const float& i_seconds)
        {
          InternalMessage("Physic::PhysicalWorld::simulate " + getObject()->getName() + " Entering") ;
//          InformationMessage("PhysicalWorld::simulate " + Kernel::toString((float)i_seconds)) ;
          
          CHECK(m_collision_space,"no collision space") ;
          /// simulate
          /* 
            collision detection
            
          */
          if (Kernel::Parameters::getValue<bool>("Physic","ActivateCollision"))
          {
            dSpaceCollide(m_collision_space->id(),this,PhysicalWorld::onSpaceCollision) ;
          }
                  
          InternalMessage("Physic::PhysicalWorld::simulate " + getObject()->getName() + " trace#1") ;
          
          // physical part
          if (m_world)
          {
            dWorldStep(m_world->id(),i_seconds) ;
          }

          dJointGroupEmpty(m_contact_group) ;

          InternalMessage("PhysicalWorld::simulate " + getObject()->getName() + " Leaving") ;
        }
        
      }
    }
  }
}
