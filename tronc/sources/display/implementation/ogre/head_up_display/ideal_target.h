/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <kernel/trait_view.h>
#include <display/implementation/ideal_target.h>
#include <display/implementation/ogre/head_up_display/head_up_display_viewpoint.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {
        namespace HUD
        {

          // Display a circle where to shoot at the current selected target
          class IdealTarget : public Kernel::TraitView<Implementation::IdealTarget,
                                                       HeadUpDisplayViewPoint>
          {
          public:
          
          /*! 
            @name Construct
          */ 
          // @{

            /// Set the target color.
            void setColour(const ::Ogre::ColourValue&) ;

          // @}
          protected:
          /*!
            @name Updates
          */
          // @{
          
            /// Create the HUD elements.
            void onInit() ;
            
            /// Remove the HUD elements.
            void onClose() ;
          
            /// Update position/status of the HUD elements.
            void onUpdate() ;
  
          // @}
          private:

            /// 3D ogre element.
            ::Ogre::Overlay* m_overlay ;
            ::Ogre::OverlayContainer* m_target_container ;
            ::Ogre::OverlayElement*   m_target ;
            
            /// true iff target is shown
            bool m_target_is_shown ;

          };
        }
      }
    }
  }
}
