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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_OGRE_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_OGRE_H_

#include <Ogre.h>
#include <OgreCEGUIRenderer.h>
#include <display/display.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      
      /// Ogre3d display implementation.
      /*!
        @see www.ogre3d.org     
      */ 
      namespace Ogre {  
  
        /// Ogre initialisation.
        bool init(DisplayStartingMode mode = DefaultRenderer) ;
        
        /// Close Ogre.
        void close() ;

        /// Access to window handle.
        /*!
          Used by Input module.
        */
        size_t getWindowHandle() ;

        /// Window size.
        void getWindowSize(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top );
        
        /// Update display.
        void update(const float& seconds) ;
        
        /// Ogre system root node.      
        ::Ogre::Root* getRoot() ;
        
        /// Window
        ::Ogre::RenderWindow* getWindow() ;
        
        /// Access to GUI system.
        ::CEGUI::System* getCEGUISystem() ;
        
        /// Access to GUI renderer.
        ::CEGUI::OgreCEGUIRenderer* getCEGUIRenderer() ;        
        
        /// Access to overlay, created on demand.
        ::Ogre::Overlay* getOverlay() ;
        
        /// Send a key event to GUI.
        void injectKey(const unsigned int& key_code) ;

      }
    }
  }
}

#endif 
