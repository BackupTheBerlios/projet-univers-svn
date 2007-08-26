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
#include <model/stick.h>
#include <model/test/test_stick.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestStick) ;

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


      void TestStick::basicTest()
      {
        InternalMessage("Model::TestThrottle::basicTest entering") ;
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestThrottle::basicTest")) ;
        
        Kernel::Object* ship = model->createObject("ship") ;
        
        Kernel::Object* stick = model->createObject("stick",ship) ;
        model->addTrait(stick,new Stick()) ;
        
        
        {
          /// variables redefines to have direct access to interesting traits
          Stick* stick = model->getObject("stick")->getTrait<Stick>() ;
          CPPUNIT_ASSERT(stick) ;

          /// set stick orientation at full thrust... 
          CPPUNIT_ASSERT(stick->getOrientation().getQuaternion().getPitch().valueDegrees()==0) ;

          stick->modifyX(100) ;
          CPPUNIT_ASSERT(equal(stick->getOrientation().getQuaternion().getYaw().valueDegrees(),-45)) ;

          stick->modifyX(-100) ;
          stick->modifyY(100) ;
          CPPUNIT_ASSERT(equal(stick->getOrientation().getQuaternion().getPitch().valueDegrees(),-45)) ;

          stick->modifyY(-100) ;
          stick->modifyZ(100) ;
          CPPUNIT_ASSERT(equal(stick->getOrientation().getQuaternion().getRoll().valueDegrees(),45)) ;
          
        }
      }
      
      void TestStick::setUp() 
      {
      }
      
      void TestStick::tearDown() 
      {
      }
      

    }
  }
}

