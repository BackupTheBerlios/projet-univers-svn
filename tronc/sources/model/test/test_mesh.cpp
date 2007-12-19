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
#include <algorithm>
#include <kernel/log.h>

#include <model/model.h>
#include <model/mesh.h>
#include <model/test/test_mesh.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestMesh) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      void TestMesh::testGetInformation()
      {
        InternalMessage("Model","Model::TestMesh::testGetInformation entering") ;
        
        Mesh test_mesh("razor.mesh") ;
        
        std::vector< ::Ogre::Vector3> vertices ;
        std::vector<unsigned long>    indices ;
        Ogre::Vector3                 scale(1,1,1) ;        

        test_mesh.getMeshInformation(vertices,indices,scale) ;
        
        CPPUNIT_ASSERT(! vertices.empty()) ;
        CPPUNIT_ASSERT(! indices.empty()) ;

        float min_x = 0 ;
        float max_x = 0 ;
        float min_y = 0 ;
        float max_y = 0 ;
        float min_z = 0 ;
        float max_z = 0 ;
        
        int i = 0 ;
        
        for(std::vector< ::Ogre::Vector3>::iterator vertex = vertices.begin() ;
            vertex != vertices.end() ;
            ++vertex)
        {
          min_x = std::min(min_x,vertex->x) ;
          min_y = std::min(min_y,vertex->y) ;
          min_z = std::min(min_z,vertex->z) ;

          max_x = std::max(max_x,vertex->x) ;
          max_y = std::max(max_y,vertex->y) ;
          max_z = std::max(max_z,vertex->z) ;
          
//          std::cout << "vertex[" << i/3 << "][0]=" << vertex->x  << ";" << std::endl ;
//          std::cout << "vertex[" << i/3 << "][1]=" << vertex->y  << ";" << std::endl ;
//          std::cout << "vertex[" << i/3 << "][2]=" << vertex->z  << ";" << std::endl ;
          ++i ;
        }
        
//        std::cout << "aabb = " << min_x << " " << max_x 
//                  << " " <<  min_y << " " << max_y
//                  << " " <<  min_z << " " << max_z << std::endl ;
        
        // indices represents triangles 
        CPPUNIT_ASSERT(indices.size()%3==0) ;
        
        i = 0 ;
        // indexes must be vertex indexes.        
        for(std::vector<unsigned long>::iterator index = indices.begin() ;
            index != indices.end() ;
            ++index)
        {
          CPPUNIT_ASSERT(*index < vertices.size()) ;
//          std::cout << "indices[" << i << "]=" << *index << ";" << std::endl ;
          ++i ;
          // check for degenerated triangles
          if (i%3==2)
          {
            if (vertices[indices[i-2]] == vertices[indices[i-1]] ||
                vertices[indices[i-2]] == vertices[indices[i]]   ||
                vertices[indices[i-1]] == vertices[indices[i]])
            {
              std::cout << "degenerated mesh" <<std::endl ;
              CPPUNIT_ASSERT(false) ;
            }
            
          }
        }

        // iterates through triangles
//        std::vector<unsigned long>::iterator index = indices.begin() ;
//        while(index != indices.end())
//        {
//          
//          ++index ;
        
        
        InternalMessage("Model","Model::TestMesh::testGetInformation leaving") ;
      }
      
      void TestMesh::testUnexistingMesh()
      {
        InternalMessage("Model","Model::TestMesh::testUnexistingMesh entering") ;
        
        Mesh test_mesh("unexisting") ;
        
        std::vector< ::Ogre::Vector3> vertices ;
        std::vector<unsigned long>    indices ;
        Ogre::Vector3                 scale(1,1,1) ;        

        test_mesh.getMeshInformation(vertices,indices,scale) ;
        
        CPPUNIT_ASSERT(vertices.empty()) ;
        CPPUNIT_ASSERT(indices.empty()) ;
        
        InternalMessage("Model","Model::TestMesh::testUnexistingMesh leaving") ;
        
      }
      
      void TestMesh::setUp() 
      {
      }
      
      void TestMesh::tearDown() 
      {
      }
      
    }
  }
}

