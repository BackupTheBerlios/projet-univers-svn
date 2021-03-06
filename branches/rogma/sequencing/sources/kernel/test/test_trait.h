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
        @name Trait dependencies udpate tests

        there are 3 operations : addTrait, destroyTrait and changeParent
        there are 7 formula constructors (And,Or,HasTrait,HasParent,HasAncestor,
        HasChild) with only 4 that are impacted by changeParent.

        That makes a total of 2x7 (add/destroy trait on all formulae)
                            + 4 (changeParent on "parentship" formulae)
                            = 18 combinations just for the nominal tests
      */
      // @{

        void depedentTrait() ;
        void removeDeducedTrait() ;
        void parentTrait() ;
        void childTrait() ;
        void orAddNewTrait() ;

        void addTraitChangeHasParentDependencies() ;
        void removeTraitChangeHasParentDependencies() ;
        void removeTraitChangeHasParentDependenciesByBecommingFalse() ;
        void changeParentChangeHasParentDependencies() ;
        void addTraitOnEmptyStructure() ;

        void hasParentFormulaDependencies() ;
        void andHasParentAddTraitChangeHasParentDependencies() ;
        void hasParentOnDeducedTrait() ;

     // @}

        CPPUNIT_TEST_SUITE(TestTrait) ;

        CPPUNIT_TEST(depedentTrait) ;
        CPPUNIT_TEST(removeDeducedTrait) ;
        CPPUNIT_TEST(parentTrait) ;
        CPPUNIT_TEST(childTrait) ;
        CPPUNIT_TEST(orAddNewTrait) ;
        CPPUNIT_TEST(addTraitChangeHasParentDependencies) ;
        CPPUNIT_TEST(removeTraitChangeHasParentDependencies) ;
        CPPUNIT_TEST(removeTraitChangeHasParentDependenciesByBecommingFalse) ;
        CPPUNIT_TEST(changeParentChangeHasParentDependencies) ;
        CPPUNIT_TEST(addTraitOnEmptyStructure) ;
        CPPUNIT_TEST(hasParentFormulaDependencies) ;
        CPPUNIT_TEST(andHasParentAddTraitChangeHasParentDependencies) ;
        CPPUNIT_TEST(hasParentOnDeducedTrait) ;

        CPPUNIT_TEST_SUITE_END() ;
      };
    }
  }
}
