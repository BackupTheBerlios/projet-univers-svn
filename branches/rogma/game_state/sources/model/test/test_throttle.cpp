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
#include <kernel/model.h>
#include <kernel/object.h>

#include <model/throttle.h>
#include <model/test/test_throttle.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestThrottle) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      namespace {
        /// Acceptable variable for comparison 
        const float delta = 0.2 ;
  
        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }
        
        const float pi = 3.1415926535 ;
      }


      void TestThrottle::basicTest()
      {
        InternalMessage("Model","Model::TestThrottle::basicTest entering") ;
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestThrottle::basicTest")) ;

        Kernel::Object* ship = model->createObject() ;
        
        Kernel::Object* throttle = ship->createObject() ;
        throttle->addTrait(new Throttle()) ;
        
        {
          /// variables redefines to have direct access to interesting traits
          
          Throttle* throttle_trait = throttle->getTrait<Throttle>() ;
          CPPUNIT_ASSERT(throttle_trait) ;

          CPPUNIT_ASSERT(throttle_trait->getOrientation().getQuaternion().getPitch().valueDegrees()==0) ;
          throttle_trait->modify(100) ;
          CPPUNIT_ASSERT(equal(throttle_trait->getOrientation().getQuaternion().getPitch().valueDegrees(),45)) ;
          throttle_trait->modify(100) ;
          CPPUNIT_ASSERT(equal(throttle_trait->getOrientation().getQuaternion().getPitch().valueDegrees(),90)) ;
          throttle_trait->modify(-100) ;
          CPPUNIT_ASSERT(equal(throttle_trait->getOrientation().getQuaternion().getPitch().valueDegrees(),45)) ;
          
        }
      }
      
      void TestThrottle::setUp() 
      {
      }
      
      void TestThrottle::tearDown() 
      {
      }
      

    }
  }
}

