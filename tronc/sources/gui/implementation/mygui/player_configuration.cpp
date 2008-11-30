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
#include <kernel/controler.h>
#include <kernel/object.h>
#include <model/player_configuration.h>
#include <input/input_gui.h>
#include <gui/implementation/gui_internal.h>
#include <gui/implementation/mygui/mygui.h>
#include <gui/implementation/mygui/gui_controler_set.h>
#include <gui/implementation/mygui/player_configuration.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace MyGUI 
      {

        RegisterControler(PlayerConfiguration,
                          EditedPlayerConfiguration,
                          GUIControlerSet) ;
        
  
        PlayerConfiguration::PlayerConfiguration(
            EditedPlayerConfiguration* configuration,
            GUIControlerSet*           gui)
        : Kernel::Controler<EditedPlayerConfiguration,
                            GUIControlerSet>(configuration,gui),
          m_controls(NULL),
          m_remaining_seconds(0),
          m_is_recording(false)
        {}
        
        void PlayerConfiguration::onInit()
        {
          InternalMessage("PlayerConfiguration","MyGui::PlayerConfiguration::onInit") ;
          std::cout << std::endl << "loading is " << (::MyGUI::Gui::getInstance().load("options.layout")?"ok":"ko") ;
          ::MyGUI::WidgetPtr window = ::MyGUI::Gui::getInstance().findWidgetT("Controls") ;
//          m_controls = ::MyGUI::Gui::getInstance().findWidget< ::MyGUI::Sheet>("Controls") ;
//          
//          // set the binding to the current trait
//          m_controls->setUserData(getObject()->getTrait<Model::PlayerConfiguration>()) ;
//
//          initialDraw() ;

          MyGUI::addActiveGUI(m_window) ;
        }
          
        void PlayerConfiguration::onUpdate()
        {
          InternalMessage("PlayerConfiguration","MyGUI::PlayerConfiguration::onUpdate") ;
          if (m_is_recording || getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecordingMode())
          
            /// nothing to do
            return ;
          
          if (getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecorded())
          {
            m_is_recording = true ;
            /// we have finished the recording 
            getObject()->getTrait<Model::PlayerConfiguration>()->stopRecording() ;
            getObject()->getTrait<Model::PlayerConfiguration>()->addMapping(getObject()->getTrait<Model::PlayerConfiguration>()->getRecordedEvent(),m_command) ;
            m_is_recording = false ;
            reDraw() ;
            return ;
          }
          
          /// normal mode
          reDraw() ;
        }
          
        void PlayerConfiguration::onClose()
        {
          MyGUI::removeActiveGUI(m_window) ;          
        }

        void PlayerConfiguration::initialDraw()
        {
          if (! m_controls)
            return ;
          
          int number = 0 ;
          
          // should depend on resolution in fact...
          const int absolute_height = 30 ;
          int number_of_element_by_column = m_controls->getHeight()/absolute_height ;
          float element_height = 1.0 / number_of_element_by_column ;

          // these should depend on m_control size
          const unsigned int font_size = 12 ;
          const float name_length = 0.3 ;
          
          std::set<std::string> commands(Kernel::Trait::getRegisteredCommands()) ;
          for(std::set<std::string>::const_iterator command = commands.begin() ;
              command != commands.end() ;
              ++command,++number)
          {
            /*
              number_of_element_by_column elements by columns,
              2 columns
            */
            int column = number/number_of_element_by_column ;
            int row = number%number_of_element_by_column ;
            
            
            ::MyGUI::StaticText* name 
              = static_cast< ::MyGUI::StaticText*>(
                  m_controls->createWidgetRealT("StaticText",
                                                "StaticText",
                                                ::MyGUI::FloatCoord(0.5*column,
                                                                    element_height*row,
                                                                    name_length,
                                                                    element_height),
                                                ::MyGUI::ALIGN_DEFAULT)) ;
            name->setCaption(*command) ;
            name->setTextAlign(::MyGUI::ALIGN_VCENTER|::MyGUI::ALIGN_LEFT) ;
            
            name->setFontHeight(font_size) ;
            Model::PlayerConfiguration::InputEvent event = 
              getObject()->getTrait<Model::PlayerConfiguration>()
                         ->getInputEvent(*command) ;

            ::MyGUI::Widget* box =
                  m_controls->createWidgetRealT("ItemBox",
                                                "ItemBox",
                                                ::MyGUI::FloatCoord(0.5*column+name_length,
                                                                    element_height*row,
                                                                    0.5-name_length,
                                                                    element_height),
                                                ::MyGUI::ALIGN_DEFAULT) ;
            
            ::MyGUI::StaticText* value =  
              static_cast< ::MyGUI::StaticText*>(
                         box->createWidgetRealT("StaticText",
                                                "StaticText",
                                                ::MyGUI::FloatCoord(0,0,1,1),
                                                ::MyGUI::ALIGN_DEFAULT)) ;
            value->setCaption(event.toString(Input::getOISKeyboard())) ;
            value->setTextAlign(::MyGUI::ALIGN_CENTER) ;
            value->setFontHeight(font_size) ;

            m_commands[*command] = value ;
            
            // binding
            value->setUserData(name) ;
            value->eventMouseButtonClick = ::MyGUI::newDelegate(this,&PlayerConfiguration::onSelect) ;
          }
          
          // binding for axes
          std::set<std::string> axes(Kernel::Trait::getRegisteredAxes()) ;
          std::cout << "number of axes =" << axes.size() << std::endl ;
          for(std::set<std::string>::const_iterator axis = axes.begin() ;
              axis != axes.end() ;
              ++axis,++number)
          {
            /*
              number_of_element_by_column elements by columns,
              2 columns
            */
            int column = number/number_of_element_by_column ;
            int row = number%number_of_element_by_column ;
            
            ::MyGUI::StaticText* name 
              = static_cast< ::MyGUI::StaticText*>(
                  m_controls->createWidgetRealT("StaticText",
                                                "StaticText",
                                                ::MyGUI::FloatCoord(0.5*column,
                                                                    element_height*row,
                                                                    name_length,
                                                                    element_height),
                                                ::MyGUI::ALIGN_DEFAULT)) ;
            name->setCaption(*axis) ;
            name->setFontHeight(font_size) ;
            name->setTextAlign(::MyGUI::ALIGN_VCENTER|::MyGUI::ALIGN_LEFT) ;
            ::MyGUI::ComboBox* box =
              static_cast< ::MyGUI::ComboBox*>(
                  m_controls->createWidgetRealT("ComboBox",
                                                "ComboBox",
                                                ::MyGUI::FloatCoord(0.5*column+name_length,
                                                                    element_height*row,
                                                                    0.5-name_length,
                                                                    element_height),
                                                ::MyGUI::ALIGN_DEFAULT)) ;
           box->setFontHeight(font_size) ;
           box->addItem("Joystick X") ;
           box->addItem("Joystick Y") ;
           box->addItem("Joystick Rudder") ;
           box->addItem("Joystick Throttle") ;
           box->addItem("Mouse X") ;
           box->addItem("Mouse Y") ;
           box->addItem("Mouse Wheel") ;
           
           Model::PlayerConfiguration::InputAxis inputaxis = 
             getObject()->getTrait<Model::PlayerConfiguration>()
                        ->getInputAxis(*axis) ;
           box->setItemSelect(int(fabs(inputaxis.getAxis()))) ;
          }
          
        }
        
        void PlayerConfiguration::reDraw()
        {
          if (! m_controls)
            return ;
          
          std::set<std::string> commands(Kernel::Trait::getRegisteredCommands()) ;
          for(std::set<std::string>::const_iterator command = commands.begin() ;
              command != commands.end() ;
              ++command)
          {
            Model::PlayerConfiguration::InputEvent event = 
              getObject()->getTrait<Model::PlayerConfiguration>()
                         ->getInputEvent(*command) ;
            
            m_commands[*command]->setCaption(event.toString(Input::getOISKeyboard())) ;
            m_commands[*command]->setTextAlign(::MyGUI::ALIGN_CENTER) ;
          }

        }
        
        void PlayerConfiguration::onSelect(::MyGUI::WidgetPtr _sender)
        {
          ::MyGUI::StaticText* name = static_cast< ::MyGUI::StaticText*>(_sender->getUserData()) ;
          m_command = name->getCaption() ;
          InternalMessage("PlayerConfiguration","setting recording mode") ;
          getObject()->getTrait<Model::PlayerConfiguration>()->setEventRecordingMode() ;
          m_remaining_seconds = 2 ;
        }
        
        void PlayerConfiguration::simulate(const float& seconds)
        {
          // no recording means nothing to stop
          if (! m_is_recording)
            return ;
          
          m_remaining_seconds -= seconds ;
          if (m_remaining_seconds < 0)
            getObject()->getTrait<Model::PlayerConfiguration>()->stopRecording() ;
        }
      }      
    }
  }
}
