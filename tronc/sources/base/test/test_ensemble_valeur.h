/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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



#ifndef TEST_ENSEMBLE_H
#define TEST_ENSEMBLE_H


#include <cppunit/extensions/HelperMacros.h>

#include "ensemble_valeur.h"



/*
CLASS
  TestEnsembleValeur

  Classe permettant de tester la classe des ensemble de valeurs.
*/
class TestEnsembleValeur : public CppUnit::TestFixture {
protected:

  
  // ****************************
  // GROUP: Tests proprement dits
  // ****************************

  
  ///////////////
  // Teste l'ajout d'un élément
  void testAjoute();

  ///////////////
  // Teste la suppression d'un élément
  void testEnleve();
  
  ///////////////
  // Teste le test d'appartenance d'un élément
  void testAppartient();
  


  // *******************************
  // GROUP: Enregistrement des tests
  // *******************************


  CPPUNIT_TEST_SUITE(TestEnsembleValeur) ;

  CPPUNIT_TEST(testAjoute) ;
  CPPUNIT_TEST(testEnleve) ;
  CPPUNIT_TEST(testAppartient) ;

  CPPUNIT_TEST_SUITE_END() ;

public:

  ///////////////
  // Initialisation du test
  void setUp() ;

  ///////////////
  // Desinitialisation du test
  void tearDown() ;


private:


  ////////////////
  // Un ensemble de valeurs
  EnsembleValeur< Entier > ensemble ; 


};



#endif
