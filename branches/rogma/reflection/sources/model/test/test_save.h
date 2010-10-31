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
  namespace Model 
  {
    namespace Test 
    {
            
      /// Test of Model::save.
      class TestSave : public CppUnit::TestFixture 
      {
      protected:
        
      /*! 
        @name Tests 
      */
      // @{
        
        void saveKeyPlayerConfiguration() ;
        void saveMouseButtonPlayerConfiguration() ;
        void saveJoystickButtonPlayerConfiguration() ;
        void saveJoystickAxes() ;
        
      // @}
      /*! 
        @name Tests registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestSave) ;
      
        CPPUNIT_TEST(saveKeyPlayerConfiguration) ;
        CPPUNIT_TEST(saveMouseButtonPlayerConfiguration) ;
        CPPUNIT_TEST(saveJoystickButtonPlayerConfiguration) ;
        CPPUNIT_TEST(saveJoystickAxes) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      };

    }
  }
}
