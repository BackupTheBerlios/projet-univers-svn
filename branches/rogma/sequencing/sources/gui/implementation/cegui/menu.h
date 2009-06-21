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
#ifndef PU_GUI_IMPLEMENTATION_CEGUI_MENU_H_
#define PU_GUI_IMPLEMENTATION_CEGUI_MENU_H_

#include <CEGUI/CEGUIWindow.h>

#include <kernel/controler.h>
#include <gui/implementation/active_menu.h>
#include <gui/implementation/cegui/gui_controler_set.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {
      namespace CEGUI {
        
        /// Menu display.
        class Menu : public Kernel::Controler<ActiveMenu,
                                              GUIControlerSet>
        {
        public:
  
          /// Constructor.
          Menu(ActiveMenu*,GUIControlerSet*) ;
  
        protected:
  
        /*!
          @name Updates.
        */
        // @{
        
          /// Build a CEGUI window.
          void onInit() ;
          
          /// Destroy the window.
          void onClose() ;
          
        // @}
          
        private:
  
          /// The menu window
          ::CEGUI::Window* m_window ;
        };
      }      
    }
  }
}

#endif /*PU_GUI_IMPLEMENTATION_CEGUI_MENU_H_*/
