// composition_array_test.h 

#ifndef COMPOSITION_ARRAY_TEST_H_
#define COMPOSITION_ARRAY_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include "composition_array.h"



/*
CLASS
  CompositionArrayTest

*/
class CompositionArrayTest : public CppUnit::TestFixture {
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


  CPPUNIT_TEST_SUITE(CompositionArrayTest) ;

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
  ObCompositionArray <int> array ; 


};


#endif // _OB_COMPOSITION_ARRAY_TEST_H_


