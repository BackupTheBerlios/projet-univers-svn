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
#ifndef PU_KERNEL_TEST_MODEL_H_
#define PU_KERNEL_TEST_MODEL_H_

#include <cppunit/extensions/HelperMacros.h>
#include <kernel/error.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {

      /// Test of model/object/trait methods.
      class TestModel : public CppUnit::TestFixture 
      {
      protected:

  
      /*! 
        @name Tests methods
      */
      // @{  

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

        /// Referencing a destroyed object after a destruction.
        void testObjectReferenceAffectation() ;

        /// Basic test for TraitReference.
        void testTraitReference() ;
        
        /// Test referencing a removed trait.
        void testTraitReferenceToRemovedTrait() ;

        /// Test referencing a trait of a destroyed object.
        void testTraitReferenceToDestroyedObject() ;

        /// Test a set of object references.
        void testSetOfObjectReferences() ;

        /// Check that a notify on a trait whithout object is correct.
        void notifyOnNotAssignedTrait() ;
        
        /// Check that destroying an object with deduced traits works.
        void destroyObjectWithDeducedTraits() ;
        
        /// Add, then remove and finally add the same trait.
        void addTraitTwice() ;
        
        /// Access to an object by name.
        void getByName() ;
        
        /// Destroy a set of objects, some parents before their children.
        void destroyObjects() ;
        
        /// Access to a destroyed child object by identifier.
        void getDestroyedChild() ;
        
      // @}


        CPPUNIT_TEST_SUITE(TestModel) ;

        CPPUNIT_TEST(testGetDescendants) ;
        CPPUNIT_TEST(testObjectReference) ;
        CPPUNIT_TEST(conversionTestObjectReference) ;
        CPPUNIT_TEST(testObjectReferenceToDestroyedObject) ;
        CPPUNIT_TEST(testObjectReferenceToDestroyedModel) ;
        CPPUNIT_TEST(testObjectReferenceAffectation) ;
        CPPUNIT_TEST(testTraitReference) ;
        CPPUNIT_TEST(testTraitReferenceToRemovedTrait) ;
        CPPUNIT_TEST(testTraitReferenceToDestroyedObject) ;
        CPPUNIT_TEST(testSetOfObjectReferences) ;
        CPPUNIT_TEST(notifyOnNotAssignedTrait) ;
        CPPUNIT_TEST(destroyObjectWithDeducedTraits) ;
        CPPUNIT_TEST(addTraitTwice) ;
        CPPUNIT_TEST(getByName) ;
        CPPUNIT_TEST(destroyObjects) ;
        CPPUNIT_TEST(getDestroyedChild) ;

        CPPUNIT_TEST_SUITE_END() ;

      };

    }
  }
}

#endif /*PU_KERNEL_TEST_MODEL_H_*/
