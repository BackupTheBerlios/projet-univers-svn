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


#include <base/association.h>
#include <base/composition.h>
#include <base/types.h>
#include <base/test/test_association.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Base::Test::TestAssociation) ;

namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


      namespace {
        class Parent 
        {};
  
        class Enfant : public Parent
        {};
        
        void FonctionEnfant(const Association<Enfant>& _enfant)
        {}
          
        void FonctionParent(const Association<Parent>& _parent)
        {}
        
      }
            
      void TestAssociation::testConversionImplicite() {
      
        Composition<Enfant> enfant(new Enfant()) ;
        Association<Enfant> enfantAssociation(enfant) ;
        Association<Parent> parent(enfantAssociation) ;
        
        Association<Parent> parent2(enfant) ;
        Association<Parent> parent3 = enfant ;
        Association<Parent> parent4 = enfantAssociation ;        
        
        
        CPPUNIT_ASSERT(parent == enfantAssociation) ;
        CPPUNIT_ASSERT(parent == parent3) ;
       
        FonctionEnfant(enfant) ;
        FonctionParent(enfant) ;
        
        
      }
      
      void TestAssociation::setUp() {
      }
      
      void TestAssociation::tearDown() {
      }
    }
  }  
}

