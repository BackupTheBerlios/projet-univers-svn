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
#include <kernel/object.h>
#include <kernel/model.h>

#include <model/model.h>
#include <model/positionned.h>
#include <model/oriented.h>

#include <model/test/test_positionned.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Model::Test::TestPositionned) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      void TestPositionned::testGetPosition1()
      {
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testGetPosition1")) ;
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Positionned(Position::Meter(0,0,0))) ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = object2->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,0,1))) ;

        /// object2 relative to root
        Ogre::Vector3 vector2 = object2->getTrait<Positionned>()
                                       ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector2.x == 1) ;        
        CPPUNIT_ASSERT(vector2.y == 1) ;        
        CPPUNIT_ASSERT(vector2.z == 0) ;        

        /// object3 relative to root
        Ogre::Vector3 vector3 = object3->getTrait<Positionned>()
                                      ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector3.x == 1) ;        
        CPPUNIT_ASSERT(vector3.y == 1) ;        
        CPPUNIT_ASSERT(vector3.z == 1) ;        

        /// object3 relative to object2
        Ogre::Vector3 vector32 = object3->getTrait<Positionned>()
                                      ->getPosition(object2).Meter() ; 
        CPPUNIT_ASSERT(vector32.x == 0) ;        
        CPPUNIT_ASSERT(vector32.y == 0) ;        
        CPPUNIT_ASSERT(vector32.z == 1) ;        

        /// object3 relative to object3
        Ogre::Vector3 vector33(object3->getTrait<Positionned>()
                                      ->getPosition(object3).Meter()) ;
                                       
