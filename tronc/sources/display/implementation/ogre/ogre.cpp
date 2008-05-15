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

#include <display/implementation/ogre/ogre.h>


using namespace ::Ogre ;
using namespace std ;

namespace ProjetUnivers {

  using namespace Kernel ;
  
  namespace Display {
    namespace Implementation {
      namespace Ogre {  

        /*!
          Ogre data
          @remark
            Ogre handle memory, so no need to destroy.
        */
      
        ::Ogre::LogManager* log_manager = NULL ;
        ::Ogre::Root* root = NULL ;
        ::Ogre::RenderWindow* window = NULL ;
        // gui
        ::CEGUI::OgreCEGUIRenderer* CEGUIRenderer = NULL;
        ::CEGUI::System* CEGUISystem = NULL ;
        ::Ogre::Overlay* m_overlay = NULL ;

        ::Ogre::Root* getRoot()
        {
          return root ;
        }
        
        ::Ogre::RenderWindow* getWindow()
        {
          return window ;
        }

        ::CEGUI::OgreCEGUIRenderer* getCEGUIRenderer()
        {
          return CEGUIRenderer ;
        }
        
        ::Ogre::Overlay* getOverlay()
        {
          // on demand create
          if (!m_overlay)
          {
            InternalMessage("Display","creating overlay") ;
            m_overlay = ::Ogre::OverlayManager::getSingleton().create("hud") ;
          }
          
          return m_overlay ;
        }
        
        size_t getWindowHandle()
        {
          size_t windowHnd = 0;

          // Get window handle
          window->getCustomAttribute("WINDOW", &windowHnd) ;
          
          return windowHnd ;
        }

        void getWindowSize(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top )
        {
          window->getMetrics( width, height, depth, left, top ) ;
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
        
        bool renderDisplayChoice()
        {
          if(root->showConfigDialog())
          {
            return true ;
          }
          else
          {
            return false ;
          }
        }
        
        bool init(bool choose_display) 
        {
          log_manager = new LogManager() ;
          log_manager->createLog("Ogre.log", false, false); 
          
          // build an ogre application
          root = new Root() ;

          // load resources
          loadRessources() ;

          // user choose display 
          if (choose_display)
          {
            bool go_on = renderDisplayChoice() ;
            if (! go_on)
            {
              root = NULL ;
              return false ;
            }
          }
          else
          {
            // default display
            root->restoreConfig() ;
          }

          // create window
          window = root->initialise(true) ;
          
          CEGUIRenderer = new CEGUI::OgreCEGUIRenderer(window) ;
          CEGUISystem = new CEGUI::System(CEGUIRenderer) ;
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
          
          // done
          return true ;
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
          
          InternalMessage("Display","...Ogre stopped") ;
          
        }

        /// update display
        /*!
          this procedure avoid "normal" loop for Ogre.
        */
        void update()
        {
          /// cf. http://www.ogre3d.org/phpBB2/viewtopic.php?t=2733
          ::Ogre::WindowEventUtilities::messagePump() ;
          root->_fireFrameStarted();
          root->_updateAllRenderTargets() ;
          root->_fireFrameEnded();
        }
        
        void injectKey(const unsigned int& key_code)
        {
          if (CEGUISystem)
          {
            CEGUISystem->injectKeyDown(key_code) ;
          }
        }
      }
    }
  }
  
}
