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
#ifndef PU_KERNEL_TEST_DEDUCED_TRAIT_H_
#define PU_KERNEL_TEST_DEDUCED_TRAIT_H_


#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      ///  Test for deduced traits.
      /*!
      */
      class TestDeducedTrait : public CppUnit::TestFixture {
      public:

        /// Initialisation du test
        void setUp() ;

        /// Desinitialisation du test
        void tearDown() ;

      protected:

      /// @name Tests methods
      // @{  

        /// Tests an And formula.
        void testAnd() ;

        /// Tests an Or formula.
        void testOr() ;

        /// Tests a Not formula.
        void testNot() ;
        
        /// Tests a composite formula.
        void testComposite() ;
        
        /// Tests a composite formula with deduced traits.
        void testCompositeWithDeduced() ;

        /// Tests view on deduced trait.
        void testDeducedTraitViews() ;

        
      // @}


        CPPUNIT_TEST_SUITE(TestDeducedTrait) ;

        CPPUNIT_TEST(testAnd) ;
        CPPUNIT_TEST(testOr) ;
        CPPUNIT_TEST(testNot) ;
        CPPUNIT_TEST(testComposite) ;
        CPPUNIT_TEST(testCompositeWithDeduced) ;
        CPPUNIT_TEST(testDeducedTraitViews) ;

        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif /*PU_KERNEL_TEST_DEDUCED_TRAIT_H_*/
