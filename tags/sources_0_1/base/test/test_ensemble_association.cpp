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


#include "test_ensemble_association.h"


// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestEnsembleAssociation) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {

      class TempAssociation {
      public:
      
        TempAssociation(const Entier& _v = 0)
        : valeur(_v)
        {}

        Entier valeur ;
      };




      ///////////////
      // Teste l'ajout d'un élément
      void TestEnsembleAssociation::testAjouter() 
      {
      
        // on ajoute un élément ...
        element = new TempAssociation(1) ;
        this->ensembleTeste.Ajouter(element) ;

        // puis on vérifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(element) == VRAI) ;

        // on le transfert dans le conteneur
        elements.Ajouter(element.Liberer()) ;

        // on ajoute un autre élément ...

        element = new TempAssociation(2) ;

        this->ensembleTeste.Ajouter(element) ;

        // puis on vérifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(element) == VRAI) ;

        // on le transfert dans le conteneur
        elements.Ajouter(element.Liberer()) ;

      
        // on vérifie que la taille est bien de 2
        CPPUNIT_ASSERT(this->ensembleTeste.NombreDElements() == 2) ;


      }

      
      ///////////////
      // Teste l'ensemble vide
      void TestEnsembleAssociation::testVide() 
      {

        element = new TempAssociation(1) ;

         // on vérifie que l'ensemble vide est vide
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(element) == FAUX) ;


      }

      ///////////////
      // Teste la suppression d'un élément
      void TestEnsembleAssociation::testEnlever() 
      {

           
        // on ajoute un élément ...
        element = new TempAssociation(1) ;

        this->ensembleTeste.Ajouter(element) ;

        referenceElement = element ;

        // on le transfert dans le conteneur
        elements.Ajouter(element.Liberer()) ;

        // on ajoute un autre élément ...

        element = new TempAssociation(2) ;

        this->ensembleTeste.Ajouter(element) ;

        // on le transfert dans le conteneur
        elements.Ajouter(element.Liberer()) ;
  
        // on enlève le premier élément
        this->ensembleTeste.Enlever(referenceElement) ;
        
        // on vérifie qu'il n'est pas dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(referenceElement) == FAUX) ;
        
      }
      
 
      ///////////////
      // Initialisation du test
      void TestEnsembleAssociation::setUp() 
      {
      
      }
    
      ///////////////
      // Desinitialisation du test
      void TestEnsembleAssociation::tearDown() 
      {
        this->ensembleTeste.Vider() ;
      }



    }
  }
}

