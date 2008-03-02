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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_IDEAL_TARGET_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_IDEAL_TARGET_H_

#include <Ogre.h>
#include <kernel/trait_view.h>
#include <display/implementation/ideal_target.h>
#include <display/implementation/ogre/head_up_display/target_displayer_viewpoint.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        namespace HeadUpDisplay {

          class IdealTarget : public Kernel::TraitView<Implementation::IdealTarget,
                                                       TargetDisplayerViewPoint>
          {
          public:
          
          /*! 
            @name Construct
          */ 
          // @{
  
            /// Constructor.
            IdealTarget(Implementation::IdealTarget*  object,
                        TargetDisplayerViewPoint* viewpoint) ;

            /// Set the target colour.
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
            ::Ogre::OverlayContainer* m_reticule_container ;
            ::Ogre::OverlayElement*   m_reticule ;
            
            /// true iff reticule is shown
            bool m_reticule_is_shown ;

          };
        }
      }
    }
  }
}

#endif /*PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_IDEAL_TARGET_H_*/
