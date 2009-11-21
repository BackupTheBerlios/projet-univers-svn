/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Mathieu ROGER                                 *
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
#pragma once

#include <Ogre.h>
#include <display/display.h>
#include <model/position.h>
#include <model/distance.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      
      /// Ogre3d display implementation.
      /*!
        @see www.ogre3d.org     
      */ 
      namespace Ogre
      {
  
        /// Ogre initialization.
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
        
        /// Access to overlay, created on demand.
        ::Ogre::Overlay* getOverlay() ;
        
        /// Get a scene manager.
        /*!
          Due to bug http://www.ogre3d.org/phpBB2/viewtopic.php?p=189032#189032 
          having animated textures and several scene managers causes a crash. 
          We handle only one scene manager and create it on demand. 
        */
        ::Ogre::SceneManager* getManager() ;
        
        /// Create a default camera and viewport iff needed.
        void createCamera() ;
        
        /// Add/remove cameras.
        void addCamera(::Ogre::Camera*) ;
        void removeCamera(::Ogre::Camera*) ;
        
        /// Create a particle effect with its own life.
        /*!
          Once created, it will be displayed until finished and then
          automatically destroyed.

          @param name name of the particle script
        */
        ::Ogre::SceneNode* createParticleEffect(const std::string& name,
                                                ::Ogre::SceneNode* parent_node,
                                                const ::Ogre::Vector3& relative_position,
                                                const ::Ogre::Quaternion& relative_orientation) ;

        /*!
          Ogre coordinates are coded on 32 bits, thus half the precision
          is between 0 and 1.

          Here we use the following scale factor :
          1 Ogre unit = 1000 meters
        */
        const float conversion_factor = 1000 ;

        /// Convert position to Ogre position
        ::Ogre::Vector3 convert(const Model::Position& _position) ;

        /// Convert a distance to an Ogre distance.
        ::Ogre::Real convert(const Model::Distance& distance) ;

        /// Scale a node
        void scale(::Ogre::Node*) ;
      }
    }
  }
}
