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
#include <sstream>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISJoyStick.h>
#include <OIS/OISInputManager.h>

#include <kernel/log.h>
#include <kernel/string.h>
#include <display/display_input.h>
#include <display/display.h>
#include <input/implementation/ois/keyboard.h>
#include <input/implementation/ois/mouse.h>
#include <input/implementation/ois/joystick.h>
#include <input/implementation/input_internal.h>
#include <input/implementation/ois/ois.h>

namespace ProjetUnivers 
{
  namespace Input 
  {
    namespace Implementation 
    {
      namespace OIS 
      {
      
        namespace {
          
          /// Destroy local objects
          class OISSystem
          {  
          public:
            /// Input manager.
            ::OIS::InputManager* manager ;
       
            /// Keyboard
            ::OIS::Keyboard* keyboard ;
            
            /// Mouse
            ::OIS::Mouse* mouse ;
            
            ::OIS::JoyStick* joystick ;
            
            Keyboard* keyboard_listener ;
            Mouse*    mouse_listener ;
            Joystick* joystick_listener ;
            
            OISSystem()
            : manager(NULL), 
              keyboard(NULL),
              mouse(NULL),
              joystick(NULL),
              keyboard_listener(NULL),
              mouse_listener(NULL),
              joystick_listener(NULL)
            {}
            
            ~OISSystem()
            {
              if (keyboard_listener)
              {
                delete keyboard_listener ;
                keyboard_listener = NULL ;
              }
              
              if (mouse_listener)
              {
                delete mouse_listener ;
                mouse_listener = NULL ;
              }

              if (joystick_listener)
              {
                delete joystick_listener ;
                joystick_listener = NULL ;
              }

              if (manager)
              {
                if (keyboard) 
                {
                  manager->destroyInputObject(keyboard) ;
                  keyboard = NULL ;
                }
                if (mouse)
                {
                  manager->destroyInputObject(mouse) ;
                  mouse = NULL ;
                }
                if (joystick)
                {
                  manager->destroyInputObject(joystick) ;
                  joystick = NULL ;
                }
                ::OIS::InputManager::destroyInputSystem(manager) ;
              }
            }  
              
          };
        
          /// OIS element
          std::auto_ptr<OISSystem> ois ;
         
        }

        void init()
        {
          InternalMessage("Input","initialising ois") ;
          
          if (ois.get())
          {
            return ;
          }
          
          ois.reset(new OISSystem()) ;
          
          ::OIS::ParamList parameters ;    
          size_t window_hanlde = 0;
          std::ostringstream window_hanlde_name ;

          Display::start() ;
          
          window_hanlde = Display::getWindowHandle() ;

          InternalMessage("Input","Input::init window_handle=" + Kernel::toString(window_hanlde)) ;
          window_hanlde_name << (unsigned int) window_hanlde;
          parameters.insert(std::make_pair(
                              std::string("WINDOW"), 
                              window_hanlde_name.str())) ;

          ois->manager = ::OIS::InputManager::createInputSystem(parameters) ;

          // create keyboard
          ois->keyboard = static_cast< ::OIS::Keyboard*>(
                      ois->manager->createInputObject(::OIS::OISKeyboard,true)) ;
          ois->keyboard_listener = new Keyboard() ;
          ois->keyboard->setEventCallback(ois->keyboard_listener) ;
          
          // create joystick
    #if OIS_VERSION==0x010000      
          if (ois->manager->numJoysticks() > 0)
    #else
          if (ois->manager->getNumberOfDevices(::OIS::OISJoyStick) > 0)
    #endif
          {
            ois->joystick = static_cast< ::OIS::JoyStick*>(
                        ois->manager->createInputObject(::OIS::OISJoyStick,true)) ;
            ois->joystick_listener = new Joystick() ;      
            ois->joystick->setEventCallback(ois->joystick_listener) ;
            
            InternalMessage("Input","initialised joystick id " + 
                                    Kernel::toString(ois->joystick->getID()) + 
                                    " vendor " + ois->joystick->vendor()) ;
          }
          else
          {
            InternalMessage("Input","no joystick found") ;
          }
          // create mouse
          ois->mouse = static_cast< ::OIS::Mouse*>(ois->manager->createInputObject(::OIS::OISMouse,true)) ;
          ois->mouse_listener = new Mouse() ;      
          ois->mouse->setEventCallback(ois->mouse_listener) ;
          
        }       
        
        void close()
        {
          InternalMessage("Input","closing ois") ;
          ois.reset() ;
        }

        void update()
        {
          /// capture all system objects
          if (!ois.get())
          {
            ErrorMessage("Input::update no ois system") ;
            return ;
          }
          if (ois->keyboard)
            ois->keyboard->capture() ;
          if (ois->joystick)
            ois->joystick->capture() ;
          if (ois->mouse)
            ois->mouse->capture() ;
        }

        ::OIS::Keyboard* getOISKeyboard()
        {
          return ois->keyboard ;
        }
        
        Keyboard* getKeyboard()
        {
          return ois->keyboard_listener ;
        }
        
        Mouse* getMouse()
        {
          return ois->mouse_listener ;
        }
        
        Joystick* getJoystick()
        {
          return ois->joystick_listener ;
        }
        
        void start()
        {
          init() ;
        }
        
        void terminate()
        {
          
        }
      
      }
    }
  }
}
