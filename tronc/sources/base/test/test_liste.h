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

#ifndef _OB_LIST_TEST_H_
#define _OB_LIST_TEST_H_


// Includes
#include <cppunit/extensions/HelperMacros.h>

#include "liste_composition.h"

#include "liste_association.h"


namespace ProjetUnivers::Base::Test {


/*
CLASS
  TestListe
*/
class TestListe : public CppUnit::TestFixture {
protected:

  
  // ****************************
  // GROUP: Tests proprement dits
  // ****************************

  ////////////////
  // Teste l'ajout dans la liste.
  void testList() ;


  ///////////////
  // Teste que même une liste temporaire peut être 
  // parcourue.
  void testListCopy() ;

  //////////////
  // Teste la destruction de liste en composition.
  void testDestroy() ;


  // ********************
  // GROUP: Mise en place
  // ********************


  CPPUNIT_TEST_SUITE(TestListe) ;

  CPPUNIT_TEST(testListCopy) ;
  CPPUNIT_TEST(testList) ;
  CPPUNIT_TEST(testDestroy) ;

  CPPUNIT_TEST_SUITE_END() ;

public:

  ///////////////
  // Initialisation du test
  void setUp() ;

  ///////////////
  // Desinitialisation du test
  void tearDown() ;


private:

  // une classe comme ça
  class Element {
  public:
  
    Entier valeur ;
  
  
    Element(const Entier _e)
    : valeur(_e)
    {}
  };

	ListeAssociation< Element > f();

  // une liste 
  EnsembleComposition< Element > liste ;

};

}
#endif // _OB_LIST_TEST_H_


