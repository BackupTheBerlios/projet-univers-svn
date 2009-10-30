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

#include <plateform.h>

#include <kernel/log.h>

#include <model/model.h>
#include <model/menu.h>

#include <display/implementation/ogre/ogre.h>


using namespace ::Ogre ;
using namespace std ;

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        void loadRessources() ;
        bool renderDisplayChoice() ;
       
        /// Handle data.
        class OgreSystem
        {
        public:
          
          OgreSystem(DisplayStartingMode mode)
          : window(NULL),
            root(),
            log_manager(),
            initialised(false),
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

            ResourceGroupManager::getSingleton().initialiseAllResourceGroups() ;
            // load all ressources :
            ResourceGroupManager::getSingleton().loadResourceGroup("General") ;
            
            m_manager = ::Ogre::Root::getSingleton().createSceneManager(::Ogre::ST_GENERIC) ;
            m_camera = m_manager->createCamera("background") ;
            m_user_camera_number = 0 ;
            ::Ogre::Viewport* viewport = window->addViewport(m_camera,-100) ;

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
          
          /// make a background/foreground viewport
          /*!
            We have several viewports with different z-order, this one is behind 
            and will be cleared
          */
          ::Ogre::SceneManager* m_manager ;
          ::Ogre::Camera*       m_camera ;
          int m_user_camera_number ;
          
          bool initialised ;
        
          // in game hud
          ::Ogre::Overlay* m_overlay ;
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
        
        ::Ogre::Overlay* getOverlay()
        {
          // on demand create
          if (!m_system->m_overlay)
          {
            InternalMessage("Display","creating overlay") ;
            m_system->m_overlay = ::Ogre::OverlayManager::getSingleton().create("hud") ;
            m_system->m_overlay->setZOrder(200) ;
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
        }

        ::Ogre::SceneManager* getManager()
        {
          return m_system->m_manager ;
        }
        
        void createCamera()
        {
          if (m_system->m_user_camera_number == 0 && ! m_system->m_camera)
          {
            m_system->m_camera = m_system->m_manager->createCamera("background") ;
            ::Ogre::Viewport* viewport = getWindow()->addViewport(m_system->m_camera,-100) ;
          }
        }
        
        void addCamera(::Ogre::Camera*)
        {
          ++m_system->m_user_camera_number ;
          if (m_system->m_camera)
          {
            getWindow()->removeViewport(-100) ;
            m_system->m_manager->destroyCamera(m_system->m_camera) ;
            m_system->m_camera = NULL ;
          }
        }
        
        void removeCamera(::Ogre::Camera*)
        {
          --m_system->m_user_camera_number ;
          if (m_system->m_user_camera_number == 0)
          {
            m_system->m_camera = m_system->m_manager->createCamera("background") ;
            ::Ogre::Viewport* viewport = m_system->window->addViewport(m_system->m_camera,-100) ;
          }
        }
        
        
      }
    }
  }
  
}
