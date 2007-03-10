/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef PU_KERNEL_TEST_MODEL_VIEW_H_
#define PU_KERNEL_TEST_MODEL_VIEW_H_


#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      ///  Test for Model/View.
      /*!
      @par Status 
        fully tested on 07/03/04.
      */
      class TestModelView : public CppUnit::TestFixture {
      public:

        /// Initialisation du test
        void setUp() ;

        /// Desinitialisation du test
        void tearDown() ;

      protected:

      /// @name Tests methods
      // @{  

        /// Tests construction on empty model.
        void testBuildOnEmptyModel() ;

        /// Tests construction on a non empty model.
        void testBuildOnNonEmptyModel() ;

        /// Tests destroying a root object.
        void testDestroyRootObject() ;

        /// Tests destroying a sub object.
        void testDestroySubObject() ;

        /// Tests destroying a trait.
        void testDestroyTrait() ;

        /// Tests changing a parentship.
        void testchangeParent() ;

        /// Tests modification of a trait.
        void testUpdate() ;

        /// Tests view access.
        void testViewAccess() ;

        /// Tests creating, destroying then recreating an object.
        void testCreateTwice() ;

        /// Tests destroying an unexisting object.
        void testDestroyUnexisting() ;

      // @}


        CPPUNIT_TEST_SUITE(TestModelView) ;

        CPPUNIT_TEST(testBuildOnEmptyModel) ;
        CPPUNIT_TEST(testBuildOnNonEmptyModel) ;
        CPPUNIT_TEST(testDestroyRootObject) ;
        CPPUNIT_TEST(testDestroySubObject) ;
        CPPUNIT_TEST(testDestroyTrait) ;
        CPPUNIT_TEST(testchangeParent) ;
        CPPUNIT_TEST(testUpdate) ;
        CPPUNIT_TEST(testViewAccess) ;
        CPPUNIT_TEST(testCreateTwice) ;
        CPPUNIT_TEST(testDestroyUnexisting) ;

        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif 
    


