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
#ifndef PU_KERNEL_TEST_MODEL_H_
#define PU_KERNEL_TEST_MODEL_H_

#include <cppunit/extensions/HelperMacros.h>
#include <kernel/error.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      ///  Test of model/object/trait methods.
      class TestModel : public CppUnit::TestFixture {
      protected:

  
        // *************
        /// @name Tests 
        // *************

        /// Test for Object::getDescendants.
        void testGetDescendants() ;

        /// Basic test for ObjectReference.
        void testObjectReference() ;

        /// Conversion test for ObjectReference.
        void conversionTestObjectReference() ;
        
        /// Test referencing a destroyed object.
        void testObjectReferenceToDestroyedObject() ;

        /// Test referencing a destroyed object in a destroyed model.
        void testObjectReferenceToDestroyedModel() ;

        /// Basic test for TraitReference.
        void testTraitReference() ;
        
        /// Test referencing a removed trait.
        void testTraitReferenceToRemovedTrait() ;

        /// Test referencing a trait of a destroyed object.
        void testTraitReferenceToDestroyedObject() ;


        // *********************
        /// @name Registerration
        // *********************


        CPPUNIT_TEST_SUITE(TestModel) ;

        CPPUNIT_TEST(testGetDescendants) ;
        CPPUNIT_TEST(testObjectReference) ;
        CPPUNIT_TEST(conversionTestObjectReference) ;
        CPPUNIT_TEST(testObjectReferenceToDestroyedObject) ;
        CPPUNIT_TEST(testObjectReferenceToDestroyedModel) ;
        CPPUNIT_TEST(testTraitReference) ;
        CPPUNIT_TEST(testTraitReferenceToRemovedTrait) ;
        CPPUNIT_TEST(testTraitReferenceToDestroyedObject) ;

        CPPUNIT_TEST_SUITE_END() ;

      public:

        void setUp() ;

        void tearDown() ;

      };

    }
  }
}

#endif /*PU_KERNEL_TEST_MODEL_H_*/
