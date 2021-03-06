/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <model/model.h>
#include <model/positioned.h>
#include <model/stellar_system.h>
#include <artificial_intelligence/implementation/agent.h>

#include <artificial_intelligence/test/test_agent.h>
#include <model/targeting_system.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::ArtificialIntelligence::Test::TestAgent) ;

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Test
    {

      Implementation::Agent* TestAgent::getAgentController(Kernel::Object* agent) const
      {
        Implementation::AISystem* ai_system = agent->getModel()->getControlerSet<Implementation::AISystem>() ;
        CPPUNIT_ASSERT(ai_system) ;

        Implementation::AutonomousAgent* autonomous_agent = agent->getTrait<Implementation::AutonomousAgent>() ;
        CPPUNIT_ASSERT(autonomous_agent) ;

        Implementation::Agent* agent_controler = autonomous_agent->getControler<Implementation::Agent>(ai_system) ;
        CPPUNIT_ASSERT(agent_controler) ;

        return agent_controler ;
      }

      void TestAgent::steeringFullBackShouldTurn()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestAgent::steeringFullBackShouldTurn")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship = Model::createShip(system) ;
        Kernel::Object* agent = Model::createAI(ship) ;

        Implementation::Agent* agent_controler = getAgentController(agent) ;

        /*
          should perform a full turn :
          <--       -->
          ship      steering

          => x or y command should be not null.
        */
        //
        agent_controler->m_steering = Ogre::Vector3::UNIT_Z ;

        Ogre::Vector3 command(agent_controler->calculateSteeringCommands(0.1)) ;

        CPPUNIT_ASSERT_MESSAGE("ship should turn",command.x != 0 || command.y != 0) ;
      }

      void TestAgent::isTargetedByTarget()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship1 = Model::createShip(system) ;
        Kernel::Object* agent = Model::createAI(ship1) ;
        Model::TargetingSystem* targeting_system1 = ship1->getChild<Model::TargetingSystem>() ;

        Kernel::Object* ship2 = Model::createShip(system) ;
        Model::TargetingSystem* targeting_system2 = ship2->getChild<Model::TargetingSystem>() ;

        Implementation::Agent* agent_controller = getAgentController(agent) ;

        targeting_system1->selectTarget(ship2) ;

        CPPUNIT_ASSERT(!agent_controller->isTargetedByTarget()) ;

        targeting_system2->selectTarget(ship1) ;

        CPPUNIT_ASSERT(agent_controller->isTargetedByTarget()) ;
      }

      void TestAgent::applyOnlyToAI()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::attackAllEnemies")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          ship1 = ship ;
        }

        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(1000,0,0)) ;
        }

        ship1->call(Model::TargetingSystem::SelectNextTarget) ;
      }

      void TestAgent::obstacles()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship1 = Model::createShip(system) ;
        Kernel::Object* agent1 = Model::createAI(ship1) ;

        Kernel::Object* ship2 = Model::createShip(system) ;
        Kernel::Object* agent2 = Model::createAI(ship2) ;

        Implementation::Agent* agent_controller1 = getAgentController(agent1) ;

        std::set<Implementation::Vehicle*> obstacles(agent_controller1->getObstacles()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,obstacles.size()) ;
        Implementation::Agent* agent_controller2 = getAgentController(agent2) ;
        CPPUNIT_ASSERT(agent_controller2->getVehicle()) ;
        CPPUNIT_ASSERT(obstacles.find(agent_controller2->getVehicle())!=obstacles.end()) ;
      }

    }
  }
}
