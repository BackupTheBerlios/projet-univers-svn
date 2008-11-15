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
#include <OIS/OIS.h>
#include <kernel/timer.h>
#include <kernel/controler.h>
#include <kernel/parameters.h>
#include <display/implementation/ogre/ogre.h>
#include <input/implementation/input_internal.h>
#include <input/implementation/ois/joystick.h>
#include <input/implementation/ois/keyboard.h>
#include <input/implementation/ois/mouse.h>
#include <input/implementation/ois/ois.h>
#include <input/implementation/ois/input_controler_set.h>
#include <input/input_gui.h>
#include <input/test/test_input_system.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Input::
                                Test::
                                TestInputSystem) ;

namespace ProjetUnivers 
{
  namespace Input 
  {
    namespace Test 
    {
      
      void TestInputSystem::severalInitClose()
      {
        InternalMessage("Input","Input::TestInputSystem::severalInitClose entering") ;

        Display::Implementation::Ogre::init() ;
        Input::init() ;
        Input::close() ;
        Input::init() ;
        Input::close() ;
        Display::Implementation::Ogre::close() ;
        
        InternalMessage("Input","Input::TestInputSystem::severalInitClose leaving") ;
      }

      namespace
      {
        
        class Keyboard : public Kernel::Trait
        {};
        
        class KeyboardListener : public Kernel::Controler<Keyboard,Implementation::OIS::InputControlerSet>
        {
        public:
          
          KeyboardListener(Keyboard* object,Implementation::OIS::InputControlerSet* set)
          : Kernel::Controler<Keyboard,Implementation::OIS::InputControlerSet>(object,set)
          {}
          
          virtual void simulate(const float&) 
          {
            Implementation::OIS::Keyboard* keyboard = Implementation::OIS::getKeyboard() ;
            if (std::find(keyboard->getKeyButtonPressed().begin(),
                          keyboard->getKeyButtonPressed().end(),
                          ::OIS::KC_0) != keyboard->getKeyButtonPressed().end())
            {
              ++m_count ;
            }
            
          }
          
          static unsigned int m_count ;
        };
        
        unsigned int KeyboardListener::m_count = 0 ;
        
        RegisterControler(KeyboardListener,Keyboard,Implementation::OIS::InputControlerSet) ;
      }
      
      
      void TestInputSystem::testKeyboardAutoRepeat()
      {
        InternalMessage("Input","Input::TestInputSystem::testKeyboardAutoRepeat entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::testKeyboardAutoRepeat")) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Keyboard()) ;
        
        
        Implementation::OIS::Keyboard* keyboard = Implementation::OIS::getKeyboard() ;
        if (!keyboard)
        {
          std::cout << "warning : no keyboard found, skipping test" ;
          return ;
        }
        // send a key pressed
        ::OIS::KeyEvent keyboard_event(getOISKeyboard(),::OIS::KC_0,(unsigned int)'0') ;
        keyboard->keyPressed(keyboard_event) ;

        // count the actual interpreted key pressed events...
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;
        
        const float simulation_time = 2 ; 
        
        while (global_timer.getSecond() < simulation_time)
        {
          if (timer.getSecond() > 0.1)
          {
            model->update(timer.getSecond()) ;
            timer.reset() ;
          }
        }
        
        CPPUNIT_ASSERT(KeyboardListener::m_count == 
                       simulation_time/
                       Kernel::Parameters::getValue<float>("Input",
                                                           "AutoRepeatDelay",
                                                           Implementation::OIS::default_autorepeat_delay)) ;
        
        InternalMessage("Input","Input::TestInputSystem::testKeyboardAutoRepeat leaving") ;
        
      }

      namespace 
      {
        class Mouse : public Kernel::Trait
        {};
        
        class MouseListener : public Kernel::Controler<Mouse,Implementation::OIS::InputControlerSet>
        {
        public:
          
          MouseListener(Mouse* object,Implementation::OIS::InputControlerSet* set)
          : Kernel::Controler<Mouse,Implementation::OIS::InputControlerSet>(object,set)
          {}
          
