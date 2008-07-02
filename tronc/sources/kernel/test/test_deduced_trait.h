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

        /// Tests setup
        void setUp() ;

        /// Tests close.
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
        
        // Add an intermediate parent and check that view has been updated.
        void addSubParentTrait() ;
        
        /// Remove a parent and check that HasParent has changed.
        void addRemoveParentTrait() ;
        
        /// Update an ancetsor trait and check that view has not been updated.
        void updateAncestorTrait() ;
        
        /// Update a parent trait and check that view has been updated.
        void updateParentTrait() ;
        
        /// Remove a element and check that grand children are updated.
        void removeSubAncestorTrait() ;

        /// Add a parent and check that HasParent has changed.
        void addParentTraitOnCompositeFormula() ;
        
        /// Add a child thas is true at beginning for HasParent.
        void addTrueChild() ;
        
        /// Change the parent of an object HasParent becomes true.
        void changeParentHasParentBecomeTrue() ;
        
        /// Change the parent of an object HasParent becomes false.
        void changeParentHasParentBecomeFalse() ;
        
        /// Change the parent with HasParent still true updates the view.
        void changeParentHasParentUpdated() ;
        
        /// Bug test : a deduced trait on a deduced trait does not work.
        void deducedTraitOnDeducedTrait() ;
        
      // @}


        CPPUNIT_TEST_SUITE(TestDeducedTrait) ;

        CPPUNIT_TEST(testAnd) ;
        CPPUNIT_TEST(testOr) ;
        CPPUNIT_TEST(testNot) ;
        CPPUNIT_TEST(testComposite) ;
        CPPUNIT_TEST(testCompositeWithDeduced) ;
        CPPUNIT_TEST(testDeducedTraitViews) ;
        CPPUNIT_TEST(notifyOnNotAssignedTrait) ;
        CPPUNIT_TEST(testGetLatestUpdatedTrait) ;

        CPPUNIT_TEST(addParentTrait) ;
        CPPUNIT_TEST(addSubParentTrait) ;
        CPPUNIT_TEST(addRemoveParentTrait) ;
        CPPUNIT_TEST(updateAncestorTrait) ;
        CPPUNIT_TEST(updateParentTrait) ;
        CPPUNIT_TEST(removeSubAncestorTrait) ;
        CPPUNIT_TEST(addParentTraitOnCompositeFormula) ;
        CPPUNIT_TEST(addTrueChild) ;
        CPPUNIT_TEST(changeParentHasParentBecomeTrue) ;
        CPPUNIT_TEST(changeParentHasParentBecomeFalse) ;
        CPPUNIT_TEST(changeParentHasParentUpdated) ;
        CPPUNIT_TEST(deducedTraitOnDeducedTrait) ;
        
        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif /*PU_KERNEL_TEST_DEDUCED_TRAIT_H_*/
