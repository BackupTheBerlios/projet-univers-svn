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
#include <kernel/log.h>
#include <kernel/object.h>
#include <model/menu.h>
#include <gui/implementation/mygui/mygui.h>
#include <gui/implementation/mygui/command_interpretor.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace MyGUI 
      {
  
        CommandInterpretor::CommandInterpretor(const std::string& command_name)
        : m_command_name(command_name)
        {}
        
        Model::Menu* CommandInterpretor::getMenu(::MyGUI::Widget* window)
        {
          
          Model::Menu* menu = static_cast<Model::Menu*>(window->getUserData()) ;
          if (menu)
            return menu ; 
          
          if (window->getParent())
            return getMenu(window->getParent()) ;
          
          return NULL ;
          
        }
        
        void CommandInterpretor::execute(::MyGUI::WidgetPtr _sender)
        {
          Model::Menu* menu = getMenu(_sender) ;
          
          if (menu)
          {
            InternalMessage("GUI","calling command " + m_command_name) ;
            menu->getObject()->call(m_command_name) ;
          }
          else
          {
            ErrorMessage("CommandInterpretor::operator() : no associated menu") ;
          }
        }
      }
    }
  }
}
