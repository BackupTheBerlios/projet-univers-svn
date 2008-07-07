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
#include <kernel/exception_kernel.h>

#include <kernel/test/test_error.h>

// test registration
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Kernel::Test::TestError) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

      namespace
      {
        class Object
        {};
      }
 
      /// Test check macro.
      void TestError::TestExpression()
      {
        try 
        {
          Object* element = NULL ;
          CHECK(element,"failed") ;
          
          CPPUNIT_ASSERT(false) ;
        }
        
        catch (const char*)
        {
          // ok
          CPPUNIT_ASSERT(true) ;
        }
      }

      void TestError::setUp()
      {        
      }

      void TestError::tearDown()
      {
      }

    }
  }
}

