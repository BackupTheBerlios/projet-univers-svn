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

#include <base/composition.h>
#include <base/test/test_fonction_association_objet_objet.h>
#include <base/fonction_association_objet_objet.h>

// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestFonctionAssociationObjectObject) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


      namespace
      {
        class ClasseObject
        {};
      }



      void TestFonctionAssociationObjectObject::testadd() 
      {
        Base::Composition<ClasseObject> objet(new ClasseObject()) ;
        FonctionAssociationObjectObject<ClasseObject,ClasseObject> fonction ;

        fonction.add(objet,objet) ;
        CPPUNIT_ASSERT(fonction.Acces(objet) == objet) ;        
        
        

      }

      
      void TestFonctionAssociationObjectObject::testVide() 
      {
        FonctionAssociationObjectObject<ClasseObject,ClasseObject> fonction ;
        Base::Composition<ClasseObject> objet(new ClasseObject()) ;
        CPPUNIT_ASSERT(!fonction.Acces(objet)) ;        

      }

 
      void TestFonctionAssociationObjectObject::setUp() 
      {}
    
      void TestFonctionAssociationObjectObject::tearDown() 
      {}



    }
  }
}

