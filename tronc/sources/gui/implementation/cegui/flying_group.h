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
#ifndef PU_GUI_IMPLEMENTATION_CEGUI_FLYING_GROUP_H_
#define PU_GUI_IMPLEMENTATION_CEGUI_FLYING_GROUP_H_

#include <CEGUI/CEGUIWindow.h>

#include <kernel/controler.h>
#include <gui/implementation/edited_flying_group.h>
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
        class Team ;
        
        /// Mission edition : flying group subsection
        class FlyingGroup : public Kernel::Controler<EditedFlyingGroup,
                                                     GUIControlerSet>
        {
        public:
  
          /// Constructor.
          FlyingGroup(EditedFlyingGroup*,GUIControlerSet*) ;
  
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
          bool deleteGroup(const ::CEGUI::EventArgs& args) ;

          /// Change the name.
          bool changedName(const ::CEGUI::EventArgs& args) ;
          
        private:
  
          /// Main window
          ::CEGUI::Window* m_window ;

          Team* m_team ;
          
          friend class ::ProjetUnivers::GUI::Test::TestCustomMission ;
          
        };
      }      
    }
  }
}

#endif /*PU_GUI_IMPLEMENTATION_CEGUI_FLYING_GROUP_H_*/
