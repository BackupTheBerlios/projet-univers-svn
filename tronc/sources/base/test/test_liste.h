//*******************************************************************
//              
//  FILE:       ob_list_test.h
//              
//  AUTHOR:     Mathieu Roger
//              
//  PROJECT:    baseTest
//              
//  COMPONENT:  -
//              
//  DATE:       19.07.2003
//              
//  COMMENTS:   -
//              
//              
//*******************************************************************


#ifndef _OB_LIST_TEST_H_
#define _OB_LIST_TEST_H_


// Includes
#include <cppunit/extensions/HelperMacros.h>

#include "ob_composition_list.h"

#include "ob_association_list.h"


// une classe comme ça
class ObElement {
public:

  ObInt valeur ;


  ObElement(const ObInt _e) ;

};



/*
CLASS
  ObListTest
*/
class ObListTest : public CppUnit::TestFixture {
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


  CPPUNIT_TEST_SUITE(ObListTest) ;

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


	ObAssociationList< ObElement > f();

  // une liste 
  ObCompositionList< ObElement > liste ;

};

#endif // _OB_LIST_TEST_H_


