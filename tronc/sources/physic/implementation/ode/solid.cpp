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
#define __cpluplus
#include <ode/ode.h>

#include <kernel/log.h>

#include <model/positionned.h>
#include <model/physical_world.h>
#include <model/physical_object.h>

#include <physic/implementation/ode/mass_property.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

#include <physic/implementation/ode/solid.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        RegisterControler(Solid, 
                          Model::Solid, 
                          PhysicSystem) ;

        Solid::Solid(Model::Solid* i_object,
                     PhysicSystem* i_physic)
        : Kernel::Controler<Model::Solid,PhysicSystem>(i_object,i_physic),
          m_geometry_id(0),
          m_geometry_placeable(NULL)
        {}

        /*
          geom is put in the world's space
        */
        void Solid::onInit()
        {
          InternalMessage("Physic::Implementation::Ode::Solid::onInit entering") ;
          
          /*
            We need the parent physical object and parent physical world 
          */
          PhysicalObject* body = getPhysicalObject(this) ;

          // precondition : physical object is initialised
          
          if (body)
          {
            body->_init() ;
            PhysicalWorld* world = getPhysicalWorld(body) ;
            
            if (world)
            {
              dSpaceID space_id = body->getCollisionSpace()->id() ; 

              createGeometry(space_id) ;
              if (m_geometry_id)
              {
                InternalMessage("Physic::Implementation::Ode::Solid::onInit trace#1") ;

                dGeomSetBody(m_geometry_id,body->getBody()->id()) ;
                
                dGeomSetData(m_geometry_id,this) ;

                InternalMessage("Physic::Implementation::Ode::Solid::onInit trace#1") ;

              }
//              createGeometry(0) ;
//              
//              m_geometry_placeable = new dGeomTransform(space_id) ;
//              m_geometry_placeable->setBody(body->getBody()->id()) ;
//              
//              world->registerSolid(m_geometry_placeable->id(),this) ;
//              
//              m_geometry_placeable->setGeom(m_geometry_id) ;
//              
//              /// geom placement is relative to body 
//              Ogre::Vector3 position = 
//                getObject()->getParent<Model::Positionned>()
//                           ->getPosition(body->getObject()).Meter() ;
//
//              dGeomSetOffsetPosition(m_geometry_placeable->id(),
//                                     (dReal)position.x,
//                                     (dReal)position.y,
//                                     (dReal)position.z) ;
              

            }
          }
          
          InternalMessage("Solid::onInit leaving") ;
          
        }

        void Solid::onClose()
        {
          InternalMessage("Solid::onClose entering") ;

          if (m_geometry_id)
          {
            dGeomDestroy(m_geometry_id) ;
            m_geometry_id = 0 ;
          }
          if (m_geometry_placeable)
          {
            delete m_geometry_placeable ;
            m_geometry_placeable = NULL ;
          }

          InternalMessage("Solid::onClose leaving") ;
        }

        void onCollide(Solid* i_solid1,Solid* i_solid2)
        {
//          if (i_solid1 && i_solid2)
//          {
//            /*!
//              get the speed and mass to calculate cinetic energy
//              and apply it to destroyable
//              
//              only a part of cinetic energy is converted into damage
//              
//              if one is laser beam then destroy it its full cinetic energy is 
//              applied as damage 
//            */
//            Model::Destroyable* destroyable1 
//              = i_solid1->getObject()->getTrait<Model::Destroyable>() ;
//            Model::Destroyable* destroyable2 
//              = i_solid2->getObject()->getTrait<Model::Destroyable>() ;
//
//            if (destroyable1 || destroyable2)
//            {
//              Model::Energy collision_energy ;
//              
//              
//            }
//          }
        }

        void Solid::onChangeParent(Kernel::Object* i_old_parent)
        {
        }
        
        void Solid::onUpdate()
        {
        }

        void Solid::createGeometry(const dSpaceID& i_space)
        {
          /// need to get the correct geom from volume.
          std::vector< ::Ogre::Vector3> vertices ;
          std::vector<unsigned long>    indices ;
          Ogre::Vector3                 scale(1,1,1) ;        
          
          InternalMessage("Physic::Implementation::Ode::Solid::createGeometry trace#0") ;
          getModel()->getMesh().getMeshInformation(vertices,indices,scale) ;

//          InternalMessage("Physic::Implementation::Ode::Solid::createGeometry trace#1") ;
          
          if (vertices.size()>0 && indices.size() > 0)
          {
            m_vertices = new dVector3[vertices.size()];
            m_indices = new int[indices.size()];
            
            for(unsigned int vertex_index = 0 ; 
                vertex_index < vertices.size() ; 
                ++vertex_index)
            {
              m_vertices[vertex_index][0] = (dReal)(vertices[vertex_index].x) ;
              m_vertices[vertex_index][1] = (dReal)(vertices[vertex_index].y) ;
              m_vertices[vertex_index][2] = (dReal)(vertices[vertex_index].z) ;
              m_vertices[vertex_index][3] = 0 ;
            }

            for(unsigned int index = 0 ; 
                index < indices.size() ; 
                ++index)
            {
              m_indices[index] = (int)indices[index] ;
            }

            // try with reverse order
//            for(unsigned int index = 0 ; 
//                index < indices.size() ; 
//                ++index)
//            {
//              m_indices[indices.size() - index -1] = (int)indices[index] ;
//            }
             

            m_data = dGeomTriMeshDataCreate() ;

//            InternalMessage("Physic::Implementation::Ode::Solid::createGeometry trace#2") ;

            dGeomTriMeshDataBuildSingle(m_data,
                                        m_vertices,3*sizeof(dReal),(int)vertices.size(),
                                        m_indices,(int)indices.size(),3*sizeof(int)) ;
                                  
//            dGeomTriMeshDataBuildSimple(m_data,
//                                        (const dReal*)m_vertices,
//                                        (int)vertices.size(),
//                                        (int*)m_indices,
//                                        (int)indices.size()); 

//            InternalMessage("Physic::Implementation::Ode::Solid::createGeometry trace#3") ;

            m_geometry_id = dCreateTriMesh(i_space,m_data,0,0,0);
            dGeomSetData(m_geometry_id,m_data) ;
            
//            InternalMessage("Physic::Implementation::Ode::Solid::createGeometry trace#4") ;
//
            InternalMessage("Physic::Implementation::Ode::Solid::createGeometry trace#5") ;
//            
//            std::cout << "aabb of geometry " << m_geometry_id << "=" ;
//            
//            for(int i = 1 ;i <= 6 ;++i)
//            {
//              std::cout << aabb[i-1] << " " ;
//            }
//            std::cout << std::endl ;


          }
        }

      }
    }
  }
}
