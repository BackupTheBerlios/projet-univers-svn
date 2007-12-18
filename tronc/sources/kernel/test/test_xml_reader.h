/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_KERNEL_TEST_TEST_XML_READER_H_
#define PU_KERNEL_TEST_TEST_XML_READER_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      ///  Test for XMLReader.
      /*!
      */
      class TestXMLReader : public CppUnit::TestFixture {
      public:

        /// Test initialisation.
        void setUp() ;

        /// Test closing.
        void tearDown() ;

      protected:

      /*!
        @name Tests methods
      */
      // @{  

        /// A simple test.
        void basicTest() ;
        
        /// A simple test.
        void XMLCharTest() ;
        
      // @}


        CPPUNIT_TEST_SUITE(TestXMLReader) ;

        CPPUNIT_TEST(basicTest) ;
        CPPUNIT_TEST(XMLCharTest) ;

        CPPUNIT_TEST_SUITE_END() ;

      
      };
    }
  }
}

#endif /*PU_KERNEL_TEST_TEST_XML_READER_H_*/
