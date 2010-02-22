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

#include <model/positioned.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/solid.h>

#include <physic/implementation/ode/mass_property.h>
#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/physical_object.h>

#include <physic/implementation/ode/solid.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {

      DeclareDeducedTrait(SolidPhysicalObject,
                          And(HasTrait(Implementation::PhysicalObject),
                              HasTrait(Model::Solid))) ;

      namespace Ode
      {

        RegisterControler(Solid, 
                          Implementation::SolidPhysicalObject, 
                          PhysicSystem) ;


        /*
          geom is put in the world's space
        */
        void Solid::onInit()
        {
          onInitCollideable() ;
          memcpy(m_last_transform,dGeomTriMeshGetLastTransform(m_geometry1),16) ;
        }

        void Solid::onClose()
        {
          onCloseCollideable() ;
          delete m_vertices ;
          delete m_indices ;
        }

        void Solid::createGeometry(const dSpaceID& i_space)
        {
          /// need to get the correct geometry from volume.
          std::vector< ::Ogre::Vector3> vertices ;
          std::vector<unsigned long>    indices ;
          Ogre::Vector3                 scale(1,1,1) ;        
          
          m_vertices = NULL ;
          m_indices = NULL ;

          InternalMessage("Physic","Physic::Implementation::Ode::Solid::createGeometry trace#0") ;
          getObject()
            ->getTrait<Model::Solid>()
            ->getMesh().getMeshInformation(vertices,indices,scale) ;

          if (vertices.size()>0 && indices.size() > 0)
          {
            m_vertices = new float[vertices.size()*3];
            m_indices = new dTriIndex[indices.size()];
            
            for(unsigned int vertex_index = 0 ; 
                vertex_index < vertices.size() ; 
                ++vertex_index)
            {
              m_vertices[vertex_index+0] = (float)(vertices[vertex_index].x) ;
              m_vertices[vertex_index+1] = (float)(vertices[vertex_index].y) ;
              m_vertices[vertex_index+2] = (float)(vertices[vertex_index].z) ;
            }

            for(unsigned int index = 0 ; 
                index < indices.size() ; 
                ++index)
            {
              m_indices[index] = (int)indices[index] ;
            }

            m_data = dGeomTriMeshDataCreate() ;

            dGeomTriMeshDataBuildSingle(m_data,
                                        m_vertices,3*sizeof(float),(int)vertices.size(),
                                        m_indices,(int)indices.size(),3*sizeof(dTriIndex)) ;
                                  
            m_geometry1 = dCreateTriMesh(i_space,m_data,0,0,0);
            dGeomSetData(m_geometry1,m_data) ;
            dGeomSetCollideBits(m_geometry1,(unsigned long)Collideable::Solid) ;
            createApproximatedGeometry(i_space) ;
            InternalMessage("Physic","Physic::Implementation::Ode::Solid::createGeometry trace#5") ;
          }
        }
        
        void Solid::createApproximatedGeometry(const dSpaceID& space)
        {
          m_geometry2 = dCreateSphere(space,getObject()->getTrait<Model::Solid>()
                                                       ->getRadius().Meter()) ;
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

        void Solid::prepare()
        {
          memcpy(m_last_transform,m_current_transform,16) ;
          dGeomTriMeshSetLastTransform(m_geometry1,m_last_transform) ;

          const dReal* Pos = dGeomGetPosition(m_geometry1);
          const dReal* Rot = dGeomGetRotation(m_geometry1);

          m_current_transform[ 0 ] = Rot[ 0 ];  m_current_transform[ 1 ] = Rot[ 1 ]; m_current_transform[ 2 ] = Rot[ 2 ]; m_current_transform[ 3 ] = 0;
          m_current_transform[ 4 ] = Rot[ 4 ];  m_current_transform[ 5 ] = Rot[ 5 ]; m_current_transform[ 6 ] = Rot[ 6 ]; m_current_transform[ 7 ] = 0;
          m_current_transform[ 8 ] = Rot[ 8 ];  m_current_transform[ 9 ] = Rot[ 9 ]; m_current_transform[10 ] = Rot[10 ]; m_current_transform[11 ] = 0;
          m_current_transform[12 ] = Pos[ 0 ];  m_current_transform[13 ] = Pos[ 1 ]; m_current_transform[14 ] = Pos[ 2 ]; m_current_transform[15 ] = 1;
        }
      }
    }
  }
}
