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
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#include <kernel/parameters.h>
#include <kernel/log.h>

int 
main( int argc, char* argv[] )
{
  ProjetUnivers::Kernel::Parameters::load("test.config") ;
  ProjetUnivers::Kernel::Log::init() ;
  
  // if command line contains "-selftest" then this is the post build check
  // => the output must be in the compiler error format.
  bool selfTest = (argc > 1)  &&  
                  (std::string("-selftest") == argv[1]);

  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  
  runner.addTest( registry.makeTest() );

  // Define the file that will store the XML output.
  std::ofstream outputFile("../../../tests-results/tests_input.xml");

  if ( selfTest )
  { // Change the default outputter to a compiler error format outputter
    // The test runner owns the new outputter.
    runner.setOutputter( CppUnit::CompilerOutputter::defaultOutputter( 
                                                        &runner.result(),
                                                        std::cerr ) );
  }
  else
  {
    // Specify XML output and inform the test runner of this format.
    CppUnit::XmlOutputter* outputter =
      new CppUnit::XmlOutputter(&runner.result(), outputFile);
    runner.setOutputter(outputter);
  }

  // Run the test.
  bool wasSucessful = runner.run( "" );

  ProjetUnivers::Kernel::Log::close() ;


  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}


