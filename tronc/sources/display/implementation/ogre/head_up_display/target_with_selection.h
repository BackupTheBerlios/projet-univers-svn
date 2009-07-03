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
#include <display/implementation/target_with_selection.h>
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

          class Target ;
          
          class TargetWithSelection : 
            public Kernel::TraitView<Implementation::TargetWithSelection,
                                     HeadUpDisplayViewPoint>
          {
          protected:
          /*!
            @name Updates
          */
          // @{
          
            /// Set target of the associated Target.
            void onInit() ;
            
            /// Remove target of the associated Target.
            void onClose() ;
          
            /// Set target of the associated Target.
            void onUpdate() ;
  
          // @}
          private:

            /// The target view to update.
            Target* m_target ;
          };
        }
      }
    }
  }
}
