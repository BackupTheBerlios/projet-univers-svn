/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#ifndef PU_INPUT_TEST_MENU_H_
#define PU_INPUT_TEST_MENU_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Test {
            
      /// Test of menu inputs.
      class TestMenu : public CppUnit::TestFixture 
      {
      public:
  
      // @}
      /*! 
        @name Mandatory methods
      */
      // @{
      
        /// Test init
        void setUp() ;
      
        /// Test close
        void tearDown() ;
      
      protected:
      
        
      // @}      
      /*! 
        @name Tests
      */ 
      // @{
        
        /// 20 seonds of menu testing.
        void mouseCursor() ;

      // @}
      /*!
        @name Test registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestMenu) ;
      
//        CPPUNIT_TEST(mouseCursor) ;
      
        CPPUNIT_TEST_SUITE_END() ;
      // @}      
      };

    }
  }
}

#endif /*PU_INPUT_TEST_MENU_H_*/
