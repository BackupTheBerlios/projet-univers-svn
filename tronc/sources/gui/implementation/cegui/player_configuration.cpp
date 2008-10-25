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
#include <CEGUI.h>

#include <input/input_gui.h>
#include <kernel/controler.h>
#include <kernel/object.h>
#include <model/player_configuration.h>
#include <gui/implementation/gui_internal.h>
#include <gui/implementation/cegui/cegui.h>
#include <gui/implementation/cegui/gui_controler_set.h>
#include <gui/implementation/cegui/player_configuration.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {
      namespace CEGUI {

        RegisterControler(PlayerConfiguration,
                          EditedPlayerConfiguration,
                          GUIControlerSet) ;
        
  
        PlayerConfiguration::PlayerConfiguration(
            EditedPlayerConfiguration* configuration,
            GUIControlerSet*           gui)
        : Kernel::Controler<EditedPlayerConfiguration,
                            GUIControlerSet>(configuration,gui),
          m_window(NULL),
          m_list(NULL),
          m_ok(NULL),
          m_remaining_seconds(0)
        {}
        
        void PlayerConfiguration::onInit()
        {
          try 
          {
            m_window = ::CEGUI::WindowManager::getSingleton().loadWindowLayout(
                "configure_keys.layout") ;
            
            // set the binding to the current trait
            m_window->setUserData(getObject()->getTrait<Model::PlayerConfiguration>()) ;

            m_list = static_cast< ::CEGUI::MultiColumnList*>(getTypedDescendant(m_window,"ProjetUnivers/MultiColumnList")) ;

            if (! m_list)
            {
              throw std::string("A Key configuration window must contain a subwindow of type ProjetUnivers/MultiColumnList") ;
            }
            
            reDraw() ;
            m_list->subscribeEvent(::CEGUI::MultiColumnList::EventSelectionChanged,
                                   ::CEGUI::Event::Subscriber(&PlayerConfiguration::onSelect,this)) ;
            
            ::CEGUI::System::getSingleton().setGUISheet(m_window) ;
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

          GUI::addActiveGUI() ;          
        }
          
        void PlayerConfiguration::onUpdate()
        {
          if (getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecordingMode())
          
            /// nothing to do
            return ;
          
          if (getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecorded())
          {
            /// we have finished the recording 
            getObject()->getTrait<Model::PlayerConfiguration>()->stopRecording() ;
            getObject()->getTrait<Model::PlayerConfiguration>()->addMapping(getObject()->getTrait<Model::PlayerConfiguration>()->getRecordedEvent(),m_command) ;
          }
          
          /// normal mode
          reDraw() ;
        }
          
        void PlayerConfiguration::onClose()
        {
          GUI::removeActiveGUI() ;          
          if (m_window)
          {
             ::CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
        }
        
        void PlayerConfiguration::reDraw()
        {
          // 1. clear the list ? won't work with a big list...
          m_list->resetList() ;
          
          std::set<std::string> commands(Kernel::Trait::getRegisteredCommands()) ;
          
          int item_identifier = 1 ;
          int row = 0 ;
          for(std::set<std::string>::const_iterator command = commands.begin() ;
              command != commands.end() ;
              ++command,++row)
          {
            ::CEGUI::ListboxTextItem* item ;
            m_list->addRow() ;
            item = new ::CEGUI::ListboxTextItem(*command,item_identifier++) ;
            item->setSelectionBrushImage("TaharezLook","MultiListSelectionBrush") ;
            m_list->setItem(item,0,row) ;          
  
            Model::PlayerConfiguration::InputEvent event = getObject()->getTrait<Model::PlayerConfiguration>()->getInputEvent(*command) ;
            item = new ::CEGUI::ListboxTextItem(event.toString(Input::getOISKeyboard()),item_identifier++) ;
            
            item->setSelectionBrushImage("TaharezLook","MultiListSelectionBrush") ;
            m_list->setItem(item,1,row) ;          
          }
        }
        
        bool PlayerConfiguration::onSelect(const ::CEGUI::EventArgs& args)
        {
          
          ::CEGUI::ListboxItem* selected_item = m_list->getFirstSelectedItem() ;
          if (selected_item)
          {
            m_command = selected_item->getText().c_str() ;
            
            /// we go to recording mo for 2 secondsde
            getObject()->getTrait<Model::PlayerConfiguration>()->setEventRecordingMode() ;
            m_remaining_seconds = 2 ;
          }
          
          return true ;
        }
        
        void PlayerConfiguration::simulate(const float& seconds)
        {
          m_remaining_seconds -= seconds ;
          if (m_remaining_seconds<0)
            getObject()->getTrait<Model::PlayerConfiguration>()->stopRecording() ;
        }
      }      
    }
  }
}
