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
#ifndef PU_GUI_IMPLEMENTATION_CEGUI_PLAYER_CONFIGURATION_H_
#define PU_GUI_IMPLEMENTATION_CEGUI_PLAYER_CONFIGURATION_H_

#include <CEGUI/CEGUIWindow.h>

#include <kernel/controler.h>
#include <gui/implementation/edited_player_configuration.h>
#include <gui/implementation/cegui/gui_controler_set.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {
      namespace CEGUI {
        
        /// Menu display.
        class PlayerConfiguration : 
          public Kernel::Controler<EditedPlayerConfiguration,
                                   GUIControlerSet>
        {
        public:
  
          /// Constructor.
          PlayerConfiguration(EditedPlayerConfiguration*,GUIControlerSet*) ;
  
          virtual void simulate(const float& seconds) ;
          
        protected:
  
        /*!
          @name Updates.
        */
        // @{
        
          /// Build a CEGUI window.
          virtual void onInit() ;
          
          /// Modify configuration.
          virtual void onUpdate() ;
          
          /// Destroy the window.
          virtual void onClose() ;
          
          
        // @}
          
          /// redraw the list
          void reDraw() ;
          
          /// Handle select event to change mapping.
          bool onSelect(const ::CEGUI::EventArgs& args) ;
          
        private:
  
          /// Main window
          ::CEGUI::Window* m_window ;
          
          /// List of mapping command/key
          ::CEGUI::MultiColumnList* m_list ;
          
          /// Current edited command.
          std::string m_command ;
          
          /// Time remaining before we cancel edition.
          float m_remaining_seconds ;
        };
      }      
    }
  }
}

#endif /*PU_GUI_IMPLEMENTATION_CEGUI_PLAYER_CONFIGURATION_H_*/
