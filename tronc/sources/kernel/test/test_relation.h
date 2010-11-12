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

      /// Tests for Relation class.
      class TestRelation : public CppUnit::TestFixture
      {
      protected:
      /// @name Tests methods
      // @{

        void add() ;
        void severalLinked() ;
        void remove() ;
        void addTwiceGetOnlyOne() ;
        void removeUnexistingIsCorrect() ;
        void destroyingCalledObjectRemoveLink() ;
        void getInverseRelation() ;
        void addInverseRelation() ;

        void isRelatedFormulaChangeStateWhenModifyingRelatedObject() ;
        void isRelatedFormulaChangeStateWhenChangingRelation() ;
        void isRelatedFormulaComplexSample() ;
        void isRelatedInverse() ;

        void relationDeducedByAddingALink() ;
        void relationDeducedByModifyingALinkedObject() ;
        void relationUnDeducedByModifyingALinkedObject() ;
        void relationUnDeducedByRemovingALink() ;

        void primitiveRelationDoesNotTriggerOtherDeduction() ;
        void havingAllButPrimitiveRelationDoesNotMakeItTrue() ;

        void deducedRelationOnAllRelation() ;
        void isPrimitive() ;
        void getPrincipalRelation() ;

      // @}

        CPPUNIT_TEST_SUITE(TestRelation) ;

        CPPUNIT_TEST(add) ;
        CPPUNIT_TEST(remove) ;
        CPPUNIT_TEST(severalLinked) ;
        CPPUNIT_TEST(addTwiceGetOnlyOne) ;
        CPPUNIT_TEST(removeUnexistingIsCorrect) ;
        CPPUNIT_TEST(destroyingCalledObjectRemoveLink) ;
        CPPUNIT_TEST(getInverseRelation) ;
        CPPUNIT_TEST(addInverseRelation) ;
        CPPUNIT_TEST(isRelatedFormulaChangeStateWhenModifyingRelatedObject) ;
        CPPUNIT_TEST(isRelatedFormulaChangeStateWhenChangingRelation) ;
        CPPUNIT_TEST(isRelatedFormulaComplexSample) ;
        CPPUNIT_TEST(isRelatedInverse) ;
        CPPUNIT_TEST(relationDeducedByAddingALink) ;
        CPPUNIT_TEST(relationDeducedByModifyingALinkedObject) ;
        CPPUNIT_TEST(relationUnDeducedByModifyingALinkedObject) ;
        CPPUNIT_TEST(relationUnDeducedByRemovingALink) ;
        CPPUNIT_TEST(primitiveRelationDoesNotTriggerOtherDeduction) ;
        CPPUNIT_TEST(havingAllButPrimitiveRelationDoesNotMakeItTrue) ;
        CPPUNIT_TEST(deducedRelationOnAllRelation) ;
        CPPUNIT_TEST(isPrimitive) ;
//        CPPUNIT_TEST(getPrincipalRelation) ;

        CPPUNIT_TEST_SUITE_END() ;
      };
    }
  }
}
