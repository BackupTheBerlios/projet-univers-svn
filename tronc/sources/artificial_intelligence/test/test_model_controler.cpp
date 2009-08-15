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
#include <iostream>

#include <kernel/object_reference.h>
#include <kernel/log.h>
#include <kernel/command_delegator.h>
#include <kernel/parameters.h>
#include <kernel/timer.h>

#include <model/model.h>
#include <model/computer.h>
#include <model/massive.h>
#include <model/detector.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/solid.h>
#include <model/stabilizer.h>
#include <model/guidance_system.h>
#include <model/guidance_controler.h>
#include <model/engine.h>
#include <model/engine_controler.h>
#include <model/stick.h>
#include <model/throttle.h>
#include <model/dragger.h>
#include <model/laser.h>
#include <model/detection_data.h>
#include <model/targeting_system.h>
#include <model/shooting_helper.h>
#include <model/autonomous_character.h>
#include <model/with_objectives.h>
#include <model/physical_world.h>
#include <model/transponder.h>
#include <model/destroyable.h>
#include <model/stellar_system.h>
#include <model/collision.h>
#include <model/team.h>
#include <model/custom_mission.h>
#include <model/flying_group.h>
#include <model/mission.h>
#include <model/played.h>
#include <model/state.h>

#include <model/implementation/logic/logic_system.h>
#include <physic/physic.h>

#include <artificial_intelligence/artificial_intelligence.h>
#include <artificial_intelligence/implementation/agent.h>
#include <artificial_intelligence/implementation/autonomous_agent.h>
#include <artificial_intelligence/test/test_model_controler.h>
#include <artificial_intelligence/implementation/with_vehicle_controler.h>
#include <model/area.h>



CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::ArtificialIntelligence::Test::TestModelControler) ;

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Test
    {

      void TestModelControler::simulate()
      {
        InternalMessage("AI","AI::TestModelControler::simulate entering") ;
        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::simulate")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Model::Computer()) ;
        ship->addTrait(new Model::Laser(Model::Position(),
                                        Model::Orientation(),
                                        Model::Energy::Joule(10))) ;
        ship->addTrait(new Model::Detector()) ;
        Model::Detector::connect(ship,ship) ;
        ship->addTrait(new Model::Transponder(team1)) ;
        ship->addTrait(new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(ship,ship) ;

        Kernel::Object* agent = ship->createObject() ;
        agent->addTrait(new Model::AutonomousCharacter()) ;
        agent->addTrait(new Model::WithObjectives()) ;
        agent->addTrait(new Kernel::CommandDelegator()) ;
        agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
        agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Model::Positionned(Model::Position::Meter(0,0,500))) ;
        ship2->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship2->addTrait(new Model::Oriented()) ;
        ship2->addTrait(new Model::Mobile(Model::Speed::MeterPerSecond(0,10,0))) ;
        ship2->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship2->addTrait(new Model::Transponder(team1)) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        ship3->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship3->addTrait(new Model::Oriented()) ;
        ship3->addTrait(new Model::Mobile()) ;
        ship3->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship3->addTrait(new Model::Transponder(team2)) ;

        model->update(0.1) ;

        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;

        model->update(0.1) ;

        // target must be ship3
        /// get the physical viewpoint
        Implementation::AISystem* ai_system = model->getControlerSet<Implementation::AISystem>() ;
        CPPUNIT_ASSERT(ai_system) ;

        Implementation::AutonomousAgent* autonomous_agent = agent->getTrait<Implementation::AutonomousAgent>() ;
        CPPUNIT_ASSERT(autonomous_agent) ;

        Implementation::Agent* agent_controler = autonomous_agent->getControler<Implementation::Agent>(ai_system) ;
        CPPUNIT_ASSERT(agent_controler) ;

        CPPUNIT_ASSERT(agent_controler->getTarget()) ;

        InternalMessage("AI","AI::TestModelControler::simulate leaving") ;
      }

      void TestModelControler::buildWithoutElements()
      {
        InternalMessage("AI","AI::TestModelControler::buildWithoutElements entering") ;

        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::buildWithoutElements")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;

        Kernel::Object* agent = ship->createObject() ;
        agent->addTrait(new Model::AutonomousCharacter()) ;
        agent->addTrait(new Model::WithObjectives()) ;
        agent->addTrait(new Kernel::CommandDelegator()) ;
        agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Model::Positionned(Model::Position::Meter(0,0,500))) ;
        ship2->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship2->addTrait(new Model::Oriented()) ;
        ship2->addTrait(new Model::Mobile(Model::Speed::MeterPerSecond(0,10,0))) ;
        ship2->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        ship3->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship3->addTrait(new Model::Oriented()) ;
        ship3->addTrait(new Model::Mobile()) ;
        ship3->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;

        model->update(0.1) ;

        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;

        InternalMessage("AI","AI::TestModelControler::buildWithoutElements leaving") ;
      }

      void TestModelControler::attackAllEnemies()
      {
        InternalMessage("AI","AI::TestModelControler::attackAllEnemies entering") ;
        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::attackAllEnemies")) ;
        model->init() ;
        model->setTimeStep(0.1) ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }


        // the attacked enemy ship
        Kernel::Object* enemy_ship = system->createObject() ;
        enemy_ship->addTrait(new Model::Positionned(Model::Position::Meter(500,0,-1000))) ;
        enemy_ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        enemy_ship->addTrait(new Model::Oriented()) ;
        enemy_ship->addTrait(new Model::Mobile()) ;
        enemy_ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        enemy_ship->addTrait(new Model::Transponder(team2)) ;
        enemy_ship->addTrait(new Model::Destroyable(Model::Energy::Joule(1))) ;
        enemy_ship->addTrait(new Model::Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient",0.01))) ;
        {
          Kernel::Object* st1 = enemy_ship->createObject() ;
          st1->addTrait(new Model::Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce",10),0)) ;
          st1->addTrait(new Model::Component()) ;

          Kernel::Object* st2 = enemy_ship->createObject() ;
          st2->addTrait(new Model::Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce",10),0,0)) ;
          st2->addTrait(new Model::Component()) ;

          Kernel::Object* st3 = enemy_ship->createObject() ;
          st3->addTrait(new Model::Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce",10))) ;
          st3->addTrait(new Model::Component()) ;
        }

        Kernel::ObjectReference enemy(enemy_ship) ;

        for(int i = 0 ; i < 500 ; ++i)
        {
          model->update(0.1) ;
        }

        // enemy is destroyed
        CPPUNIT_ASSERT(!enemy) ;
        InternalMessage("AI","AI::TestModelControler::attackAllEnemies leaving") ;
      }

      void TestModelControler::twoShips()
      {
        InternalMessage("AI","AI::TestModelControler::twoShips entering") ;

        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::twoShips")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;

          ship->destroyTrait(ship->getTrait<Model::Destroyable>()) ;
        }

        CPPUNIT_ASSERT(ship1->getModel()==model.get()) ;

        Kernel::ObjectReference ship2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-1100)) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
        }

        for(int i = 0 ; i < 3000 ; ++i)
        {
          model->update(0.1) ;
        }

        // at least one ship has been destroyed (in fact both?)
        CPPUNIT_ASSERT(!ship2) ;

        InternalMessage("AI","AI::TestModelControler::twoShips leaving") ;
      }

      void TestModelControler::groupAttack()
      {
        InternalMessage("AI","AI::TestModelControler::groupAttack entering") ;

        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::groupAttack")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          ship->destroyTrait(ship->getTrait<Model::Destroyable>()) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }

        Kernel::ObjectReference ship2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,-500,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          ship->destroyTrait(ship->getTrait<Model::Destroyable>()) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
        }

        Kernel::ObjectReference ship3 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-1100)) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship3 = ship ;
        }

        Kernel::ObjectReference ship4 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-3000)) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship4 = ship ;
        }

        // team1 cannot be destroyed -> it should win and destroy ship3/ship4

        for(int i = 0 ; i < 1000 ; ++i)
        {
          model->update(0.1) ;
        }

        // team2 has been destroyed
        CPPUNIT_ASSERT(!ship3) ;
        CPPUNIT_ASSERT(!ship4) ;

        // team1 has survived
        CPPUNIT_ASSERT(ship1 && ship2) ;
        InternalMessage("AI","AI::TestModelControler::groupAttack leaving") ;
      }

      void TestModelControler::testPositionUpdate()
      {
        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::testPositionUpdate")) ;
        model->init() ;
        Kernel::ControlerSet* logic = model->getControlerSet<Model::Implementation::Logic::LogicSystem>() ;
        logic->setTimeStep(0) ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;

        Kernel::ObjectReference ship1 ;
        Kernel::ObjectReference agent1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
          agent1 = agent ;
        }

        Kernel::ObjectReference ship2 ;
        Kernel::ObjectReference agent2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-1100)) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
          agent2 = agent ;
        }

        model->update(0) ;

        // 3. check that views/controlers are built
        Implementation::AISystem* ai_system = model->getControlerSet<Implementation::AISystem>() ;
        CPPUNIT_ASSERT(ai_system) ;

        Implementation::AutonomousAgent* autonomous_agent1 = agent1->getTrait<Implementation::AutonomousAgent>() ;
        CPPUNIT_ASSERT(autonomous_agent1) ;

        Implementation::Agent* agent_controler1 = autonomous_agent1->getControler<Implementation::Agent>(ai_system) ;
        CPPUNIT_ASSERT(agent_controler1) ;

        CPPUNIT_ASSERT(Model::getControledShip(agent1)) ;
        CPPUNIT_ASSERT(Model::getControledShip(agent1) == ship1) ;

      }

      void TestModelControler::testMission()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Model::State()) ;

        Kernel::Object* main_menu = root->createObject() ;
        main_menu->setName("main_menu") ;
        main_menu->addTrait(new Model::State()) ;

        Kernel::Object* mission = root->createObject() ;
        mission->addTrait(new Model::CustomMission("",NULL,NULL)) ;
        mission->getTrait<Model::CustomMission>()->setStartingDistance(Model::Distance(Model::Distance::_Meter,4000)) ;
        mission->addTrait(new Model::State()) ;

        {
          Kernel::Object* team = mission->createObject() ;
          team->addTrait(new Model::Team("")) ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new Model::FlyingGroup("")) ;

          flying_group->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
          flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(2) ;
          flying_group->getTrait<Model::FlyingGroup>()->setHasPlayer(true) ;
        }

        {
          Kernel::Object* team = mission->createObject() ;
          team->addTrait(new Model::Team("")) ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new Model::FlyingGroup("")) ;

          flying_group->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
          flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(3) ;
          flying_group->getTrait<Model::FlyingGroup>()->setHasPlayer(false) ;
          flying_group->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(2) ;

        }

        CPPUNIT_ASSERT(!mission->getTrait<Model::Mission>()->getSystem()) ;
        root->getTrait<Model::State>()->changeState(mission,new Model::Played()) ;

        model->update(0.1) ;
        mission->destroyTrait(mission->getTrait<Model::Played>()) ;
        model->update(0.1) ;

      }

      void TestModelControler::steering()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::twoShips")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;

        Kernel::ObjectReference ship1 ;
        Kernel::ObjectReference agent1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(-1000,0,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
          agent1 = agent ;
        }

        CPPUNIT_ASSERT(ship1->getModel()==model.get()) ;

        Kernel::ObjectReference ship2 ;
        Kernel::ObjectReference agent2;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
          agent2 = agent ;
        }

        /*
        Seen from top :

          ^                ^
          |  ship2         |  ship1

        Which must result in :

                          <- desired speed
                          <- "command"
        */


        model->update(0.1) ;

        Implementation::AISystem* ai_system = model->getControlerSet<Implementation::AISystem>() ;
        CPPUNIT_ASSERT(ai_system) ;
        Implementation::AutonomousAgent* autonomous_agent = agent1->getTrait<Implementation::AutonomousAgent>() ;
        CPPUNIT_ASSERT(autonomous_agent) ;
        Implementation::Agent* agent_controler = autonomous_agent->getControler<Implementation::Agent>(ai_system) ;
        CPPUNIT_ASSERT(agent_controler) ;

        agent_controler->applyObjective(Model::Objective::attackAllEnemies(),agent1,0.1) ;

        // need to go right
        CPPUNIT_ASSERT(agent_controler->getDesiredSpeed().positionEquals(Ogre::Vector3::UNIT_X,0.1)) ;
        CPPUNIT_ASSERT(agent_controler->calculateSteeringCommands(0.1).x > 0) ;


        // move agent...
        ship2->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
        ship2->getTrait<Model::Mobile>()->setSpeed(Model::Speed()) ;
        ship2->getTrait<Model::Oriented>()->setOrientation(Model::Orientation()) ;
        ship1->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,1000,0)) ;
        ship1->getTrait<Model::Mobile>()->setSpeed(Model::Speed()) ;
        ship1->getTrait<Model::Oriented>()->setOrientation(Model::Orientation()) ;

        Implementation::WithVehicleControler* vehicle =
            ship1->getTrait<Implementation::WithVehicle>()
                 ->getControler<Implementation::WithVehicleControler>(ai_system) ;

        CPPUNIT_ASSERT(vehicle) ;

