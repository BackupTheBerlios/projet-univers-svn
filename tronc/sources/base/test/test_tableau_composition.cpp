// composition_array_test.cpp

#include "composition_array_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CompositionArrayTest) ;


void 
CompositionArrayTest::testAdd() {

  //local variables

  ObArrayIndex i ;
  ObComposition<int> pElt(new int(123456)) ;
  
  // un opointeur sur l'élément
  ObAssociation<int> element(pElt) ;
  
  CPPUNIT_ASSERT( array.contains(element) == FALSE );
  
  i = array.add( pElt.release() ) ;
  
  CPPUNIT_ASSERT( array.contains(element) == TRUE );
  
}




void CompositionArrayTest::setUp()
{
	// 
}

void CompositionArrayTest::tearDown()
{
	// 
}
