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
#include <input/input.h>

#include <gui/implementation/cegui/cegui.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {
      namespace CEGUI { 
        
        class GUISystem
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

            ::CEGUI::SchemeManager::getSingleton().loadScheme((::CEGUI::utf8*)"TaharezLook.scheme");
            ::CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow") ;
            ::CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");        
            ::CEGUI::MouseCursor::getSingleton().hide() ;
            
            // useless if scheme contains a font reference.
            ::CEGUI::Font* font = ::CEGUI::FontManager::getSingleton().createFont("bluehighway-12.font") ;
            
          }
            
          ::Ogre::SceneManager* manager ;
          ::CEGUI::System* CEGUISystem ;
          ::CEGUI::OgreCEGUIRenderer* CEGUIRenderer ;
          ::Ogre::Camera* camera ;
          std::auto_ptr<ScriptingModule> command_interpretor ;
          
          /// current number of active guis. 
          unsigned int m_number_of_active_guis ;
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
        
        void addActiveGUI()
        {
          if (system->m_number_of_active_guis == 0)
          {
            ::CEGUI::MouseCursor::getSingleton().show() ;
          }
          
          ++system->m_number_of_active_guis ;
        }

        void removeActiveGUI()
        {
          --system->m_number_of_active_guis ;

          if (system->m_number_of_active_guis == 0)
          {
            ::CEGUI::MouseCursor::getSingleton().hide() ;
          }
        }

        ::CEGUI::Window* getRoot(::CEGUI::Window* window)
        {
          ::CEGUI::Window* parent = window->getParent() ;
          if (parent)
            return getRoot(parent) ;
          else
            return window ;
        }
        
        ::CEGUI::Window* getDescendant(::CEGUI::Window* window,const std::string& name)
        {
          if (window->getName() == name)
          {
            return window ;
          }
          else
          {
            for(int child_index = 0 ; child_index < window->getChildCount() ; ++child_index)
            {
              ::CEGUI::Window* child = window->getChildAtIdx(child_index) ;
              ::CEGUI::Window* result = getDescendant(child,name) ;
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
