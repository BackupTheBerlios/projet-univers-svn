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
#include <math.h>
#include <iostream>
#include <ode/ode.h>

#include <kernel/log.h>
#include <kernel/parameters.h>
#include <model/mesh.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/mass_property.h>

#include <physic/test/test_ode.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Physic::Test::TestODE) ;

namespace ProjetUnivers {
  namespace Physic {

    using namespace Implementation::Ode ;
    
    namespace Test {

      const float pi = 3.1415926 ;

      namespace
      {
        const int VertexCount = 5 ;
        const int IndexCount = 12 ;

        dVector3 Size ;
        dVector3 Vertices[VertexCount] ;
        int Indices[IndexCount] ;
        dGeomID TriMesh ;
      }

      void TestODE::testTwoWorlds()
      {
//        std::cout << std::endl ;
        
        std::auto_ptr<dWorld> world1(new dWorld()) ; 

        std::auto_ptr<dBody> body1(new dBody(world1->id())) ;
        body1->setPosition(0,0,0) ;
        body1->setLinearVel(10,0,0) ;      
        body1->setAngularVel(0,2*pi,0) ;
        
//        std::cout << body1->isEnabled() << std::endl ;

        const int number_of_step = 100 ;
        for (int i = 1 ; i <= number_of_step ; ++i)
        {
          world1->step(1.0/number_of_step) ;
          const dReal* final_orientation = body1->getQuaternion() ;
//          std::cout << "body1 orientation=" << final_orientation[0] << "," 
//                    << final_orientation[1] << ","
//                    << final_orientation[2] << ","
//                    << final_orientation[3] << std::endl ;

          const dReal* position = body1->getPosition() ;
//          std::cout << "body1 position=" << position[0] << "," 
//                    << position[1] << ","
//                    << position[2] << std::endl ;

        }
       
      }

      void TestODE::testTrimesh()
      {
        dInitODE();
        
        dWorld* world = new dWorld() ;
        dBody* body = new dBody(world->id()) ;
        
        Size[0] = 5.0f;
        Size[1] = 5.0f;
        Size[2] = 2.5f;
        
        Vertices[0][0] = -Size[0];
        Vertices[0][1] = -Size[1];
        Vertices[0][2] = Size[2];
        
        Vertices[1][0] = Size[0];
        Vertices[1][1] = -Size[1];
        Vertices[1][2] = Size[2];
        
        Vertices[2][0] = Size[0];
        Vertices[2][1] = Size[1];
        Vertices[2][2] = Size[2];
        
        Vertices[3][0] = -Size[0];
        Vertices[3][1] = Size[1];
        Vertices[3][2] = Size[2];
        
        Vertices[4][0] = 0;
        Vertices[4][1] = 0;
        Vertices[4][2] = 0;
        
        Indices[0] = 0;
        Indices[1] = 1;
        Indices[2] = 4;
        
        Indices[3] = 1;
        Indices[4] = 2;
        Indices[5] = 4;
        
        Indices[6] = 2;
        Indices[7] = 3;
        Indices[8] = 4;
        
        Indices[9] = 3;
        Indices[10] = 0;
        Indices[11] = 4;
        
        dTriMeshDataID Data = dGeomTriMeshDataCreate();
        
        dGeomTriMeshDataBuildSingle(Data, 
                                    &Vertices[0],3*sizeof(float),VertexCount,
                                    &Indices[0],IndexCount,3*sizeof(int));
        
        TriMesh = dCreateTriMesh(0, Data, 0, 0, 0) ;
        dGeomSetData(TriMesh, Data) ;
        
        dMass mass ;
        body->getMass(&mass) ;

//        std::cout << "masse avant " << printMass(mass) << std::endl ;

        dGeomSetBody(TriMesh,body->id()) ;

        body->getMass(&mass) ;

//        std::cout << "masse apres " << printMass(mass) << std::endl ;

        dMassSetTrimesh(&mass,1,TriMesh) ;
        dMassAdjust(&mass,1) ;
        dBodySetMass(body->id(),&mass) ;

//        std::cout << "masse " << printMass(mass) << std::endl ;

        body->setPosition(100,100,100) ;
        body->getMass(&mass) ;
//        std::cout << "masse " << printMass(mass) << std::endl ;

//        dGeomSetPosition(TriMesh, 0, 0, 0);
//        dMatrix3 Rotation;
//        dRFromAxisAndAngle(Rotation, 1, 0, 0, M_PI / 2);
//        dGeomSetRotation(TriMesh, Rotation);
     
        dReal* aabb = new dReal[6] ;
          
        dGeomGetAABB(TriMesh,aabb) ;
        
        
      }

      void TestODE::testTrimeshInertia()
      {
        Model::Mesh mesh("razor.mesh") ;
        
        std::vector< ::Ogre::Vector3> vertices ;
        std::vector<unsigned long>    indices ;
        Ogre::Vector3                 scale(1,1,1) ;        

        mesh.getMeshInformation(vertices,indices,scale) ;
        float mass ;
        Ogre::Vector3 center ;
        Ogre::Matrix3 inertia ;
        ComputeMassProperties(vertices,indices,true,mass,center,inertia) ;
      
//        std::cout << "center = " << center 
//                  << " inertia= " 
//                  << inertia.GetColumn(0) << " "  
//                  << inertia.GetColumn(1) << " "
//                  << inertia.GetColumn(2) 
//                  << std::endl ;
      }

      void TestODE::setUp() 
      {
        Kernel::Parameters::load("demonstration.config") ;
      }
      
      void TestODE::tearDown() 
      {
      }


    }
  }
}
