/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/



#ifndef _PU_BASE_TEST_AGREGATION_H_
#define _PU_BASE_TEST_AGREGATION_H_


#include <cppunit/extensions/HelperMacros.h>


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


      
      /// Test de Base::Agregation
      class TestAgregation : public CppUnit::TestFixture {
      protected:
      
        
        // ****************************
        /// @name Tests proprement dits
        // ****************************
        // @{


        /// Teste la conversion implicite dans différentes situations.
        void testConversionImplicite();

        /// Teste la destruction lorsque le dernier pointeur est relaché.
        void testDestructionAutomatique();


        // @}
        // *******************************
        /// @name Enregistrement des tests
        // *******************************
        // @{      

      
        CPPUNIT_TEST_SUITE(TestAgregation) ;
        CPPUNIT_TEST(testConversionImplicite) ;
        CPPUNIT_TEST(testDestructionAutomatique) ;
        CPPUNIT_TEST_SUITE_END() ;
      
        // @}      
                
     public:

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


#endif
