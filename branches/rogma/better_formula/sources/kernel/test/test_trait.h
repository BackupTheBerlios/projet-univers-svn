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

      /// Test for trait/deduced trait dependencies.
      class TestTrait : public CppUnit::TestFixture
      {
      protected:
      /*!
        @name Trait dependencies maintenance tests

        there are 3 operations : addTrait, destroyTrait and changeParent
        there are 7 formula constructors (And,Or,HasTrait,HasParent,HasAncestor,
        HasChild) with only 4 that are impacted by changeParent.

        That makes a total of 2x7 (add/destroy trait on all formulae)
                            + 4 (changeParent on "parentship" formulae)
                            = 18 combinations just for the nominal tests

        @todo we should also perform some tests with a recursive formula.
      */
      // @{

        void andBecomesTrueDepedentTrait() ;
        void removeDeducedTraitOnAndDepedentTrait() ;

        void addNewTraitOnOrChangeDepedencies() ;
        /// @todo
//        void removeTraitOnOrChangeDepedencies() ;

        void parentTraitHasParentDependency() ;
        void addIntermediateTraitChangeHasParentDependencies() ;
        void removeIntermediateTraitChangeHasParentDependencies() ;
        void removeTraitChangeHasParentDependenciesByBecommingFalse() ;
        void changeParentChangeHasParentDependencies() ;
        void changeParentChangeHasParentDependenciesRecursivelly() ;
        void addTraitOnEmptyStructure() ;
        void hasParentFormulaDependencies() ;
        void andHasParentAddTraitChangeHasParentDependencies() ;
        void hasParentOnDeducedTrait() ;
        void destroyParentObject() ;
        void changeParentChangingNothing() ;

        void hasAncestorHasDependencies() ;
        void addIntermediateTraitChangeHasAncestorDependencies() ;
        void removeIntermediateTraitChangeHasAncestorDependencies() ;
        void changeParentChangeHasAncestorDependencies() ;
        void destroyAncestorObject() ;
        void destroyObjectOnRecusiveFormula() ;

        void hasChildHasDependencies() ;
        void childTraitIsHasChildDependency() ;
        void addingIntermediateTraitChangeHasChildDependencies() ;
        void removingIntermediateTraitChangeHasChildDependencies() ;
        void destroyChildObjectShouldNotCrash() ;

      // @}
      /*!
        @name Formula updaters calculus test
      */
      // @{

        void hasTraitFormulaUpdaterTraits() ;
        void andUpdaterTraits() ;
        void hasParentUpdaterTraits() ;
        void updaterTraitsShouldNotBeReflexive() ;

      // @}
      /*!
        @name Formula number of true formula maintenance
      */
      // @{

        void addingAncestorChangeNumberOfTrueChildFormulae() ;
        void addingParentChangeNumberOfTrueChildFormulae() ;
        void addingChildChangeNumberOfTrueChildFormulae() ;
        void changingParentOfHasParentChangesNumberOfTrueChildFormulae() ;
        void changingParentOfHasAncestorChangesNumberOfTrueChildFormulae() ;
        void changingParentOfHasChildChangesNumberOfTrueChildFormulae() ;

     // @}

        CPPUNIT_TEST_SUITE(TestTrait) ;

        CPPUNIT_TEST(andBecomesTrueDepedentTrait) ;
        CPPUNIT_TEST(removeDeducedTraitOnAndDepedentTrait) ;

        CPPUNIT_TEST(addNewTraitOnOrChangeDepedencies) ;

        CPPUNIT_TEST(parentTraitHasParentDependency) ;
        CPPUNIT_TEST(addIntermediateTraitChangeHasParentDependencies) ;
        CPPUNIT_TEST(removeIntermediateTraitChangeHasParentDependencies) ;
        CPPUNIT_TEST(removeTraitChangeHasParentDependenciesByBecommingFalse) ;
        CPPUNIT_TEST(changeParentChangeHasParentDependencies) ;
        CPPUNIT_TEST(changeParentChangeHasParentDependenciesRecursivelly) ;
        CPPUNIT_TEST(addTraitOnEmptyStructure) ;
        CPPUNIT_TEST(hasParentFormulaDependencies) ;
        CPPUNIT_TEST(andHasParentAddTraitChangeHasParentDependencies) ;
        CPPUNIT_TEST(hasParentOnDeducedTrait) ;
        CPPUNIT_TEST(destroyParentObject) ;
        CPPUNIT_TEST(changeParentChangingNothing) ;

        CPPUNIT_TEST(hasAncestorHasDependencies) ;
        CPPUNIT_TEST(addIntermediateTraitChangeHasAncestorDependencies) ;
        CPPUNIT_TEST(removeIntermediateTraitChangeHasAncestorDependencies) ;
        CPPUNIT_TEST(changeParentChangeHasAncestorDependencies) ;
        CPPUNIT_TEST(destroyAncestorObject) ;
        CPPUNIT_TEST(destroyObjectOnRecusiveFormula) ;

        CPPUNIT_TEST(hasChildHasDependencies) ;
        CPPUNIT_TEST(childTraitIsHasChildDependency) ;
        CPPUNIT_TEST(addingIntermediateTraitChangeHasChildDependencies) ;
        CPPUNIT_TEST(removingIntermediateTraitChangeHasChildDependencies) ;
        CPPUNIT_TEST(destroyChildObjectShouldNotCrash) ;

        CPPUNIT_TEST(hasTraitFormulaUpdaterTraits) ;
        CPPUNIT_TEST(andUpdaterTraits) ;
        CPPUNIT_TEST(hasParentUpdaterTraits) ;
        CPPUNIT_TEST(updaterTraitsShouldNotBeReflexive) ;

        CPPUNIT_TEST(addingAncestorChangeNumberOfTrueChildFormulae) ;
        CPPUNIT_TEST(addingParentChangeNumberOfTrueChildFormulae) ;
        CPPUNIT_TEST(addingChildChangeNumberOfTrueChildFormulae) ;
        CPPUNIT_TEST(changingParentOfHasParentChangesNumberOfTrueChildFormulae) ;
        CPPUNIT_TEST(changingParentOfHasAncestorChangesNumberOfTrueChildFormulae) ;
        CPPUNIT_TEST(changingParentOfHasChildChangesNumberOfTrueChildFormulae) ;

        CPPUNIT_TEST_SUITE_END() ;
      };
    }
  }
}
