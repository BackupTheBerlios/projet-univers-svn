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
#include <iostream>
#include <kernel/parameters.h>
#include <kernel/test/test_parameters.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestParameters) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

      void TestParameters::basicTest()
      {
        Parameters::load("parameter.config") ;
        
        CPPUNIT_ASSERT(Parameters::getValue<std::string>("test","value1")=="toto") ;
        CPPUNIT_ASSERT(Parameters::getValue<float>("test","value2")==1) ;
        CPPUNIT_ASSERT(!Parameters::getValue<bool>("test","value3")) ;
        CPPUNIT_ASSERT(Parameters::getValue<float>("test","value4")==-2) ;
        
        CPPUNIT_ASSERT(Parameters::getValue<float>("physic","number_of_contact_points") == 10) ;
      }

      void TestParameters::testDemonstration()
      {
        Parameters::load("kernel_demonstration.config") ;
        
        CPPUNIT_ASSERT(Parameters::getValue<float>("Model","DraggerCoeeficient") == (float)0.01) ;
        CPPUNIT_ASSERT(Parameters::getValue<float>("Input","ThrottelAxis") == 6) ;
        CPPUNIT_ASSERT(Parameters::getValue<bool>("Physic","ActivateCollision")) ;
        CPPUNIT_ASSERT(Parameters::getValue<float>("Physic","MaxNumberOfContactPoints") == 100) ;
      }
      
      void TestParameters::testGetActivatedLogs()
      {
        Parameters::reset() ;
        Parameters::load("log.config") ;
        std::set<std::string> logs = Parameters::getActivatedLogs() ;
        
        CPPUNIT_ASSERT(logs.size() == 1) ;
        CPPUNIT_ASSERT(*logs.begin() == "module2") ;
      }
      
      void TestParameters::setUp()
      {
      }

      void TestParameters::tearDown()
      {
      }

    }
  }
}
