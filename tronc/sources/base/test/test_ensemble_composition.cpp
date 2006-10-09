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

#include <base/ensemble_association.h>
#include <base/test/test_ensemble_composition.h>
#include <base/iterateur_ensemble_composition.h>

// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestEnsembleComposition) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


        
      class TempComposition {
      public:
      
        TempComposition(const Entier& _v = 0)
        : valeur(_v)
        {}

        ~TempComposition()
        {
          ++nombreDObjetsDetruits ;
        }

        Entier valeur ;


        // un drapeau pour savoir combien d'�l�ment de TempComposition ont �t� d�truit
        static Entier nombreDObjetsDetruits ;

      };
    
      Entier TempComposition::nombreDObjetsDetruits = 0 ;



      ///////////////
      // Teste l'ajout d'un �l�ment
      void TestEnsembleComposition::testAjouter() 
      {
      
        // on ajoute un �l�ment ...
        element = new TempComposition(1) ;
        referenceElement = element ;
        this->ensembleTeste.Ajouter(element.Liberer()) ;

        // puis on v�rifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(referenceElement) == VRAI) ;

        CPPUNIT_ASSERT(TempComposition::nombreDObjetsDetruits == 0) ;

        // on ajoute un autre �l�ment ...

        element = new TempComposition(2) ;
        referenceElement = element ;
        this->ensembleTeste.Ajouter(element.Liberer()) ;

        // puis on v�rifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(referenceElement) == VRAI) ;

        CPPUNIT_ASSERT(TempComposition::nombreDObjetsDetruits == 0) ;
      
        // on v�rifie que la taille est bien de 2
        CPPUNIT_ASSERT(this->ensembleTeste.NombreDElements() == 2) ;

        // on v�rifie que le parcours est possible
        
        EntierPositif taille = 0 ;
        
        for(IterateurEnsembleComposition< TempComposition > i(ensembleTeste) ;
            i.Valide() ;
            ++i)
        {
        
           ++taille ;
        } 

        CPPUNIT_ASSERT(taille == 2) ;

      }

      
      ///////////////
      // Teste l'ensemble vide
      void TestEnsembleComposition::testVide() 
      {

        element = new TempComposition(1) ;

         // on v�rifie que l'ensemble vide est vide
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(element) == FAUX) ;


      }

      ///////////////
      // Teste la suppression d'un �l�ment
      void TestEnsembleComposition::testEnlever() 
      {

           
        // on ajoute un �l�ment ...
        element = new TempComposition(1) ;
        referenceElement = element ;
        this->ensembleTeste.Ajouter(element.Liberer()) ;

        // on ajoute un autre �l�ment ...

        element = new TempComposition(2) ;
        this->ensembleTeste.Ajouter(element.Liberer()) ;

  
        // on enl�ve le premier �l�ment
        this->ensembleTeste.Enlever(referenceElement) ;

        // on v�rifie que l'objet a �t� d�truit
        CPPUNIT_ASSERT(TempComposition::nombreDObjetsDetruits == 1) ;        
        // on v�rifie qu'il n'est pas dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(referenceElement) == FAUX) ;

        
      }
      
      void TestEnsembleComposition::testConversion()
      {
        this->ensembleTeste.Ajouter(new TempComposition(1)) ;
        this->ensembleTeste.Ajouter(new TempComposition(2)) ;
        
        EnsembleAssociation<TempComposition> 
          ensemble(this->ensembleTeste) ;
        
      }
 
      ///////////////
      // Initialisation du test
      void TestEnsembleComposition::setUp() 
      {
        TempComposition::nombreDObjetsDetruits = 0 ;
      
      }
    
      ///////////////
      // Desinitialisation du test
      void TestEnsembleComposition::tearDown() 
      {
        this->ensembleTeste.Vider() ;
      }


    }
  }
}

