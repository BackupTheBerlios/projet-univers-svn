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


#include <string>

#include <base/test/test_chaine.h>
#include <base/chaine.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Base::Test::TestChaine) ;

namespace ProjetUnivers {

  namespace Base {
  
    namespace Test {
     
     
      void TestChaine::TesteAffectation()
      {
      
        Chaine test("ceci est un test") ;
        Chaine test2 = test ;
        
        CPPUNIT_ASSERT(test == test2) ;
        CPPUNIT_ASSERT(test == "ceci est un test") ;
        
        test = "ceci est un autre test" ;
        
        CPPUNIT_ASSERT(test != test2) ;
        CPPUNIT_ASSERT(test == "ceci est un autre test") ;

      }
      
      void TestChaine::TesteCreation() 
      {
        const char* temp = "bonjour" ;
        
        {
          Chaine chaine(temp) ;
        }
        
        // chaine a été détruite et maintenant, temp doit toujours exister
        // et valoir la même chose
        CPPUNIT_ASSERT(std::string("bonjour") == std::string(temp)) ;
        

        // idem mais avec une modification au lieu de destruction
        Chaine chaine(temp) ;
        chaine += "toto" ;
        
        CPPUNIT_ASSERT(std::string("bonjour") == std::string(temp)) ;        
        
        
      }
      
      void TestChaine::setUp()
      {
      }
      
      void TestChaine::tearDown()
      {
      }
    }
  }
}
