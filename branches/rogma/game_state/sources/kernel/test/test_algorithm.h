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
#ifndef PU_KERNEL_TEST_ALGORITHM_H_
#define PU_KERNEL_TEST_ALGORITHM_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

      ///  Test for Algorithm functions.
      class TestAlgorithm : public CppUnit::TestFixture {
      public:

        /// Tests setup.
        void setUp() ;

        /// Tests close.
        void tearDown() ;

      protected:

      /// @name Tests methods
      // @{  

        /// findAfter findBefore test on a cardinality 2 set.
        void testFindAfterBeforeOnSmallSet() ;
        
        /// findAfter findBefore test on a bigger set.
        void testFindAfterBeforeOnBigSet() ;
        
        /// Chech that interception time is positive.
        void calculateInterceptionTime() ;
       
        
      // @}


        CPPUNIT_TEST_SUITE(TestAlgorithm) ;

        CPPUNIT_TEST(testFindAfterBeforeOnSmallSet) ;
        CPPUNIT_TEST(testFindAfterBeforeOnBigSet) ;
        CPPUNIT_TEST(calculateInterceptionTime) ;

        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif /*PU_KERNEL_TEST_ALGORITHM_H_*/
