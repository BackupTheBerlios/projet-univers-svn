/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <OgreVector3.h>
#include <model/area.h>

#include <model/test/test_area.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Model::Test::TestArea) ;

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Test 
    {

      void TestArea::build()
      {
        Position p1(Position::Meter(1,0,0)) ;
        Position p2(Position::Meter(0,1,0)) ;
        Position p3(Position::Meter(0,0,1)) ;
        
        std::set<Position> positions ;
        positions.insert(p1) ;
        positions.insert(p2) ;
        positions.insert(p3) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)3,positions.size()) ;
        
        Area area(positions) ;

        CPPUNIT_ASSERT(area.contains(Position::Meter(0.5,0.5,0.5))) ;
      }
      
      void TestArea::getCenter()
      {
        Position p1(Position::Meter(1,0,0)) ;
        Position p2(Position::Meter(0,1,0)) ;
        Position p3(Position::Meter(0,0,1)) ;
        
        std::set<Position> positions ;
        positions.insert(p1) ;
        positions.insert(p2) ;
        positions.insert(p3) ;
        
        CPPUNIT_ASSERT_EQUAL((unsigned int)3,positions.size()) ;
        Area area(positions) ;

        CPPUNIT_ASSERT(area.getCenter() == Position::Meter(0.5,0.5,0.5)) ;
      }

      void TestArea::getRadius()
      {
        Position p1(Position::Meter(1,0,0)) ;
        Position p2(Position::Meter(0,1,0)) ;
        Position p3(Position::Meter(0,0,1)) ;
        
        std::set<Position> positions ;
        positions.insert(p1) ;
        positions.insert(p2) ;
        positions.insert(p3) ;
        
        CPPUNIT_ASSERT_EQUAL((unsigned int)3,positions.size()) ;
        Area area(positions) ;

        CPPUNIT_ASSERT_EQUAL(Distance(Distance::_Meter,Ogre::Vector3(0.5,0.5,0.5).length()),area.getRadius()) ;
      }
      
    }
  }
}

