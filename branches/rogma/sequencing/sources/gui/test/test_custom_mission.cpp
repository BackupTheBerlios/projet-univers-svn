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
#include <CEGUI.h>
#include <CEGUIExceptions.h>

#include <kernel/model.h>
#include <kernel/timer.h>
#include <kernel/parameters.h>

#include <model/model.h>
#include <model/edited.h>
#include <model/player.h>
#include <model/player_configuration.h>
#include <model/positionned.h>
#include <model/displayed.h>
#include <model/custom_mission.h>
#include <model/team.h>
#include <model/flying_group.h>

#include <display/implementation/ogre/ogre.h>

#include <input/input_gui.h>
#include <input/implementation/input_internal.h>

#include <gui/implementation/edited_custom_mission.h>
#include <gui/implementation/edited_team.h>
#include <gui/implementation/cegui/gui_controler_set.h>
#include <gui/implementation/cegui/custom_mission.h>
#include <gui/implementation/cegui/flying_group.h>
#include <gui/implementation/cegui/team.h>
#include <gui/implementation/cegui/cegui.h>
#include <gui/test/test_custom_mission.h>


//CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
//                                GUI::
//                                Test::
//                                TestCustomMission) ;

namespace ProjetUnivers
{
  namespace GUI
  {
    namespace Test
    {

      void TestCustomMission::moveDownTeamWindows()
      {
        InternalMessage("CustomMission","GUI::TestCustomMission::moveDownTeamWindows entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::moveDownTeamWindows")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Model::Team("team 1")) ;

        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Model::Team("team 2")) ;

        Kernel::Object* team3 = mission->createObject() ;
        team3->addTrait(new Model::Team("team 3")) ;

        Implementation::CEGUI::CustomMission* custom_mission =
          mission->getTrait<Implementation::EditedCustomMission>()
                 ->getControler<Implementation::CEGUI::CustomMission>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        Implementation::CEGUI::Team* team1_controler =
          team1->getTrait<Implementation::EditedTeam>()
               ->getControler<Implementation::CEGUI::Team>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        Implementation::CEGUI::Team* team2_controler =
          team2->getTrait<Implementation::EditedTeam>()
               ->getControler<Implementation::CEGUI::Team>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        ::CEGUI::UVector2 position = team2_controler->m_window->getArea().getPosition() ;
        ::CEGUI::UVector2 delta(::CEGUI::UDim(0,0),::CEGUI::UDim(0.1,0)) ;

        Implementation::CEGUI::moveDownWindows(custom_mission->m_team_windows,
                                               team1_controler->m_window,
                                               ::CEGUI::UDim(0.1,0)) ;

        ::CEGUI::UVector2 expected = position+delta ;

        CPPUNIT_ASSERT(expected == team2_controler->m_window->getArea().getPosition()) ;
      }

