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
#include <input/input_gui.h>
#include <gui/implementation/gui_internal.h>
#include <gui/implementation/cegui/cegui.h>
#include <gui/implementation/cegui/flying_group.h>
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

        RegisterControler(FlyingGroup,
                          EditedFlyingGroup,
                          GUIControlerSet) ;
  
        FlyingGroup::FlyingGroup(EditedFlyingGroup* group,
                                 GUIControlerSet*   gui)
        : Kernel::Controler<EditedFlyingGroup,GUIControlerSet>(group,gui),
          m_window(NULL)
        {}
        
        void FlyingGroup::onInit()
        {
          InternalMessage("CustomMission","CEGUI::FlyingGroup::onInit") ;
          m_team =
              getObject()->getParent<EditedTeam>()
                         ->getControler<Team>(getControlerSet()) ;

          m_window = m_team->addGroupWindow(getObject()) ;
          
          ::CEGUI::WindowManager& manager = ::CEGUI::WindowManager::getSingleton() ;
          
          ::CEGUI::Window* button_delete = manager.createWindow("ProjetUnivers/Button") ;
          button_delete->setArea(::CEGUI::UDim(0,0),
                                 ::CEGUI::UDim(0.9,0),
                                 ::CEGUI::UDim(0.3,0),
                                 ::CEGUI::UDim(0.1,0)) ;
          button_delete->setText("Delete FlyingGroup") ;
          button_delete->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                        ::CEGUI::Event::Subscriber(&FlyingGroup::deleteGroup,this)) ;
          
          m_window->addChildWindow(button_delete) ;
        }
          
        void FlyingGroup::onClose()
        {
          InternalMessage("CustomMission","CEGUI::FlyingGroup::onClose") ;
          m_team->removeGroupWindow(m_window) ;
          if (m_window)
          {
             ::CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
        }
        
        bool FlyingGroup::deleteGroup(const ::CEGUI::EventArgs& args)
        {
          getObject()->destroyObject() ;
          return true ;
        }
        
      }      
    }
  }
}
