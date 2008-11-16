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
#include <CEGUI.h>

#include <kernel/object.h>
#include <model/menu.h>
#include <gui/implementation/gui_internal.h>
#include <gui/implementation/cegui/menu.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {
      namespace CEGUI {
        
        RegisterControler(Menu, 
                          ActiveMenu, 
                          GUIControlerSet) ;
        
        Menu::Menu(ActiveMenu* object,GUIControlerSet* viewpoint)
        : Kernel::Controler<ActiveMenu,GUIControlerSet>(object,viewpoint), 
          m_window(NULL)
        {
          InternalMessage("Display","Building CEGUI::Menu::Menu") ;
        }
  
        void Menu::onInit()
        {
          InternalMessage("Display","Building CEGUI::Menu::onInit entering") ;
          
          m_window = ::CEGUI::WindowManager::getSingleton().loadWindowLayout(
              getObject()->getTrait<Model::Menu>()->getFileName()) ;
          
          // set the binding to the current trait
          m_window->setUserData(getObject()->getTrait<Model::Menu>()) ;
          
          InternalMessage("Display","Building CEGUI::Menu::onInit #1") ;

          /// @todo change to own mouse cursor
          m_window->setMouseCursor("TaharezLook", "MouseArrow");
          
          GUI::addActiveGUI(m_window) ;          
          
          InternalMessage("Display","Building CEGUI::Menu::onInit leaving") ;
        }
        
        void Menu::onClose()
        {
          GUI::removeActiveGUI(m_window) ;          
          if (m_window)
          {
             ::CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
        }
      }        
    }
  }
}
