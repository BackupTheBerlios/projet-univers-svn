/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef PU_MODEL_TEST_POSITIONNED_H_
#define PU_MODEL_TEST_POSITIONNED_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

            
      /// Test for Model::Positionned
      class TestPositionned : public CppUnit::TestFixture {
      protected:
      
        
      /*!
        @name Test methods
      */
      // @{
        
        /// Test Model::Positionned::getPosition(Kernel::Object*).
        void testGetPosition1() ;

        /// Test getPosition(Object*) with non Positionned ancestor.
        void testGetPosition2() ;

        /// Test getPosition(Object*) with non Positionned intermediate.
        void testGetPosition3() ;
           
        /// Test setPosition(Position,Object*) in normal case.
        void testSetPosition1() ;

        /// Test setPosition(Position,Object*) with non Positionned ancestor.
        void testSetPosition2() ;

        /// Test setPosition(Position,Object*) with non Positionned intermediate.
        void testSetPosition3() ;


      // @}
      /*!
        @name Test registration
      */
      // @{      
      
        CPPUNIT_TEST_SUITE(TestPositionned) ;
      
        CPPUNIT_TEST(testGetPosition1) ;
        CPPUNIT_TEST(testGetPosition2) ;
        CPPUNIT_TEST(testGetPosition3) ;
        CPPUNIT_TEST(testSetPosition1) ;
        CPPUNIT_TEST(testSetPosition2) ;
        CPPUNIT_TEST(testSetPosition3) ;
      
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
