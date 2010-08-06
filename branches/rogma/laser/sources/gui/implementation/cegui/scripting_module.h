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
#ifndef PU_GUI_IMPLEMENTATION_CEGUI_SCRIPTING_MODULE_H_
#define PU_GUI_IMPLEMENTATION_CEGUI_SCRIPTING_MODULE_H_

#include <CEGUI.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {
      namespace CEGUI {
        
        /// Specialized scripting module for CEGUI 
        class ScriptingModule : public ::CEGUI::ScriptModule
        {
        public:
          
          virtual void executeScriptFile(const ::CEGUI::String& filename,
                                         const ::CEGUI::String& resourceGroup="") ;
          
          virtual int executeScriptGlobal(const ::CEGUI::String& function_name) ;
          
          /// Link an event to a command interpretor.
          virtual ::CEGUI::Event::Connection subscribeEvent(
              ::CEGUI::EventSet*     target, 
              const ::CEGUI::String& name, 
              const ::CEGUI::String& subscriber_name) ;
          
          /// Link an event to a command interpretor.
          virtual ::CEGUI::Event::Connection subscribeEvent(
              ::CEGUI::EventSet*     target,
              const ::CEGUI::String& name,
              ::CEGUI::Event::Group  group,
              const ::CEGUI::String& subscriber_name) ;
          
          virtual void executeString(const ::CEGUI::String &str) ;
          
          /// execute a script
          virtual bool executeScriptedEventHandler(
              const ::CEGUI::String&    handler_name,
              const ::CEGUI::EventArgs& e) ;
        };
      }
    }
  }
}

#endif /*PU_GUI_IMPLEMENTATION_CEGUI_SCRIPTING_MODULE_H_*/