          virtual void simulate(const float&) 
          {
            Implementation::OIS::Mouse* mouse = Implementation::OIS::getMouse() ;
            if (std::find(mouse->getKeyButtonPressed().begin(),
                          mouse->getKeyButtonPressed().end(),
                          ::OIS::MB_Right) != mouse->getKeyButtonPressed().end())
            {
              ++m_count ;
            }
            
          }
          
          static unsigned int m_count ;
        };
        
        unsigned int MouseListener::m_count = 0 ;
        
        RegisterControler(MouseListener,Mouse,Implementation::OIS::InputControlerSet) ;
        
      }
      
      void TestInputSystem::testMouseAutoRepeat()
      {
        InternalMessage("Input","Input::TestInputSystem::testMouseAutoRepeat entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::testMouseAutoRepeat")) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Mouse()) ;

        Implementation::OIS::Mouse* mouse = Implementation::OIS::getMouse() ;
        if (!mouse)
        {
          std::cout << "warning : no mouse found, skipping test" ;
          return ;
        }
        // send a key pressed
        ::OIS::MouseEvent mouse_event(NULL,::OIS::MouseState()) ;
        mouse->mousePressed(mouse_event,::OIS::MB_Right) ;
        
        // count the actual interpreted key pressed events...
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;
        
        const float simulation_time = 2 ; 
        
        while (global_timer.getSecond() < simulation_time)
        {
          if (timer.getSecond() > 0.1)
          {
            model->update(timer.getSecond()) ;
            timer.reset() ;
          }
        }

        CPPUNIT_ASSERT(MouseListener::m_count == 
                       simulation_time/
                       Kernel::Parameters::getValue<float>("Input",
                                                           "AutoRepeatDelay",
                                                           Implementation::OIS::default_autorepeat_delay)) ;
        
        InternalMessage("Input","Input::TestInputSystem::testMouseAutoRepeat leaving") ;
        
      }
      
      namespace
      {
        
        class Joystick : public Kernel::Trait
        {};
        
        class JoystickListener : public Kernel::Controler<Joystick,Implementation::OIS::InputControlerSet>
        {
        public:
          
          JoystickListener(Joystick* object,Implementation::OIS::InputControlerSet* set)
          : Kernel::Controler<Joystick,Implementation::OIS::InputControlerSet>(object,set)
          {}
          
          virtual void simulate(const float&) 
          {
            Implementation::OIS::Joystick* joystick = Implementation::OIS::getJoystick() ;
            if (std::find(joystick->getKeyButtonPressed().begin(),
                          joystick->getKeyButtonPressed().end(),
                          1) != joystick->getKeyButtonPressed().end())
            {
              ++m_count ;
            }
            
          }
          
          static unsigned int m_count ;
        };
        
        unsigned int JoystickListener::m_count = 0 ;
        
        RegisterControler(JoystickListener,Joystick,Implementation::OIS::InputControlerSet) ;
      }
      
      void TestInputSystem::testJoystickAutoRepeat()
      {
        InternalMessage("Input","Input::TestInputSystem::testJoystickAutoRepeat entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::testJoystickAutoRepeat")) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Joystick()) ;

        Implementation::OIS::Joystick* joystick = Implementation::OIS::getJoystick() ;
        if (!joystick)
        {
          std::cout << "warning : no joystick found, skipping test" ;
          return ;
        }
        // send a button pressed
        ::OIS::JoyStickEvent joystick_event(NULL,::OIS::JoyStickState()) ;
        joystick->buttonPressed(joystick_event,1) ;
        
        // count the actual interpreted key pressed events...
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;
        
        const float simulation_time = 2 ; 
        
        while (global_timer.getSecond() < simulation_time)
        {
          if (timer.getSecond() > 0.1)
          {
            model->update(timer.getSecond()) ;
            timer.reset() ;
          }
        }

        CPPUNIT_ASSERT(JoystickListener::m_count == 
                       simulation_time/
                       Kernel::Parameters::getValue<float>("Input",
                                                           "AutoRepeatDelay",
                                                           Implementation::OIS::default_autorepeat_delay)) ;
        
        InternalMessage("Input","Input::TestInputSystem::testJoystickAutoRepeat leaving") ;
      }
      
    }
  }
}

