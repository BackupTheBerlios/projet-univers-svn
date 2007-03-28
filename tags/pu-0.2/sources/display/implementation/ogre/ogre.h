/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      
      /// Ogre3d display implementation.
      /*!
        @see www.ogre3d.org     
      */ 
      namespace Ogre {  
  
        /// Ogre initialisation.
        bool init() ;
        
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
        void update() ;
        
        /// Ogre system root node.      
        ::Ogre::Root* getRoot() ;
        
        /// Window
        ::Ogre::RenderWindow* getWindow() ;
        
        ::Ogre::SceneManager* getManager() ;

        // @}
        
        
      }
    
    }
    
  }
  
}



#endif 
