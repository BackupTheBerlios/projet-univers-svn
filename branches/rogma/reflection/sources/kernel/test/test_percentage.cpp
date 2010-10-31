/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <iostream>

#include <kernel/percentage.h>

#include <kernel/test/test_percentage.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {
      
      CPPUNIT_TEST_SUITE_REGISTRATION(TestPercentage) ;

      void TestPercentage::build()
      {
        {
          Percentage value(0) ;
          CPPUNIT_ASSERT(int(value) == 0) ;
        }
        {
          Percentage value(float(0.0)) ;
          CPPUNIT_ASSERT(int(value) == 0) ;
        }
        {
          Percentage value(1000) ;
          CPPUNIT_ASSERT(int(value) == 100) ;
        }
        {
          Percentage value(-1000) ;
          CPPUNIT_ASSERT(int(value) == -100) ;
        }
        {
          Percentage value(float(10.0)) ;
          CPPUNIT_ASSERT(int(value) == 100) ;
        }
        {
          Percentage value(float(-10.0)) ;
          CPPUNIT_ASSERT(int(value) == -100) ;
        }
      }

      void TestPercentage::conversions()
      {
        {
          Percentage value(float(0.5)) ;
          CPPUNIT_ASSERT(int(value) == 50) ;
          CPPUNIT_ASSERT(float(value) == 0.5) ;
        }
      }
      
    }
  }
}
