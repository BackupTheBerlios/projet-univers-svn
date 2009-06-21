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
#include <kernel/model.h>
#include <model/model.h>
#include <model/player_configuration.h>
#include <model/test/test_player_configuration.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Model::Test::TestPlayerConfiguration) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {
        
      void TestPlayerConfiguration::testGetInputEvent()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::testGetInputEvent")) ;
        
        Kernel::Object* configuration = model->createObject() ;
        configuration->addTrait(new Model::PlayerConfiguration()) ;
        configuration->getTrait<Model::PlayerConfiguration>()->addMapping(
            Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN),"command") ;

        Model::PlayerConfiguration::InputEvent event = configuration->getTrait<Model::PlayerConfiguration>()->getInputEvent("command") ;
        CPPUNIT_ASSERT(event == Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN)) ;
      }

      void TestPlayerConfiguration::decreaseAxis()
      {
        PlayerConfiguration::InputAxis axis(PlayerConfiguration::InputAxis::JoystickY) ;
        --axis ;
        CPPUNIT_ASSERT(axis == PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::JoystickX)) ;
        --axis ;
        CPPUNIT_ASSERT(axis == PlayerConfiguration::InputAxis()) ;
      }

      void TestPlayerConfiguration::decreaseFirstAxis() 
      {
        PlayerConfiguration::InputAxis axis ;
        --axis ;
        CPPUNIT_ASSERT(axis == PlayerConfiguration::InputAxis(-PlayerConfiguration::InputAxis::JoystickX)) ;
      }

      void TestPlayerConfiguration::increaseAxis()
      {
        PlayerConfiguration::InputAxis axis ;
        ++axis ;
        CPPUNIT_ASSERT(axis == PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::JoystickX)) ;
        ++axis ;
        CPPUNIT_ASSERT(axis == PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::JoystickY)) ;
      }

      void TestPlayerConfiguration::increaseLastAxis() 
      {
        PlayerConfiguration::InputAxis axis(PlayerConfiguration::InputAxis::MouseWheel) ;
        ++axis ;
        CPPUNIT_ASSERT(axis == PlayerConfiguration::InputAxis(-PlayerConfiguration::InputAxis::MouseWheel)) ;
      }
      
      void TestPlayerConfiguration::invertedAxisPrint()
      {
        PlayerConfiguration::InputAxis axis(-PlayerConfiguration::InputAxis::MouseWheel) ;
        CPPUNIT_ASSERT_EQUAL(std::string("Inverted Mouse Wheel"),axis.toString()) ;
      }
      
      void TestPlayerConfiguration::normalAxisPrint()
      {
        PlayerConfiguration::InputAxis axis(PlayerConfiguration::InputAxis::JoystickThrottle) ;
        CPPUNIT_ASSERT_EQUAL(std::string("Joystick Throttle"),axis.toString()) ;
      }
      
      void TestPlayerConfiguration::changeAxisMapping()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::changeAxisMapping")) ;
        
        Kernel::Object* configuration = model->createObject() ;
        configuration->addTrait(new Model::PlayerConfiguration()) ;
        Model::PlayerConfiguration* player_configuration = configuration->getTrait<Model::PlayerConfiguration>() ;
        Model::PlayerConfiguration::InputAxis axis ;
        player_configuration->addMapping(axis,"axis") ;
        
        --axis ;
        player_configuration->addMapping(axis,"axis") ;

        CPPUNIT_ASSERT(axis == player_configuration->getInputAxis("axis")) ;
      }
      
      void TestPlayerConfiguration::cycleThoughAxesMapping()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::cycleThoughAxesMapping")) ;
        
        Kernel::Object* configuration = model->createObject() ;
        Model::PlayerConfiguration* player_configuration = new Model::PlayerConfiguration() ;
        configuration->addTrait(player_configuration) ;
        
        player_configuration->addMapping(Model::PlayerConfiguration::InputAxis::MouseX,"X") ;
        player_configuration->addMapping(Model::PlayerConfiguration::InputAxis::MouseY,"Y") ;

        // we cycle as in the version of gui...
        player_configuration->addMapping(Model::PlayerConfiguration::InputAxis::MouseY,"X") ;
        player_configuration->addMapping(Model::PlayerConfiguration::InputAxis::JoystickThrottle,"X") ;

        CPPUNIT_ASSERT_EQUAL(std::string("Y"), 
                             player_configuration->getAxis(Model::PlayerConfiguration::InputAxis::MouseY)) ;
      }
      
      void TestPlayerConfiguration::axisViolation()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::axisViolation")) ;
        
        Kernel::Object* configuration = model->createObject() ;
        Model::PlayerConfiguration* player_configuration = new Model::PlayerConfiguration() ;
        configuration->addTrait(player_configuration) ;

        player_configuration->addMapping(Model::PlayerConfiguration::InputAxis::MouseX,"X") ;
        player_configuration->addMapping(Model::PlayerConfiguration::InputAxis::MouseY,"Y") ;
        
        CPPUNIT_ASSERT(player_configuration->getViolatingAxes() == std::set<std::string>()) ;
        CPPUNIT_ASSERT(player_configuration->getViolatingCommands() == std::set<std::string>()) ;
        
        player_configuration->addMapping(Model::PlayerConfiguration::InputAxis::MouseY,"X") ;

        std::set<std::string> all_violation ;
        all_violation.insert("X") ;
        all_violation.insert("Y") ;
        
        CPPUNIT_ASSERT(player_configuration->getViolatingAxes() == all_violation) ;
        CPPUNIT_ASSERT(player_configuration->getViolatingCommands() == std::set<std::string>()) ;
      }
      
      void TestPlayerConfiguration::commandViolation()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::commandViolation")) ;
        
        Kernel::Object* configuration = model->createObject() ;
        Model::PlayerConfiguration* player_configuration = new Model::PlayerConfiguration() ;
        configuration->addTrait(player_configuration) ;

        player_configuration->addMapping(Model::PlayerConfiguration::InputEvent::joystickButton(1),"X") ;
        player_configuration->addMapping(Model::PlayerConfiguration::InputEvent::mouseButton(2),"Y") ;
        
        CPPUNIT_ASSERT(player_configuration->getViolatingCommands() == std::set<std::string>()) ;
        CPPUNIT_ASSERT(player_configuration->getViolatingAxes() == std::set<std::string>()) ;
        
        player_configuration->addMapping(Model::PlayerConfiguration::InputEvent::mouseButton(2),"X") ;

        std::set<std::string> all_violation ;
        all_violation.insert("X") ;
        all_violation.insert("Y") ;
        
        CPPUNIT_ASSERT(player_configuration->getViolatingCommands() == all_violation) ;
        CPPUNIT_ASSERT(player_configuration->getViolatingAxes() == std::set<std::string>()) ;
      }
      
      void TestPlayerConfiguration::invertAxis()
      {
        Model::PlayerConfiguration::InputAxis axis(Model::PlayerConfiguration::InputAxis::MouseX) ;
        
        CPPUNIT_ASSERT(-axis == Model::PlayerConfiguration::InputAxis(-Model::PlayerConfiguration::InputAxis::MouseX)) ;
      }
      
    }
  }
}
