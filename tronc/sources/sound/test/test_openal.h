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
#ifndef PU_SOUND_TEST_OPENAL_H_
#define PU_SOUND_TEST_OPENAL_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

            
      /// Basic test for openal
      class TestOpenAL : public CppUnit::TestFixture {
      protected:
      
        
      // ************
      /// @name Tests
      // ************
      // @{
        
        /// 
        void basicTest() ;
           
      // @}
      // *******************************
      /// @name Register
      // *******************************
      // @{      
      
        CPPUNIT_TEST_SUITE(TestOpenAL) ;
      
        CPPUNIT_TEST(basicTest) ;
      
        CPPUNIT_TEST_SUITE_END() ;
      
      // @}      
                
     public:

      // ************
      /// @name Setup
      // ************
      // @{

      
        /// Initit
        void setUp() ;
      
        /// Close
        void tearDown() ;
      
      // @}      
      
      
      };

    }
  }
}


#endif