      void TestCustomMission::moveUpTeamWindows()
      {
        InternalMessage("CustomMission","GUI::TestCustomMission::moveUpTeamWindows entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::moveUpTeamWindows")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Model::Team("team 1")) ;

        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Model::Team("team 2")) ;

        Kernel::Object* team3 = mission->createObject() ;
        team3->addTrait(new Model::Team("team 3")) ;

        Implementation::CEGUI::CustomMission* custom_mission =
          mission->getTrait<Implementation::EditedCustomMission>()
                 ->getControler<Implementation::CEGUI::CustomMission>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        Implementation::CEGUI::Team* team1_controler =
          team1->getTrait<Implementation::EditedTeam>()
               ->getControler<Implementation::CEGUI::Team>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        Implementation::CEGUI::Team* team2_controler =
          team2->getTrait<Implementation::EditedTeam>()
               ->getControler<Implementation::CEGUI::Team>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        ::CEGUI::UVector2 position = team2_controler->m_window->getArea().getPosition() ;
        ::CEGUI::UVector2 delta(::CEGUI::UDim(0,0),::CEGUI::UDim(0.1,0)) ;

        Implementation::CEGUI::moveUpWindows(custom_mission->m_team_windows,
                                             team1_controler->m_window,
                                             ::CEGUI::UDim(0.1,0)) ;

        ::CEGUI::UVector2 expected = position-delta ;

        CPPUNIT_ASSERT(expected == team2_controler->m_window->getArea().getPosition()) ;
      }

      void TestCustomMission::addTeamWindow()
      {
        InternalMessage("CustomMission","GUI::TestCustomMission::addTeamWindow entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::addTeamWindow")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team 1")) ;

        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team 2")) ;

        Implementation::CEGUI::CustomMission* custom_mission =
          mission->getTrait<Implementation::EditedCustomMission>()
                 ->getControler<Implementation::CEGUI::CustomMission>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        ::CEGUI::Window* team1_window = custom_mission->addTeamWindow(team1) ;

        CPPUNIT_ASSERT(::CEGUI::UDim(0,0) == team1_window->getYPosition()) ;

        ::CEGUI::Window* team2_window = custom_mission->addTeamWindow(team2) ;

        // next one is placed just after
        CPPUNIT_ASSERT(team1_window->getYPosition()+team1_window->getHeight() ==
                       team2_window->getYPosition()) ;
      }

      void TestCustomMission::addTeam()
      {
        InternalMessage("CustomMission","GUI::TestCustomMission::addTeam entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::addTeam")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Implementation::CEGUI::CustomMission* custom_mission =
          mission->getTrait<Implementation::EditedCustomMission>()
                 ->getControler<Implementation::CEGUI::CustomMission>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        custom_mission->addTeam(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(size_t(1),mission->getChildren().size()) ;
      }

      void TestCustomMission::createFlyingGroup()
      {
        InternalMessage("CustomMission","GUI::TestCustomMission::createFlyingGroup entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::createFlyingGroup")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        Implementation::CEGUI::Team* team_gui =
        team->getTrait<Implementation::EditedTeam>()
            ->getControler<Implementation::CEGUI::Team>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui->m_window->getParent()==team_gui->m_window) ;
      }

      void TestCustomMission::destroyFlyingGroup()
      {
        InternalMessage("CustomMission","GUI::TestCustomMission::destroyFlyingGroup entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::destroyFlyingGroup")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;

        Implementation::CEGUI::Team* team_gui =
        team->getTrait<Implementation::EditedTeam>()
            ->getControler<Implementation::CEGUI::Team>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;


        unsigned int number_of_children = team_gui->m_window->getChildCount() ;

        group_gui->deleteGroup(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(team_gui->m_window->getChildCount(),number_of_children-1) ;
      }

      void TestCustomMission::close()
      {
        InternalMessage("CustomMission","GUI::TestCustomMission::close entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::close")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;

        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Model::Team("team 1")) ;

        Kernel::Object* flying_group = team1->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;

        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Model::Team("team 2")) ;

        Kernel::Object* team3 = mission->createObject() ;
        team3->addTrait(new Model::Team("team 3")) ;

        mission->addTrait(new Model::Edited()) ;

        model->update(0.1) ;

        mission->destroyTrait(mission->getTrait<Model::Edited>()) ;

        CPPUNIT_ASSERT(!flying_group->getTrait<Implementation::EditedFlyingGroup>()) ;
      }

      void TestCustomMission::changeTeamName()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::changeTeamName")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;

        Implementation::CEGUI::Team* team_gui =
        team->getTrait<Implementation::EditedTeam>()
            ->getControler<Implementation::CEGUI::Team>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(team_gui) ;
        CPPUNIT_ASSERT(team_gui->m_window) ;

        ::CEGUI::Window* name = Implementation::CEGUI::getTypedDescendant(
            team_gui->m_window,"ProjetUnivers/Editbox") ;

        CPPUNIT_ASSERT(name) ;

        name->setText("new name") ;

        CPPUNIT_ASSERT_EQUAL(std::string("new name"),
                             team->getTrait<Model::Team>()->getName()) ;

      }

      void TestCustomMission::changeFlyingGroupName()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::changeFlyingGroupName")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* name = Implementation::CEGUI::getTypedDescendant(
            group_gui->m_window,"ProjetUnivers/Editbox") ;

        CPPUNIT_ASSERT(name) ;

        name->setText("new name") ;

        CPPUNIT_ASSERT_EQUAL(std::string("new name"),
                             flying_group->getTrait<Model::FlyingGroup>()->getName()) ;
      }

      void TestCustomMission::setInitialNumberOfShips()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::setInitialNumberOfShips")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(10) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_ships = group_gui->m_number_of_ships ;
        CPPUNIT_ASSERT(number_of_ships) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(10),std::string(number_of_ships->getText().c_str())) ;
      }

      void TestCustomMission::increaseInitialNumberOfShips()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::increaseInitialNumberOfShips")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(10) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_ships = group_gui->m_number_of_ships ;
        CPPUNIT_ASSERT(number_of_ships) ;

        group_gui->increaseNumberOfShips(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(11),
                             std::string(number_of_ships->getText().c_str())) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)11,
                             flying_group->getTrait<Model::FlyingGroup>()->getInitialNumberOfShips()) ;
      }

      void TestCustomMission::decreaseInitialNumberOfShips()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::decreaseInitialNumberOfShips")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(10) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_ships = group_gui->m_number_of_ships ;
        CPPUNIT_ASSERT(number_of_ships) ;

        group_gui->decreaseNumberOfShips(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(9),
                             std::string(number_of_ships->getText().c_str())) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)9,
                             flying_group->getTrait<Model::FlyingGroup>()->getInitialNumberOfShips()) ;
      }

      void TestCustomMission::decreaseInitialNumberOfShipsEqualOne()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::decreaseInitialNumberOfShips")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(1) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_ships = group_gui->m_number_of_ships ;
        CPPUNIT_ASSERT(number_of_ships) ;

        group_gui->decreaseNumberOfShips(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(1),
                             std::string(number_of_ships->getText().c_str())) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,
                             flying_group->getTrait<Model::FlyingGroup>()->getInitialNumberOfShips()) ;
       }

      void TestCustomMission::setNumberOfSpawn()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::setNumberOfSpawn")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(10) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_spawn = group_gui->m_number_of_spawn ;
        CPPUNIT_ASSERT(number_of_spawn) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(10),std::string(number_of_spawn->getText().c_str())) ;
      }

      void TestCustomMission::increaseNumberOfSpawn()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::increaseNumberOfSpawn")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(10) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_spawn = group_gui->m_number_of_spawn ;
        CPPUNIT_ASSERT(number_of_spawn) ;

        group_gui->increaseNumberOfSpawn(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(11),
                             std::string(number_of_spawn->getText().c_str())) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)11,
                             flying_group->getTrait<Model::FlyingGroup>()->getNumberOfSpawn()) ;
      }

      void TestCustomMission::decreaseNumberOfSpawn()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::increaseNumberOfSpawn")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(10) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_spawn = group_gui->m_number_of_spawn ;
        CPPUNIT_ASSERT(number_of_spawn) ;

        group_gui->decreaseNumberOfSpawn(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(9),
                             std::string(number_of_spawn->getText().c_str())) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)9,
                             flying_group->getTrait<Model::FlyingGroup>()->getNumberOfSpawn()) ;
      }

      void TestCustomMission::decreaseNumberOfSpawnEqualOne()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::increaseNumberOfSpawn")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(1) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* number_of_spawn = group_gui->m_number_of_spawn ;
        CPPUNIT_ASSERT(number_of_spawn) ;

        group_gui->decreaseNumberOfSpawn(::CEGUI::EventArgs()) ;

        CPPUNIT_ASSERT_EQUAL(Kernel::toString(1),
                             std::string(number_of_spawn->getText().c_str())) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,
                             flying_group->getTrait<Model::FlyingGroup>()->getNumberOfSpawn()) ;

      }

      void TestCustomMission::hasPlayer()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::increaseNumberOfSpawn")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setHasPlayer(true) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* pilot = group_gui->m_pilot ;
        CPPUNIT_ASSERT(pilot) ;
        CPPUNIT_ASSERT_EQUAL(std::string("Player"),
                             std::string(pilot->getText().c_str())) ;
      }

      void TestCustomMission::hasNotPlayer()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCustomMission::increaseNumberOfSpawn")) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("test",NULL,NULL)) ;
        mission->addTrait(new Model::Edited()) ;

        Kernel::Object* team = mission->createObject() ;
        team->addTrait(new Model::Team("test")) ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new Model::FlyingGroup("test")) ;
        flying_group->getTrait<Model::FlyingGroup>()->setHasPlayer(false) ;

        Implementation::CEGUI::FlyingGroup* group_gui =
        flying_group->getTrait<Implementation::EditedFlyingGroup>()
                    ->getControler<Implementation::CEGUI::FlyingGroup>(model->getControlerSet<Implementation::CEGUI::GUIControlerSet>()) ;

        CPPUNIT_ASSERT(group_gui) ;
        CPPUNIT_ASSERT(group_gui->m_window) ;

        ::CEGUI::Window* pilot = group_gui->m_pilot ;
        CPPUNIT_ASSERT(pilot) ;
        CPPUNIT_ASSERT_EQUAL(std::string("AI"),
                             std::string(pilot->getText().c_str())) ;
      }


    }
  }
}

