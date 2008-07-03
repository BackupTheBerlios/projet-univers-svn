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
#ifndef PU_MODEL_TEST_MESH_H_
#define PU_MODEL_TEST_MESH_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Test {


            
      /// Test of Mesh.
      /*!

      */
      class TestMesh : public CppUnit::TestFixture {
      protected:
      
      /*! 
        @name Tests 
      */
      // @{
        
        /// Tests mesh triangle loading.
        void testGetInformation() ;

        /// Tests loading a unexisting mesh.
        void testUnexistingMesh() ;
           
      // @}
      /*! 
        @name Tests registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestMesh) ;
      
        CPPUNIT_TEST(testGetInformation) ;
        CPPUNIT_TEST(testUnexistingMesh) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      public:
  
      // @}
      /*! 
        @name Mandatory methods
      */
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


#endif
