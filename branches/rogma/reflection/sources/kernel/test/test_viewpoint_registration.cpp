/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <iostream>

#include <kernel/view_point.h>
#include <kernel/controler_set.h>

#include <kernel/test/test_viewpoint_registration.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {
      
      CPPUNIT_TEST_SUITE_REGISTRATION(TestViewPointRegistration) ;

      namespace
      {
        class TestViewPoint : public ViewPoint
        {
        public:
          
          TestViewPoint(Model* model)
          : ViewPoint(model)
          {
            ++number_of_instances ;
          }
          
          static int number_of_instances ;
        };
        
        int TestViewPoint::number_of_instances = 0 ;
        
        RegisterViewPoint(TestViewPoint) ;

        class TestControlerSet : public ControlerSet
        {
        public:
          
          TestControlerSet(Model* model)
          : ControlerSet(model)
          {
            ++number_of_instances ;
          }
          
          static int number_of_instances ;
        };
        
        int TestControlerSet::number_of_instances = 0 ;
        
        RegisterControlerSet(TestControlerSet) ;
        
      }
      
      void TestViewPointRegistration::automaticCreation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        
        CPPUNIT_ASSERT(model->getViewPoint<TestViewPoint>()) ;
        CPPUNIT_ASSERT_EQUAL(1,TestViewPoint::number_of_instances) ;
        
        CPPUNIT_ASSERT(model->getControlerSet<TestControlerSet>()) ;
        CPPUNIT_ASSERT_EQUAL(1,TestControlerSet::number_of_instances ) ;
      }
      
    }
  }
}
