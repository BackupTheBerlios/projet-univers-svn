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
#include "test_tableau_composition.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestTableauComposition) ;


void 
TableauComposition::testAdd() {

  //local variables

  ObArrayIndex i ;
  ObComposition<int> pElt(new int(123456)) ;
  
  // un opointeur sur l'élément
  ObAssociation<int> element(pElt) ;
  
  CPPUNIT_ASSERT( array.contains(element) == FALSE );
  
  i = array.add( pElt.release() ) ;
  
  CPPUNIT_ASSERT( array.contains(element) == TRUE );
  
}




void TableauComposition::setUp()
{
	// 
}

void TableauComposition::tearDown()
{
	// 
}
