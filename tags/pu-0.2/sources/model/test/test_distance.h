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
#ifndef PU_MODEL_TEST_DISTANCE_H_
#define PU_MODEL_TEST_DISTANCE_H_


#include <cppunit/extensions/HelperMacros.h>


namespace ProjetUnivers {

  namespace Model {

  
    namespace Test {

            
      /// Test de Model::Distance
      class TestDistance : public CppUnit::TestFixture {
      protected:
      
        
      // ****************************
      /// @name Tests proprement dits
      // ****************************
      // @{
        
        /// Teste l'ordre sur les unit�s.
        void testComparisonUnit() ;
           
      // @}
      // *******************************
      /// @name Registerment des tests
      // *******************************
      // @{      
      
        CPPUNIT_TEST_SUITE(TestDistance) ;
      
        CPPUNIT_TEST(testComparisonUnit) ;
      
        CPPUNIT_TEST_SUITE_END() ;
      
      // @}      
                
     public:

      // *******************************
      /// @name M�thodes obligatoires
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


#endif
