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

#include <base/ensemble_composition.h>
#include <base/ensemble_association.h>
#include <base/iterateur_ensemble_association.h>


#include <base/test/test_iterateur_ensemble_association.h>


// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestIterateurEnsembleAssociation) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {
      
      namespace
      {
        class A
        {};
      
        EnsembleComposition<A> conteneur ;
        EnsembleAssociation<A> ensemble ;

        IterateurEnsembleAssociation<A> fonction()
        {
          Composition<A> element(new A()) ;
          ensemble.Ajouter(element) ;
          conteneur.Ajouter(element.Liberer()) ;
          
          return ensemble ;
        }

        
      }
  
      
        
      void TestIterateurEnsembleAssociation::testParcours()
      {
        EnsembleComposition<A> conteneur ;
        EnsembleAssociation<A> ensemble ;
        
        EntierPositif nombreDePassage ;
        
        nombreDePassage = 0 ;
        
        // test du parcours vide
        for(IterateurEnsembleAssociation<A> courant(ensemble) ;
            courant.Valide() ;
            ++courant)
        {
          ++nombreDePassage ;
        }
        
        CPPUNIT_ASSERT(nombreDePassage == 0) ;
        
        // test du parcours d'une liste de 1 élément        
        Composition<A> element(new A()) ;
        ensemble.Ajouter(element) ;
        conteneur.Ajouter(element.Liberer()) ;

        nombreDePassage = 0 ;

        for(IterateurEnsembleAssociation<A> courant(ensemble) ;
            courant.Valide() ;
            ++courant)
        {
          ++nombreDePassage ;
        }

        CPPUNIT_ASSERT(nombreDePassage == 1) ;
        
        nombreDePassage = 0 ;

        for(IterateurEnsembleAssociation<A> courant(fonction()) ;
            courant.Valide() ;
            ++courant)
        {
          ++nombreDePassage ;
        }

        CPPUNIT_ASSERT(nombreDePassage == 1) ;
        
      }

      void TestIterateurEnsembleAssociation::testCopie()
      {
        EnsembleComposition<A> conteneur ;
        EnsembleAssociation<A> ensemble ;
        EntierPositif nombreDePassage ;
        nombreDePassage = 0 ;
        
        // on ajoute un élément
        Composition<A> element(new A()) ;
        ensemble.Ajouter(element) ;
        conteneur.Ajouter(element.Liberer()) ;

        IterateurEnsembleAssociation<A> iterateur(ensemble) ;
        
        // test de la copie d'un itérateur
        for(IterateurEnsembleAssociation<A> courant(iterateur) ;
            courant.Valide() ;
            ++courant)
        {
          ++nombreDePassage ;
        }

        CPPUNIT_ASSERT(nombreDePassage == 1) ;
         
        
      }
    
    
    
    
      void TestIterateurEnsembleAssociation::setUp()
      {}
    
      void TestIterateurEnsembleAssociation::tearDown()
      {}
    }
  }
}

