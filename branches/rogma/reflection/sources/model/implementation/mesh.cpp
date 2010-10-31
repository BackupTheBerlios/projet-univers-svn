/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <kernel/log.h>
#include <kernel/string.h>

#include <model/model.h>
#include <model/mesh.h>

namespace ProjetUnivers {
  namespace Model {
    
    Mesh::Mesh(const std::string& _name)
    : m_name(_name)
    {}
      
    Mesh::Mesh(const Mesh& _model)
    : m_name(_model.m_name)
    {}

    Mesh& Mesh::operator=(const Mesh& mesh)
    {
      if (this != &mesh)
      {
        m_name = mesh.m_name ;
      }
      return *this ;
    }
    
    Mesh Mesh::read(Kernel::Reader* reader)
    {
      Mesh result("") ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("ogre_ressource") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_name = finder->second.c_str() ;
      }
      else
      {
        ErrorMessage("Model::Mesh::read required attribute : ogre_ressource") ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;
      
      return result ;            
    }   
      
    std::string Mesh::getName() const
    {
      return m_name ;
    }

    using namespace Ogre ;

    /*!
      Code taken from http://www.ogre3d.org/wiki/index.php/RetrieveVertexData.
    */
    void Mesh::getMeshInformation(
      std::vector< ::Ogre::Vector3>& o_vertices,
      std::vector<unsigned long>&    o_indices,
      const Ogre::Vector3&           i_scale) const
    {
      InternalMessage("Model","Model::Mesh::getMeshInformation entering") ;

      bool added_shared = false;
      size_t current_offset = 0;
      size_t shared_offset = 0;
      size_t next_offset = 0;
      size_t index_offset = 0;
      size_t vertex_count = 0 ;
      size_t index_count = 0 ; 
    
      initRessources() ;
    
      Ogre::MeshManager* manager = Ogre::MeshManager::getSingletonPtr() ; 
      
      if (! manager)
      {
        InternalMessage("Model","Model::Mesh::getMeshInformation no manager") ;
        o_vertices.clear() ;
        o_indices.clear() ;
        return ;
      }
      
      InternalMessage("Model","Model::Mesh::getMeshInformation manager found") ;
      // Load the mesh
      Ogre::Mesh* mesh = NULL ;
      try
      {
        
        MeshPtr local_mesh =
        manager->load(m_name,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME) ; 
        InternalMessage("Model","Model::Mesh::getMeshInformation loaded") ;
        
        mesh = local_mesh.get() ; 
      }
      catch(Ogre::Exception& e)
      {
        InternalMessage("Model","Model::Mesh::getMeshInformation exception " + std::string(e.getDescription())) ;
      }
      
      if (!mesh)
      {
        InternalMessage("Model","Model::Mesh::getMeshInformation no mesh") ;
        o_vertices.clear() ;
        o_indices.clear() ;
        return ;
      }
      
      vertex_count = index_count = 0;

      InternalMessage("Model","Model::Mesh::getMeshInformation calculating vertice count...") ;
    
      // Calculate how many vertices and indices we're going to need
      for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
      {
        Ogre::SubMesh* submesh = mesh->getSubMesh( i );
      
        // We only need to add the shared vertices once
        if(submesh->useSharedVertices)
        {
          if( !added_shared )
          {
            vertex_count += mesh->sharedVertexData->vertexCount;
            added_shared = true;
          }
        }
        else
        {
          vertex_count += submesh->vertexData->vertexCount;
        }
      
        // Add the indices
        index_count += submesh->indexData->indexCount;
      }
    
      InternalMessage("Model","Model::Mesh::getMeshInformation " 
                      + Kernel::toString(vertex_count) +" vertices "
                      + Kernel::toString(index_count) +" indexes" ) ;
                      
      // Allocate space for the vertices and indices
      o_vertices.reserve(vertex_count) ;
      o_indices.reserve(index_count) ;
    
      added_shared = false;

      InternalMessage("Model","Model::Mesh::getMeshInformation adding vertices...") ;
    
      // Run through the submeshes again, adding the data into the arrays
      for (unsigned short i = 0 ;i < mesh->getNumSubMeshes() ;++i)
      {
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);
    
        Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
    
        if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
        {
          if(submesh->useSharedVertices)
          {
            added_shared = true;
            shared_offset = current_offset;
          }
    
          const Ogre::VertexElement* posElem =
            vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
    
          Ogre::HardwareVertexBufferSharedPtr vbuf =
            vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
    
          unsigned char* vertex =
            static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
    
          // There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
          //  as second argument. So make it float, to avoid trouble when Ogre::Real will
          //  be comiled/typedefed as double:
          //      Ogre::Real* pReal;
          Ogre::Real* pReal;
    
          for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
          {
            posElem->baseVertexPointerToElement(vertex, &pReal);
    
            Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
    
            o_vertices.push_back(pt * i_scale) ;
          }
          
          vbuf->unlock();
          next_offset += vertex_data->vertexCount;
        }
        InternalMessage("Model","Model::Mesh::getMeshInformation added " 
                        + Kernel::toString(o_vertices.size()) + " vertices") ;
    
        InternalMessage("Model","Model::Mesh::getMeshInformation adding indexes...") ;
    
        Ogre::IndexData* index_data = submesh->indexData;
        size_t numTris = index_data->indexCount / 3;
        Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
        
        bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
    
        unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);
    
    
        size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;
    
        if ( use32bitindexes )
        {
          for ( size_t k = 0; k < numTris*3; ++k)
          {
            o_indices.push_back(pLong[k] + static_cast<unsigned long>(offset)) ;
            InternalMessage("Model","Model::Mesh::getMeshInformation adding one index") ;
          }
        }
        else
        {
          for ( size_t k = 0; k < numTris*3; ++k)
          {
            o_indices.push_back(static_cast<unsigned long>(pShort[k]) +
                                static_cast<unsigned long>(offset)) ;
          }
        }
    
        ibuf->unlock();
        current_offset = next_offset;
      }

      InternalMessage("Model","Model::Mesh::getMeshInformation leaving") ;
    }

    float Mesh::getBoundingSphereRadius() const
    {
      initRessources() ;
      Ogre::MeshManager* manager = Ogre::MeshManager::getSingletonPtr() ; 

      // Load the mesh
      Ogre::Mesh* mesh = NULL ;
      try
      {
        MeshPtr local_mesh =
        manager->load(m_name,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME) ; 
        InternalMessage("Model","Model::Mesh::getBoundingSphereRadius loaded") ;
        mesh = local_mesh.get() ; 
      }
      catch(Ogre::Exception& e)
      {
        InternalMessage("Model","Model::Mesh::getBoundingSphereRadius exception " + std::string(e.getDescription())) ;
      }
      
      if (mesh)
      {
        return mesh->getBoundingSphereRadius() ;
      }
      else
      {
        return -1 ;
      }
    }
    
  }
}
