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

#include <base/test/test_liste.h>

#include <base/implantation/liste_association.h>
#include <base/implantation/iterateur_liste_association.h>


CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Base::Implantation::Test::TestListe) ;


namespace ProjetUnivers {
  
  namespace Base {
    
    namespace Implantation {
      
      namespace Test {
  
  
  
        // une classe comme ça
        class ElementTestListe {
        public:
  
          Entier valeur ;
  
  
          ElementTestListe(const Entier _e)
          : valeur(_e)
          {}
  
          ~ElementTestListe()
          {
            // le destructeur marque sa destruction.
            ++nombreDObjectsDetruits ;
          }
          // un drapeau pour savoir combien d'élément de TempComposition 
          // ont été détruit
          static Entier nombreDObjectsDetruits ;
  
        };
  
        Entier ElementTestListe::nombreDObjectsDetruits = 0 ;
  
  
        void TestListe::TestDestruction()
        {
  
          // on ouvre un nouveau bloc, ses variables temporaires sont détruites 
          // à la sortie
          {
            // 
            ListeComposition< ElementTestListe > liste2 ;
  
            Composition< ElementTestListe > element1(new ElementTestListe(1)) ;
            Composition< ElementTestListe > element2(new ElementTestListe(2)) ;
  
            liste2.addEnTete(element1.Liberer()) ;
            liste2.addEnTete(element2.Liberer()) ;
  
          } 
          // ici liste2 est détruite et ses doivent l'être aussi 
          CPPUNIT_ASSERT(ElementTestListe::nombreDObjectsDetruits == 2 ) ;
        }
  
  
  
  
  
        void TestListe::Testadd()
        {
  	      // 
          ListeAssociation< ElementTestListe > temp ;
  
          Composition< ElementTestListe > element1(new ElementTestListe(1)) ;
          Composition< ElementTestListe > element2(new ElementTestListe(2)) ;
  
          temp.addEnTete(element1) ;
          temp.addEnTete(element2) ;
  
          CPPUNIT_ASSERT(temp.NombreDElements() == 2) ;
  
          CPPUNIT_ASSERT(temp.Contient(element1)) ;
          CPPUNIT_ASSERT(temp.Contient(element2)) ;
  
          Entier resultat(0) ;
  
          for(
            IterateurListeAssociation< ElementTestListe > i(temp) ;
            i.Valide() ;
            ++i)
          {
            resultat += i->valeur ;
          }
          
          CPPUNIT_ASSERT(resultat == 3) ;

          // liste de valeurs
   
          listeChaine.addEnTete("toto") ;
          listeChaine.addEnTete("titi") ;
  
          CPPUNIT_ASSERT(listeChaine.Contient("toto")) ;
          CPPUNIT_ASSERT(listeChaine.Contient("titi")) ;
          
          // test de l'itérateur
          
          IterateurListeValeur<Chaine> chaine(listeChaine) ;

          CPPUNIT_ASSERT(chaine == Chaine("titi")) ;
          ++chaine ;

          CPPUNIT_ASSERT(chaine == "toto") ;
          
        }
  
  
  
        ListeAssociation< ElementTestListe > TestListe::f() 
        {
   
          return liste ;
        }
  
  
  
  
  
        void TestListe::TestParcoursListeTemporaire()
        {
  
  
          Entier resultat(0) ;
  
  
  	      // itération sur une liste temporaire
          for(
          IterateurListeAssociation< ElementTestListe > i(f()) ; 
          i.Valide() ;
          ++i)
    
            resultat += i->valeur ;
  
    
  
          CPPUNIT_ASSERT(resultat == 3) ;
  
          resultat = 0 ;
  
          for(
          IterateurListeComposition< ElementTestListe > j(liste) ; 
          j.Valide() ;
          ++j)
    
   
           resultat += j->valeur ;
  
  
          CPPUNIT_ASSERT(resultat == 3) ;
  
  
        }
  
  
        void TestListe::setUp()
        {
  	      // 
          ElementTestListe::nombreDObjectsDetruits = 0 ;
  
          liste.addEnTete(new ElementTestListe(1)) ;
          liste.addEnTete(new ElementTestListe(2)) ;
  
        }
  
        void TestListe::tearDown()
        {
  	      // 
          liste.Vider() ;
          listeChaine.Vider() ;
        }

      }

    }
  }
}
