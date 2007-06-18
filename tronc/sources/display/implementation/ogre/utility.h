/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_OGRE_UTILS_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_OGRE_UTILS_H_

#include <Ogre.h>
#include <model/position.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {  
        
        /// Utility functions for Ogre
        /*!
        */
        namespace Utility
        {
          
          /// Create a unique Ogre name.
          std::string getUniqueName() ;
          
          /// create a 3D line.
          ::Ogre::MovableObject* createLine(
              const Model::Position& i_start_point,
              const Model::Position& i_end_point,
              ::Ogre::SceneManager*  i_scene_manager) ;
        }
      }
    }
  }
}

#endif /*PU_DISPLAY_IMPLEMENTATION_OGRE_OGRE_UTILS_H_*/
