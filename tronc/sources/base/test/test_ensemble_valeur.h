// test_ensemble_valeur.h


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
