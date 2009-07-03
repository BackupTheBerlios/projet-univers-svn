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

#include <CEGUI/CEGUIWindow.h>

#include <kernel/controler.h>
#include <gui/implementation/edited_team.h>
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
        class CustomMission ;
        
        /// Mission edition : Team subsection
        class Team : public Kernel::Controler<EditedTeam,
                                              GUIControlerSet>
        {
        public:
  
          /// Create a new sub window for a new flying group edition.
          ::CEGUI::Window* addGroupWindow(Kernel::Object*) ;

          /// Remove flying group's window, must decal every other ones.
          void removeGroupWindow(::CEGUI::Window*) ;
          
        protected:
  
        /*!
          @name Updates.
        */
        // @{
        
          /// Build a CEGUI window.
          virtual void onInit() ;
          
          /// Destroy the window.
          virtual void onClose() ;
          
          
        // @}
          
          /// Delete the current object.
          bool deleteTeam(const ::CEGUI::EventArgs& args) ;
          
          /// Add a flying group
          bool addGroup(const ::CEGUI::EventArgs& args) ;
          
          /// Change the name.
          bool changedName(const ::CEGUI::EventArgs& args) ;
          
        private:
  
          /// Main window
          ::CEGUI::Window* m_window ;

          /// Up to parent
          CustomMission* m_mission ;
          
          /// Button to add a group
          ::CEGUI::Window* m_add_group ;
          
          /// The ordered list of groups windows.
          std::list< ::CEGUI::Window*> m_group_windows ;
          
          friend class ::ProjetUnivers::GUI::Test::TestCustomMission ;
          
        };
      }      
    }
  }
}
