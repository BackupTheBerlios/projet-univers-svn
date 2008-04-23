/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#ifndef PU_KERNEL_TEST_COMMAND_H_
#define PU_KERNEL_TEST_COMMAND_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      ///  Test for trait command and trait functions.
      class TestCommand : public CppUnit::TestFixture {
      public:

        /// Initialisation du test
        void setUp() ;

        /// Desinitialisation du test
        void tearDown() ;

      protected:

      /// @name Tests methods
      // @{  

        /// A simple test.
        void basicTest() ;
        
        /// A test for command delegating.
        void testCommandDelegator() ; 

        /// A test for command delegating.
        void testCommandDelegatorWithTwoDelegates() ; 
        
        /// A test for function call and declaration.
        void testFunctionCall() ;

        /// A test for function call in the error cases.
        void testFunctionCallErrorCases() ;
        
        /// Call an unexisting command.
        void callUnexistingCommand() ;
        
        /// Command call on a recursive structure.
        void callOnRecursiveStructure() ;
        
      // @}


        CPPUNIT_TEST_SUITE(TestCommand) ;

        CPPUNIT_TEST(basicTest) ;
        CPPUNIT_TEST(testCommandDelegator) ;
        CPPUNIT_TEST(testCommandDelegatorWithTwoDelegates) ;
        CPPUNIT_TEST(testFunctionCall) ;
        CPPUNIT_TEST(callUnexistingCommand) ;
        CPPUNIT_TEST(callOnRecursiveStructure) ;

        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif /*PU_KERNEL_TEST_COMMAND_H_*/
