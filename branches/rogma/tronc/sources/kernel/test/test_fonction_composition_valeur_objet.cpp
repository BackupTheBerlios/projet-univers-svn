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

#include <base/test/test_fonction_composition_valeur_objet.h>
#include <base/composition.h>

// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestFonctionCompositionValeurObject) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


      namespace
      {
        class ClasseObject
        {
        public:
        
          ClasseObject()
          {
            ++ nombre_instances ;
          }
        
          ~ClasseObject()
          {
            --nombre_instances ;
          }
          
          static int nombre_instances ;
        };
        
        int ClasseObject::nombre_instances = 0 ;
      }



      void TestFonctionCompositionValeurObject::testadd() 
      {
        Base::Composition<ClasseObject> objet(new ClasseObject()) ;
        Base::Association<ClasseObject> associationObject(objet) ;
        
        FonctionCompositionValeurObject<int,ClasseObject> fonction ;

        
        fonction.add(3,objet.Liberer()) ;
        CPPUNIT_ASSERT(fonction[3] == associationObject) ;        

      }

      
      void TestFonctionCompositionValeurObject::testVide() 
      {
        FonctionCompositionValeurObject<int,ClasseObject> fonction ;
        CPPUNIT_ASSERT(!fonction[3]) ;        
      }


      void TestFonctionCompositionValeurObject::testVider() 
      {
        Base::Composition<ClasseObject> objet(new ClasseObject()) ;
        Base::Association<ClasseObject> associationObject(objet) ;
        
        FonctionCompositionValeurObject<int,ClasseObject> fonction ;

        CPPUNIT_ASSERT(ClasseObject::nombre_instances == 1) ;
        
        fonction.add(3,objet.Liberer()) ;
        
        fonction.Vider() ;
        
        CPPUNIT_ASSERT(!fonction[3]) ;
        CPPUNIT_ASSERT(ClasseObject::nombre_instances == 0) ;

      }

 
      void TestFonctionCompositionValeurObject::setUp() 
      {}
    
      void TestFonctionCompositionValeurObject::tearDown() 
      {}



    }
  }
}

