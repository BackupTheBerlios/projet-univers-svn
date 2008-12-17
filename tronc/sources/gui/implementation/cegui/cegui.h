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
#ifndef PU_GUI_IMPLEMENTATION_CEGUI_CEGUI_H_
#define PU_GUI_IMPLEMENTATION_CEGUI_CEGUI_H_

#include <string>

namespace CEGUI
{
  class Window ;
  class UDim ;
  class UVector2 ;
}

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {

      /// Implementation through CEGUI.
      namespace CEGUI 
      { 
        
        /// Init the module.
        void start() ;
        
        /// Terminate the module.
        void terminate() ;

        /// Tells the system a new active GUI is present.
        void addActiveGUI(::CEGUI::Window* window) ;
        
        /// Tells the system an active GUI has became inactive.
        void removeActiveGUI(::CEGUI::Window* window) ;

        /// Access to the current root window.
        ::CEGUI::Window* getRoot() ;
        
        /// Access to the root window of @c window
        ::CEGUI::Window* getRoot(::CEGUI::Window* window) ;
        
        //: Print hierarchy name and type of a window.
        std::string printStructure(::CEGUI::Window* window,const int& indent) ; 
        
        /// Access to descendant of @c window with @c name
        /*!
          @return NULL if not found
        */
        ::CEGUI::Window* getNamedDescendant(::CEGUI::Window* window,const std::string& name) ;

        /// Access to descendant of @c window with @c type
        /*!
          @return NULL if not found
        */
        ::CEGUI::Window* getTypedDescendant(::CEGUI::Window* window,const std::string& type) ;

        /// Access to descendant of @c window with @c type and text @c text
        /*!
          @return NULL if not found
        */
        ::CEGUI::Window* getTypedDescendant(::CEGUI::Window* window,const std::string& type,const std::string& text) ;
        
        std::string toString(const ::CEGUI::UDim&) ;
        std::string toString(const ::CEGUI::UVector2& vector) ;
      }
    }    
  }
}

#endif /*PU_GUI_IMPLEMENTATION_CEGUI_CEGUI_H_*/
