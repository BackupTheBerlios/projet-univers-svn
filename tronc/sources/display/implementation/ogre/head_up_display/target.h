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
#include <display/implementation/target.h>
#include <display/implementation/ogre/head_up_display/target_displayer_viewpoint.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Test
    {
      class TestTarget ;
    }
  }
}

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        namespace HeadUpDisplay {

          class Target : public Kernel::TraitView<Implementation::Target,
                                                  TargetDisplayerViewPoint>
          {
          public:
          
          /*! 
            @name Construct
          */ 
          // @{
  
            /// Constructor.
            Target(Implementation::Target*  object,
                   TargetDisplayerViewPoint* viewpoint) ;

            /// Set the target colour.
            void setTargetColour(const ::Ogre::ColourValue&) ;
 
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
            
            /// Calculate the clockwize angle to up from @c (x,y) coordinates.  
            static ::Ogre::Degree calculateRotation(float x,float y) ;
            
            /// True iff the target is selected            
            bool isSelected() const ;

            /// 3D ogre element.
            ::Ogre::OverlayContainer* m_reticule_container ;
            ::Ogre::OverlayElement*   m_reticule ;

            ::Ogre::OverlayContainer* m_arrow_container ;
            ::Ogre::OverlayElement*   m_arrow ;
            
            /// true iff reticule is shown
            bool m_reticule_is_shown ;

            /// true iff arrow is shown
            bool m_arrow_is_shown ;
            
            /// for tests
            friend class ProjetUnivers::Display::Test::TestTarget ;
            
          };
        }
      }
    }
  }
}

#endif /*PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_TARGET_VIEW_H_*/
