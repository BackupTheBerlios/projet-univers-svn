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
      /// Test for replication of data to a client
      class TestReplication : public CppUnit::TestFixture
      {
      protected:
      /*!
        @name Test methods
      */
      // @{

        void createObject() ;
        void addTrait() ;
        void createSubObject() ;
        void createSubObjectOnNonEmptyModel() ;
        void destroyObject() ;
        void destroyTrait() ;
        void updateTrait() ;
        void addRelation() ;
        void removeRelation() ;
        void replicationOfCustomMission() ;
        void createObjectInClientDoesNotCreateObjectInServer() ;
        void createObjectWithSeveralClients() ;

        /*
        @todo
        try with several messages sent in the same time frame

        */

      // @}
      /*!
        @name Test registration
      */
      // @{

        CPPUNIT_TEST_SUITE(TestReplication) ;

        CPPUNIT_TEST(createObject) ;
        CPPUNIT_TEST(addTrait) ;
        CPPUNIT_TEST(createSubObject) ;
        CPPUNIT_TEST(createSubObjectOnNonEmptyModel) ;
        CPPUNIT_TEST(destroyObject) ;
        CPPUNIT_TEST(destroyTrait) ;
        CPPUNIT_TEST(updateTrait) ;
        CPPUNIT_TEST(addRelation) ;
        CPPUNIT_TEST(removeRelation) ;
        CPPUNIT_TEST(replicationOfCustomMission) ;
        CPPUNIT_TEST(createObjectInClientDoesNotCreateObjectInServer) ;
        CPPUNIT_TEST(createObjectWithSeveralClients) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}

        void connect(Kernel::Object* server,Kernel::Object* client) ;
      };

    }
  }
}
