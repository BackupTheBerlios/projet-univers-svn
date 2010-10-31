/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#pragma once

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Test
    {


      /// Test for Client/server connection
      class TestConnection : public CppUnit::TestFixture
      {
      protected:
      /*!
        @name Test methods
      */
      // @{

        /// Basic creation of a server
        void createServer() ;
        /// Client connects to server
        void connectClient() ;
        /// Server stops and disconnect clients
        void disconnectClientByServer() ;
        /// Client stops and disconnect from server
        void disconnectClientByClient() ;
        /// Client try to connect but the maximum number of clients is reached
        void maximumNumberOfClientReached() ;

      // @}
      /*!
        @name Test registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestConnection) ;

        CPPUNIT_TEST(createServer) ;
        CPPUNIT_TEST(connectClient) ;
        CPPUNIT_TEST(disconnectClientByServer) ;
        CPPUNIT_TEST(disconnectClientByClient) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      };

    }
  }
}
