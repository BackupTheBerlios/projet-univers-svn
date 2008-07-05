/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <input/implementation/keyboard.h>
#include <input/implementation/mouse.h>
#include <input/implementation/joystick.h>
#include <input/implementation/input_internal.h>
#include <input/input.h>

namespace ProjetUnivers {
  namespace Input {

    void start()
    {
      
    }

    namespace {
      
      /// Destroy local objects
      class OISSystem
      {  
      public:
        /// Input manager.
        OIS::InputManager* manager ;
   
        /// Keyboard
        OIS::Keyboard* keyboard ;
        
        /// Mouse
        OIS::Mouse* mouse ;
        
        OIS::JoyStick* joystick ;
        
        
        OISSystem()
        : manager(NULL), 
          keyboard(NULL),
          mouse(NULL),
          joystick(NULL)
        {}
        
        ~OISSystem()
        {
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
            OIS::InputManager::destroyInputSystem(manager) ;
          }
        }  
          
      };
    
      /// OIS element
      std::auto_ptr<OISSystem> ois ;
     
      std::auto_ptr<Implementation::Keyboard> keyboard_listener ;
      std::auto_ptr<Implementation::Mouse> mouse_listener ;
      std::auto_ptr<Implementation::Joystick> joystick_listener ;
    }

   
    void init()
    {
      InternalMessage("Input","initialising ois") ;
      
      if (ois.get())
      {
        return ;
      }
      
      ois.reset(new OISSystem()) ;
      
      OIS::ParamList parameters ;    
      size_t window_hanlde = 0;
      std::ostringstream window_hanlde_name ;

      window_hanlde = Display::getWindowHandle() ;

      InternalMessage("Input","Input::init window_handle=" + Kernel::toString(window_hanlde)) ;
      window_hanlde_name << (unsigned int) window_hanlde;
      parameters.insert(std::make_pair(
                          std::string("WINDOW"), 
                          window_hanlde_name.str())) ;

      ois->manager = OIS::InputManager::createInputSystem(parameters) ;

      // create keyboard
      ois->keyboard = static_cast<OIS::Keyboard*>(
                  ois->manager->createInputObject(OIS::OISKeyboard,true)) ;
      keyboard_listener.reset(new Implementation::Keyboard()) ;
      ois->keyboard->setEventCallback(keyboard_listener.get()) ;
      
      // create joystick
#if OIS_VERSION==0x010000      
      if (ois->manager->numJoysticks() > 0)
#else
      if (ois->manager->getNumberOfDevices(OIS::OISJoyStick) > 0)
#endif
      {
        ois->joystick = static_cast<OIS::JoyStick*>(
                    ois->manager->createInputObject(OIS::OISJoyStick,true)) ;
        joystick_listener.reset(new Implementation::Joystick()) ;      
        ois->joystick->setEventCallback(joystick_listener.get()) ;
      }
      else
      {
        InternalMessage("Input","no joystick found") ;
      }
      // create mouse
      ois->mouse = static_cast<OIS::Mouse*>(ois->manager->createInputObject(OIS::OISMouse,true)) ;
      mouse_listener.reset(new Implementation::Mouse()) ;      
      ois->mouse->setEventCallback(mouse_listener.get()) ;
      
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
    
    Implementation::Keyboard* getKeyboard()
    {
      return keyboard_listener.get() ;
    }
    
    Implementation::Mouse* getMouse()
    {
      return mouse_listener.get() ;
    }
    
    Implementation::Joystick* getJoystick()
    {
      return joystick_listener.get() ;
    }
    
    std::set<Model::PlayerConfiguration::InputEvent> getEvents()
    {
      std::set<Model::PlayerConfiguration::InputEvent> result ;
      result.insert(keyboard_listener->getEvents().begin(),
                    keyboard_listener->getEvents().end()) ;
      result.insert(mouse_listener->getEvents().begin(),
                    mouse_listener->getEvents().end()) ;
      result.insert(joystick_listener->getEvents().begin(),
                    joystick_listener->getEvents().end()) ;
      return result ;
    }
    
    std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> getAxes()
    {
      std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> result ;
      result.insert(keyboard_listener->getAxes().begin(),
                    keyboard_listener->getAxes().end()) ;
      result.insert(mouse_listener->getAxes().begin(),
                    mouse_listener->getAxes().end()) ;
      result.insert(joystick_listener->getAxes().begin(),
                    joystick_listener->getAxes().end()) ;
      return result ;
    }
    
    void apply(Model::PlayerConfiguration* configuration,Kernel::Object* object)
    {
      std::set<Model::PlayerConfiguration::InputEvent> events(getEvents()) ;
      
      for(std::set<Model::PlayerConfiguration::InputEvent>::const_iterator 
            event = events.begin() ;
          event != events.end() ;
          ++event)
      {
        std::string command = configuration->getCommand(*event) ;
        if (!command.empty())
        {
          InternalMessage("Input","applying " + command) ;
          object->call(command) ;
        }
      }
      
      std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> axes(getAxes()) ;
      
      for(std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage>::const_iterator 
            axis = axes.begin() ;
          axis != axes.end() ;
          ++axis)
      {
        std::string command = configuration->getAxis(axis->first) ;
        if (!command.empty())
        {
          InternalMessage("Input","applying " + command) ;
          object->call(command,int(axis->second)) ;
        }
        else
        {
          // try with inverted axis
          command = configuration->getAxis(-axis->first) ;
          if (!command.empty())
          {
            InternalMessage("Input","applying " + command) ;
            object->call(command,-int(axis->second)) ;
          }
        }
        
        
      }
      
    }
    
  }
}



