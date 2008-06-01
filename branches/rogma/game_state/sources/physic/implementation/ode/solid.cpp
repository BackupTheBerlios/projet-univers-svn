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
#define __cpluplus
#include <ode/ode.h>

#include <kernel/log.h>

#include <model/positionned.h>
#include <model/physical_world.h>
#include <model/physical_object.h>

#include <physic/implementation/ode/mass_property.h>

#include <physic/implementation/ode/ode.h>

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
        : Kernel::Controler<Model::Solid,PhysicSystem>(i_object,i_physic)
        {}

        /*
          geom is put in the world's space
        */
        void Solid::onInit()
        {
          onInitCollideable() ;
        }

        void Solid::onClose()
        {
          onCloseCollideable() ;
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
          
          InternalMessage("Physic","Physic::Implementation::Ode::Solid::createGeometry trace#0") ;
          getTrait()->getMesh().getMeshInformation(vertices,indices,scale) ;

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

            m_data = dGeomTriMeshDataCreate() ;

            dGeomTriMeshDataBuildSingle(m_data,
                                        m_vertices,3*sizeof(dReal),(int)vertices.size(),
                                        m_indices,(int)indices.size(),3*sizeof(int)) ;
                                  
            m_geometry1 = dCreateTriMesh(i_space,m_data,0,0,0);
            dGeomSetData(m_geometry1,m_data) ;
            dGeomSetCollideBits(m_geometry1,(unsigned long)Collideable::Solid) ;
            createApproximatedGeometry(i_space) ;
            InternalMessage("Physic","Physic::Implementation::Ode::Solid::createGeometry trace#5") ;
          }
        }
        
        void Solid::createApproximatedGeometry(const dSpaceID& space)
        {
          m_geometry2 = dCreateSphere(space,getTrait()->getRadius().Meter()) ;
          dGeomSetCollideBits(m_geometry2,(unsigned long)Collideable::ApproximatedSolid) ;
        }
        
        const Kernel::BaseControler* Solid::getControler() const
        {
          return this ;
        }

        bool Solid::isCollideableWith(const Collideable*) const
        {
          return true ;
        }

      }
    }
  }
}
