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
#ifndef PU_KERNEL_TEST_ERREUR_H_
#define PU_KERNEL_TEST_ERREUR_H_


#include <cppunit/extensions/HelperMacros.h>
#include <kernel/error.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      /// Test .
      class TestError : public CppUnit::TestFixture {
      protected:

  
      /*! 
        @name Tests
      */ 
      // @{
  
        /// Test check macro.
        void TestExpression();

      // @}
      /*!
        @name Test registration
      */
      // @{      

        CPPUNIT_TEST_SUITE(TestError) ;

        CPPUNIT_TEST(TestExpression) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      public:

        /// Tests setup
        void setUp() ;

        /// Tests close.
        void tearDown() ;
      };

    }
  }
}

#endif
