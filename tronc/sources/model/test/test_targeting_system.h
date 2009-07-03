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
#pragma once

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {
            
      /// Test of TargetingSystem.
      class TestTargetingSystem : public CppUnit::TestFixture
      {
      protected:
      
        
      /*!
        @name Test methods
      */
      // @{
        
        /// Basic test.
        void selectOneObject() ;

        /// Change selection.
        void changeSelection() ;

        /// Test a Computer destruction.
        void destroyComputer() ;

        /// Test a Detector destruction.
        void destroyDetector() ;
        
        /// Test the nearest target selection.
        void selectNearestTarget() ;
        
        /// Test the nearest enemy selection.
        void selectNearestEnemy() ;
        
        /// Test the nearest enemy selection.
        void selectNearestEnemyAfterDestruction() ;
        
        /*!
          @todo 
            test of selection whithout data
            test of real object destruction
        */
        
      // @}
      /*!
        @name Test registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestTargetingSystem) ;
      
        CPPUNIT_TEST(selectOneObject) ;
        CPPUNIT_TEST(changeSelection) ;
        CPPUNIT_TEST(destroyComputer) ;
        CPPUNIT_TEST(destroyDetector) ;
        CPPUNIT_TEST(selectNearestTarget) ;
        CPPUNIT_TEST(selectNearestEnemy) ;
        CPPUNIT_TEST(selectNearestEnemyAfterDestruction) ;

        CPPUNIT_TEST_SUITE_END() ;
      
      };

    }
  }
}
