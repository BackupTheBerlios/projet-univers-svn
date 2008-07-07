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
#include <model/selected.h>
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

#include <physic/physic.h>

#include <artificial_intelligence/artificial_intelligence.h>
#include <artificial_intelligence/implementation/agent.h>
#include <artificial_intelligence/implementation/autonomous_agent.h>
#include <artificial_intelligence/test/test_model_controler.h>



CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::ArtificialIntelligence::Test::TestModelControler) ;

namespace ProjetUnivers {
  namespace ArtificialIntelligence {
    namespace Test {

      
      void TestModelControler::build()
      {
        InternalMessage("AI","AI::TestModelControler::build entering") ;

        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::build")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        ship->addTrait(new Model::Computer()) ;
        ship->addTrait(new Model::Laser(Model::Position(),
                                              Model::Orientation(),
                                              Model::Energy::Joule(10))) ;
        ship->addTrait(new Model::Detector(ship)) ;
        ship->addTrait(new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(ship,ship) ;
        
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
        ship2->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        ship3->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship3->addTrait(new Model::Oriented()) ;
        ship3->addTrait(new Model::Mobile()) ;
        ship3->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        
        model->update(0) ;

        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;
        
        // 3. check that views/controlers are built 
        /// get the physical viewpoint        
        Implementation::AISystem* ai_system = model->getControlerSet<Implementation::AISystem>() ;
        CPPUNIT_ASSERT(ai_system) ;
        
        Implementation::AutonomousAgent* autonomous_agent = agent->getTrait<Implementation::AutonomousAgent>() ;
        CPPUNIT_ASSERT(autonomous_agent) ;
        
        Implementation::Agent* agent_controler = autonomous_agent->getControler<Implementation::Agent>(ai_system) ;
        CPPUNIT_ASSERT(agent_controler) ;
        
        CPPUNIT_ASSERT(Model::getControledShip(agent)) ;
        CPPUNIT_ASSERT(Model::getControledShip(agent) == ship) ;
        
        std::set<Model::Computer*> computers = Model::getControledShip(agent)->getChildren<Model::Computer>() ;
        CPPUNIT_ASSERT(computers.size() == 1) ;
        
        CPPUNIT_ASSERT(Model::getControledShip(agent)) ;
        
        const std::set<Implementation::Vehicle*>& vehicles = agent_controler->getVehicles() ;
        CPPUNIT_ASSERT(vehicles.size()==2) ;
        
        // check selected target
        CPPUNIT_ASSERT(! agent_controler->getTarget()) ;
        ship->getTrait<Model::TargetingSystem>()->selectNextTarget() ;
        CPPUNIT_ASSERT(agent_controler->getTarget()) ;
        
        // check position and speed of vehicles
        for(std::set<Implementation::Vehicle*>::const_iterator vehicle = vehicles.begin() ; 
            vehicle != vehicles.end() ;
            ++vehicle)
        {
          CPPUNIT_ASSERT(((*vehicle)->getPosition() == Ogre::Vector3(0,0,500)) ||
                         ((*vehicle)->getPosition() == Ogre::Vector3(500,0,500))) ;
          
          CPPUNIT_ASSERT(((*vehicle)->getSpeed() == Ogre::Vector3(0,0,0)) ||
                         ((*vehicle)->getSpeed() == Ogre::Vector3(0,10,0))) ;
        }
        
        ship2->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(-500,0,500)) ;
        ship3->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,-10,0)) ;
        model->update(0) ;
        
        for(std::set<Implementation::Vehicle*>::const_iterator vehicle = vehicles.begin() ; 
            vehicle != vehicles.end() ;
            ++vehicle)
        {
          CPPUNIT_ASSERT(((*vehicle)->getPosition() == Ogre::Vector3(-500,0,500)) ||
                         ((*vehicle)->getPosition() == Ogre::Vector3(500,0,500))) ;
          
          CPPUNIT_ASSERT(((*vehicle)->getSpeed() == Ogre::Vector3(0,-10,0)) ||
                         ((*vehicle)->getSpeed() == Ogre::Vector3(0,10,0))) ;
        }
        
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(1000,0,500)) ;
        ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        model->update(0) ;