//        std::cout << vehicle->getVehicle()->toString() << std::endl ;

        /*
        Seen from left :

        <-- ship1

        <-- ship2

        Which must result in :

             |  desired speed
             V

             |  "command"
             V
        */


        model->update(0.1) ;

//        std::cout << vehicle->getVehicle()->toString() << std::endl ;

        agent_controler->applyObjective(Model::Objective::attackAllEnemies(),agent1,0.1) ;

//        std::cout << vehicle->getVehicle()->toString() << std::endl ;
//
//        std::cout << agent_controler->getDesiredSpeed() ;
        CPPUNIT_ASSERT(agent_controler->getDesiredSpeed().positionEquals(Ogre::Vector3::NEGATIVE_UNIT_Y,0.1)) ;
        CPPUNIT_ASSERT(agent_controler->calculateSteeringCommands(0.1).y > 0) ;
      }

      void TestModelControler::avoidMutualFlee()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::avoidMutualFlee")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;

        /*
        Situaltion seen from top :

        ------------------------
        |                      |
        | <--            -->   |
        | ship1          ship2 |
        |                      |
        ------------------------

        Objective of the the system : they must stay in the box
        (initial_distance+ship_size*4,ship_size*4,ship_size*4)
        */

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(-500,0,0)) ;
          ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y))) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          ship->destroyTrait(ship->getTrait<Model::Destroyable>()) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }

        Kernel::ObjectReference ship2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(500,0,0)) ;
          ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y))) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          ship->destroyTrait(ship->getTrait<Model::Destroyable>()) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
        }

        float ship_size = ship1->getTrait<Model::Solid>()->getRadius().Meter()*2 ;

        std::set<Model::Position> positions ;
        positions.insert(Model::Position::Meter(500,2*ship_size,2*ship_size)) ;
        positions.insert(Model::Position::Meter(-500,-2*ship_size,-2*ship_size)) ;

        Model::Area area(positions) ;


        for(int i = 0 ; i < 400 ; ++i)
        {
          model->update(0.1) ;

          // check they stay in the box
          CPPUNIT_ASSERT_MESSAGE("ship1 left the area at " + Kernel::toString(i) +
                                 " with position " + Ogre::StringConverter::toString(ship1->getTrait<Model::Positionned>()->getPosition().Meter()),
                                 area.contains(ship1->getTrait<Model::Positionned>()->getPosition())) ;
          CPPUNIT_ASSERT_MESSAGE("ship2 left the area at " + Kernel::toString(i) +
                                 " with position " + Ogre::StringConverter::toString(ship2->getTrait<Model::Positionned>()->getPosition().Meter()),
                                 area.contains(ship2->getTrait<Model::Positionned>()->getPosition())) ;
        }

      }

    }
  }
}
