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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_TARGET_VIEW_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_TARGET_VIEW_H_

#include <Ogre.h>
#include <kernel/trait_view.h>
#include <display/implementation/ogre/head_up_display/target.h>
#include <display/implementation/ogre/head_up_display/target_displayer_viewpoint.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        namespace HeadUpDisplay {

          class TargetView : public Kernel::TraitView<Target,
                                                      TargetDisplayerViewPoint>
          {
          public:
          
          /*! 
            @name Construct
          */ 
          // @{
  
            /// Constructeur.
            TargetView(Target* object,
                       TargetDisplayerViewPoint* viewpoint) ;
          // @}
        protected:
          /*!
            @name Updates
          */
          // @{
          
            /// .
            void onInit() ;
            
            /// .
            void onClose() ;
          
            /// 
            void onUpdate() ;
  
          // @}
          private:

            /// Create the overlay. 
            void createOverlay() ;
            
            /// True iff the target is selected            
            bool isSelected() const ;

            /// 3D ogre element.
            ::Ogre::OverlayContainer* m_container ;
            ::Ogre::OverlayElement*   m_reticule ;
            
            ::Ogre::Camera*           m_camera ;            
            bool m_is_shown ;
          
          };
        }
      }
    }
  }
}

#endif /*PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_TARGET_VIEW_H_*/
