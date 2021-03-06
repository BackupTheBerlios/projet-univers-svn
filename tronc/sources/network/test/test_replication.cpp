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
#include <model/custom_mission.h>
#include <model/team.h>

#include <network/test/local/t1.h>
#include <network/test/local/r1.h>
#include <network/implementation/enet/network_system.h>
#include <network/implementation/enet/server.h>
#include <network/test/test_replication.h>
#include <network/implementation/enet/client.h>
#include <gui/implementation/cegui/custom_mission.h>


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
        client->addTrait(new Model::Client("localhost",Model::Duration::Second(5))) ;
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

      void TestReplication::createSubObjectOnNonEmptyModel()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;
        client_model->createObject() ;

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

      void TestReplication::destroyObject()
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

        o1->destroyObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // the object has been destroy in replication
        CPPUNIT_ASSERT(client->getChildren().empty()) ;
      }

      void TestReplication::destroyTrait()
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

        Kernel::Trait* trait = o1->addTrait(new Local::T1()) ;
        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT(o1_client->getTrait<Local::T1>()) ;

        o1->destroyTrait(trait) ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT(!o1_client->getTrait<Local::T1>()) ;
      }

      void TestReplication::updateTrait()
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

        Local::T1* trait = static_cast<Local::T1*>(o1->addTrait(new Local::T1())) ;
        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT(o1_client->getTrait<Local::T1>()) ;
        CPPUNIT_ASSERT_EQUAL(std::string(""),o1_client->getTrait<Local::T1>()->getName()) ;

        trait->setName("toto") ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT(o1_client->getTrait<Local::T1>()) ;
        CPPUNIT_ASSERT_EQUAL(std::string("toto"),o1_client->getTrait<Local::T1>()->getName()) ;
      }

      void TestReplication::addRelation()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;

        connect(server,client) ;

        Kernel::Object* o1 = server->createObject() ;
        Kernel::Object* o2 = server->createObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,client->getChildren().size()) ;

        Kernel::ControlerSet* controler_set = client_model->getControlerSet<Implementation::Enet::NetworkSystem>() ;

        Implementation::Enet::Client* client_controler =
            client->getTrait<Implementation::Client>()
                  ->getControler<Implementation::Enet::Client>(controler_set) ;

        CPPUNIT_ASSERT(client_controler) ;

        Kernel::Object* o1_client = client_controler->getNetworkObject(1) ;
        Kernel::Object* o2_client = client_controler->getNetworkObject(2) ;

        Kernel::Link<Local::R1>(o1,o2) ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT(Kernel::Relation::areLinked<Local::R1>(o1_client,o2_client)) ;
      }

      void TestReplication::removeRelation()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;

        connect(server,client) ;

        Kernel::Object* o1 = server->createObject() ;
        Kernel::Object* o2 = server->createObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,client->getChildren().size()) ;

        Kernel::ControlerSet* controler_set = client_model->getControlerSet<Implementation::Enet::NetworkSystem>() ;

        Implementation::Enet::Client* client_controler =
            client->getTrait<Implementation::Client>()
                  ->getControler<Implementation::Enet::Client>(controler_set) ;

        CPPUNIT_ASSERT(client_controler) ;

        Kernel::Object* o1_client = client_controler->getNetworkObject(1) ;
        Kernel::Object* o2_client = client_controler->getNetworkObject(2) ;

        Kernel::Link<Local::R1>(o1,o2) ;
        Kernel::UnLink<Local::R1>(o1,o2) ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        CPPUNIT_ASSERT(!Kernel::Relation::areLinked<Local::R1>(o1_client,o2_client)) ;
      }

      void TestReplication::replicationOfCustomMission()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        Kernel::Object* mission = server->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;

        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Model::Team("team 1")) ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;

        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // @todo : need to remove model controler...
      }

      void TestReplication::createObjectInClientDoesNotCreateObjectInServer()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model(new Kernel::Model()) ;
        client_model->init() ;
        Kernel::Object* client = client_model->createObject() ;

        connect(server,client) ;

        Kernel::Object* o1 = client->createObject() ;

        client_model->update(0.1) ;
        server_model->update(0.1) ;
        client_model->update(0.1) ;

        // no object has been replicated
        CPPUNIT_ASSERT(server->getChildren().empty()) ;
      }

      void TestReplication::createObjectWithSeveralClients()
      {
        std::auto_ptr<Kernel::Model> server_model(new Kernel::Model()) ;
        server_model->init() ;
        Kernel::Object* server = server_model->createObject() ;

        std::auto_ptr<Kernel::Model> client_model1(new Kernel::Model()) ;
        client_model1->init() ;
        Kernel::Object* client1 = client_model1->createObject() ;

        std::auto_ptr<Kernel::Model> client_model2(new Kernel::Model()) ;
        client_model2->init() ;
        Kernel::Object* client2 = client_model2->createObject() ;

        connect(server,client1) ;
        connect(server,client2) ;

        Kernel::Object* o1 = server->createObject() ;

        server_model->update(0.1) ;
        client_model1->update(0.1) ;
        client_model2->update(0.1) ;

        // a sub object has been replicated for both clients
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,client1->getChildren().size()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,client2->getChildren().size()) ;
      }

    }
  }
}


