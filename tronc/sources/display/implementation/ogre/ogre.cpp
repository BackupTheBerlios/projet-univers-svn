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
      
        /// le système ogre      
        ::Ogre::Root* root = NULL ;
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre gère lui même sa mémoire et détruira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit être considéré comme une association.
        */
        ::Ogre::RenderWindow* window ;
        
        // gui
        ::CEGUI::OgreCEGUIRenderer* CEGUIRenderer ;
        ::CEGUI::System* CEGUISystem ;


        /// le système ogre      
        ::Ogre::Root* getRoot()
        {
          if (root)
          {
            return root ;
          }
          else
          {
            return NULL ;
          }
        }
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre gère lui même sa mémoire et détruira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit être considéré comme une association.
        */
        ::Ogre::RenderWindow* getWindow()
        {
          return window ;
        }

        ::CEGUI::OgreCEGUIRenderer* getCEGUIRenderer()
        {
          return CEGUIRenderer ;
        }
        
        size_t getWindowHandle()
        {
          size_t windowHnd = 0;

          // Get window handle
          window->getCustomAttribute("WINDOW", &windowHnd) ;
          
          return windowHnd ;
        }

        /// Accès à la taille de la fenêtre
        void getWindowSize(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top )
        {
          window->getMetrics( width, height, depth, left, top ) ;
        }
        
        /// Charge les ressources à partir du fichier ressources.cfg
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
        
        bool displayPiloteChoice()
        {
          // affiche l'écran de configuration et demande si on continue
          if(root->showConfigDialog())
          {
            return true ;
          }
          else
          {
            return false ;
          }
        }
        
        bool init() {

      
          // build an ogre application
          // *******************************
          root = new Root() ;
          
          // On charge le fichier de configuration des ressources
          // ****************************************************
          loadRessources() ;


          // On laisse l'utilisateur choisir le pilote d'affichage
          bool go_on = displayPiloteChoice() ;
          if (! go_on)
          {
            root = NULL ;
            return false ;
          }

          // on se crée une window par défaut
          window = root->initialise(true) ;
          
          CEGUIRenderer = new CEGUI::OgreCEGUIRenderer(window) ;
          CEGUISystem = new CEGUI::System(CEGUIRenderer) ;
          CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative) ;
          
          ResourceGroupManager::getSingleton().initialiseAllResourceGroups() ;
          
          // cegui 
          CEGUI::Imageset::setDefaultResourceGroup("imagesets");
          CEGUI::Font::setDefaultResourceGroup("fonts");
          CEGUI::Scheme::setDefaultResourceGroup("schemes");
          CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
          CEGUI::WindowManager::setDefaultResourceGroup("layouts");
          CEGUI::SchemeManager::getSingleton().loadScheme("ProjetUnivers.scheme") ;
          
          // useless if scheme contains a font reference.
          CEGUI::Font* font = CEGUI::FontManager::getSingleton().createFont("bluehighway-12.font") ;
          
//          CEGUI::SchemeManager::getSingleton()
//            .loadScheme((CEGUI::utf8*)"TaharezLook.scheme") ;
//          CEGUISystem->setDefaultFont(font);                          
//          font = CEGUI::FontManager::getSingleton()
//            .createFont("Commonwealth-10.font") ;

          InternalMessage("Display","Ogre launched") ;
          
          // voila
          return true ;
        }

        void close() 
        {
          InternalMessage("Display","stopping Ogre..") ;
          if(CEGUISystem)
          {
            delete CEGUISystem;
            CEGUISystem = 0;
          }
          
          if(CEGUIRenderer)
          {
            delete CEGUIRenderer;
            CEGUIRenderer = 0;
          }

          if (root)
          {
            delete root ;
            root = NULL ;  
          }

          InternalMessage("Display","...Ogre stopped") ;
          
        }

        /// Rafraichi l'affichage
        /*!
          Met à jour tout ce qui doit être affiché. On se sert de cette méthode 
          pour ne pas passer par la boucle standard de Ogre.
        */
        void update()
        {
          /// cf. http://www.ogre3d.org/phpBB2/viewtopic.php?t=2733
          ::Ogre::WindowEventUtilities::messagePump();
          root->_fireFrameStarted();
          window->update() ;
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
