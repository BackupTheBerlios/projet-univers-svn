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


#include <base/test/test_ensemble_association.h>


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

      namespace {

        class A
        {};
        
        class B : virtual public A
        {};
        
        class C : virtual public A
        {} ;
        
        class D : public B, public C
        {};
    

      }


      void TestEnsembleAssociation::testadd() 
      {
      
        // on ajoute un élément ...
        element = new TempAssociation(1) ;
        this->ensembleTeste.add(element) ;
        // puis on vérifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(element) == VRAI) ;

        // on le transfert dans le conteneur
        elements.add(element.Liberer()) ;

        // on ajoute un autre élément ...
        element = new TempAssociation(2) ;
        this->ensembleTeste.add(element) ;

        // puis on vérifie qu'il est dedans
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(element) == VRAI) ;
        // on le transfert dans le conteneur
        elements.add(element.Liberer()) ;

      
        // on vérifie que la taille est bien de 2
        CPPUNIT_ASSERT(this->ensembleTeste.NombreDElements() == 2) ;


      }


      void TestEnsembleAssociation::testadd2() 
      {

        EnsembleAssociation<A> ensemble ;
        
        Composition<D> d1(new D()) ;
        Composition<D> d2(new D()) ;
        Composition<D> d3(new D()) ;
        
        ensemble.add(d1) ;
        ensemble.add(d2) ;
        ensemble.add(d3) ;

        CPPUNIT_ASSERT(ensemble.Contient(d1)) ;
        CPPUNIT_ASSERT(ensemble.Contient(d2)) ;
        CPPUNIT_ASSERT(ensemble.Contient(d3)) ;
        
        EntierPositif nombre(0) ;
        
        for(IterateurEnsembleAssociation<A> a(ensemble) ;
            a.Valide() ;
            ++a)
        {
          ++nombre ;
        }

        CPPUNIT_ASSERT(nombre == 3) ;

      }
      
      void TestEnsembleAssociation::testVide() 
      {

        element = new TempAssociation(1) ;

         // on vérifie que l'ensemble vide est vide
        CPPUNIT_ASSERT(this->ensembleTeste.Contient(element) == FAUX) ;


      }

      ///////////////
      // Teste la suppression d'un élément
      void TestEnsembleAssociation::testremove() 
      {

           
        // on ajoute un élément ...
        element = new TempAssociation(1) ;
        this->ensembleTeste.add(element) ;
        referenceElement = element ;
        // on le transfert dans le conteneur
        elements.add(element.Liberer()) ;

        // on ajoute un autre élément ...
        element = new TempAssociation(2) ;
        this->ensembleTeste.add(element) ;
        
        Association<TempAssociation> deuxieme_element(element) ;
        
        // on le transfert dans le conteneur
        elements.add(element.Liberer()) ;

        // on enlève le premier élément
        this->ensembleTeste.remove(referenceElement) ;
        
        // on vérifie qu'il n'est pas dedans
        CPPUNIT_ASSERT(! this->ensembleTeste.Contient(referenceElement)) ;
        
        // on enlève le deuxième élément
        this->ensembleTeste.remove(deuxieme_element) ;
        
        // on vérifie qu'il n'est pas dedans
        CPPUNIT_ASSERT(! this->ensembleTeste.Contient(deuxieme_element)) ;
        
        CPPUNIT_ASSERT(this->ensembleTeste.NombreDElements() == 0) ;
        
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

