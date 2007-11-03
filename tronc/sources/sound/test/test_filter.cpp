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
#include <sound/implementation/openal/filter.h>

#include <sound/test/test_filter.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestFilter) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {
      using namespace Implementation::OpenAL;
      void TestFilter::basicTest()
      {
        /*!
          - create a source and try reverb and filter on it
        */
        
        Filter a = Filter(0.5,0.25);
        Filter b = Filter(0.5,0.75);
        Filter c = Filter(0.0,1.0);
        Filter d = Filter(1.0,0.0);
        
        Filter plus1 = a + b ;
        CPPUNIT_ASSERT(plus1.getGain() == 0.25 && plus1.getGainHF() == 0.1875);
        Filter moins2 = a - c ;
        CPPUNIT_ASSERT(moins2.getGain() == 0.0 && moins2.getGainHF() == 0.25);
        Filter moins3 = a - d ;
        CPPUNIT_ASSERT(moins3.getGain() == 0.5 && moins3.getGainHF() == 0.0);
        
      }

      void TestFilter::setUp() 
      {
      }
      
      void TestFilter::tearDown() 
      {
      }
      

    }
  }
}

