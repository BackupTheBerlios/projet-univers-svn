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

#include <base/test/test_fonction_valeur_valeur.h>
#include <base/composition.h>

// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestFonctionValeurValeur) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {

      namespace {
       
        /// une class locale pour le test
        class Objet
        {
        public:
          
          int contenu ;
        };
      }

      void TestFonctionValeurValeur::testAjouter() 
      {
        FonctionValeurValeur<int,int> fonction ;
        
        fonction.Ajouter(3,7) ;
        CPPUNIT_ASSERT(fonction[3] == 7) ;

        fonction.Ajouter(4,10) ;
        CPPUNIT_ASSERT(fonction[4] == 10) ;

        


      }

      void TestFonctionValeurValeur::testChanger() 
      {
        FonctionValeurValeur<int,int> fonction ;
        
        fonction.Ajouter(3,7) ;
        CPPUNIT_ASSERT(fonction[3] == 7) ;

        fonction.Ajouter(4,10) ;
        CPPUNIT_ASSERT(fonction[4] == 10) ;

        fonction.Changer(3,20) ;
        CPPUNIT_ASSERT(fonction[3] == 20) ;

      }
      
      void TestFonctionValeurValeur::testVide() 
      {
        FonctionValeurValeur<int,int> fonction ;
        CPPUNIT_ASSERT(!fonction[3]) ;        
      }

 
      void TestFonctionValeurValeur::setUp() 
      {}
    
      void TestFonctionValeurValeur::tearDown() 
      {}



    }
  }
}

