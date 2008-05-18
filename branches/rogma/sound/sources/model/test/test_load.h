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
#ifndef PU_MODEL_TEST_LOAD_H_
#define PU_MODEL_TEST_LOAD_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Test {


            
      /// Test of Model::load.
      class TestLoad : public CppUnit::TestFixture {
      protected:
      
        
      /*! 
        @name Tests 
      */
      // @{
        
        void testLoadComponent() ;
        void testLoadComputer() ;
        void testLoadDestroyable() ;
        void testLoadDetector() ;
        void testLoadDragger() ;
        void testLoadEngine() ;
        void testLoadForceGenerator() ;
        void testLoadGuidanceControler() ;
        void testLoadGuidanceSystem() ;
        void testLoadHearing() ;
        void testLoadLaser() ;
        void testLoadMassive() ;
        void testLoadMenu() ;
        void testLoadMobile() ;
        void testLoadObserver() ;
        void testLoadOriented() ;
        void testLoadPositionned() ;
        void testLoadSolid() ;
        void testLoadStabilizer() ;
        void testLoadStick() ;
        void testLoadTorqueGenerator() ;
        void testLoadUniverse() ;

      // @}
      /*! 
        @name Tests registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestLoad) ;
      
        CPPUNIT_TEST(testLoadComponent) ;
        CPPUNIT_TEST(testLoadComputer) ;
        CPPUNIT_TEST(testLoadDestroyable) ;
        CPPUNIT_TEST(testLoadDetector) ;
        CPPUNIT_TEST(testLoadDragger) ;
        CPPUNIT_TEST(testLoadEngine) ;
        CPPUNIT_TEST(testLoadForceGenerator) ;
        CPPUNIT_TEST(testLoadLaser) ;
        CPPUNIT_TEST(testLoadMassive) ;
        CPPUNIT_TEST(testLoadMenu) ;
        CPPUNIT_TEST(testLoadMobile) ;
        CPPUNIT_TEST(testLoadObserver) ;
        CPPUNIT_TEST(testLoadOriented) ;
        CPPUNIT_TEST(testLoadPositionned) ;
        CPPUNIT_TEST(testLoadSolid) ;
        CPPUNIT_TEST(testLoadStabilizer) ;
        CPPUNIT_TEST(testLoadStick) ;
        CPPUNIT_TEST(testLoadTorqueGenerator) ;
        CPPUNIT_TEST(testLoadUniverse) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      public:
  
      // @}
      // *******************************
      /// @name Mandatory methods
      // *******************************
      // @{

      
        /// Initialisation du test
        void setUp() ;
      
        /// Desinitialisation du test
        void tearDown() ;
      
      // @}      
                
       
      
      };

    }
  }
}


#endif /*PU_MODEL_TEST_LOAD_H_*/
