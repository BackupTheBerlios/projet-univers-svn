// test.cpp


#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>


int 
main( int argc, char* argv[] )
{
  // if command line contains "-selftest" then this is the post build check
  // => the output must be in the compiler error format.
  bool selfTest = (argc > 1)  &&  
                  (std::string("-selftest") == argv[1]);

  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  
  runner.addTest( registry.makeTest() );

  if ( selfTest )
  { // Change the default outputter to a compiler error format outputter
    // The test runner owns the new outputter.
    runner.setOutputter( CppUnit::CompilerOutputter::defaultOutputter( 
                                                        &runner.result(),
                                                        std::cerr ) );
  }

  // Run the test.
  bool wasSucessful = runner.run( "" );

  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}


