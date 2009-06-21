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
#include <model/team.h>
#include <model/flying_group.h>
#include <input/input_gui.h>
#include <gui/implementation/gui_internal.h>
#include <gui/implementation/cegui/cegui.h>
#include <gui/implementation/cegui/custom_mission.h>
#include <gui/implementation/cegui/team.h>
#include <gui/implementation/cegui/gui_controler_set.h>

namespace ProjetUnivers
{
  namespace GUI
  {
    namespace Implementation
    {
      namespace CEGUI
      {

        RegisterControler(Team,
                          EditedTeam,
                          GUIControlerSet) ;

        Team::Team(EditedTeam*      team,
                   GUIControlerSet* gui)
        : Kernel::Controler<EditedTeam,GUIControlerSet>(team,gui),
          m_window(NULL)
        {}

        void Team::onInit()
        {
          InternalMessage("CustomMission","CEGUI::Team::onInit") ;

          m_mission = getControler<CustomMission>() ;

          m_window = m_mission->addTeamWindow(getObject()) ;

          ::CEGUI::WindowManager& manager = ::CEGUI::WindowManager::getSingleton() ;

          ::CEGUI::Window* name = createWindow(m_window,"ProjetUnivers/Editbox","name") ;
          name->setText(getTrait<Model::Team>()->getName()) ;
          name->setArea(::CEGUI::UDim(0,5),
                        ::CEGUI::UDim(0,0),
                        ::CEGUI::UDim(0.3,0),
                        ::CEGUI::UDim(0.1,0)) ;

          name->subscribeEvent(::CEGUI::Window::EventTextChanged,
                               ::CEGUI::Event::Subscriber(&Team::changedName,this)) ;


          ::CEGUI::Window* button_delete = createWindow(m_window,"ProjetUnivers/DeleteButton","delete") ;
          button_delete->setArea(::CEGUI::UDim(0.8,0),
                                 ::CEGUI::UDim(0,0),
                                 ::CEGUI::UDim(0.2,0),
                                 ::CEGUI::UDim(0.1,0)) ;
          button_delete->setText("Delete Team") ;
          button_delete->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                        ::CEGUI::Event::Subscriber(&Team::deleteTeam,this)) ;

          m_add_group = createWindow(m_window,"ProjetUnivers/AddButton","add") ;
          m_add_group->setArea(::CEGUI::UDim(0.4,0),
                               ::CEGUI::UDim(0,0),
                               ::CEGUI::UDim(0.2,0),
                               ::CEGUI::UDim(0.1,0)) ;
          m_add_group->setText("Add Group") ;
          m_add_group->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                      ::CEGUI::Event::Subscriber(&Team::addGroup,this)) ;
        }

        void Team::onClose()
        {
          InternalMessage("CustomMission","CEGUI::Team::onClose") ;
          m_mission->removeTeamWindow(m_window) ;
          if (m_window)
          {
             ::CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
        }

        bool Team::deleteTeam(const ::CEGUI::EventArgs& args)
        {
          getObject()->destroyObject() ;
          return true ;
        }

        ::CEGUI::Window* Team::addGroupWindow(Kernel::Object* group)
        {
          ::CEGUI::WindowManager& manager = ::CEGUI::WindowManager::getSingleton() ;

          ::CEGUI::Window* result = manager.createWindow("ProjetUnivers/BasicWindow") ;

          const unsigned int number_of_groups = m_group_windows.size() ;

          result->setArea(::CEGUI::UDim(0,0),
                          ::CEGUI::UDim(number_of_groups*0.1+0.1,0),
                          ::CEGUI::UDim(1,-12),
                          ::CEGUI::UDim(0.1,0)) ;

          m_window->addChildWindow(result) ;

          m_group_windows.push_back(result) ;

          return result ;
        }

        void Team::removeGroupWindow(::CEGUI::Window* window)
        {
          m_group_windows.remove(window) ;
          moveUpWindows(m_group_windows,window,::CEGUI::UDim(0.1,0)) ;
          m_window->removeChildWindow(window) ;
        }

        bool Team::addGroup(const ::CEGUI::EventArgs& args)
        {
          Kernel::Object* group = getObject()->createObject() ;
          group->addTrait(new Model::FlyingGroup("new group")) ;
        }

        bool Team::changedName(const ::CEGUI::EventArgs& args)
        {
          const ::CEGUI::WindowEventArgs* argument = dynamic_cast<const ::CEGUI::WindowEventArgs*>(&args) ;
          if (argument && argument->window)
          {
            getTrait<Model::Team>()->setName(argument->window->getText().c_str()) ;
          }
          return true ;
        }

      }
    }
  }
}
