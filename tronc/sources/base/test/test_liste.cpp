// ob_list_test.cpp

#include "ob_list_test.h"

#include "ob_association_list.h"
#include "ob_association_list_iterator.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ObListTest) ;


void ObListTest::testDestroy()
{
	// 
  ObCompositionList< ObElement > liste2 ;

  ObComposition< ObElement > element1(new ObElement(1)) ;
  ObComposition< ObElement > element2(new ObElement(2)) ;

  liste2.add_first(element1.release()) ;
  liste2.add_first(element2.release()) ;

 
}


ObElement::ObElement(const ObInt _e)
: valeur(_e)
{}


void ObListTest::testList()
{
	// 
  ObAssociationList< ObElement > temp ;

  ObComposition< ObElement > element1(new ObElement(1)) ;
  ObComposition< ObElement > element2(new ObElement(2)) ;

  temp.add_first(element1) ;
  temp.add_first(element2) ;

  CPPUNIT_ASSERT(temp.count() == 2) ;

  CPPUNIT_ASSERT(temp.contains(element1)) ;
  CPPUNIT_ASSERT(temp.contains(element2)) ;

  ObInt resultat(0) ;

  for(
  ObAssociationListIterator< ObElement > i(temp) ;
  i.valid() ;
  ++i)

    resultat += i->valeur ;

  CPPUNIT_ASSERT(resultat == 3) ;
 

}



ObAssociationList< ObElement > ObListTest::f() 
{

  return liste ;
}


void ObListTest::testListCopy()
{


  ObInt resultat(0) ;


	// itération sur une liste temporaire
  for(
  ObAssociationListIterator< ObElement > i(f()) ; 
  i.valid() ;
  ++i)
  
    resultat += i->valeur ;
  

  CPPUNIT_ASSERT(resultat == 3) ;

  resultat = 0 ;

  for(
  ObAssociationListIterator< ObElement > j(liste) ; 
  j.valid() ;
  ++j)
  
    resultat += j->valeur ;

  CPPUNIT_ASSERT(resultat == 3) ;


}

void ObListTest::setUp()
{
	// 

  liste.add_first(new ObElement(1)) ;
  liste.add_first(new ObElement(2)) ;

}

void ObListTest::tearDown()
{
	// 
}
