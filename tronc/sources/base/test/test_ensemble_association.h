/***************************************************************************
 *   Copyright (C) 2004 by Projet Univers                                  *
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

#ifndef TEST_ENSEMBLE_H
#define TEST_ENSEMBLE_H


#include <cppunit/extensions/HelperMacros.h>

#include "ensemble_association.h"
#include "ensemble_composition.h"
#include "types.h"

namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {
        
      /*
      CLASS
        TestEnsembleAssociation
      
        Classe permettant de tester la classe des ensemble en association.
      */
      class TestEnsembleAssociation : public CppUnit::TestFixture {
      protected:
      
        
        // ****************************
        // GROUP: Tests proprement dits
        // ****************************
      
        
        ///////////////
        // Teste l'ajout d'un �l�ment
        void testAjoute();
      
        ///////////////
        // Teste la suppression d'un �l�ment
        void testEnleve();
        
        ///////////////
        // Teste le test d'appartenance d'un �l�ment
        void testAppartient();
        
        /////////////////
        // Teste la construction d'un ensemble.
        
        
        /////////////////
        // Teste la conversion d'un ensemble en composition.
        
      
      
      
        // *******************************
        // GROUP: Enregistrement des tests
        // *******************************
      
      
        CPPUNIT_TEST_SUITE(TestEnsembleAssociation) ;
      
        CPPUNIT_TEST(testAjoute) ;
        CPPUNIT_TEST(testEnleve) ;
        CPPUNIT_TEST(testAppartient) ;
      
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
      
        ////////////////
        // Un ensemble en composition
        EnsembleComposition< Entier > ensemble ; 
      
      
        ////////////////
        // Un ensemble en association
        EnsembleAssociation< Entier > ensembleTeste ; 
      
      
      };
    }
  }
}


#endif
