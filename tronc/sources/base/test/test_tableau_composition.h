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

#ifndef COMPOSITION_ARRAY_TEST_H_
#define COMPOSITION_ARRAY_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include "tableau_composition.h"



/*
CLASS
  TestTableauComposition

*/
class TestTableauComposition : public CppUnit::TestFixture {
protected:

  
  // ****************************
  // GROUP: Tests proprement dits
  // ****************************

  
  ///////////////
  // Teste l'ajout d'un élément
  void testAdd();


  // ********************
  // GROUP: Mise en place
  // ********************


  CPPUNIT_TEST_SUITE(TestTableauComposition) ;

  CPPUNIT_TEST(testAdd) ;

  CPPUNIT_TEST_SUITE_END() ;

public:

  ///////////////
  // Initialisation du test
  void setUp() ;

  ///////////////
  // Desinitialisation du test
  void tearDown() ;


private:

  // *******************************
  // GROUP: Des éléments nécessaires
  // *******************************

  ////////////////
  // empty array
  TableauComposition <int> array ; 


};


#endif // _OB_COMPOSITION_ARRAY_TEST_H_