        for(std::set<Implementation::Vehicle*>::const_iterator vehicle = vehicles.begin() ; 
            vehicle != vehicles.end() ;
            ++vehicle)
        {
          CPPUNIT_ASSERT(((*vehicle)->getPosition() == Ogre::Vector3(-500,0,500)) ||
                         ((*vehicle)->getPosition() == Ogre::Vector3(500,0,500))) ;
          
          CPPUNIT_ASSERT(((*vehicle)->getSpeed() == Ogre::Vector3(0,-10,0)) ||
                         ((*vehicle)->getSpeed() == Ogre::Vector3(0,10,0))) ;
        }
        
        CPPUNIT_ASSERT(agent_controler->getVehicle()) ;
        InternalMessage("AI","AI::TestModelControler::build leaving") ;
      }

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
        ship->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        ship->addTrait(new Model::Computer()) ;
        ship->addTrait(new Model::Laser(Model::Position(),
                                        Model::Orientation(),
                                        Model::Energy::Joule(10))) ;
        ship->addTrait(new Model::Detector(ship)) ;
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
        ship2->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        ship2->addTrait(new Model::Transponder(team1)) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        ship3->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship3->addTrait(new Model::Oriented()) ;
        ship3->addTrait(new Model::Mobile()) ;
        ship3->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
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
        ship->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        
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
        ship2->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        ship3->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship3->addTrait(new Model::Oriented()) ;
        ship3->addTrait(new Model::Mobile()) ;
        ship3->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        
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

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;
        
        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1))) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        ship->addTrait(new Model::Computer()) ;
        ship->addTrait(new Model::Laser(Model::Position::Meter(19.2,0,57),
                                              Model::Orientation(),
                                              Model::Energy::Joule(10))) ;
        
        ship->getTrait<Model::Laser>()->setShotTimeDelay(Model::Duration::Second(1)) ;
        ship->addTrait(new Model::Detector(ship,Model::Distance(Model::Distance::_Meter,5000))) ;
        ship->addTrait(new Model::Transponder(team1)) ;
        ship->addTrait(new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(ship,ship) ;
        
        ship->addTrait(new Model::ShootingHelper()) ;
        Model::ShootingHelper::connect(ship,ship,ship) ;

        ship->addTrait(new Model::Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;

        Kernel::Object* st1 = ship->createObject() ;
        st1->addTrait(new Model::Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
        st1->addTrait(new Model::Component()) ;

        Kernel::Object* st2 = ship->createObject() ;
        st2->addTrait(new Model::Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
        st2->addTrait(new Model::Component()) ;
        
        Kernel::Object* st3 = ship->createObject() ;
        st3->addTrait(new Model::Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
        st3->addTrait(new Model::Component()) ;

        Kernel::Object* stick = ship->createObject() ;
        stick->addTrait(new Model::Positionned()) ;
        stick->addTrait(new Model::Stick()) ;
        stick->addTrait(new Model::Component()) ;
        
        ship->addTrait(new Model::GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce"))) ;
        ship->addTrait(new Model::GuidanceControler()) ;
        // stick,ship
        Model::connectStickControler(stick,ship) ;
        Model::connectControlerGuidanceSystem(ship,ship) ;
        
        /// engine + engine control...
        Kernel::Object* throttle = ship->createObject() ;
        throttle->addTrait(new Model::Throttle()) ;
        throttle->addTrait(new Model::Component()) ;
        
        Kernel::Object* engine = ship->createObject() ;
        engine->addTrait(new Model::Engine(Model::Force::Newton(0,0,Kernel::Parameters::getValue<float>("Model","EngineMaxForce")))) ;
        engine->addTrait(new Model::Component()) ;

        Kernel::Object* engine_control = ship->createObject() ;
        engine_control->addTrait(new Model::EngineControler()) ;
        engine_control->addTrait(new Model::Component()) ;

        Model::connectThrottleControler(throttle,engine_control) ;
        Model::connectControlerEngine(engine_control,engine) ;                   
        
        Kernel::Object* agent = ship->createObject() ;
        agent->addTrait(new Model::AutonomousCharacter()) ;
        agent->addTrait(new Model::WithObjectives()) ;
        agent->addTrait(new Kernel::CommandDelegator()) ;
        agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
        agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
        
        
        // the attacked enemy ship
        Kernel::Object* enemy_ship = system->createObject() ;
        enemy_ship->addTrait(new Model::Positionned(Model::Position::Meter(500,0,-1500))) ;
        enemy_ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        enemy_ship->addTrait(new Model::Oriented()) ;
        enemy_ship->addTrait(new Model::Mobile()) ;
        enemy_ship->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        enemy_ship->addTrait(new Model::Transponder(team2)) ;
        enemy_ship->addTrait(new Model::Destroyable(Model::Energy::Joule(10))) ;
        enemy_ship->addTrait(new Model::Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;
        {
          Kernel::Object* st1 = enemy_ship->createObject() ;
          st1->addTrait(new Model::Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
          st1->addTrait(new Model::Component()) ;
  
          Kernel::Object* st2 = enemy_ship->createObject() ;
          st2->addTrait(new Model::Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
          st2->addTrait(new Model::Component()) ;
          
          Kernel::Object* st3 = enemy_ship->createObject() ;
          st3->addTrait(new Model::Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
          st3->addTrait(new Model::Component()) ;
        }
        
        Kernel::ObjectReference enemy(enemy_ship) ;
        
        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;
        
        for(int i = 0 ; i < 200 ; ++i)
        {
          model->update(0.1) ;
        }
        
        /// get the physical viewpoint        
        Implementation::AISystem* ai_system = model->getControlerSet<Implementation::AISystem>() ;
        CPPUNIT_ASSERT(ai_system) ;
        
        Implementation::AutonomousAgent* autonomous_agent = agent->getTrait<Implementation::AutonomousAgent>() ;
        CPPUNIT_ASSERT(autonomous_agent) ;
        
        Implementation::Agent* agent_controler = autonomous_agent->getControler<Implementation::Agent>(ai_system) ;
        CPPUNIT_ASSERT(agent_controler) ;

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

        for(int i = 0 ; i < 300 ; ++i)
        {
          model->update(0.1) ;
        }
        
        // at least one ship has been destroyed (in fact both?)
        CPPUNIT_ASSERT(!ship1 || !ship2) ;
        
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
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }          

        Kernel::ObjectReference ship2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,500,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
        }          
          
        Kernel::ObjectReference ship3 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,1100)) ;
          // enought to make it die
          ship->getTrait<Model::Destroyable>()->damage(Model::Energy::Joule(50)) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship3 = ship ;
        }

        Kernel::ObjectReference ship4 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,3000)) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship4 = ship ;
        }          
        
        // team2 is 2 against one -> it should win and destroy ship4
        
        for(int i = 0 ; i < 400 ; ++i)
        {
          model->update(0.1) ;
        }
        
        /*  
          @warning following depends a lot on initial distances
          
          team1 is grouped and team2 is dispersed, so team1 attack both ships 
          one after the other
          
        */  
        // team2 has been destroyed
        CPPUNIT_ASSERT(!ship3) ;
        CPPUNIT_ASSERT(!ship4) ;
        
        // team1 has at least one survivor
//        CPPUNIT_ASSERT(ship1 || ship2) ;
        InternalMessage("AI","AI::TestModelControler::groupAttack leaving") ;
      }
      
      void TestModelControler::testPositionUpdate()
      {
        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::testPositionUpdate")) ;
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
        
        const std::set<Implementation::Vehicle*>& vehicles1 = agent_controler1->getVehicles() ;
        CPPUNIT_ASSERT(vehicles1.size()==1) ;
        
        Implementation::Vehicle* agent1_other_vehicle = *(vehicles1.begin()) ;
        
        CPPUNIT_ASSERT(agent1_other_vehicle->getPosition() == Ogre::Vector3(0,0,-1100)) ;

        ship2->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(-1000,200,150)) ;
        InternalMessage("AI","TestModelControler::testPositionUpdate") ;

        model->update(0) ;
        
//        std::cout << agent1_other_vehicle->getPosition() ;
        CPPUNIT_ASSERT(agent1_other_vehicle->getPosition() == Ogre::Vector3(-1000,200,150)) ;
        
      }
      
      void TestModelControler::setUp()
      {
      }

      void TestModelControler::tearDown()
      {
      }
    }
  }
}
