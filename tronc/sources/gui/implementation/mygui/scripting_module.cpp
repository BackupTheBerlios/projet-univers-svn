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
#include <gui/implementation/mygui/scripting_module.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace MyGUI 
      {
        
        void ScriptingModule::makeBinding(const std::vector< ::MyGUI::WidgetPtr>& widgets)
        {
          for(std::vector< ::MyGUI::WidgetPtr >::const_iterator widget = widgets.begin() ;
              widget != widgets.end() ;
              ++widget)
          {
            makeBinding(*widget) ;
          }
        }

        void ScriptingModule::makeBinding(const ::MyGUI::WidgetPtr& widget)
        {
          if (widget->isUserString("Clicked"))
          {
            std::multimap< ::MyGUI::WidgetPtr,CommandInterpretor>::iterator command =
              m_bindings.insert(std::pair< ::MyGUI::WidgetPtr,
                                           CommandInterpretor>(widget,CommandInterpretor(widget->getUserString("Clicked")))) ;
            widget->eventMouseButtonClick = ::MyGUI::newDelegate(&(command->second), &CommandInterpretor::execute) ;
          }
          for(::MyGUI::EnumeratorWidgetPtr child = widget->getEnumerator() ;
              child.next() ;)
          {
            makeBinding(child.current()) ;
          }
        }
        
        void ScriptingModule::removeBinding(const std::vector< ::MyGUI::WidgetPtr>& widgets)
        {
          for(std::vector< ::MyGUI::WidgetPtr >::const_iterator widget = widgets.begin() ;
              widget != widgets.end() ;
              ++widget)
          {
            removeBinding(*widget) ;
          }
        }

        void ScriptingModule::removeBinding(const ::MyGUI::WidgetPtr& widget)
        {
          m_bindings.erase(widget) ;
        }
        
      }
    }
  }
}
