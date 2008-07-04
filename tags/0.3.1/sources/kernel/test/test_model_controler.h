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
#ifndef PU_KERNEL_TEST_MODEL_CONTROLER_H_
#define PU_KERNEL_TEST_MODEL_CONTROLER_H_


#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      ///  Test for Model/Controler.
      /*!
      */
      class TestModelControler : public CppUnit::TestFixture {
      public:

        void setUp() ;

        void tearDown() ;

      protected:

      /*! 
        @name Tests methods
      */
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

        /// Tests closing a controler set.
        void testCloseControlerSet() ;

        /// Tests the bottom up simulation.
        void testSimulateAll() ;
        
        /// Tests several controler sets on the same model.
        void testMultiControlerSet() ;

        /// Tests several controler set of the same kind on the same model.
        void testMultiControlerSetOfTheSameKind() ;

        /// Tests destroying a model with controlers on it.
        void testDestroyModel() ;

        /// Tests a controler on a base trait class.
        void testBaseTraitControler() ;

        /// Test a bug : crash on init controler set with NULL model.
        void initControlerSetWithNullModel() ;
        
        /// Test the correction of the preceeding bug.
        /*!
          # building a controler set with a NULL model
          # init the controler set
          # reset a non NULL model
          # check that controlers have been initialised 
        */
        void setModelOnInitialisedControlerSetWithNullModel() ;

        /// Test the correction of the preceeding bug.
        /*!
          # building a controler set on a model
          # init the controler set
          # reset another model
          # check that controler have been closed 
        */
        void changeModelOnInitialisedControlerSet() ;

      // @}


        CPPUNIT_TEST_SUITE(TestModelControler) ;

        CPPUNIT_TEST(testBuildOnEmptyModel) ;
        CPPUNIT_TEST(testBuildOnNonEmptyModel) ;
        CPPUNIT_TEST(testDestroyRootObject) ;
        CPPUNIT_TEST(testDestroySubObject) ;
        CPPUNIT_TEST(testDestroyTrait) ;
        CPPUNIT_TEST(testCloseControlerSet) ;
        CPPUNIT_TEST(testSimulateAll) ;
        CPPUNIT_TEST(testMultiControlerSet) ;
        CPPUNIT_TEST(testMultiControlerSetOfTheSameKind) ;
        CPPUNIT_TEST(testBaseTraitControler) ;
        CPPUNIT_TEST(initControlerSetWithNullModel) ;
        CPPUNIT_TEST(setModelOnInitialisedControlerSetWithNullModel) ;
        CPPUNIT_TEST(changeModelOnInitialisedControlerSet) ;
        
        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif 
    


