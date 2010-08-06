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
#include <kernel/relation_view.h>
#include <display/implementation/target.h>
#include <display/implementation/ogre/real_world_view_point.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Test
    {
      class TestTarget ;
      class TestModelView ;
    }
  }
}

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

          /// Display a selection around the detected target
          class Target : public Kernel::RelationView<RealWorldViewPoint>
          {
          public:
          /*! 
            @name Construct
          */ 
          // @{

            /// Set the target color.
            void setTargetColour(const ::Ogre::ColourValue&) ;
 
            /// Set the identification of the target.
            void setIdentification(const std::string&) ;

            /// Set the identification of the target's target.
            void setTargetIdentification(const std::string&) ;
            
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
            
            /// Calculate the clockwise angle to up from @c (x,y) coordinates.
            /*!
              param[in,out] x,y screen coordinates
              param[in] z eye z position 
            */
            static ::Ogre::Degree calculateRotation(float x,float y) ;
            
            /// 3D ogre element.
            ::Ogre::OverlayContainer* m_target_container ;
            ::Ogre::OverlayElement*   m_target ;

            /// The side arrow used when target is out of screen
            ::Ogre::OverlayContainer* m_arrow_container ;
            ::Ogre::OverlayElement*   m_arrow ;

            /// contains the text of the target's identification.
            ::Ogre::OverlayContainer* m_identification_container ;
            ::Ogre::OverlayElement*   m_identification ;
            
            /// contains the text of the target's target.
            ::Ogre::OverlayContainer* m_target_text_container ;
            ::Ogre::OverlayElement*   m_target_text ;
            
            /// true iff target is shown
            bool m_target_is_shown ;

            /// true iff arrow is shown
            bool m_arrow_is_shown ;
            
            /// for tests
            friend class ProjetUnivers::Display::Test::TestTarget ;
            friend class ProjetUnivers::Display::Test::TestModelView ;
          };
        }
      }
    }
  }
}
