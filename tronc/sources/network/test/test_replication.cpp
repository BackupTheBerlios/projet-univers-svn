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
#include <kernel/model.h>
#include <kernel/object.h>
#include <model/server.h>
#include <model/active.h>
#include <model/client.h>
#include <model/connecting.h>
#include <model/connected.h>
#include <model/disconnected.h>

#include <network/test/local/t1.h>
#include <network/implementation/enet/network_system.h>
#include <network/implementation/enet/server.h>
#include <network/test/test_replication.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestReplication) ;

      void TestReplication::connect(Kernel::Object* server,Kernel::Object* client)
      {
        server->addTrait(new Model::Server()) ;
        server->addTrait(new Model::Active()) ;
        client->addTrait(new Model::Client("localhost")) ;
        client->addTrait(new Model::Connecting()) ;

        // simulate alternativelly to ensure messages sending
        client->getModel()->update(0.1) ;
        server->getModel()->update(0.1) ;
        client->getModel()->update(0.1) ;
        server->getModel()->update(0.1) ;

        // client is marqued as connected
        CPPUNIT_ASSERT(client->getTrait<Model::Connected>()) ;
        CPPUNIT_ASSERT(!client->getTrait<Model::Connecting>()) ;
      }

      void TestReplication::createObject()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;

        connect(server,client) ;

        Kernel::Object* o1 = server->createObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // a sub object has been replicated
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,client->getChildren().size()) ;
        Kernel::Object* o1_client = *client->getChildren().begin() ;
      }

      void TestReplication::addTrait()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;

        connect(server,client) ;

        Kernel::Object* o1 = server->createObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // a sub object has been replicated
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,client->getChildren().size()) ;
        Kernel::Object* o1_client = *client->getChildren().begin() ;

        o1->addTrait(new Local::T1()) ;
        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT(o1_client->getTrait<Local::T1>()) ;
      }

      void TestReplication::createSubObject()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;

        connect(server,client) ;

        Kernel::Object* o1 = server->createObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // a sub object has been replicated
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,client->getChildren().size()) ;
        Kernel::Object* o1_client = *client->getChildren().begin() ;

        o1->createObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // a sub object has been replicated
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,o1_client->getChildren().size()) ;
      }

    }
  }
}


