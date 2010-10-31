/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

      ///  Test for deduced traits.
      class TestDeducedTrait : public CppUnit::TestFixture
      {
      protected:

      /// @name Tests methods
      // @{

        /// Tests an And formula.
        void testAnd() ;

        void testAndOnSubTrait() ;

        /// Tests an Or formula.
        void testOr() ;

        /// Tests a Not formula.
        void testNot() ;

        /// Tests a composite formula.
        void testComposite() ;

        /// Tests a composite formula with deduced traits.
        void testCompositeWithDeduced() ;

        /// Tests view on deduced trait and correct notification.
        void testDeducedTraitViews() ;

        /// Check that a notify on a trait whithout object is correct.
        /*!
          The trait is involved in a formula.
        */
        void notifyOnNotAssignedTrait() ;

        /// Test getLatestUpdatedTrait with a view updating a trait of the object.
        /*!
          Test a bug found on getLatestUpdatedTrait.
        */
        void testGetLatestUpdatedTrait() ;

        /// Add a parent and check that HasParent has changed.
        void addParentTrait() ;

        /// Add an intermediate parent and check that view has been updated.
        void addSubParentTrait() ;

        /// Remove a parent and check that HasParent has changed.
        void removeParentTrait() ;

        /// Update an ancestor trait and check that view has not been updated.
        void updateAncestorTrait() ;

        /// Update a parent trait and check that view has been updated.
        void updateParentTrait() ;

        /// Remove a element and check that grand children are updated.
        void removeSubAncestorTrait() ;

        /// Add a parent and check that HasParent has changed.
        void addParentTraitOnCompositeFormula() ;

        // Add an intermediate parent and check that view has been updated.
        void addSubParentTraitOnCompositeFormula() ;

        /// Add a child thas is true at beginning for HasParent.
        void addTrueChild() ;

        /// Change the parent of an object HasParent becomes true.
        void changeParentHasParentBecomeTrue() ;

        /// Change the ancestor of an object HasParent becomes true.
        void changeAncestorHasParentBecomeTrue() ;

        /// Change the parent of an object HasParent becomes false.
        void changeParentHasParentBecomeFalse() ;

        /// Change the parent with HasParent still true updates the view.
        void changeParentHasParentUpdated() ;

        /// Bug test : a deduced trait on a deduced trait does not work.
        void deducedTraitOnDeducedTrait() ;

        /// Add a child and check that HasChild has changed.
        void addChildTrait() ;

        /// Remove a child and check that HasChild has changed.
        void removeChildTrait() ;

        /// Change the parent of an object, HasChild becomes true.
        /*!
          HasChild become true for the new parent and false for the old one.
        */
        void changeParentHasChildBecomeTrue() ;

        void removeParentDeducedTrait() ;

        void hasAncestor() ;
        void hasAncestorRemoveAncestor() ;
        void hasAncestorChangeParent() ;

        void orStillTrueUpdatesObserver() ;
        void orStillTrueUpdatesObserverThroughAnd() ;


      // @}


        CPPUNIT_TEST_SUITE(TestDeducedTrait) ;

        CPPUNIT_TEST(testAnd) ;
        CPPUNIT_TEST(testAndOnSubTrait) ;
        CPPUNIT_TEST(testOr) ;
        CPPUNIT_TEST(testNot) ;
        CPPUNIT_TEST(testComposite) ;
        CPPUNIT_TEST(testCompositeWithDeduced) ;
        CPPUNIT_TEST(testDeducedTraitViews) ;
        CPPUNIT_TEST(notifyOnNotAssignedTrait) ;
        CPPUNIT_TEST(testGetLatestUpdatedTrait) ;

        CPPUNIT_TEST(addParentTrait) ;
        CPPUNIT_TEST(addSubParentTrait) ;
        CPPUNIT_TEST(removeParentTrait) ;
        CPPUNIT_TEST(updateAncestorTrait) ;
        CPPUNIT_TEST(updateParentTrait) ;
        CPPUNIT_TEST(removeSubAncestorTrait) ;
        CPPUNIT_TEST(addParentTraitOnCompositeFormula) ;
        CPPUNIT_TEST(addSubParentTraitOnCompositeFormula) ;
        CPPUNIT_TEST(addTrueChild) ;
        CPPUNIT_TEST(changeParentHasParentBecomeTrue) ;
        CPPUNIT_TEST(changeAncestorHasParentBecomeTrue) ;

        CPPUNIT_TEST(changeParentHasParentBecomeFalse) ;
        CPPUNIT_TEST(changeParentHasParentUpdated) ;
        CPPUNIT_TEST(deducedTraitOnDeducedTrait) ;

        CPPUNIT_TEST(addChildTrait) ;
        CPPUNIT_TEST(removeChildTrait) ;
        CPPUNIT_TEST(changeParentHasChildBecomeTrue) ;
        CPPUNIT_TEST(removeParentDeducedTrait) ;

        CPPUNIT_TEST(hasAncestor) ;
        CPPUNIT_TEST(hasAncestorRemoveAncestor) ;
        CPPUNIT_TEST(hasAncestorChangeParent) ;
        CPPUNIT_TEST(orStillTrueUpdatesObserver) ;
        CPPUNIT_TEST(orStillTrueUpdatesObserverThroughAnd) ;

        CPPUNIT_TEST_SUITE_END() ;


      };
    }
  }
}
