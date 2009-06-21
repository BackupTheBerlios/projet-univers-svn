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
#include <iostream>
#include <math.h>
#include <CEGUI.h>

#include <kernel/log.h>
#include <kernel/controler.h>
#include <kernel/object.h>

#include <model/custom_mission.h>
#include <model/team.h>

#include <input/input_gui.h>

#include <gui/implementation/gui_internal.h>
#include <gui/implementation/cegui/cegui.h>
#include <gui/implementation/cegui/custom_mission.h>
#include <gui/implementation/cegui/gui_controler_set.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace CEGUI 
      {

        RegisterControler(CustomMission,
                          EditedCustomMission,
                          GUIControlerSet) ;
        
  
        CustomMission::CustomMission(EditedCustomMission* mission,
                                     GUIControlerSet*     gui)
        : Kernel::Controler<EditedCustomMission,
                            GUIControlerSet>(mission,gui),
          m_window(NULL),
          m_teams(NULL)
        {}
        
        void CustomMission::onInit()
        {
          InternalMessage("CustomMission","CEGUI::CustomMission::onInit") ;
          
          try 
          {
            m_window = ::CEGUI::WindowManager::getSingleton().loadWindowLayout("custom_mission.layout") ;

            m_teams = m_window->getChild("Mission/Teams") ;
            m_add_team = getNamedDescendant(m_window,"Mission/AddTeam") ;
            
            // set the binding to the current trait
            m_window->setUserData(getObject()) ;
            
            m_add_team->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                       ::CEGUI::Event::Subscriber(&CustomMission::addTeam,this)) ;
            
          }
          catch(::CEGUI::Exception& exception)
          {
            std::cout << exception.getMessage() << std::cout ;
            ErrorMessage(exception.getMessage().c_str()) ;
            throw ;
          }
          catch (std::string& message)
          {
            std::cout << message << std::cout ;
            ErrorMessage(message) ;
            throw ;
          }

          GUI::addActiveGUI(m_window) ;          
        }
          
        void CustomMission::onClose()
        {
          InternalMessage("CustomMission","CEGUI::CustomMission::onClose") ;
          GUI::removeActiveGUI(m_window) ;          
          if (m_window)
          {
             ::CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
        }
        
        ::CEGUI::Window* CustomMission::addTeamWindow(Kernel::Object* team)
        {
          ::CEGUI::Window* result = createWindow(m_teams,"ProjetUnivers/BasicWindow","team") ;
          
          const unsigned int number_of_teams = m_team_windows.size() ;
          
          result->setArea(::CEGUI::UDim(0,0),
                          ::CEGUI::UDim(number_of_teams*0.5,0),
                          ::CEGUI::UDim(1,-12),
                          ::CEGUI::UDim(0.5,0)) ;
          
          m_team_windows.push_back(result) ;
          
          return result ;
        }
        
        void CustomMission::removeTeamWindow(::CEGUI::Window* team)
        {
          /// move all the other team windows below
          m_team_windows.remove(team) ;
          moveUpWindows(m_team_windows,team,::CEGUI::UDim(0.5,0)) ;
          m_teams->removeChildWindow(team) ;
        }
        
        bool CustomMission::addTeam(const ::CEGUI::EventArgs& args)
        {
          Kernel::Object* team = getObject()->createObject() ;
          team->addTrait(new Model::Team("new team")) ;
        }
        
      }
    }
  }
}
