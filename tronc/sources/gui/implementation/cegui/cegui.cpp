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
#include <Ogre.h>
#include <OgreCEGUIRenderer.h>


#include <gui/implementation/cegui/command_interpretor.h>
#include <gui/implementation/cegui/scripting_module.h>

#include <display/display.h>
#include <display/display_gui.h>
#include <display/display_input.h>
#include <input/input.h>
#include <input/input_gui.h>
#include <input/input_listener.h>

#include <gui/implementation/cegui/cegui.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace CEGUI 
      { 
        
        /// Manage the GUI.
        class GUISystem : public Input::InputListener
        {
        public:
          
          GUISystem()
          {
            command_interpretor.reset(new ScriptingModule()) ;

            m_number_of_active_guis= 0 ;
            
            CEGUIRenderer = new ::CEGUI::OgreCEGUIRenderer(Display::getWindow()) ;
            
            CEGUISystem = new ::CEGUI::System(CEGUIRenderer) ;
            CEGUISystem->setScriptingModule(command_interpretor.get()) ;

            manager = ::Ogre::Root::getSingleton().createSceneManager(::Ogre::ST_GENERIC) ;
            CEGUIRenderer->setTargetSceneManager(manager) ;

            camera = manager->createCamera("gui") ;
            ::Ogre::Viewport* viewport = Display::getWindow()->addViewport(camera,500) ;
            
            // so it is transparent
            viewport->setClearEveryFrame(false) ;
            
            ::CEGUI::Logger::getSingleton().setLoggingLevel(::CEGUI::Informative) ;

            // cegui 
            ::CEGUI::Imageset::setDefaultResourceGroup("imagesets");
            ::CEGUI::Font::setDefaultResourceGroup("fonts");
            ::CEGUI::Scheme::setDefaultResourceGroup("schemes");
            ::CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
            ::CEGUI::WindowManager::setDefaultResourceGroup("layouts");
            ::CEGUI::SchemeManager::getSingleton().loadScheme("ProjetUnivers.scheme") ;

            ::CEGUI::System::getSingleton().setDefaultMouseCursor("ProjetUnivers", "PointerMouse") ;
            ::CEGUI::MouseCursor::getSingleton().setImage("ProjetUnivers", "PointerMouse");        
            ::CEGUI::MouseCursor::getSingleton().hide() ;
            
            // useless if scheme contains a font reference.
            ::CEGUI::FontManager::getSingleton().createFont("bluehighway-12.font") ;
            
            // create a default window
            m_window = ::CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","System") ;

            // register to input
            Input::setGUIInputListener(this) ;
          }
            
          ::CEGUI::System* CEGUISystem ;
          ::CEGUI::OgreCEGUIRenderer* CEGUIRenderer ;

          /// Special scene manager for gui injectMouseButtonDown
          ::Ogre::SceneManager* manager ;
          
          /// Special camera for gui
          ::Ogre::Camera* camera ;
          
          /// interpretes commands
          std::auto_ptr<ScriptingModule> command_interpretor ;
          
          /// Main window
          ::CEGUI::Window* m_window ;
          
          /// current number of active guis. 
          unsigned int m_number_of_active_guis ;
          
          virtual void injectKeyPressed(int key_code)
          {
            CEGUISystem->injectKeyDown(key_code) ;
          }
          
          virtual void injectKeyReleased(int key_code)
          {
            CEGUISystem->injectKeyUp(key_code) ;
          }
          
          virtual void injectChar(unsigned int key_char)
          {
            CEGUISystem->injectChar(key_char) ;
          }
          
          /// initialise mouse position at the center of the screen
          void initMousePosition()
          {
            unsigned int width ;
            unsigned int height ;
            unsigned int depth ;
            int left ;        
            int top ;
            Display::getWindowSize(width,height,depth,left,top) ;
            
            m_mouse_position_x = width/2 ;
            m_mouse_position_y = height/2 ;
            m_mouse_position_z = 0 ;

            ::CEGUI::Point position(m_mouse_position_x,m_mouse_position_y) ;
            ::CEGUI::MouseCursor::getSingleton().setPosition(position) ;
          }
          
          /// inject the new mouse position
          virtual void injectMousePosition(int x,int y, int z)
          {
            int delta_x = x - m_mouse_position_x ;
            int delta_y = y - m_mouse_position_y ;

            m_mouse_position_x = x ;
            m_mouse_position_y = y ;
            m_mouse_position_z = z ;
            
            if (delta_x != 0 || delta_y != 0)
              CEGUISystem->injectMouseMove(delta_x,delta_y) ;
          }

          /// previous mouse position
          int m_mouse_position_x ;
          int m_mouse_position_y ;
          int m_mouse_position_z ;
          
          
          virtual void injectMousePressed(int button)
          {
            CEGUISystem->injectMouseButtonDown(::CEGUI::MouseButton(button)) ;
          }

          virtual void injectMouseReleased(int button) 
          {
            CEGUISystem->injectMouseButtonUp(::CEGUI::MouseButton(button)) ;
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
          
        }
        
        void addActiveGUI(::CEGUI::Window* window)
        {
          system->m_window->addChildWindow(window) ;
          if (system->m_number_of_active_guis == 0)
          {
            ::CEGUI::MouseCursor::getSingleton().show() ;
            ::CEGUI::System::getSingleton().setGUISheet(system->m_window) ;
            system->initMousePosition() ;
          }
          ++system->m_number_of_active_guis ;
        }

        void removeActiveGUI(::CEGUI::Window* window)
        {
          --system->m_number_of_active_guis ;
          system->m_window->removeChildWindow(window) ;
          
          if (system->m_number_of_active_guis == 0)
          {
            ::CEGUI::MouseCursor::getSingleton().hide() ;
          }
        }

        ::CEGUI::Window* getRoot()
        {
          return system->m_window ;
        }
        
        ::CEGUI::Window* getRoot(::CEGUI::Window* window)
        {
          ::CEGUI::Window* parent = window->getParent() ;
          if (parent)
            return getRoot(parent) ;
          else
            return window ;
        }
        
        ::CEGUI::Window* getNamedDescendant(::CEGUI::Window* window,
                                            const std::string& name)
        {
          if (window->getName() == name)
          {
            return window ;
          }
          else
          {
            for(unsigned int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
            {
              ::CEGUI::Window* child = window->getChildAtIdx(child_index) ;
              ::CEGUI::Window* result = getNamedDescendant(child,name) ;
              if (result)
              {
                return result ;
              }
            }
          }
          
          return NULL ;
        }

        ::CEGUI::Window* getTypedDescendant(::CEGUI::Window* window,
                                            const std::string& type)
        {
          if (window->getType() == type)
          {
            return window ;
          }
          else
          {
            for(unsigned int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
            {
              ::CEGUI::Window* child = window->getChildAtIdx(child_index) ;
              ::CEGUI::Window* result = getTypedDescendant(child,type) ;
              if (result)
              {
                return result ;
              }
            }
          }
          
          return NULL ;
        }
        
        ::CEGUI::Window* getTypedDescendant(::CEGUI::Window* window,
                                            const std::string& type,
                                            const std::string& text)
        {
          if (window->getType() == type && window->getText() == text)
          {
            return window ;
          }
          else
          {
            for(unsigned int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
            {
              ::CEGUI::Window* child = window->getChildAtIdx(child_index) ;
              ::CEGUI::Window* result = getTypedDescendant(child,type,text) ;
              if (result)
              {
                return result ;
              }
            }
          }
          
          return NULL ;
        }
        
        std::string toString(const ::CEGUI::UDim& dimension)
        {
          return "{" + Kernel::toString(dimension.d_scale) + "," + Kernel::toString(dimension.d_offset) + "}" ;
        }

        std::string toString(const ::CEGUI::UVector2& vector)
        {
          return toString(vector.d_x) + "," + toString(vector.d_y) ; 
        }        
        
        std::string printStructure(::CEGUI::Window* window,const int& indent)
        {
          if (window)
          {
            std::string printed_indent(indent,' ') ;
            std::string result(printed_indent) ;
            
            std::string name = window->getName().c_str() ;
            std::string type = window->getType().c_str() ;
            
            
            result = result + name + " : " + type + " at " + toString(window->getPosition()) + "," + toString(window->getSize()) + "\n" ;
            
//            for(::CEGUI::PropertySet::Iterator property = window->PropertySet::getIterator() ;
//                ! property.isAtEnd() ;
//                ++property)
//            {
//              ::CEGUI::String property_name =(*property)->getName() ;
//              result = result + printed_indent + property_name.c_str() + "="+ window->getProperty(property_name).c_str() + "\n"; 
//            }
            
            for(unsigned int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
            {
              ::CEGUI::Window* child = window->getChildAtIdx(child_index) ;
              result += printStructure(child,indent+2) ;
            }
            return result ;
          }
          else
          {
            return "" ;
          }
        }
        
        void moveWindow(::CEGUI::Window* window,const ::CEGUI::UDim& delta)
        {
          ::CEGUI::URect area(window->getArea()) ;
          area.d_min.d_y += delta ;
          area.d_max.d_y += delta ;
          window->setArea(area) ;
        }

        void moveDownWindows(const std::list< ::CEGUI::Window*>& windows,
                                 ::CEGUI::Window* from,
                                 const ::CEGUI::UDim& delta)
        {
          float botom = (from->getYPosition() + from->getHeight()).asRelative(1) ;
          for(std::list< ::CEGUI::Window*>::const_iterator window = windows.begin() ;
              window != windows.end() ;
              ++window)
          {
            if ((*window)->getYPosition().asRelative(1) >= botom)
            {
              moveWindow(*window,delta) ;
            }
          }
        }

        void moveUpWindows(const std::list< ::CEGUI::Window*>& windows,
                           ::CEGUI::Window* from,
                           const ::CEGUI::UDim& delta)
        {
          ::CEGUI::UDim negative_delta(-delta.d_scale,-delta.d_offset) ;
          
          moveDownWindows(windows,from,negative_delta) ;
        }
        
        ::CEGUI::Window* createWindow(::CEGUI::Window* parent,
                                      const std::string& type,
                                      const std::string& local_name)
        {
          ::CEGUI::WindowManager& manager = ::CEGUI::WindowManager::getSingleton() ;
          ::CEGUI::Window* result = manager.createWindow(type) ;
          result->addProperty(new ::CEGUI::PropertyDefinition("local_name","",false,false)) ;
          
          result->setProperty("local_name",local_name) ;
          parent->addChildWindow(result) ;
          return result ;
        }

        ::CEGUI::Window* getChild(::CEGUI::Window* window,
                                  const std::string& local_name)
        {
          if (window->isPropertyPresent("local_name") && 
              window->getProperty("local_name") == local_name) 
          {
            return window ;
          }
          else
          {
            for(unsigned int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
            {
              ::CEGUI::Window* child = window->getChildAtIdx(child_index) ;
              ::CEGUI::Window* result = getChild(child,local_name) ;
              if (result)
              {
                return result ;
              }
            }
          }
          
          return NULL ;
        }
        
      }
    }    
  }
}
