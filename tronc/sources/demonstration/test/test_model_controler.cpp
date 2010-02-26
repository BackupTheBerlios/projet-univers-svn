/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2009 Mathieu ROGER                                 *
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

#include <model/universe.h>
#include <model/observer.h>
#include <model/player.h>
#include <model/active.h>
#include <model/model.h>
#include <model/computer.h>
#include <model/massive.h>
#include <model/detector.h>
#include <model/positioned.h>
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
#include <model/area.h>
#include <model/head_up_display.h>
#include <model/implementation/logic/logic_system.h>

#include <physic/physic.h>

#include <artificial_intelligence/artificial_intelligence.h>
#include <artificial_intelligence/implementation/agent.h>
#include <artificial_intelligence/implementation/autonomous_agent.h>
#include <artificial_intelligence/implementation/with_vehicle_controler.h>

#include <demonstration/test/test_model_controler.h>

namespace ProjetUnivers
{
  namespace Demonstration
  {
    namespace Test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(TestModelControler) ;

      void TestModelControler::attackAllEnemies()
      {
        InternalMessage("Demonstration","Demonstration::TestModelControler::attackAllEnemies entering") ;
        // 1. build a model
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::attackAllEnemies")) ;
        model->init() ;
        InternalMessage("Demonstration","Demonstration::TestModelControler::attackAllEnemies inited") ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned(Model::Position::Meter(400,1500,-1000))) ;
        observer->addTrait(new Model::Oriented(Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(-90),::Ogre::Vector3::UNIT_X)))) ;

        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,0)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }

        // the attacked enemy ship
        Kernel::Object* enemy_ship = system->createObject() ;
        enemy_ship->addTrait(new Model::Positioned(Model::Position::Meter(500,0,-1000))) ;
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
        InternalMessage("Demonstration","Demonstration::TestModelControler::attackAllEnemies created") ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < 10)
        {
          float seconds = timer.getSecond() ;
          if (seconds > 0)
          {
            timer.reset() ;
            model->update(seconds) ;
          }
        }

        // enemy is destroyed
        CPPUNIT_ASSERT(!enemy) ;
        InternalMessage("Demonstration","Demonstration::TestModelControler::attackAllEnemies leaving") ;
      }

      void TestModelControler::basicDestroy()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::basicDestroy")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned(Model::Position::Meter(0,1000,0))) ;
        observer->addTrait(new Model::Oriented(Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(-90),::Ogre::Vector3::UNIT_X)))) ;

        /*
        Situation seen from top :

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
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(-500,0,0)) ;
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
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(1000,0,0)) ;
          ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y))) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          ship2 = ship ;
        }

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < 20)
        {
          float seconds = timer.getSecond() ;
          if (seconds > 0)
          {
            timer.reset() ;
            model->update(seconds) ;
          }
        }

        CPPUNIT_ASSERT(!ship2) ;
      }
    }
  }
}
