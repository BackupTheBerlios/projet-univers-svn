/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#include <kernel/parameters.h>

#include <model/active.h>
#include <model/autonomous_character.h>
#include <model/custom_mission.h>
#include <model/flying_group.h>
#include <model/mission.h>
#include <model/played.h>
#include <model/player.h>
#include <model/positioned.h>
#include <model/solid.h>
#include <model/state.h>
#include <model/team.h>
#include <model/transponder.h>
#include <model/with_lifetime.h>

#include <model/implementation/with_flying_group.h>
#include <model/implementation/activated_flying_group.h>
#include <model/implementation/activated_mission.h>
#include <model/implementation/model_internal.h>
#include <model/test/test_mission.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestMission) ;

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {

      void TestMission::closeMission()
      {
        InternalMessage("Mission","Model::TestMission::closeMission entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        root->addTrait(new Active()) ;

        Kernel::Object* menu = root->createObject() ;
        menu->addTrait(new State()) ;
        menu->setName("menu") ;

        Kernel::Object* game = root->createObject() ;
        game->addTrait(new State()) ;
        game->addTrait(new Mission("",NULL,NULL)) ;

        Kernel::Object* player = game->createObject() ;
        player->addTrait(new State()) ;

        player->getTrait<State>()->setCommandOnQuit("change(menu,Active)") ;
        player->addTrait(new WithLifetime(Duration::Second(0.1))) ;

        root->getTrait<State>()->changeState(game,new Played()) ;

        CPPUNIT_ASSERT(!menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Implementation::ActivatedMission>()) ;

        model->update(0.5) ;
        model->update(1) ;

        CPPUNIT_ASSERT(menu->getTrait<Active>()) ;
      }

      void TestMission::loadMission()
      {
        InternalMessage("Mission","Model::TestMission::loadMission entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Mission("basic_mission",NULL,NULL)) ;

        Model::loadMission("basic_mission",root,NULL,NULL) ;
      }

      void TestMission::initCustomMission()
      {
        InternalMessage("Mission","Model::TestMission::initCustomMission entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(2) ;

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,
                             system->getChildren<Implementation::WithFlyingGroup>().size()) ;

      }

      void TestMission::initCustomMissionWithPlayer()
      {
        InternalMessage("Mission","Model::TestMission::initCustomMissionWithPlayer entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(3) ;
        flying_group->getTrait<FlyingGroup>()->setHasPlayer(true) ;

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,
                             system->getChildren<Player>().size()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,
                             system->getChildren<AutonomousCharacter>().size()) ;

      }

      void TestMission::initCustomMissionWithOnePlayer()
      {
        InternalMessage("Mission","Model::TestMission::initCustomMissionWithOnePlayer entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        {
          Kernel::Object* team = mission->createObject() ;
          team->addTrait(new Team("")) ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new FlyingGroup("")) ;

          flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
          flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(3) ;
          flying_group->getTrait<FlyingGroup>()->setHasPlayer(true) ;
        }

        {
          Kernel::Object* team = mission->createObject() ;
          team->addTrait(new Team("")) ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new FlyingGroup("")) ;

          flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
          flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(3) ;
          flying_group->getTrait<FlyingGroup>()->setHasPlayer(false) ;
        }

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,
                             system->getChildren<Player>().size()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)5,
                             system->getChildren<AutonomousCharacter>().size()) ;

      }

      void TestMission::initCustomMissionShipsHaveTeam()
      {
        InternalMessage("Mission","Model::TestMission::initCustomMissionShipsHaveTeam entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(3) ;
        flying_group->getTrait<FlyingGroup>()->setHasPlayer(true) ;

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)3,
                             system->getChildren<Transponder>().size()) ;
      }

      void TestMission::initCustomMissionShipSpawnAtDistance()
      {
        InternalMessage("Mission","Model::TestMission::initCustomMissionShipSpawnAtDistance entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Distance starting_distance(Distance::_Meter,1000) ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;
        mission->getTrait<CustomMission>()->setStartingDistance(starting_distance) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("1")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(1) ;
        flying_group->getTrait<FlyingGroup>()->setHasPlayer(true) ;

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;
        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        unsigned int ship_number = system->getChildren<Transponder>().size() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,ship_number) ;

        Kernel::Object* ship1 = (*system->getChildren<Transponder>().begin())
                                ->getObject() ;

        CPPUNIT_ASSERT(ship1->getTrait<Model::Positioned>()) ;

        Position ship1_position = ship1->getTrait<Model::Positioned>()->getPosition() ;

        // add anbother team and a flying group
        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Team("2")) ;

        FlyingGroup* group = new FlyingGroup("") ;
        group->setShipName("test_ship") ;
        group->setInitialNumberOfShips(1) ;
        group->setHasPlayer(false) ;

        Kernel::Object* flying_group2 = team2->createObject() ;
        flying_group2->addTrait(group) ;

        CPPUNIT_ASSERT_EQUAL(ship_number+1,system->getChildren<Transponder>().size()) ;

        Kernel::Object* ship2 = NULL ;
        std::set<Transponder*> objects = system->getChildren<Transponder>() ;
        for(std::set<Transponder*>::const_iterator object = objects.begin() ;
            object != objects.end() && !ship2;
            ++object)
        {
          if ((*object)->getObject() != ship1)
            ship2 = (*object)->getObject() ;
        }

        CPPUNIT_ASSERT(ship2) ;
        CPPUNIT_ASSERT(ship2->getTrait<Model::Positioned>()) ;

        Position ship2_position = ship2->getTrait<Model::Positioned>()->getPosition() ;

        Distance distance = ship1_position.calculateDistance(ship2_position) ;
        CPPUNIT_ASSERT(distance >= starting_distance) ;
      }

      void TestMission::initCustomMissionShipSpawn()
      {
        InternalMessage("Mission","Model::TestMission::initCustomMissionShipSpawn entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(3) ;
        flying_group->getTrait<FlyingGroup>()->setHasPlayer(true) ;

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        // distance between ships is at least the size of the ship
        CPPUNIT_ASSERT_EQUAL((unsigned int)3,
                             system->getChildren<Transponder>().size()) ;

        std::set<Transponder*> ships = system->getChildren<Transponder>() ;
        std::set<Transponder*>::const_iterator ship = ships.begin() ;

        Position p1 = (*ship)->getObject()->getTrait<Positioned>()->getPosition() ;
        ++ship ;
        Position p2 = (*ship)->getObject()->getTrait<Positioned>()->getPosition() ;
        ++ship ;
        Position p3 = (*ship)->getObject()->getTrait<Positioned>()->getPosition() ;

        CPPUNIT_ASSERT((*ship)->getObject()->getTrait<Solid>()) ;
        Distance radius =  (*ship)->getObject()->getTrait<Solid>()->getRadius() ;

        CPPUNIT_ASSERT(p1.calculateDistance(p2) >= 2*radius) ;

      }

      void TestMission::respawn()
      {
        InternalMessage("Mission","Model::TestMission::respawn entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(2) ;
        flying_group->getTrait<FlyingGroup>()->setNumberOfSpawn(2) ;

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        std::set<Implementation::WithFlyingGroup*> ships =
          system->getChildren<Implementation::WithFlyingGroup>() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,ships.size()) ;

        for(std::set<Implementation::WithFlyingGroup*>::const_iterator
              ship = ships.begin() ;
            ship != ships.end() ;
            ++ship)
        {
          (*ship)->getObject()->destroyObject() ;
        }

        // respawn
        CPPUNIT_ASSERT_EQUAL(
            (unsigned int)2,
            system->getChildren<Implementation::WithFlyingGroup>().size()) ;

      }

      void TestMission::endOfRespawn()
      {
        InternalMessage("Mission","Model::TestMission::endOfRespawn entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(2) ;
        flying_group->getTrait<FlyingGroup>()->setNumberOfSpawn(1) ; // only one spawn

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        std::set<Implementation::WithFlyingGroup*> ships = system->getChildren<Implementation::WithFlyingGroup>() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,ships.size()) ;


        for(std::set<Implementation::WithFlyingGroup*>::const_iterator ship = ships.begin() ;
            ship != ships.end() ;
            ++ship)
        {
          (*ship)->getObject()->destroyObject() ;
        }

        // no respawn
        CPPUNIT_ASSERT_EQUAL((unsigned int)0,system->getChildren<Implementation::WithFlyingGroup>().size()) ;

      }

      void TestMission::respawnPlayer()
      {
        InternalMessage("Mission","Model::TestMission::respawnPlayer entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new CustomMission("",NULL,NULL)) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Team("")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup("")) ;

        flying_group->getTrait<FlyingGroup>()->setShipName("test_ship") ;
        flying_group->getTrait<FlyingGroup>()->setInitialNumberOfShips(2) ;
        flying_group->getTrait<FlyingGroup>()->setHasPlayer(true) ;

        CPPUNIT_ASSERT(!mission->getTrait<Mission>()->getSystem()) ;

        mission->addTrait(new Played()) ;

        Kernel::Object* system = mission->getTrait<Mission>()->getSystem() ;
        CPPUNIT_ASSERT(system) ;

        std::set<Implementation::WithFlyingGroup*> ships =
          system->getChildren<Implementation::WithFlyingGroup>() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,ships.size()) ;

        Kernel::ObjectReference player_ship ;
        Kernel::ObjectReference ai_ship ;

        for(std::set<Implementation::WithFlyingGroup*>::const_iterator ship = ships.begin() ;
            ship != ships.end() ;
            ++ship)
        {
          if (!(*ship)->getObject()->getChildren<Player>().empty())
            player_ship = (*ship)->getObject() ;
          else
            ai_ship = (*ship)->getObject() ;
        }

        // destroy player ship and check that ai_chip has now a player and no ai
        player_ship->destroyObject() ;

        CPPUNIT_ASSERT(!ai_ship->getChildren<Player>().empty()) ;
        CPPUNIT_ASSERT(ai_ship->getChildren<AutonomousCharacter>().empty()) ;
      }

      void TestMission::stopPlayingMission()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
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

        mission->addTrait(new Model::Played()) ;
        model->update(0.1) ;
        mission->destroyTrait(mission->getTrait<Model::Played>()) ;
        model->update(0.1) ;
      }

      void TestMission::endOfMissionPlayerHasLost()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Model::State()) ;
        root->addTrait(new Model::Active()) ;

        Kernel::Object* menu = root->createObject() ;
        menu->addTrait(new Model::State()) ;
        menu->setName("main_menu") ;

        Kernel::Object* mission = root->createObject() ;
        mission->addTrait(new Model::CustomMission("",NULL,NULL)) ;
        mission->getTrait<Model::CustomMission>()->setStartingDistance(Model::Distance(Model::Distance::_Meter,4000)) ;
        mission->addTrait(new Model::State()) ;
        mission->getTrait<Model::State>()->addCommandAlias("quit","change(main_menu,Active)") ;

        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Model::Team("")) ;

        Kernel::Object* flying_group1 = team1->createObject() ;
        flying_group1->addTrait(new Model::FlyingGroup("")) ;

        flying_group1->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
        flying_group1->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(1) ;
        flying_group1->getTrait<Model::FlyingGroup>()->setHasPlayer(true) ;
        flying_group1->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(2) ;

        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Model::Team("")) ;

        Kernel::Object* flying_group2 = team2->createObject() ;
        flying_group2->addTrait(new Model::FlyingGroup("")) ;

        flying_group2->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
        flying_group2->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(1) ;
        flying_group2->getTrait<Model::FlyingGroup>()->setHasPlayer(false) ;
        flying_group2->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(2) ;

        root->getTrait<Model::State>()->changeState(mission,new Model::Played()) ;
        model->update(0.1) ;
        CPPUNIT_ASSERT(mission->getTrait<Model::Played>()) ;

        std::set<Kernel::ObjectReference> ships1 = flying_group1->getTrait<Model::FlyingGroup>()->getShips() ;
        for(std::set<Kernel::ObjectReference>::iterator ship = ships1.begin() ;
            ship != ships1.end() ;
            ++ship)
        {
          if (*ship)
            (*ship)->destroyObject() ;
        }
        model->update(0.1) ;

        // we still have life
        CPPUNIT_ASSERT(mission->getTrait<Model::Played>()) ;

        ships1 = flying_group1->getTrait<Model::FlyingGroup>()->getShips() ;
        for(std::set<Kernel::ObjectReference>::iterator ship = ships1.begin() ;
            ship != ships1.end() ;
            ++ship)
        {
          (*ship)->destroyObject() ;
        }
        model->update(0.1) ;

        // no more life --> mission is over
        CPPUNIT_ASSERT(!mission->getTrait<Model::Played>()) ;
      }

      void TestMission::endOfMissionEnemiesAreDestroyed()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Model::State()) ;
        root->addTrait(new Model::Active()) ;

        Kernel::Object* menu = root->createObject() ;
        menu->addTrait(new Model::State()) ;
        menu->setName("main_menu") ;

        Kernel::ObjectReference mission = root->createObject() ;
        mission->addTrait(new Model::CustomMission("",NULL,NULL)) ;
        mission->getTrait<Model::CustomMission>()->setStartingDistance(Model::Distance(Model::Distance::_Meter,4000)) ;
        mission->addTrait(new Model::State()) ;
        mission->getTrait<Model::State>()->addCommandAlias("quit","change(main_menu,Active)") ;

        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Model::Team("")) ;

        Kernel::Object* flying_group1 = team1->createObject() ;
        flying_group1->addTrait(new Model::FlyingGroup("")) ;

        flying_group1->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
        flying_group1->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(1) ;
        flying_group1->getTrait<Model::FlyingGroup>()->setHasPlayer(true) ;
        flying_group1->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(2) ;

        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Model::Team("")) ;

        Kernel::Object* flying_group2 = team2->createObject() ;
        flying_group2->addTrait(new Model::FlyingGroup("")) ;

        flying_group2->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
        flying_group2->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(1) ;
        flying_group2->getTrait<Model::FlyingGroup>()->setHasPlayer(false) ;
        flying_group2->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(2) ;

        root->getTrait<Model::State>()->changeState(mission,new Model::Played()) ;
        model->update(0.1) ;
        CPPUNIT_ASSERT(mission->getTrait<Model::Played>()) ;

        std::set<Kernel::ObjectReference> ships1 = flying_group2->getTrait<Model::FlyingGroup>()->getShips() ;
        for(std::set<Kernel::ObjectReference>::iterator ship = ships1.begin() ;
            ship != ships1.end() ;
            ++ship)
        {
          if (*ship)
            (*ship)->destroyObject() ;
        }
        model->update(0.1) ;

        // enemies still have life
        CPPUNIT_ASSERT(mission->getTrait<Model::Played>()) ;

        ships1 = flying_group2->getTrait<Model::FlyingGroup>()->getShips() ;
        for(std::set<Kernel::ObjectReference>::iterator ship = ships1.begin() ;
            ship != ships1.end() ;
            ++ship)
        {
          (*ship)->destroyObject() ;
        }
        model->update(0.1) ;

        // enemy has no more life --> mission is over
        CPPUNIT_ASSERT(mission) ;
        CPPUNIT_ASSERT(!mission->getTrait<Model::Played>()) ;
      }

    }
  }
}
