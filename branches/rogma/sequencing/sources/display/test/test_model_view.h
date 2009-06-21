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
#ifndef PU_DISPLAY_TEST_MODEL_VIEW_H_
#define PU_DISPLAY_TEST_MODEL_VIEW_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers 
{
  namespace Display 
  {
    namespace Test 
    {
            
      /// Global testing of this viewpoint.
      class TestModelView : public CppUnit::TestFixture 
      {
      protected:
      /*! 
        @name Tests
      */ 
      // @{
        
        /// Basic test, mainly to check against seg fault.
        void testConstruct() ;

        /// Build a viewpoint and then destroy the observer.
        /*!
          created a seg fault
        */
        void destroyObserver() ;
        
        /// Select a target and display it
        void selectedTarget() ;
        
        /// Display an ideal target
        void displayIdealTarget() ;
        
        /// Test the space dust effect.
        void spaceDust() ;
        
        /// Display a test image.
        void displayImage() ;
        
        /// Display a test image.
        void displayExplosion() ;
        
        /// Build a viewpoint and then destroy the observer and finally recreate it.
        void recreateObserver() ;
        
        /// Access to mesh size.
        void getMeshSize() ;
        
        /// Create a displayable object then change parent
        void changeParent() ;
        
        void changeObserver() ;
        
        void changeTargetDisplayer() ;
        
      // @}
        /*! 
          @name Tests registration
        */ 
        // @{
    
        CPPUNIT_TEST_SUITE(TestModelView) ;
      
        CPPUNIT_TEST(testConstruct) ;
        CPPUNIT_TEST(destroyObserver) ;
        CPPUNIT_TEST(selectedTarget) ;
        CPPUNIT_TEST(displayIdealTarget) ;
        CPPUNIT_TEST(spaceDust) ;
        CPPUNIT_TEST(displayImage) ;
        CPPUNIT_TEST(displayExplosion) ;
        CPPUNIT_TEST(recreateObserver) ;
        CPPUNIT_TEST(getMeshSize) ;
        CPPUNIT_TEST(changeParent) ;
        CPPUNIT_TEST(changeObserver) ;
        CPPUNIT_TEST(changeTargetDisplayer) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      // @}
      };

    }
  }
}


#endif
