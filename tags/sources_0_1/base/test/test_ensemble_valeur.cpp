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


#include "test_ensemble_valeur.h"


// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestEnsembleValeur) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


      ///////////////
      // Teste l'ajout d'un �l�ment
      void TestEnsembleValeur::TestAjouter() 
      {
      
        this->ensemble.Ajouter(1) ;

        // puis on v�rifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensemble.Contient(1) == VRAI) ;

        this->ensemble.Ajouter(2) ;

        // puis on v�rifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensemble.Contient(2) == VRAI) ;

      
        // on v�rifie que la taille est bien de 2
        CPPUNIT_ASSERT(this->ensemble.NombreDElements() == 2) ;


        // on r�ajoute le m�me �l�ment...
        this->ensemble.Ajouter(1) ;
        
        // on v�rifie que la taille est bien de 2
        CPPUNIT_ASSERT(this->ensemble.NombreDElements() == 2) ;


      }

      
      ///////////////
      // Teste l'ensemble vide
      void TestEnsembleValeur::TestVide() 
      {

         // on v�rifie que l'ensemble vide est vide
        CPPUNIT_ASSERT(this->ensemble.Contient(1) == FAUX) ;


      }

      ///////////////
      // Teste la suppression d'un �l�ment
      void TestEnsembleValeur::TestEnlever() 
      {

           

        this->ensemble.Ajouter(1) ;
        this->ensemble.Ajouter(2) ;

        // on enl�ve le premier �l�ment
        this->ensemble.Enlever(1) ;
        
        // on v�rifie qu'il n'est pas dedans
        CPPUNIT_ASSERT(this->ensemble.Contient(1) == FAUX) ;
        
      }
      
 
      ///////////////
      // Initialisation du test
      void TestEnsembleValeur::setUp() 
      {
      
      }
    
      ///////////////
      // Desinitialisation du test
      void TestEnsembleValeur::tearDown() 
      {
        this->ensemble.Vider() ;
      }



    }
  }
}

