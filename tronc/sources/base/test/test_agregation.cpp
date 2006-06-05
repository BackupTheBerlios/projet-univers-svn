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


#include <base/agregation.h>
#include <base/types.h>
#include <base/test/test_agregation.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Base::Test::TestAgregation) ;

namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {


      namespace {
        
        class Parent 
        {
        public:
          virtual ~Parent()
          {}
          
        protected:
          Parent()
          {}
        };
  
        class Enfant : public Parent
        {
        public:
          Enfant()
          : Parent()
          {}
          
          ~Enfant()
          {}
          
        };
        
        /// une classe qui m�morise le nombre de ses instances.
        class Objet
        {
        public:
        
          Objet()
          {
            ++nombreDInstance ;
          }

          ~Objet()
          {
            --nombreDInstance ;
          }
          
          
          static unsigned int nombreDInstance ;
          
        };
        
        unsigned int Objet::nombreDInstance = 0 ;
        
      }
            
      void TestAgregation::testConversionImplicite() 
      {
     
        Agregation<Enfant> enfant(new Enfant()) ;

        Agregation<Parent> parent(enfant) ;
        Agregation<Parent> parent2 = enfant ;
        
        
        CPPUNIT_ASSERT(parent == enfant) ;
        CPPUNIT_ASSERT(parent == parent2) ;
       
       
      }


      void TestAgregation::testDestructionAutomatique()
      {

        Agregation<Objet> o1(new Objet()) ;

        {
          Agregation<Objet> o2 = o1 ;
          
          
        }
        
        CPPUNIT_ASSERT(Objet::nombreDInstance == 1) ;

        /// plus personne ne point sur l'objet
        o1 = NULL ;
        
        CPPUNIT_ASSERT(Objet::nombreDInstance == 0) ;
        

      }

      
      void TestAgregation::setUp() 
      {
      }
      
      void TestAgregation::tearDown() 
      {
      }


    }
  }  
}

