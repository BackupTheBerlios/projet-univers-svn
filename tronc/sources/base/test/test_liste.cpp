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

#include "test_liste.h"

#include "liste_association.h"
#include "iterateur_list_association.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ObListTest) ;


void ListTest::testDestroy()
{
	// 
  CompositionList< Element > liste2 ;

  Composition< Element > element1(new Element(1)) ;
  Composition< Element > element2(new Element(2)) ;

  liste2.add_first(element1.release()) ;
  liste2.add_first(element2.release()) ;

 
}


Element::Element(const Int _e)



void TestListe::testList()
{
	// 
  AssociationList< Element > temp ;

  Composition< Element > element1(new Element(1)) ;
  Composition< Element > element2(new Element(2)) ;

  temp.add_first(element1) ;
  temp.add_first(element2) ;

  CPPUNIT_ASSERT(temp.count() == 2) ;

  CPPUNIT_ASSERT(temp.contains(element1)) ;
  CPPUNIT_ASSERT(temp.contains(element2)) ;

  Int resultat(0) ;

  for(
  AssociationListIterator< Element > i(temp) ;
  i.valid() ;
  ++i)

    resultat += i->valeur ;

  CPPUNIT_ASSERT(resultat == 3) ;
 

}



AssociationList< Element > TestListe::f() 
{

  return liste ;
}


void TestListe::testListCopy()
{


  Int resultat(0) ;


	// itération sur une liste temporaire
  for(
  AssociationListIterator< Element > i(f()) ; 
  i.valid() ;
  ++i)
  
    resultat += i->valeur ;
  

  CPPUNIT_ASSERT(resultat == 3) ;

  resultat = 0 ;

  for(
  AssociationListIterator< Element > j(liste) ; 
  j.valid() ;
  ++j)
  
    resultat += j->valeur ;

  CPPUNIT_ASSERT(resultat == 3) ;


}

void TestListe::setUp()
{
	// 

  liste.add_first(new Element(1)) ;
  liste.add_first(new Element(2)) ;

}

void TestListe::tearDown()
{
	// 
}
