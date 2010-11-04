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
#pragma once


#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      ///  Test for Model/View.
      class TestModelView : public CppUnit::TestFixture
      {
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

        /// Test manual view construction on an initialized viewpoint.
        void testManualViewOnInitViewPoint() ;

        /// Test a bug : crash on init viewpoint with NULL model.
        void initViewPointWithNullModel() ;

        /// Test the correction of the preceding bug.
        /*!
          # building a viewpoint with a NULL model
          # init the viewpoint
          # reset a non NULL model
          # check that views have been initialized
        */
        void setModelOnInitialisedViewPointWithNullModel() ;

        /// Test the correction of the preceding bug.
        /*!
          # building a viewpoint on a model
          # init the viewpoint
          # reset another model
          # check that views have been closed
        */
        void changeModelOnInitialisedViewPoint() ;

        /// Test the correction of the preceding bug.
        /*!
          # building a viewpoint on a model
          # init the viewpoint
          # reset another model
          # add object
          # check that views on new model's objects exist
        */
        void changeModelOnViewPoint() ;

        /// Check that destroying an object with deduced traits works.
        void destroyObjectWithDeducedTraits() ;

        /// Destroy a viewpoint.
        void detroyViewPoint() ;

        /// Destroying a model must call onClose on viewpoint.
        void destroyModelAndCloseViewPoint() ;

        /// Access a trait of object.
        void accessOtherTrait() ;

        /// Updating an ancestor trait update the descendant deduced trait
        void updateAncestor() ;
        /// Same test as above in recursive case
        void updateRecursiveAncestor() ;
        /// Same test as above with two level children
        void updateRecursiveAncestorLevel2() ;

        void addingParentUpdateHasAncestor() ;

        /// Updating a parent trait update the descendant deduced traits
        void updateParentTrait() ;
        /// Same test as above with two level children
        void updateRecursiveParentTrait() ;
        void addingNewParentObjectShouldNotUpdateHasParentDescendant() ;
        void removingAncestorShouldNotUpdateHasParentDescendant() ;
        void removingAncestorShouldNotUpdateHasAncestorDescendant() ;
        void removingDescendantShouldNotUpdateHasChildAncestor() ;

        void initNotTrait() ;

        void updatingChildObjectUpdatesHasChild() ;
        void addingNewChildObjectUpdatesHasChild() ;
        void addingNewDescendentObjectDoesNotUpdateHasChild() ;
        void removingDescendentObjectDoesNotUpdateHasChild() ;
        void removingChildObjectUpdatesHasChild() ;
        void removingIntermediateUpdatesHasChild() ;

        void changingParentUpdatesHasParent() ;
        void changingParentUpdatesHasParentNegativeTest() ;
        void changingParentUpdatesHasAncestor() ;
        void changingParentUpdatesHasAncestorNegativeTest() ;
        void changingParentUpdatesHasChild() ;

        void severalViewsOnATraitForTheSameViewPoint() ;

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
        CPPUNIT_TEST(accessOtherTrait) ;
        CPPUNIT_TEST(updateAncestor) ;
        CPPUNIT_TEST(updateRecursiveAncestor) ;
        CPPUNIT_TEST(updateRecursiveAncestorLevel2) ;
        CPPUNIT_TEST(addingParentUpdateHasAncestor) ;
        CPPUNIT_TEST(updateParentTrait) ;
        CPPUNIT_TEST(updateRecursiveParentTrait) ;
        CPPUNIT_TEST(addingNewParentObjectShouldNotUpdateHasParentDescendant) ;
        CPPUNIT_TEST(removingAncestorShouldNotUpdateHasParentDescendant) ;
        CPPUNIT_TEST(removingAncestorShouldNotUpdateHasAncestorDescendant) ;
        CPPUNIT_TEST(removingDescendantShouldNotUpdateHasChildAncestor) ;
        CPPUNIT_TEST(initNotTrait) ;
        CPPUNIT_TEST(updatingChildObjectUpdatesHasChild) ;
        CPPUNIT_TEST(addingNewChildObjectUpdatesHasChild) ;
        CPPUNIT_TEST(addingNewDescendentObjectDoesNotUpdateHasChild) ;
        CPPUNIT_TEST(removingDescendentObjectDoesNotUpdateHasChild) ;
        CPPUNIT_TEST(removingChildObjectUpdatesHasChild) ;
        CPPUNIT_TEST(removingIntermediateUpdatesHasChild) ;
        CPPUNIT_TEST(changingParentUpdatesHasParent) ;
        CPPUNIT_TEST(changingParentUpdatesHasParentNegativeTest) ;
        CPPUNIT_TEST(changingParentUpdatesHasAncestor) ;
        CPPUNIT_TEST(changingParentUpdatesHasAncestorNegativeTest) ;
        CPPUNIT_TEST(changingParentUpdatesHasChild) ;
        CPPUNIT_TEST(severalViewsOnATraitForTheSameViewPoint) ;

        CPPUNIT_TEST_SUITE_END() ;


      };
    }
  }
}



