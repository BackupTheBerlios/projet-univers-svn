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
#include <network/test/test_connection.h>
#include <kernel/model.h>
#include <model/server.h>
#include <model/active.h>
#include <network/implementation/enet/network_system.h>
#include <network/implementation/enet/server.h>
#include <model/client.h>
#include <model/connecting.h>
#include <model/connected.h>
#include <model/disconnected.h>
#include <network/implementation/enet/client.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestConnection) ;

      void TestConnection::createServer()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::ControlerSet* controler_set = model->getControlerSet<Implementation::Enet::NetworkSystem>() ;
        CPPUNIT_ASSERT(controler_set) ;

        Kernel::Object* server = model->createObject() ;
        server->addTrait(new Model::Server()) ;
        server->addTrait(new Model::Active()) ;

        CPPUNIT_ASSERT(server->getTrait<Implementation::ActiveServer>()) ;

        Implementation::Enet::Server* enet_server =
            server->getTrait<Implementation::ActiveServer>()
                  ->getControler<Implementation::Enet::Server>(controler_set) ;

        CPPUNIT_ASSERT(enet_server) ;
        CPPUNIT_ASSERT(enet_server->m_host) ;
      }

      void TestConnection::connectClient()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;

        Kernel::Object* server = server_model->createObject() ;
        server->addTrait(new Model::Server()) ;
        server->addTrait(new Model::Active()) ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;

        Kernel::ControlerSet* server_controler_set = server_model->getControlerSet<Implementation::Enet::NetworkSystem>() ;
        CPPUNIT_ASSERT(server_controler_set) ;

        Implementation::Enet::Server* enet_server =
            server->getTrait<Implementation::ActiveServer>()
                  ->getControler<Implementation::Enet::Server>(server_controler_set) ;

        CPPUNIT_ASSERT(enet_server) ;

        Kernel::Object* client = client_model->createObject() ;
        client->addTrait(new Model::Client("localhost",Model::Duration::Second(5))) ;
        client->addTrait(new Model::Connecting()) ;

        // simulate alternativelly to ensure messages sending
        client_model->update(0.1) ;
        server_model->update(0.1) ;
        client_model->update(0.1) ;
        server_model->update(0.1) ;

        // client is marqued as connected
        CPPUNIT_ASSERT(client->getTrait<Model::Connected>()) ;
        CPPUNIT_ASSERT(!client->getTrait<Model::Connecting>()) ;

        // server has a peer
        CPPUNIT_ASSERT(!enet_server->m_clients.empty()) ;
      }

      void TestConnection::disconnectClientByServer()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;

        Kernel::Object* server = server_model->createObject() ;
        server->addTrait(new Model::Server()) ;
        server->addTrait(new Model::Active()) ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;

        Kernel::Object* client = client_model->createObject() ;
        client->addTrait(new Model::Client("localhost",Model::Duration::Second(5))) ;
        client->addTrait(new Model::Connecting()) ;

        // simulate alternativelly to ensure sending
        client_model->update(0.1) ;
        server_model->update(0.1) ;
        client_model->update(0.1) ;
        server_model->update(0.1) ;

        CPPUNIT_ASSERT(client->getTrait<Model::Connected>()) ;
        CPPUNIT_ASSERT(!client->getTrait<Model::Connecting>()) ;

        // destroy the server and disconnect the client
        server->destroyTrait(server->getTrait<Model::Active>()) ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // the client has received the notification
        CPPUNIT_ASSERT(client->getTrait<Model::Disconnected>()) ;
      }

      void TestConnection::disconnectClientByClient()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;

        Kernel::Object* server = server_model->createObject() ;
        server->addTrait(new Model::Server()) ;
        server->addTrait(new Model::Active()) ;

        Kernel::ControlerSet* server_controler_set = server_model->getControlerSet<Implementation::Enet::NetworkSystem>() ;
        CPPUNIT_ASSERT(server_controler_set) ;

        Implementation::Enet::Server* enet_server =
            server->getTrait<Implementation::ActiveServer>()
                  ->getControler<Implementation::Enet::Server>(server_controler_set) ;

        CPPUNIT_ASSERT(enet_server) ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;

        Kernel::Object* client = client_model->createObject() ;
        client->addTrait(new Model::Client("localhost",Model::Duration::Second(5))) ;
        client->addTrait(new Model::Connecting()) ;

        // simulate alternativelly to ensure sending
        client_model->update(0.1) ;
        server_model->update(0.1) ;
        client_model->update(0.1) ;
        server_model->update(0.1) ;

        CPPUNIT_ASSERT(client->getTrait<Model::Connected>()) ;
        CPPUNIT_ASSERT(!client->getTrait<Model::Connecting>()) ;

        // destroy the client and disconnect from the server
        client->destroyTrait(client->getTrait<Model::Client>()) ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // the server has received the notification and removed the client
        CPPUNIT_ASSERT(enet_server->m_clients.empty()) ;
      }

      void TestConnection::connectionTimeout()
      {
        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;

        Kernel::Object* client = client_model->createObject() ;
        client->addTrait(new Model::Client("localhost",Model::Duration::Second(5))) ;
        client->addTrait(new Model::Connecting()) ;

        client_model->init() ;

        Kernel::ControlerSet* network_controler_set = client_model->getControlerSet<Implementation::Enet::NetworkSystem>() ;
        CPPUNIT_ASSERT(network_controler_set) ;

        Implementation::Enet::Client* enet_client =
            client->getTrait<Implementation::Client>()
                  ->getControler<Implementation::Enet::Client>(network_controler_set) ;

        CPPUNIT_ASSERT(enet_client) ;

        client_model->update(6) ;

        CPPUNIT_ASSERT(client->getTrait<Model::Disconnected>()) ;
      }

      void TestConnection::maximumNumberOfClientReached()
      {
        // @todo
        CPPUNIT_ASSERT(false) ;
      }


    }
  }
}


