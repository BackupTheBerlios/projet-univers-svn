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
#include <gui/implementation/cegui/cegui.h>
#include <gui/implementation/cegui/command_interpretor.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace CEGUI 
      {
  
        CommandInterpretor::CommandInterpretor(const std::string& command_name)
        : m_command_name(command_name)
        {}
        
        Model::Menu* CommandInterpretor::getMenu(::CEGUI::Window* window)
        {
          
          Model::Menu* menu = static_cast<Model::Menu*>(window->getUserData()) ;
          if (menu)
            return menu ; 
          
          if (window->getParent())
            return getMenu(window->getParent()) ;
          
          return NULL ;
          
        }
        
        bool CommandInterpretor::operator()(const ::CEGUI::EventArgs& args) const
        {
          const ::CEGUI::WindowEventArgs* argument = dynamic_cast<const ::CEGUI::WindowEventArgs*>(&args) ;
          if (argument && argument->window)
          {
            Model::Menu* menu = getMenu(argument->window) ;
            
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
          return true ;
        }
      }
    }
  }
}
