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


#include <base/test/test_association_virtuelle.h>
#include <base/chaine.h>
#include <base/association_virtuelle.h>
#include <base/composition.h>
#include <base/association.h>


// enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Base::Test::TestAssociationVirtuelle) ;


namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


      namespace TempAssociationVirtuelle {
      
        class A
        {
        public:
          
          virtual ~A()
          {}

          virtual Chaine Nom() const = 0 ;
        
        protected:
        
          A()
          {}
          
        };
        
        class A1 : public A
        {
        public:
        
          virtual Chaine Nom() const 
          {
            return "A1" ;
          }
          
          A1()
          : A()
          {}

        };
        
        class A2 : public A
        {
        public:

          virtual Chaine Nom() const 
          {
            return "A2" ;
          }
        
        }; 
      
        class B 
        {  
        public:
          
          DECLARATION_ASSOCIATION_VIRTUELLE(A,a)
          
        protected:
          
          B(const Association<A>& _a)
          : BASE_VREF(a)(_a)
          {}
          
        };
        
        class B1 : public B
        {
        public:
        
           B1(const Association<A>& _a)
           : B(_a)
           {}
          
           UTILISATION_ASSOCIATION_VIRTUELLE(A1,a)
        };
        
      }
      
      using namespace TempAssociationVirtuelle ;


      ///////////////
      // Teste l'ajout d'un élément
      void TestAssociationVirtuelle::TesteRedefinition() 
      {
      
        Composition<A> a1(new A1()) ;  
        Composition<B> b(new B1(a1)) ;
        CPPUNIT_ASSERT(b->a()->Nom() == Chaine("A1")) ;
      }

      
      ///////////////
      // Teste l'ensemble vide
      void TestAssociationVirtuelle::TesteModificateursAcces() 
      {

      }

 
      ///////////////
      // Initialisation du test
      void TestAssociationVirtuelle::setUp() 
      {
      
      }
    
      ///////////////
      // Desinitialisation du test
      void TestAssociationVirtuelle::tearDown() 
      {

      }



    }
  }
}

