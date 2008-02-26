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
#ifndef PU_MODEL_TEST_SHOOTING_HELPER_H_
#define PU_MODEL_TEST_SHOOTING_HELPER_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

            
      /// Test for the Model::ShootingHelper and associated logic.
      class TestShootingHelper : public CppUnit::TestFixture {
      protected:
      
        
      /*!
        @name Test methods
      */
      // @{
        
        /// A basic functional test.
        void basicTest() ;
        
        /// @todo test with mobile object and different speed
        
        /// @todo test with connection/deconnection of Computer/TargetSelector
        
      // @}
      /*!
        @name Test registration
      */
      // @{      
      
        CPPUNIT_TEST_SUITE(TestShootingHelper) ;

        CPPUNIT_TEST(basicTest) ;

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


#endif /*PU_MODEL_TEST_SHOOTING_HELPER_H_*/
