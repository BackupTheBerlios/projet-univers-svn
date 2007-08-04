/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <physic/implementation/ode/solid.h>
#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/ode.h>

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

          dWorldSetCFM(m_world->id(),0.001) ;
          dWorldSetERP(m_world->id(),1) ;
          dWorldSetContactSurfaceLayer(m_world->id(), 0.1f) ;
          dWorldSetContactMaxCorrectingVel(m_world->id(),5) ;
           
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
//          std::cout << "collision between " ;
//          
//          if (dGeomIsSpace(i_geometry1))
//          {
//            std::cout << "space " ; 
//          }
//          else
//          {
//            std::cout << "geometry " ; 
//          }
//            
//          std::cout << i_geometry1 << " and " ;
//          
//          if (dGeomIsSpace(i_geometry2))
//          {
//            std::cout << "space " ; 
//          }
//          else
//          {
//            std::cout << "geometry " ; 
//          }
//
//          std::cout << i_geometry2 << std::endl ;
          
          // i_world is a world.
          PhysicalWorld* world = static_cast<PhysicalWorld*>(i_world) ;
          
          if (!world)
          {
            return ;
          }

          // should call Solid callback...
          Solid* solid1 = dynamic_cast<Solid*>((Kernel::BaseControler*)dGeomGetData(i_geometry1)) ;  
          Solid* solid2 = dynamic_cast<Solid*>((Kernel::BaseControler*)dGeomGetData(i_geometry2)) ;  
          PhysicalObject* object1 = solid1 ? getPhysicalObject(solid1) : NULL ;
          PhysicalObject* object2 = solid2 ? getPhysicalObject(solid2) : NULL ;

          if (solid1 && solid2 && object1 && object2)
          {
            // call to custom callback function for gameplay reaction
            onCollide(solid1,solid2) ;
            
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
            
            // calculate contact points
            const int maximum_contact_points = 200 ;
            static dContactGeom contact_points[maximum_contact_points] ;
            int number_of_contacts = dCollide(i_geometry1,
                                              i_geometry2,
                                              maximum_contact_points,
                                              contact_points,
                                              sizeof(dContactGeom)) ;

            InformationMessage("number of contact points = " + toString(number_of_contacts)) ;

            Ogre::Vector3 result(0,0,0) ;
            
            for (int contact_index = 0 ; 
                 contact_index < number_of_contacts ; 
                 ++contact_index)
            {
              
              // test : set collision point to center of mass...               
//              contact_points[contact_index]
              
              
              // create contact joint
              dContact contact ;
              contact.surface.mode = dContactSoftCFM|dContactSoftERP ;
              contact.surface.mu = 0 ;
              contact.surface.mu2 = 0 ;
              contact.surface.bounce = 0 ;
              contact.surface.bounce_vel = 0 ;
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
  
              InformationMessage("contact point : depth=" 
                                 + toString(contact_points[contact_index].depth)
                                 + " normal(x=" 
                                 + toString(contact_points[contact_index].normal[0]) 
                                 + ",y=" 
                                 + toString(contact_points[contact_index].normal[1]) 
                                 + ",z=" 
                                 + toString(contact_points[contact_index].normal[2]) 
                                 + ") point(x=" 
                                 + toString(contact_points[contact_index].pos[0]) 
                                 + ",y=" 
                                 + toString(contact_points[contact_index].pos[1]) 
                                 + ",z=" 
                                 + toString(contact_points[contact_index].pos[2]) 
                                 + ")" 
                                 ) ;

              Ogre::Vector3 point(contact_points[contact_index].pos[0],
                                  contact_points[contact_index].pos[1],
                                  contact_points[contact_index].pos[2]) ;

              Ogre::Vector3 v1 = point - object1_position ;
              Ogre::Vector3 v2 = point - object2_position ;
              

              Ogre::Vector3 temp(contact_points[contact_index].normal[0],
                                 contact_points[contact_index].normal[1],
                                 contact_points[contact_index].normal[2]) ;
              
              float dot1 = v1.dotProduct(temp) ;
              float dot2 = v2.dotProduct(temp) ;

              InformationMessage("dot products dot1=" 
                                 + toString(dot1)
                                 + " dot2=" 
                                 + toString(dot2)
                                 ) ;
              result += contact_points[contact_index].depth*temp ;
              
              if (dot1 < 0)
              {
                dJointID joint_id = dJointCreateContact(world->m_world->id(), 
                                                        world->m_contact_group, 
                                                        &contact) ;
                
                if (i_geometry1 != contact_points[contact_index].g1 ||
                    i_geometry2 != contact_points[contact_index].g2)
                {
                  std::cout << "faut pas s'ettonner si ca marche pas " << std::endl ;
                }
                
                dJointAttach(joint_id,
                             object1->getBody()->id(),
                             object2->getBody()->id()) ;
              }
            }
            
            if (number_of_contacts != 0)
            {
              result = result / number_of_contacts ;
            }
            
            InformationMessage("average contact point : depth=" 
                               + toString(result.length())
                               + " normal(x=" 
                               + toString(result.x) 
                               + ",y=" 
                               + toString(result.y) 
                               + ",z=" 
                               + toString(result.z) 
                               + ")" 
                               ) ;
          
          }          
        }
        
        void PhysicalWorld::simulate(const float& i_seconds)
        {
          InternalMessage("Physic::PhysicalWorld::simulate " + getObject()->getName() + " Entering") ;
//          InformationMessage("PhysicalWorld::simulate " + toString((float)i_seconds)) ;
          
          check(m_collision_space,"no collision space") ;
          /// simulate
          /* 
            collision detection
            
          */
//          dSpaceCollide(m_collision_space->id(),this,PhysicalWorld::onSpaceCollision) ;
          
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