//        std::cout << "position=" << object3->getTrait<Positionned>()
//                                      ->getPosition(object3) << std::endl ;
        CPPUNIT_ASSERT(vector33.x == 0) ;        
        CPPUNIT_ASSERT(vector33.y == 0) ;        
        CPPUNIT_ASSERT(vector33.z == 0) ;        
      }

      void TestPositionned::testGetPosition2()
      {
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testGetPosition2")) ;
        Kernel::Object* root = model->createObject() ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = object2->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,0,1))) ;


        /// object2 relative to root
        Ogre::Vector3 vector2 = object2->getTrait<Positionned>()
                                       ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector2.x == 1) ;        
        CPPUNIT_ASSERT(vector2.y == 1) ;        
        CPPUNIT_ASSERT(vector2.z == 0) ;        

        /// object3 relative to root
        Ogre::Vector3 vector3 = object3->getTrait<Positionned>()
                                      ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector3.x == 1) ;        
        CPPUNIT_ASSERT(vector3.y == 1) ;        
        CPPUNIT_ASSERT(vector3.z == 1) ;        

        /// object3 relative to object2
        Ogre::Vector3 vector32 = object3->getTrait<Positionned>()
                                      ->getPosition(object2).Meter() ; 
        CPPUNIT_ASSERT(vector32.x == 0) ;        
        CPPUNIT_ASSERT(vector32.y == 0) ;        
        CPPUNIT_ASSERT(vector32.z == 1) ;        

        /// object3 relative to object3
        Ogre::Vector3 vector33 = object3->getTrait<Positionned>()
                                      ->getPosition(object3).Meter() ; 
        CPPUNIT_ASSERT(vector33.x == 0) ;        
        CPPUNIT_ASSERT(vector33.y == 0) ;        
        CPPUNIT_ASSERT(vector33.z == 0) ;        
      }

      void TestPositionned::testGetPosition3()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testGetPosition3")) ;
        Kernel::Object* root = model->createObject() ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;

        Kernel::Object* intermediate = object1->createObject() ;
        
        Kernel::Object* object2 = intermediate->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = object2->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,0,1))) ;

        /// object2 relative to root
        Ogre::Vector3 vector2 = object2->getTrait<Positionned>()
                                       ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector2.x == 1) ;        
        CPPUNIT_ASSERT(vector2.y == 1) ;        
        CPPUNIT_ASSERT(vector2.z == 0) ;        

        /// object3 relative to root
        Ogre::Vector3 vector3 = object3->getTrait<Positionned>()
                                      ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector3.x == 1) ;        
        CPPUNIT_ASSERT(vector3.y == 1) ;        
        CPPUNIT_ASSERT(vector3.z == 1) ;        

        /// object3 relative to object2
        Ogre::Vector3 vector32 = object3->getTrait<Positionned>()
                                      ->getPosition(object2).Meter() ; 
        CPPUNIT_ASSERT(vector32.x == 0) ;        
        CPPUNIT_ASSERT(vector32.y == 0) ;        
        CPPUNIT_ASSERT(vector32.z == 1) ;        

        /// object3 relative to object3
        Ogre::Vector3 vector33 = object3->getTrait<Positionned>()
                                      ->getPosition(object3).Meter() ; 
        vector3 = vector33 ;

        CPPUNIT_ASSERT(vector33.x == 0) ;
        CPPUNIT_ASSERT(vector33.y == 0) ;
        CPPUNIT_ASSERT(vector33.z == 0) ;
      }

      void TestPositionned::testGetPosition4()
      {
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testGetPosition4")) ;
        Kernel::Object* root = model->createObject() ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = root->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,0,1))) ;


        /// object2 relative to root
        Ogre::Vector3 vector2 = object2->getTrait<Positionned>()
                                       ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector2.x == 1) ;        
        CPPUNIT_ASSERT(vector2.y == 1) ;        
        CPPUNIT_ASSERT(vector2.z == 0) ;        

        /// object3 relative to root
        Ogre::Vector3 vector3 = object3->getTrait<Positionned>()
                                      ->getPosition(root).Meter() ; 
        CPPUNIT_ASSERT(vector3.x == 0) ;        
        CPPUNIT_ASSERT(vector3.y == 0) ;        
        CPPUNIT_ASSERT(vector3.z == 1) ;        

        /// object3 relative to object2
        Ogre::Vector3 vector32 = object3->getTrait<Positionned>()
                                      ->getPosition(object2).Meter() ; 
        CPPUNIT_ASSERT(vector32.x == -1) ;
        CPPUNIT_ASSERT(vector32.y == -1) ;        
        CPPUNIT_ASSERT(vector32.z == 1) ;        

        /// object3 relative to object3
        Ogre::Vector3 vector33 = object3->getTrait<Positionned>()
                                      ->getPosition(object3).Meter() ; 
        CPPUNIT_ASSERT(vector33.x == 0) ;        
        CPPUNIT_ASSERT(vector33.y == 0) ;        
        CPPUNIT_ASSERT(vector33.z == 0) ;        
      }
      
      void TestPositionned::testSetPosition1()
      {
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testSetPosition1")) ;
        Kernel::Object* root = model->createObject() ;
        model->addTrait(root,new Positionned(Position::Meter(0,0,0))) ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = object2->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,0,1))) ;

        object3->getTrait<Positionned>()
               ->setPosition(Position::Meter(2,2,2),root) ;

        {
          /// object3 relative to root
          Ogre::Vector3 vector = object3->getTrait<Positionned>()
                                        ->getPosition(root).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 2) ;        
          CPPUNIT_ASSERT(vector.y == 2) ;        
          CPPUNIT_ASSERT(vector.z == 2) ;        
        }
        
        {
          /// object3 relative to object2
          Ogre::Vector3 vector = object3->getTrait<Positionned>()
                                        ->getPosition(object2).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 1) ;        
          CPPUNIT_ASSERT(vector.y == 1) ;        
          CPPUNIT_ASSERT(vector.z == 2) ;        
        }

        {
          /// object2 relative to root : must be unchanged
          Ogre::Vector3 vector = object2->getTrait<Positionned>()
                                        ->getPosition(root).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 1) ;        
          CPPUNIT_ASSERT(vector.y == 1) ;        
          CPPUNIT_ASSERT(vector.z == 0) ;        
        }
        
      }

      void TestPositionned::testSetPosition2()
      {
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testSetPosition2")) ;
        Kernel::Object* root = model->createObject() ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = object2->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,0,1))) ;

        object3->getTrait<Positionned>()
               ->setPosition(Position::Meter(2,2,2),root) ;

        {
          /// object3 relative to root
          Ogre::Vector3 vector = object3->getTrait<Positionned>()
                                        ->getPosition(root).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 2) ;        
          CPPUNIT_ASSERT(vector.y == 2) ;        
          CPPUNIT_ASSERT(vector.z == 2) ;        
        }
        
        {
          /// object3 relative to object2
          Ogre::Vector3 vector = object3->getTrait<Positionned>()
                                        ->getPosition(object2).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 1) ;        
          CPPUNIT_ASSERT(vector.y == 1) ;        
          CPPUNIT_ASSERT(vector.z == 2) ;        
        }

        {
          /// object2 relative to root : must be unchanged
          Ogre::Vector3 vector = object2->getTrait<Positionned>()
                                        ->getPosition(root).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 1) ;        
          CPPUNIT_ASSERT(vector.y == 1) ;        
          CPPUNIT_ASSERT(vector.z == 0) ;        
        }
        
      }

      void TestPositionned::testSetPosition3()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testSetPosition3")) ;
        Kernel::Object* root = model->createObject() ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;

        Kernel::Object* intermediate = object1->createObject() ;
        
        Kernel::Object* object2 = intermediate->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = object2->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,0,1))) ;

        object3->getTrait<Positionned>()
               ->setPosition(Position::Meter(2,2,2),root) ;

        {
          /// object3 relative to root
          Ogre::Vector3 vector = object3->getTrait<Positionned>()
                                        ->getPosition(root).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 2) ;        
          CPPUNIT_ASSERT(vector.y == 2) ;        
          CPPUNIT_ASSERT(vector.z == 2) ;        
        }
        
        {
          /// object3 relative to object2
          Ogre::Vector3 vector = object3->getTrait<Positionned>()
                                        ->getPosition(object2).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 1) ;        
          CPPUNIT_ASSERT(vector.y == 1) ;        
          CPPUNIT_ASSERT(vector.z == 2) ;        
        }

        {
          /// object2 relative to root : must be unchanged
          Ogre::Vector3 vector = object2->getTrait<Positionned>()
                                        ->getPosition(root).Meter() ; 
          CPPUNIT_ASSERT(vector.x == 1) ;        
          CPPUNIT_ASSERT(vector.y == 1) ;        
          CPPUNIT_ASSERT(vector.z == 0) ;        
        }
        
      }

      void TestPositionned::testGetRelativePosition()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::testGetRelativePosition")) ;
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Positionned()) ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(1,0,0))) ;
        
        CPPUNIT_ASSERT(getRelativePosition(object1,root) == Position::Meter(1,0,0)) ;
      }
      
      void TestPositionned::relativePositionWithRotation()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::relativePositionWithRotation")) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Positionned()) ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(0,0,0))) ;
        
        Kernel::Object* object2 = model->createObject(object1) ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;
        
        Kernel::Object* object3 = root->createObject() ;
        object3->addTrait(new Positionned()) ;
        // rotation of 90� anti clockwize against Z axis
        object3->addTrait(new Oriented(Orientation(Ogre::Quaternion(sqrt(0.5),0,0,sqrt(0.5))))) ;
        
        CPPUNIT_ASSERT(getRelativePosition(object2,object3).Meter().positionEquals(Ogre::Vector3(1,0,0),1e-4)) ;

        // re-orient the root must not change anything
        root->addTrait(new Oriented(Orientation(Ogre::Quaternion(sqrt(0.5),0,0,sqrt(0.5))))) ;
        CPPUNIT_ASSERT(getRelativePosition(object2,object3).Meter().positionEquals(Ogre::Vector3(1,0,0),1e-4)) ;
        
        // adding a void object should not change anything
        Kernel::Object* object4 = object2->createObject() ;
        CPPUNIT_ASSERT(getRelativePosition(object4,object3).Meter().positionEquals(Ogre::Vector3(1,0,0),1e-4)) ;

        Kernel::Object* object5 = object3->createObject() ;
        CPPUNIT_ASSERT(getRelativePosition(object4,object5).Meter().positionEquals(Ogre::Vector3(1,0,0),1e-4)) ;
        
        // changing position of the root should not change anything
        root->getTrait<Positionned>()->setPosition(Position::Meter(100,100,100)) ;
        CPPUNIT_ASSERT(getRelativePosition(object4,object5).Meter().positionEquals(Ogre::Vector3(1,0,0),1e-4)) ;
      }

      void TestPositionned::relativePositionWithRotations()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::relativePositionWithRotations")) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Positionned()) ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(100,0,0))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;
        
        Kernel::Object* object3 = root->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(100,0,0))) ;
        // rotation of 90� anti clockwize against Z axis
        object3->addTrait(new Oriented(Orientation(Ogre::Quaternion(sqrt(0.5),0,0,sqrt(0.5))))) ;
        
        CPPUNIT_ASSERT(getRelativePosition(object2,object3).Meter().positionEquals(Ogre::Vector3(1,0,0),1e-4)) ;
      }
      
      void TestPositionned::relativePositionToAncestor()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::relativePositionToAncestor")) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Positionned()) ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(100,0,0))) ;
        // rotation of 90� anti clockwize against Z axis
        object1->addTrait(new Oriented(Orientation(Ogre::Quaternion(sqrt(0.5),0,0,sqrt(0.5))))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        CPPUNIT_ASSERT(getRelativePosition(object2,root).Meter().positionEquals(Ogre::Vector3(99,0,0),1e-4)) ;
      }
      
      void TestPositionned::relativePositionToOrientedCousin()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPositionned::relativePositionToOrientedCousin")) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Positionned()) ;
        
        Kernel::Object* object1 = root->createObject() ;
        object1->addTrait(new Positionned(Position::Meter(100,0,0))) ;
        // rotation of 90� anti clockwize against Z axis
        object1->addTrait(new Oriented(Orientation(Ogre::Quaternion(sqrt(0.5),0,0,sqrt(0.5))))) ;
        
        Kernel::Object* object2 = object1->createObject() ;
        object2->addTrait(new Positionned(Position::Meter(0,1,0))) ;

        Kernel::Object* object3 = root->createObject() ;
        object3->addTrait(new Positionned(Position::Meter(0,100,0))) ;
        // rotation of 90� clockwize against Z axis
        object3->addTrait(new Oriented(Orientation(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Z)))) ;
        
        Kernel::Object* object4 = object3->createObject() ;
        object4->addTrait(new Positionned(Position::Meter(1,0,0))) ;
        
        CPPUNIT_ASSERT(getRelativePosition(object2,object4).Meter().positionEquals(Ogre::Vector3(99,99,0),1e-4)) ;
      }
      
      void TestPositionned::setUp() 
      {
      }
      
      void TestPositionned::tearDown() 
      {
      }
      

    }
  }
}

