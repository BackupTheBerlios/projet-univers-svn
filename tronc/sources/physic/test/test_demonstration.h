/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_PHYSIC_TEST_DEMONSTRATION_H_
#define PU_PHYSIC_TEST_DEMONSTRATION_H_


#include <cppunit/extensions/HelperMacros.h>


namespace ProjetUnivers {
  namespace Physic {
    namespace Test {


            
      /// Physic tests on demonstration model.
      /*!

      */
      class TestDemonstration : public CppUnit::TestFixture {
      protected:
      
        
      /*!
        @name Test methods
      */
      // @{
        
        /// Test a build plus init.
        void testBuild() ;

        /// Simulation with nothing moving.
        void testSimulateNoMove() ;

        /// Simulation with a moving object with a force.
        void testSimulateMoving() ;

        /// Test the rotation of a solid with a torque.
        void testRotationTorque() ;
        
        /// Simulation with a moving object with initial speed.
        void testSimulateMovingInitialSpeed() ;

        /// Simulation with a moving object with initial angular speed.
        void testSimulateMovingInitialRotation() ;
           
        /// Simulation with a half turn rotation.
        void testSimulateRotatingHalfTurn() ;

        /// Test a stabilizer.
        /*!
          Add a stabilizer on an object
          Make it totate in the direction of the stabilizer
          check that after a certain amount of time, the angular speed is null
        */
        void testStabilizer() ;
        
        /// Check that a stabilizer only affects its direction.
        void testNegativeStabilizer() ;

        /// Test a stabilizer with opposite rotation.
        /*!
          Add a stabilizer on an object
          Make it totate in the direction of the stabilizer
          check that after a certain amount of time, the angular speed is null
        */
        void testStabilizer2() ;
        
        /// test engine propulsion.
        void testEngine() ;

      // @}
      /*!
        @name Test registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestDemonstration) ;
      
        CPPUNIT_TEST(testBuild) ;
        CPPUNIT_TEST(testSimulateNoMove) ;
        CPPUNIT_TEST(testSimulateMoving) ;
        CPPUNIT_TEST(testRotationTorque) ;
        CPPUNIT_TEST(testSimulateMovingInitialSpeed) ;
        CPPUNIT_TEST(testSimulateMovingInitialRotation) ;
        CPPUNIT_TEST(testSimulateRotatingHalfTurn) ;
        CPPUNIT_TEST(testStabilizer) ;
        CPPUNIT_TEST(testNegativeStabilizer) ;
        CPPUNIT_TEST(testStabilizer2) ;
        CPPUNIT_TEST(testEngine) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      public:
  
      // @}
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
