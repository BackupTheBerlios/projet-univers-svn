/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <OIS/OIS.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>
#include <model/player.h>
#include <model/player_configuration.h>
#include <input/implementation/input_internal.h>
#include <input/implementation/ois/keyboard.h>
#include <input/implementation/ois/ois.h>
#include <input/test/test_player_configuration.h>
#include <input/input_gui.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Input::
                                Test::
                                TestPlayerConfiguration) ;

namespace ProjetUnivers {
  namespace Input {
    namespace Test {
      
      namespace
      {
        class T1 : public Kernel::Trait
        {
        public:
          
          T1()
          : m_f_called(false)
          {}
          
          void f()
          {
            m_f_called = true ;
          }
          
          bool m_f_called ;
        };
        
        RegisterCommand("command",T1,f) ;
        
      }
      
      void TestPlayerConfiguration::testCommandMapping()
      {
        InternalMessage("Input","Input::TestPlayerConfiguration::testCommandMapping entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::testCommandMapping")) ;
        model->init() ;
        
        Kernel::Object* configuration = model->createObject() ;
        configuration->addTrait(new Model::PlayerConfiguration()) ;
        configuration->getTrait<Model::PlayerConfiguration>()->addMapping(
            Model::PlayerConfiguration::InputEvent::key(::OIS::KC_RETURN),"command") ;

        Kernel::Object* player = model->createObject() ;
        player->addTrait(new Model::Player()) ;
        player->addTrait(new T1()) ;
        Model::Player::connect(player,configuration) ;

        // inject correct key
        Implementation::OIS::getKeyboard()->keyPressed(::OIS::KeyEvent(NULL,OIS::KC_RETURN,0)) ;
        model->update(0.1) ;

        CPPUNIT_ASSERT(player->getTrait<T1>()->m_f_called) ;
        
        InternalMessage("Input","Input::TestPlayerConfiguration::testCommandMapping leaving") ;
      }

      void TestPlayerConfiguration::printInputEvent()
      {
        InternalMessage("Input","Input::TestPlayerConfiguration::printInputEvent entering") ;

        Input::init() ;
        CPPUNIT_ASSERT(getOISKeyboard()) ;

        Model::PlayerConfiguration::InputEvent event = 
          Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN) ;
        CPPUNIT_ASSERT(event.toString(getOISKeyboard())=="Return") ;
        
        Input::close() ;
        
        InternalMessage("Input","Input::TestPlayerConfiguration::printInputEvent leaving") ;
      }
      
      void TestPlayerConfiguration::setUp() 
      {
      }
      
      void TestPlayerConfiguration::tearDown() 
      {
      }

    }
  }
}

