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
#include <kernel/object.h>

#include <model/model.h>
#include <model/oriented.h>

#include <model/test/test_oriented.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Model::Test::TestOriented) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      void TestOriented::testGetOrientation()
      {
        Model::init() ;
        Kernel::Object* root = Model::createObject("root") ;
        Model::addTrait(root,new Oriented(Ogre::Quaternion(1,0,0,0))) ;
        
        Kernel::Object* object1 = Model::createObject("object1",root) ;
        Model::addTrait(object1,new Oriented(Ogre::Quaternion(0,1,0,0))) ;
        
        Kernel::Object* object2 = Model::createObject("object2",object1) ;
        Model::addTrait(object2,new Oriented(Ogre::Quaternion(0,0,1,0))) ;

        Kernel::Object* object3 = Model::createObject("object3",object2) ;
        Model::addTrait(object3,new Oriented(Ogre::Quaternion(0,0,0,1))) ;
        
        /// object2 relative to root
        Ogre::Quaternion orientation2 = object2->getTrait<Oriented>()
                                           ->getOrientation(root).getQuaternion() ; 

        CPPUNIT_ASSERT(orientation2.w == 0) ;        
        CPPUNIT_ASSERT(orientation2.x == 0) ;        
        CPPUNIT_ASSERT(orientation2.y == 0) ;        
        CPPUNIT_ASSERT(orientation2.z == 1) ;        

        /// object3 relative to root
        Ogre::Quaternion orientation3 = object3->getTrait<Oriented>()
                                           ->getOrientation(root).getQuaternion() ; 

        CPPUNIT_ASSERT(orientation3.w == -1) ;        
        CPPUNIT_ASSERT(orientation3.x == 0) ;        
        CPPUNIT_ASSERT(orientation3.y == 0) ;        
        CPPUNIT_ASSERT(orientation3.z == 0) ;        


      }

      void TestOriented::testSetAbsoluteOrientation()
      {
        Model::init() ;
        Kernel::Object* root = Model::createObject("root") ;
        Model::addTrait(root,new Oriented(Ogre::Quaternion(1,0,0,0))) ;
        
        Kernel::Object* object1 = Model::createObject("object1",root) ;
        Model::addTrait(object1,new Oriented(Ogre::Quaternion(0,1,0,0))) ;
        
        Kernel::Object* object2 = Model::createObject("object2",object1) ;
        Model::addTrait(object2,new Oriented(Ogre::Quaternion(0,0,1,0))) ;

        Kernel::Object* object3 = Model::createObject("object3",object2) ;
        Model::addTrait(object3,new Oriented(Ogre::Quaternion(0,0,0,1))) ;

        object3->getTrait<Oriented>()
               ->setOrientation(Ogre::Quaternion(0,0,1,0),root) ;

        {
          /// object3 relative to root
          Ogre::Quaternion orientation = object3->getTrait<Oriented>()
                                                ->getOrientation(root).getQuaternion() ; 
  
          CPPUNIT_ASSERT(orientation.w == 0) ;        
          CPPUNIT_ASSERT(orientation.x == 0) ;        
          CPPUNIT_ASSERT(orientation.y == 1) ;        
          CPPUNIT_ASSERT(orientation.z == 0) ;        
        }

      }
      
      void TestOriented::setUp() 
      {
      }
      
      void TestOriented::tearDown() 
      {
      }
      

    }
  }
}

