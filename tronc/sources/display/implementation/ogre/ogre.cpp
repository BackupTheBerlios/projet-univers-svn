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
#include <stddef.h>
#include <Ogre.h>
#include <CEGUI.h>

#include <plateform.h>

#include <kernel/log.h>

#include <model/model.h>
#include <model/menu.h>

#include <display/implementation/ogre/ogre.h>


using namespace ::Ogre ;
using namespace std ;

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {  

        void loadRessources() ;
        bool renderDisplayChoice() ;

        
        const CEGUI::Window* getRoot(const CEGUI::Window* window)
        {
          const CEGUI::Window* parent = window->getParent() ;
          if (parent)
            return getRoot(parent) ;
          else
            return window ;
        }
        
        /// Callback for a event command 
        class CommandInterpretor
        {
        public:

          CommandInterpretor(const std::string& name)
          : m_name(name)
          {}
          
          bool operator()(const CEGUI::EventArgs& args) const
          {
            std::cout << m_name ;
            
            const CEGUI::WindowEventArgs* argument = dynamic_cast<const CEGUI::WindowEventArgs*>(&args) ;
            
            if (argument)
            {
              std::cout << " " << argument->window->getName()
                        << " type=" << argument->window->getType()
                        << " Custom=" << argument->window->getProperty("Custom") ;
              
              Model::Menu* menu = (Model::Menu*)(getRoot(argument->window)->getUserData()) ;
              
              if (menu)
                std::cout << " object id=" << menu->getObject()->getIdentifier() ;
              
              
//              for(CEGUI::PropertySet::Iterator property = argument->window->CEGUI::PropertySet::getIterator() ;
//                  ! property.isAtEnd() ; ++property)
//              {
//                std::cout << property.getCurrentKey() << "=" << property.getCurrentValue() << "," ;
//              }
                  
            }
            
            std::cout << std::endl ;
            
            return true ;
          }
          
          std::string m_name ;
          
        };
        
        
        /// Specialized scripting module for CEGUI 
        class ScriptingModule : public CEGUI::ScriptModule
        {
        public:
          
          
          virtual void executeScriptFile(const CEGUI::String &filename, const CEGUI::String &resourceGroup="")
          {
            
          }
          
          virtual int executeScriptGlobal(const CEGUI::String& function_name)
          {
            return 0 ;
          }
          
          virtual CEGUI::Event::Connection subscribeEvent(
              CEGUI::EventSet*     target, 
              const CEGUI::String& name, 
              const CEGUI::String& subscriber_name)
          {
            CommandInterpretor command(subscriber_name.c_str()) ;
            return target->subscribeEvent(name,CEGUI::Event::Subscriber(command)) ;
          }
          
          virtual CEGUI::Event::Connection subscribeEvent(
              CEGUI::EventSet*     target,
              const CEGUI::String& name,
              CEGUI::Event::Group  group,
              const CEGUI::String& subscriber_name)
          {
            CommandInterpretor command(subscriber_name.c_str()) ;
            return target->subscribeEvent(name,group,CEGUI::Event::Subscriber(command)) ;
          }
          
          virtual void executeString(const CEGUI::String &str)
          {
            
          }
          
          /// execute a script
          virtual bool executeScriptedEventHandler(
              const CEGUI::String& handler_name,
              const CEGUI::EventArgs &e)
          {
            return true ;
          }
        };

        
        
        /// Handle data.
        class OgreSystem
        {
        public:
          
          OgreSystem(DisplayStartingMode mode)
          : window(NULL),
            root(),
            log_manager(),
            initialised(false),
            CEGUIRenderer(NULL),
            CEGUISystem(NULL),
            m_overlay(NULL)
          {
            /// model may have created a root and log manager
            Model::closeRessources() ;
            
            log_manager = new LogManager() ;
            log_manager->createLog("Ogre.log", false, false); 
            
            // build an ogre application
            root = new Root() ;

            // load resources
            loadRessources() ;

            // user choose display 
            if (mode == ChooseRenderer)
            {
              bool go_on = renderDisplayChoice() ;
              if (! go_on)
              {
                delete root ;
                root = NULL ;
                initialised = false ;
                return ;
              }
            }
            else
            {
              // default display
              root->restoreConfig() ;
            }

            // create window
            window = root->initialise(true) ;

            command_interpretor.reset(new ScriptingModule()) ;
            
            CEGUIRenderer = new CEGUI::OgreCEGUIRenderer(window) ;
//            CEGUISystem = new CEGUI::System(CEGUIRenderer,0,0,command_interpretor.get()) ;
            CEGUISystem = new CEGUI::System(CEGUIRenderer) ;
            CEGUISystem->setScriptingModule(command_interpretor.get()) ;
            CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative) ;
            
            ResourceGroupManager::getSingleton().initialiseAllResourceGroups() ;
            // load all ressources :
            ResourceGroupManager::getSingleton().loadResourceGroup("General") ;
            
            // cegui 
            CEGUI::Imageset::setDefaultResourceGroup("imagesets");
            CEGUI::Font::setDefaultResourceGroup("fonts");
            CEGUI::Scheme::setDefaultResourceGroup("schemes");
            CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
            CEGUI::WindowManager::setDefaultResourceGroup("layouts");
            CEGUI::SchemeManager::getSingleton().loadScheme("ProjetUnivers.scheme") ;
            
            // useless if scheme contains a font reference.
            CEGUI::Font* font = CEGUI::FontManager::getSingleton().createFont("bluehighway-12.font") ;
            
            InternalMessage("Display","Ogre launched") ;
            
            initialised = true ;
          }
          
          ~OgreSystem()
          {
            InternalMessage("Display","stopping Ogre..") ;


            /// @see http://www.ogre3d.org/phpBB2/viewtopic.php?t=35372
            if (window)
            {
              ::Ogre::WindowEventUtilities::_removeRenderWindow(window) ;
              window = NULL ;
            }
            
            
            if (log_manager)
            {
              delete log_manager ;
              log_manager = NULL ;
            }
            
            m_overlay= NULL ;
            
            initialised = false ;
            
            InternalMessage("Display","...Ogre stopped") ;
          }
          
          void close()
          {
            InternalMessage("Display","stopping Ogre..") ;

            if(CEGUISystem)
            {
              delete CEGUISystem;
              CEGUISystem = NULL ;
            }
            
            if(CEGUIRenderer)
            {
              delete CEGUIRenderer;
              CEGUIRenderer = NULL ;
            }


            /// @see http://www.ogre3d.org/phpBB2/viewtopic.php?t=35372
            if (window)
            {
              ::Ogre::WindowEventUtilities::_removeRenderWindow(window) ;
              window = NULL ;
            }
            
            if (root)
            {
              delete root ;
              root = NULL ;
            }
            
            if (log_manager)
            {
              delete log_manager ;
              log_manager = NULL ;
            }
            
            m_overlay= NULL ;
            
            initialised = false ;
            
            InternalMessage("Display","...Ogre stopped") ;
          }
          
          bool renderDisplayChoice()
          {
            if (root->showConfigDialog())
            {
              return true ;
            }
            else
            {
              return false ;
            }
          }
          
          ::Ogre::RenderWindow* window ;
        
          ::Ogre::Root* root ;
          ::Ogre::LogManager* log_manager ;
          bool initialised ;
        
          // gui
          ::CEGUI::OgreCEGUIRenderer* CEGUIRenderer ;
          ::CEGUI::System* CEGUISystem ;
          ::Ogre::Overlay* m_overlay ;
          
          std::auto_ptr<ScriptingModule> command_interpretor ;
        };
        
        /// store data
        std::auto_ptr<OgreSystem> m_system ;
        
        ::Ogre::Root* getRoot()
        {
          return m_system->root ;
        }
        
        ::Ogre::RenderWindow* getWindow()
        {
          return m_system->window ;
        }

        ::CEGUI::OgreCEGUIRenderer* getCEGUIRenderer()
        {
          return m_system->CEGUIRenderer ;
        }
        
        ::CEGUI::System* getCEGUISystem()
        {
          return m_system->CEGUISystem ;
        }
        
        ::Ogre::Overlay* getOverlay()
        {
          // on demand create
          if (!m_system->m_overlay)
          {
            InternalMessage("Display","creating overlay") ;
            m_system->m_overlay = ::Ogre::OverlayManager::getSingleton().create("hud") ;
            m_system->m_overlay->setZOrder(500) ;
          }
          
          return m_system->m_overlay ;
        }
        
        size_t getWindowHandle()
        {
          size_t windowHnd = 0;

          // Get window handle
          m_system->window->getCustomAttribute("WINDOW", &windowHnd) ;
          
          return windowHnd ;
        }

        void getWindowSize(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top )
        {
          m_system->window->getMetrics( width, height, depth, left, top ) ;
        }
        
        void loadRessources() 
        {
            
          ConfigFile file ;
          file.load("ressources.cfg") ;

          // On parcours ses sections
          ConfigFile::SectionIterator section = file.getSectionIterator();

          String nomSection, nomType, nomArchitecture ;
          while (section.hasMoreElements())
          {
            nomSection = section.peekNextKey();
            ConfigFile::SettingsMultiMap* settings = section.getNext();
            
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                nomType = i->first;
                nomArchitecture = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(
                    nomArchitecture, nomType, nomSection);
            }
          }
        }
        
        bool init(DisplayStartingMode mode) 
        {
          if(! m_system.get())
            
            m_system.reset(new OgreSystem(mode)) ;
          
          return m_system->initialised ;
        }

        void close() 
        {
          m_system->close() ;
          m_system.reset() ;
        }

        /// update display
        /*!
          this procedure avoid "normal" loop for Ogre.
        */
        void update(const float& seconds)
        {
          /// cf. http://www.ogre3d.org/phpBB2/viewtopic.php?t=2733
          ::Ogre::WindowEventUtilities::messagePump() ;
          m_system->root->_fireFrameStarted();
          m_system->root->_updateAllRenderTargets() ;
          m_system->root->_fireFrameEnded();
          
          CEGUI::System::getSingleton().injectTimePulse(seconds) ;
        }
        
        void injectKey(const unsigned int& key_code)
        {
          if (m_system->CEGUISystem)
          {
            m_system->CEGUISystem->injectKeyDown(key_code) ;
          }
        }
      }
    }
  }
  
}
