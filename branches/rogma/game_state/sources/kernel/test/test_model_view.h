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
#ifndef PU_KERNEL_TEST_MODEL_VIEW_H_
#define PU_KERNEL_TEST_MODEL_VIEW_H_


#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      ///  Test for Model/View.
      /*!
      */
      class TestModelView : public CppUnit::TestFixture {
      public:

        /// Tests setup
        void setUp() ;

        /// Tests close.
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

        /// Changing a parentship must not call other updates.
        void testchangeParentIsAtomic() ;

        /// Tests modification of a trait.
        void testUpdate() ;

        /// Tests view access.
        void testViewAccess() ;

        /// Tests creating, destroying then recreating an object.
        void testCreateTwice() ;

        /// Tests destroying an unexisting object.
        void testDestroyUnexisting() ;

        /// Tests closing viewpoint.
        void testCloseViewPoint() ;

        /// Tests for a bug on getting not present trait.
        void testNotPresentTrait() ;

        /// Tests destroying a model with a view on it.
        void testDestroyModel() ;

        /// Tests the top down apply.
        void testForAll() ;
        
        /// Tests several viewpoints on the same model.
        void testMultiViewPoint() ;

        /// Tests several viewpoints of the same kind on the same model.
        void testMultiViewPointOfTheSameKind() ;

        /// Test views on trait class with inheritance.
        void testTraitInheritance() ;

        /// Test views on trait class with virtual inheritance.
        void testTraitVitrualInheritance() ;

        /// Test manual views handling.
        void testManualView() ;

        /// Test manual view construction on an initialised viewpoint.
        void testManualViewOnInitViewPoint() ;
        
        /// Test a bug : crash on init viewpoint with NULL model.
        void initViewPointWithNullModel() ;
        
        /// Test the correction of the preceeding bug.
        /*!
          # building a viewpoint with a NULL model
          # init the viewpoint
          # reset a non NULL model
          # check that views have been initialised 
        */
        void setModelOnInitialisedViewPointWithNullModel() ;

        /// Test the correction of the preceeding bug.
        /*!
          # building a viewpoint on a model
          # init the viewpoint
          # reset another model
          # check that views have been closed 
        */
        void changeModelOnInitialisedViewPoint() ;

        /// Test the correction of the preceeding bug.
        /*!
          # building a viewpoint on a model
          # init the viewpoint
          # reset another model
          # adde object
          # check that views on new model's objects exist 
        */
        void changeModelOnViewPoint() ;
        
        /// Check that destroying an object with deduced traits works.
        void destroyObjectWithDeducedTraits() ;
        
        /// Destroy a viewpoint.
        void detroyViewPoint() ;
        
        /// Destroying a model must call onClose on viewpoint.
        void destroyModelAndCloseViewPoint() ;
        
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
        CPPUNIT_TEST(testCloseViewPoint) ;
        CPPUNIT_TEST(testNotPresentTrait) ;
        CPPUNIT_TEST(testDestroyModel) ;
        CPPUNIT_TEST(testForAll) ;
        CPPUNIT_TEST(testMultiViewPoint) ;
        CPPUNIT_TEST(testMultiViewPointOfTheSameKind) ;
        CPPUNIT_TEST(testTraitInheritance) ;
        CPPUNIT_TEST(testTraitVitrualInheritance) ;
        CPPUNIT_TEST(testchangeParentIsAtomic) ;
        CPPUNIT_TEST(testManualView) ;
        CPPUNIT_TEST(testManualViewOnInitViewPoint) ;
        CPPUNIT_TEST(initViewPointWithNullModel) ;
        CPPUNIT_TEST(setModelOnInitialisedViewPointWithNullModel) ;
        CPPUNIT_TEST(changeModelOnInitialisedViewPoint) ;
        CPPUNIT_TEST(changeModelOnViewPoint) ;
        CPPUNIT_TEST(destroyObjectWithDeducedTraits) ;
        CPPUNIT_TEST(detroyViewPoint) ;
        CPPUNIT_TEST(destroyModelAndCloseViewPoint) ;

        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif 
    


