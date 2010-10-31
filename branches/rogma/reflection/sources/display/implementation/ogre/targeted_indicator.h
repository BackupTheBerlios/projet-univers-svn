/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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

#include <kernel/deduced_trait.h>
#include <kernel/relation_view.h>
#include <display/implementation/ogre/real_world_view_point.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      /// Local deduced trait
      class TargetedIndicator : public Kernel::DeducedRelation
      {};

      namespace Ogre
      {

        /// Indicate that player ship is targeted on HUD
        /*!
        We make data static to build only one graphical element for the
        player.
        */
        class TargetedIndicator : public Kernel::RelationView<RealWorldViewPoint>
        {
        protected:
        /*!
          @name Updates.
        */
        // @{

          /// Create indicator
          void onInit() ;

          /// Remove indicator
          void onClose() ;

        // @}
        private:

          static void createIndicator() ;
          static void removeIndicator() ;

          bool m_is_enemy_target ;

          /// Number of targets...
          static unsigned int m_count ;

          /// 3D ogre element.
          static ::Ogre::Overlay* m_overlay ;

        };
      }
    }
  }
}
