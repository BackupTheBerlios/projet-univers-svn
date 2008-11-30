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
#ifndef PU_GUI_IMPLEMENTATION_MYGUI_COMMAND_INTERPETOR_H_
#define PU_GUI_IMPLEMENTATION_MYGUI_COMMAND_INTERPETOR_H_

#include <MyGUI.h>

namespace ProjetUnivers 
{
  namespace Model
  {
    class Menu ;
  }
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace MyGUI 
      {
      
        /// Callback for a event command 
        class CommandInterpretor
        {
        public:
  
          /// Construction.
          CommandInterpretor(const std::string& command_name) ;
          
          /// Execute the command on a given window.
          void execute(::MyGUI::WidgetPtr _sender) ;
  
        private:
          
          /// Access to associated menu.
          static Model::Menu* getMenu(::MyGUI::Widget* window) ;
          
          /// Command name.
          std::string m_command_name ;
          
        };
      }
    }
  }
}

#endif /*PU_GUI_IMPLEMENTATION_MYGUI_COMMAND_INTERPETOR_H_*/
