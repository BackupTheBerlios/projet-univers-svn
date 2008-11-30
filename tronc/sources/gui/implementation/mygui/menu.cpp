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
#include <kernel/object.h>
#include <model/menu.h>
#include <gui/implementation/gui_internal.h>
#include <gui/implementation/mygui/mygui.h>
#include <gui/implementation/mygui/menu.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace MyGUI 
      {
        
        RegisterControler(Menu, 
                          ActiveMenu, 
                          GUIControlerSet) ;
        
        Menu::Menu(ActiveMenu* object,GUIControlerSet* viewpoint)
        : Kernel::Controler<ActiveMenu,GUIControlerSet>(object,viewpoint)
        {
          InternalMessage("GUI","Building MyGUI::Menu::Menu") ;
        }
  
        void Menu::onInit()
        {
          InternalMessage("GUI","Building MyGUI::Menu::onInit entering") ;

          m_window = ::MyGUI::LayoutManager::getInstance().loadLayout(getObject()->getTrait<Model::Menu>()->getFileName(),"General") ;
          
          for(std::vector< ::MyGUI::WidgetPtr >::iterator widget = m_window.begin() ;
              widget != m_window.end() ;
              ++widget)
          {
            (*widget)->setUserData(getObject()->getTrait<Model::Menu>()) ;
          }
          
          InternalMessage("Display","Building MyGUI::Menu::onInit #1") ;
          
          MyGUI::addActiveGUI(m_window) ;          
          
          InternalMessage("GUI","Building MyGUI::Menu::onInit leaving") ;
        }
        
        void Menu::onClose()
        {
          MyGUI::removeActiveGUI(m_window) ;          
          m_window.clear() ;
        }
      }        
    }
  }
}
