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


#ifndef _PU_BASE_TEST_ENSEMBLE_COMPOSITION_H_
#define _PU_BASE_TEST_ENSEMBLE_COMPOSITION_H_


#include <cppunit/extensions/HelperMacros.h>

#include <base/ensemble_composition.h>
#include <base/types.h>
#include <base/composition.h>


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {
      
      /// une classe locale pour le test  
      class TempComposition ;
        
      
      ///  Classe permettant de tester la classe des ensemble en composition.
      class TestEnsembleComposition : public CppUnit::TestFixture {
      protected:
      
        
        // ****************************
        // GROUP: Tests proprement dits
        // ****************************
      
        
        /// Teste l'ajout d'un élément
        void testAjouter();
      
        /// Teste la suppression d'un élément
        void testEnlever();
        
        /// Teste l'ensemble vide
        void testVide();
        
        
      
      
      
        // *******************************
        // GROUP: Enregistrement des tests
        // *******************************
      
      
        CPPUNIT_TEST_SUITE(TestEnsembleComposition) ;
      
        CPPUNIT_TEST(testAjouter) ;
        CPPUNIT_TEST(testEnlever) ;
        CPPUNIT_TEST(testVide) ;
      
        CPPUNIT_TEST_SUITE_END() ;
      
      public:
      
        // *******************************************
        // GROUP: Initialisation et femeture des tests
        // *******************************************
        
      
        ///////////////
        // Initialisation du test
        void setUp() ;
      
        ///////////////
        // Desinitialisation du test
        void tearDown() ;
      
      
      private:
      
      
        /// Un ensemble en association
        EnsembleComposition< TempComposition > ensembleTeste ; 
  
 
        /// conteneur temporaire des éléments
        Composition< TempComposition > element ;

        /// réérence temporaire
        Association< TempComposition > referenceElement ;
        
      };
    }
  }
}


#endif
