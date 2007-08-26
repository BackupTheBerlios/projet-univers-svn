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
#ifndef PU_MODEL_TEST_ORIENTED_H_
#define PU_MODEL_TEST_ORIENTED_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

            
      /// Test for Model::Oriented
      class TestOriented : public CppUnit::TestFixture {
      protected:
      
        
      /*!
        @name Test methods
      */
      // @{
        

        /// Test getOrientation(Kernel::Object*) in normal case.
        void testGetOrientation1() ;

        /// Test getOrientation(Kernel::Object*) with non Oriented ancestor.
        void testGetOrientation2() ;

        /// Test getOrientation(Kernel::Object*) with non Oriented intermediate.
        void testGetOrientation3() ;

        /// Test setOrientation(Position,Object*) in normal case.
        void testSetOrientation1() ;
        
        /// Test setOrientation(Position,Object*) with non Oriented ancestor.
        void testSetOrientation2() ;
        
        /// Test setOrientation(Position,Object*) with non Oriented intermediate.
        void testSetOrientation3() ;
        
        /// Check that roll of default orientation is 0. 
        void rollOfDefaultOrientation() ;
        
      // @}
      /*!
        @name Test registration
      */
      // @{      
      
        CPPUNIT_TEST_SUITE(TestOriented) ;
      
        CPPUNIT_TEST(testGetOrientation1) ;
        CPPUNIT_TEST(testGetOrientation2) ;
        CPPUNIT_TEST(testGetOrientation3) ;

        CPPUNIT_TEST(testSetOrientation1) ;
        CPPUNIT_TEST(testSetOrientation2) ;
        CPPUNIT_TEST(testSetOrientation3) ;

        CPPUNIT_TEST(rollOfDefaultOrientation) ;
      
        CPPUNIT_TEST_SUITE_END() ;
      
      // @}      
                
     public:

      /*!
        @name Mandatory methods
      */
      // @{

      
        void setUp() ;
        void tearDown() ;
      
      // @}      
      
      
      };

    }
  }
}


#endif
