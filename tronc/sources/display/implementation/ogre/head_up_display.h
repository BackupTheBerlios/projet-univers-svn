/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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

#include <model/head_up_display.h>

#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/head_up_display/head_up_display_viewpoint.h>

namespace ProjetUnivers 
{
  namespace Display 
  {
    namespace Test
    {
      class TestTarget ;
    }
    
    namespace Implementation 
    {
      namespace Ogre 
      {

        /// Display targets.
        class HeadUpDisplay : public Kernel::TraitView<Model::HeadUpDisplay,
                                                       RealWorldViewPoint>
        {
        protected:
        /*!
          @name Updates
        */
        // @{
        
          /// create a viewpoint.
          virtual void onInit() ;
          
          /// Destroy the viewpoint.
          virtual void onClose() ;
        
          /// Update the viewpoint model
          virtual void onUpdate() ;

        // @}
        private:
          
          /// Display a cross at the center of the screen
          ::Ogre::Overlay* m_overlay ;
          
          /// Viewpoint displaying targets
          std::auto_ptr<Kernel::ViewPoint> m_implementation ;
          
          friend class ::ProjetUnivers::Display::Test::TestTarget ;
        };
      }
    }
  }
}
