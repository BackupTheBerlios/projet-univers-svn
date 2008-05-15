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
#include <artificial_intelligence/implementation/artificial_intelligence_internal.h>
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
        Model::init() ;

        Kernel::Object* system = Model::createObject("system") ;

        Kernel::Object* ship = Model::createObject("ship",system) ;
        Model::addTrait(ship,new Model::Positionned()) ;
        Model::addTrait(ship,new Model::Oriented()) ;
        Model::addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship,new Model::Mobile()) ;
        Model::addTrait(ship,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        Model::addTrait(ship,new Model::Computer()) ;
        Model::addTrait(ship,new Model::Laser(Model::Position(),
                                              Model::Orientation(),
                                              Model::Energy::Joule(10))) ;
        Model::addTrait(ship,new Model::Detector(ship)) ;
        Model::addTrait(ship,new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(ship,ship) ;
        
        Kernel::Object* agent = Model::createObject("pilot",ship) ;
        Model::addTrait(agent,new Model::AutonomousCharacter()) ;
        Model::addTrait(agent,new Model::WithObjectives()) ;
        Model::addTrait(agent,new Kernel::CommandDelegator()) ;
        agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
        
        Kernel::Object* ship2 = Model::createObject(system) ;
        Model::addTrait(ship2,new Model::Positionned(Model::Position::Meter(0,0,500))) ;
        Model::addTrait(ship2,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship2,new Model::Oriented()) ;
        Model::addTrait(ship2,new Model::Mobile(Model::Speed::MeterPerSecond(0,10,0))) ;
        Model::addTrait(ship2,new Model::Solid(Model::Mesh("razor.mesh"))) ;

        Kernel::Object* ship3 = Model::createObject(system) ;
        Model::addTrait(ship3,new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        Model::addTrait(ship3,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship3,new Model::Oriented()) ;
        Model::addTrait(ship3,new Model::Mobile()) ;
        Model::addTrait(ship3,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        
        Model::update(Model::Duration::Second(0.1)) ;

        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;
        
        // 2. build a AI on it
        ArtificialIntelligence::build(system) ;
        ArtificialIntelligence::init() ;
       
        InternalMessage("AI","AI::TestModelControler::build module initialised") ;
        
        // 3. check that views/controlers are built 
        Implementation::AISystem* ai_system = Implementation::getAISystem() ;
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
        Model::update(Model::Duration::Second(0.1)) ;
        
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
        Model::update(Model::Duration::Second(0.1)) ;

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

        ArtificialIntelligence::close() ;
        Model::close() ;
        
        InternalMessage("AI","AI::TestModelControler::build leaving") ;
      }

      void TestModelControler::simulate()
      {
        InternalMessage("AI","AI::TestModelControler::simulate entering") ;
        // 1. build a model
        
        Model::init() ;

        Kernel::Object* team1 = Model::createObject() ;
        Model::addTrait(team1,new Model::Team("team1")) ;
        Kernel::Object* team2 = Model::createObject() ;
        Model::addTrait(team2,new Model::Team("team2")) ;
        
        Kernel::Object* system = Model::createObject("system") ;

        Kernel::Object* ship = Model::createObject("ship",system) ;
        Model::addTrait(ship,new Model::Positionned()) ;
        Model::addTrait(ship,new Model::Oriented()) ;
        Model::addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship,new Model::Mobile()) ;
        Model::addTrait(ship,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        Model::addTrait(ship,new Model::Computer()) ;
        Model::addTrait(ship,new Model::Laser(Model::Position(),
                                              Model::Orientation(),
                                              Model::Energy::Joule(10))) ;
        Model::addTrait(ship,new Model::Detector(ship)) ;
        Model::addTrait(ship,new Model::Transponder(team1)) ;
        Model::addTrait(ship,new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(ship,ship) ;
        
        Kernel::Object* agent = Model::createObject("pilot",ship) ;
        Model::addTrait(agent,new Model::AutonomousCharacter()) ;
        Model::addTrait(agent,new Model::WithObjectives()) ;
        Model::addTrait(agent,new Kernel::CommandDelegator()) ;
        agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
        agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
        
        Kernel::Object* ship2 = Model::createObject(system) ;
        Model::addTrait(ship2,new Model::Positionned(Model::Position::Meter(0,0,500))) ;
        Model::addTrait(ship2,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship2,new Model::Oriented()) ;
        Model::addTrait(ship2,new Model::Mobile(Model::Speed::MeterPerSecond(0,10,0))) ;
        Model::addTrait(ship2,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        Model::addTrait(ship2,new Model::Transponder(team1)) ;

        Kernel::Object* ship3 = Model::createObject(system) ;
        Model::addTrait(ship3,new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        Model::addTrait(ship3,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship3,new Model::Oriented()) ;
        Model::addTrait(ship3,new Model::Mobile()) ;
        Model::addTrait(ship3,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        Model::addTrait(ship3,new Model::Transponder(team2)) ;
        
        Model::update(Model::Duration::Second(0.1)) ;

        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;
        
        // 2. build a AI on it
        ArtificialIntelligence::build(system) ;
        ArtificialIntelligence::init() ;
        ArtificialIntelligence::update(Model::Duration::Second(0.1)) ;

        // target must be ship3
        Implementation::AISystem* ai_system = Implementation::getAISystem() ;
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
        Model::init() ;

        Kernel::Object* system = Model::createObject("system") ;

        Kernel::Object* ship = Model::createObject("ship",system) ;
        Model::addTrait(ship,new Model::Positionned()) ;
        Model::addTrait(ship,new Model::Oriented()) ;
        Model::addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship,new Model::Mobile()) ;
        Model::addTrait(ship,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        
        Kernel::Object* agent = Model::createObject("pilot",ship) ;
        Model::addTrait(agent,new Model::AutonomousCharacter()) ;
        Model::addTrait(agent,new Model::WithObjectives()) ;
        Model::addTrait(agent,new Kernel::CommandDelegator()) ;
        agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
        
        Kernel::Object* ship2 = Model::createObject(system) ;
        Model::addTrait(ship2,new Model::Positionned(Model::Position::Meter(0,0,500))) ;
        Model::addTrait(ship2,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship2,new Model::Oriented()) ;
        Model::addTrait(ship2,new Model::Mobile(Model::Speed::MeterPerSecond(0,10,0))) ;
        Model::addTrait(ship2,new Model::Solid(Model::Mesh("razor.mesh"))) ;

        Kernel::Object* ship3 = Model::createObject(system) ;
        Model::addTrait(ship3,new Model::Positionned(Model::Position::Meter(500,0,500))) ;
        Model::addTrait(ship3,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship3,new Model::Oriented()) ;
        Model::addTrait(ship3,new Model::Mobile()) ;
        Model::addTrait(ship3,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        
        Model::update(Model::Duration::Second(0.1)) ;

        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;
        
        // 2. build a AI on it
        ArtificialIntelligence::build(system) ;
        ArtificialIntelligence::init() ;
       
        InternalMessage("AI","AI::TestModelControler::buildWithoutElements module initialised") ;

        ArtificialIntelligence::update(Model::Duration::Second(0.1)) ;

        InternalMessage("AI","AI::TestModelControler::buildWithoutElements leaving") ;
      }
      
      void TestModelControler::attackAllEnemies()
      {
        InternalMessage("AI","AI::TestModelControler::attackAllEnemies entering") ;
        // 1. build a model
        
        Model::init() ;
        Physic::init() ;

        Kernel::Object* team1 = Model::createObject() ;
        Model::addTrait(team1,new Model::Team("team1")) ;
        Kernel::Object* team2 = Model::createObject() ;
        Model::addTrait(team2,new Model::Team("team2")) ;
        
        Kernel::Object* system = Model::createObject("system") ;
        Model::addTrait(system,new Model::StellarSystem()) ;
        Model::addTrait(system,new Model::Positionned()) ;

        Kernel::Object* ship = Model::createObject("ship",system) ;
        Model::addTrait(ship,new Model::Positionned()) ;
        Model::addTrait(ship,new Model::Oriented()) ;
        Model::addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1))) ;
        Model::addTrait(ship,new Model::Mobile()) ;
        Model::addTrait(ship,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        Model::addTrait(ship,new Model::Computer()) ;
        Model::addTrait(ship,new Model::Laser(Model::Position::Meter(19.2,0,57),
                                              Model::Orientation(),
                                              Model::Energy::Joule(10))) ;
        
        ship->getTrait<Model::Laser>()->setShotTimeDelay(Model::Duration::Second(1)) ;
        Model::addTrait(ship,new Model::Detector(ship,Model::Distance(Model::Distance::_Meter,5000))) ;
        Model::addTrait(ship,new Model::Transponder(team1)) ;
        Model::addTrait(ship,new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(ship,ship) ;
        
        Model::addTrait(ship,new Model::ShootingHelper()) ;
        Model::ShootingHelper::connect(ship,ship,ship) ;

        Model::addTrait(ship,new Model::Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;

        Kernel::Object* st1 = Model::createObject("st1",ship) ;
        Model::addTrait(st1,new Model::Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
        Model::addTrait(st1,new Model::Component()) ;

        Kernel::Object* st2 = Model::createObject("st2",ship) ;
        Model::addTrait(st2,new Model::Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
        Model::addTrait(st2,new Model::Component()) ;
        
        Kernel::Object* st3 = Model::createObject("st3",ship) ;
        Model::addTrait(st3,new Model::Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
        Model::addTrait(st3,new Model::Component()) ;

        Kernel::Object* stick = Model::createObject("stick",ship) ;
        Model::addTrait(stick,new Model::Positionned()) ;
        Model::addTrait(stick,new Model::Stick()) ;
        Model::addTrait(stick,new Model::Component()) ;
        
        Model::addTrait(ship,new Model::GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce"))) ;
        Model::addTrait(ship,new Model::GuidanceControler()) ;
        // stick,ship
        Model::connectStickControler(stick,ship) ;
        Model::connectControlerGuidanceSystem(ship,ship) ;
        
        /// engine + engine control...
        Kernel::Object* throttle = Model::createObject("throttle",ship) ;
        Model::addTrait(throttle,new Model::Throttle()) ;
        Model::addTrait(throttle,new Model::Component()) ;
        
        Kernel::Object* engine = Model::createObject("engine",ship) ;
        Model::addTrait(engine,new Model::Engine(Model::Force::Newton(0,0,Kernel::Parameters::getValue<float>("Model","EngineMaxForce")))) ;
        Model::addTrait(engine,new Model::Component()) ;

        Kernel::Object* engine_control = Model::createObject("engine_control",ship) ;
        Model::addTrait(engine_control,new Model::EngineControler()) ;
        Model::addTrait(engine_control,new Model::Component()) ;

        Model::connectThrottleControler(throttle,engine_control) ;
        Model::connectControlerEngine(engine_control,engine) ;                   
        
        Kernel::Object* agent = Model::createObject("pilot",ship) ;
        Model::addTrait(agent,new Model::AutonomousCharacter()) ;
        Model::addTrait(agent,new Model::WithObjectives()) ;
        Model::addTrait(agent,new Kernel::CommandDelegator()) ;
        agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
        agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
        
        
        // the attacked enemy ship
        Kernel::Object* enemy_ship = Model::createObject(system) ;
        Model::addTrait(enemy_ship,new Model::Positionned(Model::Position::Meter(500,0,-1500))) ;
        Model::addTrait(enemy_ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(enemy_ship,new Model::Oriented()) ;
        Model::addTrait(enemy_ship,new Model::Mobile()) ;
        Model::addTrait(enemy_ship,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        Model::addTrait(enemy_ship,new Model::Transponder(team2)) ;
        Model::addTrait(enemy_ship,new Model::Destroyable(Model::Energy::Joule(10))) ;
        Model::addTrait(enemy_ship,new Model::Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;
        {
          Kernel::Object* st1 = Model::createObject(enemy_ship) ;
          Model::addTrait(st1,new Model::Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
          Model::addTrait(st1,new Model::Component()) ;
  
          Kernel::Object* st2 = Model::createObject(enemy_ship) ;
          Model::addTrait(st2,new Model::Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
          Model::addTrait(st2,new Model::Component()) ;
          
          Kernel::Object* st3 = Model::createObject(enemy_ship) ;
          Model::addTrait(st3,new Model::Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
          Model::addTrait(st3,new Model::Component()) ;
        }
        
        Kernel::ObjectReference enemy(enemy_ship) ;
        
        Model::PhysicalWorld* physical_world = agent->getAncestor<Model::PhysicalWorld>() ;
        CPPUNIT_ASSERT(physical_world) ;
        
        // 2. build a AI on it
        ArtificialIntelligence::build(system) ;
        ArtificialIntelligence::init() ;
        
        Physic::build(system) ;
        
        Model::Duration time = Model::Duration::Second(0.1) ;
        for(int i = 0 ; i < 200 ; ++i)
        {
          Model::update(time) ;
          Physic::update(time) ;
          ArtificialIntelligence::update(time) ;
        }
        
        Implementation::AISystem* ai_system = Implementation::getAISystem() ;
        CPPUNIT_ASSERT(ai_system) ;
        
        Implementation::AutonomousAgent* autonomous_agent = agent->getTrait<Implementation::AutonomousAgent>() ;
        CPPUNIT_ASSERT(autonomous_agent) ;
        
        Implementation::Agent* agent_controler = autonomous_agent->getControler<Implementation::Agent>(ai_system) ;
        CPPUNIT_ASSERT(agent_controler) ;

        // enemy is destroyed
        CPPUNIT_ASSERT(!enemy) ;
        
        Physic::close() ;
        InternalMessage("AI","AI::TestModelControler::attackAllEnemies leaving") ;
      }
      
      void TestModelControler::twoShips()
      {
        InternalMessage("AI","AI::TestModelControler::twoShips entering") ;

        // 1. build a model
        Model::init() ;
        Physic::init() ;

        Kernel::Object* team1 = Model::createObject() ;
        Model::addTrait(team1,new Model::Team("team1")) ;
        Kernel::Object* team2 = Model::createObject() ;
        Model::addTrait(team2,new Model::Team("team2")) ;
        
        Kernel::Object* system = Model::createObject("system") ;
        Model::addTrait(system,new Model::StellarSystem()) ;
        Model::addTrait(system,new Model::Positionned()) ;

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          Model::addTrait(ship,new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }          
          
        Kernel::ObjectReference ship2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-1100)) ;
          Model::addTrait(ship,new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
        }          

        // 2. build a AI on it
        ArtificialIntelligence::build(system) ;
        ArtificialIntelligence::init() ;
        
        Physic::build(system) ;
        
        Model::Duration time = Model::Duration::Second(0.1) ;
        for(int i = 0 ; i < 300 ; ++i)
        {
          Model::update(time) ;
          Physic::update(time) ;
          ArtificialIntelligence::update(time) ;
        }
        
        std::set<Kernel::Object*> ships = system->getChildren() ;

        // only one has been destroyed @warning depends a lot on initial distances
        CPPUNIT_ASSERT(!ship1 || !ship2) ;
        CPPUNIT_ASSERT(ships.size() == 1) ;
        
        ArtificialIntelligence::close() ;
        Physic::close() ;
        Model::close() ;

        InternalMessage("AI","AI::TestModelControler::twoShips leaving") ;
      }
      
      void TestModelControler::groupAttack()
      {
        InternalMessage("AI","AI::TestModelControler::groupAttack entering") ;

        // 1. build a model
        Model::init() ;
        Physic::init() ;

        Kernel::Object* team1 = Model::createObject() ;
        Model::addTrait(team1,new Model::Team("team1")) ;
        Kernel::Object* team2 = Model::createObject() ;
        Model::addTrait(team2,new Model::Team("team2")) ;
        
        Kernel::Object* system = Model::createObject("system") ;
        Model::addTrait(system,new Model::StellarSystem()) ;
        Model::addTrait(system,new Model::Positionned()) ;

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          Model::addTrait(ship,new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }          

        Kernel::ObjectReference ship2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,500,0)) ;
          Model::addTrait(ship,new Model::Transponder(team1)) ;
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
          Model::addTrait(ship,new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship3 = ship ;
        }

        Kernel::ObjectReference ship4 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,3000)) ;
          Model::addTrait(ship,new Model::Transponder(team2)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship4 = ship ;
        }          
        
        // team2 is 2 against one -> it should win and destroy ship4
        
        // 2. build a AI on it
        ArtificialIntelligence::build(system) ;
        ArtificialIntelligence::init() ;
        
        Physic::build(system) ;

        Model::Duration time = Model::Duration::Second(0.1) ;
        for(int i = 0 ; i < 400 ; ++i)
        {
          Model::update(time) ;
          Physic::update(time) ;
          ArtificialIntelligence::update(time) ;
        }

//        if (ship1)
//        {
//          std::cout << "ship1 life=" << ship1->getTrait<Model::Destroyable>()->getLife() << std::endl ;
//        }
//        if (ship2)
//        {
//          std::cout << "ship2 life=" << ship2->getTrait<Model::Destroyable>()->getLife() << std::endl ;
//        }
//        if (ship3)
//        {
//          std::cout << "ship3 life=" << ship3->getTrait<Model::Destroyable>()->getLife() << std::endl ;
//        }
//        if (ship4)
//        {
//          std::cout << "ship4 life=" << ship4->getTrait<Model::Destroyable>()->getLife() << std::endl ;
//        }
        
        std::set<Kernel::Object*> ships = system->getChildren() ;
        std::cout << ships.size() ;
  
        CPPUNIT_ASSERT(!ship3) ;
        CPPUNIT_ASSERT(!ship4) ;
        
        CPPUNIT_ASSERT(ships.size() == 2) ;
        
        ArtificialIntelligence::close() ;
        Physic::close() ;
        Model::close() ;

        InternalMessage("AI","AI::TestModelControler::groupAttack leaving") ;
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
