// test_ensemble_association.h


#ifndef TEST_ENSEMBLE_H
#define TEST_ENSEMBLE_H


#include <cppunit/extensions/HelperMacros.h>

#include "ensemble_association.h"
#include "ensemble_compsition.h"



/*
CLASS
  TestEnsembleAssociation

  Classe permettant de tester la classe des ensemble en association.
*/
class TestEnsembleAssociation : public CppUnit::TestFixture {
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
  
  /////////////////
  // Teste la construction d'un ensemble.
  
  
  /////////////////
  // Teste la conversion d'un ensemble en composition.
  



  // *******************************
  // GROUP: Enregistrement des tests
  // *******************************


  CPPUNIT_TEST_SUITE(TestEnsembleAssociation) ;

  CPPUNIT_TEST(testAjoute) ;
  CPPUNIT_TEST(testEnleve) ;
  CPPUNIT_TEST(testAppartient) ;

  CPPUNIT_TEST_SUITE_END() ;

public:

  // *******************************************
  // GROUP: Initialisation et femeture des tests
  // *******************************************
  

  ///////////////
  // Initialisation du test
  void setUp() ;

  ///////////////
  // Desinitialisation du test
  void tearDown() ;


private:

  ////////////////
  // Un ensemble en composition
  EnsembleComposition< Entier > ensemble ; 


  ////////////////
  // Un ensemble en association
  EnsembleAssociation< Entier > ensembleTeste ; 


};



#endif
