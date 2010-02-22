/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2009 Mathieu ROGER                                 *
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
        /// Display an ideal target
        void displayIdealTarget() ;
        /// Display a test image.
        void displayImage() ;
        /// Build a viewpoint and then destroy the observer and finally recreate it.
        void recreateObserver() ;
        /// Access to mesh size.
        void getMeshSize() ;
        /// Create a displayable object then change parent
        void changeParent() ;
        void changeObserver() ;
        void setOrientation() ;
        void testMission() ;

      // @}
        /*!
          @name Tests registration
        */
        // @{

        CPPUNIT_TEST_SUITE(TestModelView) ;

        CPPUNIT_TEST(testConstruct) ;
        CPPUNIT_TEST(destroyObserver) ;
        CPPUNIT_TEST(displayIdealTarget) ;
        CPPUNIT_TEST(displayImage) ;
        CPPUNIT_TEST(recreateObserver) ;
        CPPUNIT_TEST(getMeshSize) ;
        CPPUNIT_TEST(changeParent) ;
        CPPUNIT_TEST(changeObserver) ;
        CPPUNIT_TEST(setOrientation) ;
        CPPUNIT_TEST(testMission) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      };

    }
  }
}
