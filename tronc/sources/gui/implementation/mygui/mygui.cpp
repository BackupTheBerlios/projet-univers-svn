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
#include <MyGUI.h>
#include <Ogre.h>

#include <display/display.h>
#include <display/display_gui.h>
#include <display/display_input.h>

#include <input/input.h>
#include <input/input_gui.h>
#include <input/input_listener.h>

#include <gui/implementation/mygui/scripting_module.h>
#include <gui/implementation/mygui/mygui.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace MyGUI 
      { 
        
        class GUISystem : public Input::InputListener
        {
        public:
          
          GUISystem()
          {
            m_number_of_active_guis = 0 ;
            
            manager = ::Ogre::Root::getSingleton().createSceneManager(::Ogre::ST_GENERIC) ;
            camera = manager->createCamera("gui") ;
            viewport = Display::getWindow()->addViewport(camera,500) ;

            MyGUISystem = new ::MyGUI::Gui() ;
            MyGUISystem->initialise(Display::getWindow()) ;
            
            // because we use several scene managers
            ::MyGUI::LayerManager::getInstance().setSceneManager(manager) ;
//            m_window = MyGUISystem->createWidgetRealT("Widget","Widget",::MyGUI::FloatCoord(0,0,1,1),::MyGUI::ALIGN_DEFAULT,"Back") ;
            // register to input
            Input::setGUIInputListener(this) ;
          }

          ~GUISystem()
          {
            Display::getWindow()->removeViewport(500) ;
            manager->destroyCamera(camera) ;
            ::Ogre::Root::getSingleton().destroySceneManager(manager) ;
            delete MyGUISystem ;
          }
          
          ::MyGUI::Gui* MyGUISystem ;

          /// Special scene manager for gui 
          ::Ogre::SceneManager* manager ;
          
          /// Special camera for gui
          ::Ogre::Camera* camera ;
          
          ::Ogre::Viewport* viewport ;
          
          /// interpretes commands
          ScriptingModule m_scripting_module ;
          
          /// Main window
          ::MyGUI::Widget* m_window ;
          
          /// current number of active guis. 
          unsigned int m_number_of_active_guis ;

          virtual void injectKeyPressed(int key_code)
          {
            MyGUISystem->injectKeyPress(::MyGUI::KeyCode(key_code)) ;
          }
          
          virtual void injectKeyReleased(int key_code)
          {
            MyGUISystem->injectKeyRelease(::MyGUI::KeyCode(key_code)) ;
          }
          
          virtual void injectChar(unsigned int key_char)
          {
            
          }
          
          int m_mouse_x ;
          int m_mouse_y ;
          
          virtual void injectMousePosition(int x,int y, int z)
          {
            MyGUISystem->injectMouseMove(x,y,z) ;
            m_mouse_x = x ;
            m_mouse_y = y ;
          }

          virtual void injectMousePressed(int button)
          {
            MyGUISystem->injectMousePress(m_mouse_x,m_mouse_y,::MyGUI::MouseButton(button)) ;
          }

          virtual void injectMouseReleased(int button) 
          {
            MyGUISystem->injectMouseRelease(m_mouse_x,m_mouse_y,::MyGUI::MouseButton(button)) ;
          }
          
        };
          
        std::auto_ptr<GUISystem> system ;
        
        void start()
        {
          Display::start() ;
          Input::start() ;
          
          if (! system.get())
            system.reset(new GUISystem()) ;
        }
        
        void terminate()
        {
          system.reset(NULL) ;
        }
        
        ::MyGUI::Gui* getWindowManager()
        {
          return system->MyGUISystem ;
        }
        
        ::MyGUI::Widget* getMainWindow()
        {
          return system->m_window ;
        }
        
        void addActiveGUI(::MyGUI::VectorWidgetPtr window)
        {
          // mouse cursor
          if (system->m_number_of_active_guis == 0)
          {
            system->MyGUISystem->showPointer() ;
          }
          ++system->m_number_of_active_guis ;
          
          system->m_scripting_module.makeBinding(window) ;
          for(std::vector< ::MyGUI::WidgetPtr >::const_iterator widget = window.begin() ;
              widget != window.end() ;
              ++widget)
          {
            ::MyGUI::LayerManager::getInstance().attachToLayerKeeper("Back",*widget) ;
          }

        }

        void removeActiveGUI(::MyGUI::VectorWidgetPtr window)
        {
          --system->m_number_of_active_guis ;
          if (system->m_number_of_active_guis == 0)
          {
            system->MyGUISystem->hidePointer() ;
          }
          system->m_scripting_module.removeBinding(window) ;
          getWindowManager()->destroyWidgetsVector(window) ;
        }

//        ::MyGUI::Widget* getRoot(::MyGUI::Widget* window)
//        {
//          ::MyGUI::Widget* parent = window->getParent() ;
//          if (parent)
//            return getRoot(parent) ;
//          else
//            return window ;
//        }
//        
//        ::MyGUI::Widget* getNamedDescendant(::MyGUI::Widget* window,const std::string& name)
//        {
//          if (window->getName() == name)
//          {
//            return window ;
//          }
//          else
//          {
//            for(int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
//            {
//              ::MyGUI::Widget* child = window->getChildAtIdx(child_index) ;
//              ::MyGUI::Widget* result = getNamedDescendant(child,name) ;
//              if (result)
//              {
//                return result ;
//              }
//            }
//          }
//          
//          return NULL ;
//        }
//
//        ::MyGUI::Widget* getTypedDescendant(::MyGUI::Widget* window,const std::string& type)
//        {
//          if (window->getType() == type)
//          {
//            return window ;
//          }
//          else
//          {
//            for(int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
//            {
//              ::MyGUI::Widget* child = window->getChildAtIdx(child_index) ;
//              ::MyGUI::Widget* result = getTypedDescendant(child,type) ;
//              if (result)
//              {
//                return result ;
//              }
//            }
//          }
//          
//          return NULL ;
//        }
        
      }
    }    
  }
}
