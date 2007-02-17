/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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
#ifndef _PU_BASE_TEST_ERREUR_H_
#define _PU_BASE_TEST_ERREUR_H_


#include <cppunit/extensions/HelperMacros.h>
#include <base/erreur.h>

namespace ProjetUnivers {
  namespace Base {
    namespace Test {


      ///  Test des erreurs.
      class TestErreur : public CppUnit::TestFixture {
      protected:

  
        // ****************************
        /// @name Tests proprement dits
        // ****************************

  
        /// Teste certaines expressions.
        void TestExpression();


        // *******************************
        /// @name Enregistrement des tests
        // *******************************


        CPPUNIT_TEST_SUITE(TestErreur) ;

        CPPUNIT_TEST(TestExpression) ;

        CPPUNIT_TEST_SUITE_END() ;

      public:

        /// Initialisation du test
        void setUp() ;

        /// Desinitialisation du test
        void tearDown() ;



      };

    }
  }
}

#endif
