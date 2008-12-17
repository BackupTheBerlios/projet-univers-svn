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
#ifndef PU_GUI_IMPLEMENTATION_CEGUI_CUSTOM_MISSION_H_
#define PU_GUI_IMPLEMENTATION_CEGUI_CUSTOM_MISSION_H_

#include <CEGUI/CEGUIWindow.h>

#include <kernel/controler.h>
#include <gui/implementation/edited_custom_mission.h>
#include <gui/implementation/cegui/gui_controler_set.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Test
    {
      class TestCustomMission ;
    }
    
    namespace Implementation 
    {
      namespace CEGUI 
      {
        
        /// Mission edition.
        class CustomMission : 
          public Kernel::Controler<EditedCustomMission,
                                   GUIControlerSet>
        {
        public:
  
          /// Constructor.
          CustomMission(EditedCustomMission*,GUIControlerSet*) ;
  
          /// Create a new sub window for a new team edition.
          ::CEGUI::Window* addTeamWindow(Kernel::Object*) ;

          /// Remove team's window, must decal every other ones.
          void removeTeamWindow(::CEGUI::Window*) ;
          
          
        protected:
  
        /*!
          @name Updates.
        */
        // @{
        
          /// Build a CEGUI window.
          virtual void onInit() ;
          
          /// Destroy the window.
          virtual void onClose() ;
          
          /// Add a team
          bool addTeam(const ::CEGUI::EventArgs& args) ;
          
        // @}
        private:
  
          /// Main window
          ::CEGUI::Window* m_window ;
         
          /// Teams window
          ::CEGUI::Window* m_teams ;
          
          /// Button to add a team
          ::CEGUI::Window* m_add_team ;
          
          /// Move a window
          void moveWindow(::CEGUI::Window*,const ::CEGUI::UDim&) ;
          
          /// Move down all windows positionned below @c from down
          void moveDownTeamWindows(::CEGUI::Window* from,const ::CEGUI::UDim&) ;

          /// Move down all windows positionned below @c from up
          void moveUpTeamWindows(::CEGUI::Window* from,const ::CEGUI::UDim&) ;
          
          /// The ordered list of team windows.
          std::list< ::CEGUI::Window*> m_team_windows ;
          
          friend class ::ProjetUnivers::GUI::Test::TestCustomMission ;
        };
      }      
    }
  }
}

#endif /*PU_GUI_IMPLEMENTATION_CEGUI_CUSTOM_MISSION_H_*/
