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

#include <kernel/exception_kernel.h>

#include <kernel/test/test_error.h>

// enregistrement du test
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

  
      /// Teste certaines expressions.
      void TestError::TestExpression()
      {
        try 
        {
          Object* element = NULL ;
          check(element,ExceptionKernel("failed")) ;
          
          CPPUNIT_ASSERT(false) ;
        }
        
        catch (ExceptionKernel&)
        {
          // ok
          CPPUNIT_ASSERT(true) ;
        }
      }




      /// Initialisation du test
      void TestError::setUp()
      {        
      }

      /// Desinitialisation du test
      void TestError::tearDown()
      {
      }




    }
  }
}

