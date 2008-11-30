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
#ifndef PU_GUI_IMPLEMENTATION_MYGUI_MYGUI_H_
#define PU_GUI_IMPLEMENTATION_MYGUI_MYGUI_H_

#include <string>
#include <MyGUI.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {

      /// Implementation through MyGUI.
      namespace MyGUI { 
        
        /// Init the module.
        void start() ;
        
        /// Terminate the module.
        void terminate() ;

        /// Access to window manager.
        ::MyGUI::Gui* getWindowManager() ;
        
        /// Tells the system a new active GUI is present.
        void addActiveGUI(::MyGUI::VectorWidgetPtr windows) ;
        
        /// Tells the system an active GUI has became inactive.
        void removeActiveGUI(::MyGUI::VectorWidgetPtr windows) ;

        /// Access tio the main window.
        ::MyGUI::Widget* getMainWindow() ;
        
        /// Access to the root window of @c window
        ::MyGUI::Widget* getRoot(::MyGUI::Widget* window) ;
        
        /// Access to descendant of @c window with @c name
        /*!
          @return NULL if not found
        */
        ::MyGUI::Widget* getNamedDescendant(::MyGUI::Widget* window,const std::string& name) ;

        /// Access to descendant of @c window with @c type
        /*!
          @return NULL if not found
        */
        ::MyGUI::Widget* getTypedDescendant(::MyGUI::Widget* window,const std::string& type) ;
        
      }
    }    
  }
}

#endif /*PU_GUI_IMPLEMENTATION_MYGUI_MYGUI_H_*/
