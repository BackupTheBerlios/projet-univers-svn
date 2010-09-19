/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-20010 Mathieu ROGER                                *
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

#include <kernel/trait_view.h>
#include <model/laser_beam.h>
#include <display/implementation/ogre/real_world_view_point.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      /// A displayable beam
      class LaserBeam : public Kernel::DeducedTrait
      {};

      namespace Ogre
      {

        /// Display 3D objects.
        class LaserBeam : public Kernel::TraitView<Implementation::LaserBeam,
                                                   RealWorldViewPoint>
        {
        protected:
        /*!
          @name Updates
        */
        // @{
        
          /// create a Ogre::Entity.
          void onInit() ;
          
          /// Destroy the Ogre::Entity.
          void onClose() ;

        // @}

        private:
          
          ::Ogre::RibbonTrail* m_beam ;
          ::Ogre::SceneNode*   m_node ;
        };
      }
    }
  }
}
