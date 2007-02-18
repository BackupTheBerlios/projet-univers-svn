/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef PU_DISPLAY_TEST_TEST_POINT_DE_VUE_H_
#define PU_DISPLAY_TEST_TEST_POINT_DE_VUE_H_


#include <cppunit/extensions/HelperMacros.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Test {


            
      /// Test de la mise à jour MV
      /*!

      */
      class TestViewPoint : public CppUnit::TestFixture {
      protected:
      
        
      // ****************************
      /// @name Tests proprement dits
      // ****************************
      // @{
        
        /// Teste une construction.
        void testConstruction() ;
           
      // @}
      // *******************************
      /// @name Registerment des tests
      // *******************************
      // @{      
    
        CPPUNIT_TEST_SUITE(TestViewPoint) ;
      
        CPPUNIT_TEST(testConstruction) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      public:
  
      // @}
      // *******************************
      /// @name Méthodes obligatoires
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


#endif /*PU_DISPLAY_TEST_TEST_POINT_DE_VUE_H_*/
