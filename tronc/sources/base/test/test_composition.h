// test_ensemble_valeur.h


#ifndef TEST_ENSEMBLE_H
#define TEST_ENSEMBLE_H


#include <cppunit/extensions/HelperMacros.h>

#include "ensemble_valeur.h"



/*
CLASS
  TestComposition

  Classe permettant de tester la classe de composition d'objets.
*/
class TestComposition : public CppUnit::TestFixture {
protected:

  
  // ****************************
  // GROUP: Tests proprement dits
  // ****************************

  
  ///////////////
  // Teste l'ajout d'un élément
  void testConstruction();

  ///////////////
  // Teste les conversions de 
  void testConversion();
  
 


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
  // Une composition
  Composition< Entier > ensemble ; 


};



#endif
