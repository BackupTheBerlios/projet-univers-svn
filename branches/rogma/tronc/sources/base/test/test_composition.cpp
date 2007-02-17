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
#include <base/types.h>
#include <base/test/test_composition.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Base::Test::TestComposition) ;

namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {

      namespace {

        Booleen vivant = VRAI ;
  
        class Element {
        public:
        
          Element() {
          
            // on met un drapeau en place
            vivant = VRAI ;
          }
        
          ~Element() {
            // le destructeur modifier le drapeau
            vivant = FAUX ;
            
          }
        };
      }
      
      void TestComposition::testDestructionAutomatique() {
      
        {
          // on construit un Element
          Composition< Element > composition ; 
          composition = new Element() ;
          
          // il doit �tre vivant 
          CPPUNIT_ASSERT(vivant == VRAI) ;
          
        }
        
        // il doit �tre d�truit
        CPPUNIT_ASSERT(vivant == FAUX) ;
        
        
      }
      
      void TestComposition::setUp() {
      }
      
      void TestComposition::tearDown() {
      }
    }
  }  
}

