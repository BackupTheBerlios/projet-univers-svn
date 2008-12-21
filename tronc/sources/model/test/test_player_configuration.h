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
#ifndef PU_MODEL_TEST_PLAYER_CONFIGURATION_H_
#define PU_MODEL_TEST_PLAYER_CONFIGURATION_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Test 
    {
            
      /// Test of PlayerConfiguration.
      class TestPlayerConfiguration : public CppUnit::TestFixture {
      protected:
      
      /*! 
        @name Tests 
      */
      // @{
        
        void testGetInputEvent() ;

        /// Normal decrease axis 
        void decreaseAxis() ;

        /// Limit case 
        void decreaseFirstAxis() ;
        
        /// Normal increase axis 
        void increaseAxis() ;

        /// Limit case 
        void increaseLastAxis() ;
        
        void invertedAxisPrint() ;
        
        void normalAxisPrint() ;
        
        void changeAxisMapping() ;
        
        void cycleThoughAxesMapping() ;
        
        void axisViolation() ;
        void commandViolation() ;
        
        void invertAxis() ;
        
      // @}
      /*! 
        @name Tests registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestPlayerConfiguration) ;
      
        CPPUNIT_TEST(testGetInputEvent) ;
        CPPUNIT_TEST(decreaseAxis) ;
        CPPUNIT_TEST(decreaseFirstAxis) ;
        CPPUNIT_TEST(increaseAxis) ;
        CPPUNIT_TEST(increaseLastAxis) ;
        CPPUNIT_TEST(invertedAxisPrint) ;
        CPPUNIT_TEST(normalAxisPrint) ;
        CPPUNIT_TEST(changeAxisMapping) ;
        CPPUNIT_TEST(cycleThoughAxesMapping) ;
        CPPUNIT_TEST(axisViolation) ;
        CPPUNIT_TEST(commandViolation) ;
        CPPUNIT_TEST(invertAxis) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      // @}
      
      };

    }
  }
}

#endif /*PU_MODEL_TEST_PLAYER_CONFIGURATION_H_*/
