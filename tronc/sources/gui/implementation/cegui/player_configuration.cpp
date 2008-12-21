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
#include <model/player_configuration.h>
#include <input/input_gui.h>
#include <gui/implementation/gui_internal.h>
#include <gui/implementation/cegui/cegui.h>
#include <gui/implementation/cegui/gui_controler_set.h>
#include <gui/implementation/cegui/player_configuration.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace CEGUI 
      {

        RegisterControler(PlayerConfiguration,
                          EditedPlayerConfiguration,
                          GUIControlerSet) ;
        
  
        PlayerConfiguration::PlayerConfiguration(
            EditedPlayerConfiguration* configuration,
            GUIControlerSet*           gui)
        : Kernel::Controler<EditedPlayerConfiguration,
                            GUIControlerSet>(configuration,gui),
          m_window(NULL),
          m_controls(NULL),
          m_ok(NULL),
          m_remaining_seconds(0),
          m_is_recording(false)
        {}
        
        void PlayerConfiguration::onInit()
        {
          InternalMessage("PlayerConfiguration","CEGUI::PlayerConfiguration::onInit") ;
          
          try 
          {
            m_window = ::CEGUI::WindowManager::getSingleton().loadWindowLayout(
                "configure_keys.layout") ;

            InternalMessage("GUI",printStructure(m_window,0)) ;
            
            m_controls = m_window->getChild("Controls_content") ;
            
            // set the binding to the current trait
            m_window->setUserData(getObject()) ;
            
            initialDraw() ;
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

          GUI::addActiveGUI(m_window) ;          
        }
          
        void PlayerConfiguration::onUpdate()
        {
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
          InternalMessage("PlayerConfiguration","CEGUI::PlayerConfiguration::onClose") ;
          GUI::removeActiveGUI(m_window) ;          
          if (m_window)
          {
             ::CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
          
          InternalMessage("PlayerConfiguration","New configuration is :") ;
          std::set<std::string> axes(Kernel::Trait::getRegisteredAxes()) ;
          for(std::set<std::string>::const_iterator axis = axes.begin() ;
              axis != axes.end() ;
              ++axis)
          {
            InternalMessage("PlayerConfiguration","Axis " + *axis + "=" +
                            getTrait<Model::PlayerConfiguration>()->getInputAxis(*axis).toString()) ;
            InternalMessage("PlayerConfiguration","Input axis " + 
                            getTrait<Model::PlayerConfiguration>()->getInputAxis(*axis).toString() +
                            " is associated to " + getTrait<Model::PlayerConfiguration>()->getAxis(getTrait<Model::PlayerConfiguration>()->getInputAxis(*axis))) ;
            
          }
        }
        
        void PlayerConfiguration::initialDraw()
        {
          if (! m_controls)
            return ;
          
          int number = 0 ;
          
          // should depend on resolution in fact...
          const int absolute_height = 30 ;
          int number_of_element_by_column = 10 ;
          float element_height = 1.0 / number_of_element_by_column ;

          // these should depend on m_control size
          const unsigned int font_size = 12 ;
          const float name_length = 0.25 ;
          
          ::CEGUI::WindowManager& manager = ::CEGUI::WindowManager::getSingleton() ;
          
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
            
            ::CEGUI::Window* name = manager.createWindow("ProjetUnivers/StaticText") ;
            name->setText( *command) ;
            name->setArea(::CEGUI::UDim(0.5*column,0),
                          ::CEGUI::UDim(element_height*row,0),
                          ::CEGUI::UDim(name_length,0),
                          ::CEGUI::UDim(element_height,0)) ;
            
            m_controls->addChildWindow(name) ;
            
            Model::PlayerConfiguration::InputEvent event = 
              getObject()->getTrait<Model::PlayerConfiguration>()
                         ->getInputEvent(*command) ;

            ::CEGUI::Window* box = manager.createWindow("ProjetUnivers/Button") ;
            box->setArea(::CEGUI::UDim(0.5*column+name_length,0),
                         ::CEGUI::UDim(element_height*row,0),
                         ::CEGUI::UDim(0.5-name_length,0),
                         ::CEGUI::UDim(element_height,0)) ;

            box->setText(event.toString(Input::getOISKeyboard())) ;

            m_controls->addChildWindow(box) ;
            
            m_commands[*command] = box ;
            
            // binding
            box->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                ::CEGUI::Event::Subscriber(&PlayerConfiguration::onSelect,this)) ;
            box->setUserData(name) ;
          }
          
          const int button_width = 16 ;
          
          // binding for axes
          std::set<std::string> axes(Kernel::Trait::getRegisteredAxes()) ;
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
            
            ::CEGUI::Window* name = manager.createWindow("ProjetUnivers/StaticText") ;
            name->setText(*axis) ;
            name->setArea(::CEGUI::UDim(0.5*column,0),
                          ::CEGUI::UDim(element_height*row,0),
                          ::CEGUI::UDim(name_length,0),
                          ::CEGUI::UDim(element_height,0)) ;
            m_controls->addChildWindow(name) ;
            
            ::CEGUI::Window* value = manager.createWindow("ProjetUnivers/StaticText") ;
            value->setArea(::CEGUI::UDim(0.5*column+name_length,button_width),
                           ::CEGUI::UDim(element_height*row,0),
                           ::CEGUI::UDim(0.5-name_length,-2*button_width),
                           ::CEGUI::UDim(element_height,0)) ;
            value->setProperty("HorzFormatting","WordWrapLeftAligned") ;
            
            Model::PlayerConfiguration::InputAxis inputaxis = 
              getObject()->getTrait<Model::PlayerConfiguration>()
                         ->getInputAxis(*axis) ;
            value->setText(inputaxis.toString()) ;
            m_controls->addChildWindow(value) ;
            
            // pointer from name to value in order to change display
            name->setUserData(value) ;
            
            // decrease and increase
            ::CEGUI::Window* decrease = manager.createWindow("ProjetUnivers/DecreaseButton") ;
            decrease->setArea(::CEGUI::UDim(0.5*column+name_length,0),
                              ::CEGUI::UDim(element_height*row,0),
                              ::CEGUI::UDim(0,button_width),
                              ::CEGUI::UDim(element_height,0)) ;
            decrease->setUserData(name) ;
            m_controls->addChildWindow(decrease) ;
            decrease->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                     ::CEGUI::Event::Subscriber(&PlayerConfiguration::onDecrease,this)) ;

            ::CEGUI::Window* increase = manager.createWindow("ProjetUnivers/IncreaseButton") ;
            increase->setArea(::CEGUI::UDim(0.5*column+0.5,-button_width),
                              ::CEGUI::UDim(element_height*row,0),
                              ::CEGUI::UDim(0,button_width),
                              ::CEGUI::UDim(element_height,0)) ;
            increase->setUserData(name) ;
            m_controls->addChildWindow(increase) ;
            increase->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                     ::CEGUI::Event::Subscriber(&PlayerConfiguration::onIncrease,this)) ;
            
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
            
            m_commands[*command]->setText(event.toString(Input::getOISKeyboard())) ;
          }
        }
        
        bool PlayerConfiguration::onSelect(const ::CEGUI::EventArgs& args)
        {
          const ::CEGUI::WindowEventArgs* argument = dynamic_cast<const ::CEGUI::WindowEventArgs*>(&args) ;
          if (! getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecordingMode() &&
              argument && argument->window)
          {
            ::CEGUI::Window* name = (::CEGUI::Window*)argument->window->getUserData() ;
            m_command = name->getText().c_str() ;
            InternalMessage("PlayerConfiguration","setting recording mode") ;
            getObject()->getTrait<Model::PlayerConfiguration>()->setEventRecordingMode() ;
            m_remaining_seconds = 2 ;
          }          
          
          return true ;
        }
        
        bool PlayerConfiguration::onDecrease(const ::CEGUI::EventArgs& args)
        {
          const ::CEGUI::WindowEventArgs* argument = dynamic_cast<const ::CEGUI::WindowEventArgs*>(&args) ;
          if (argument && argument->window)
          {
            ::CEGUI::Window* name = (::CEGUI::Window*)argument->window->getUserData() ;
            std::string axis_name(name->getText().c_str()) ; 

            Model::PlayerConfiguration* configuration = getTrait<Model::PlayerConfiguration>() ;
            Model::PlayerConfiguration::InputAxis axis = configuration->getInputAxis(axis_name) ;

            --axis ;
            configuration->addMapping(axis,axis_name) ;

            ::CEGUI::Window* value = (::CEGUI::Window*)name->getUserData() ;
            value->setText(axis.toString()) ;
          }
        }

        bool PlayerConfiguration::onIncrease(const ::CEGUI::EventArgs& args)
        {
          const ::CEGUI::WindowEventArgs* argument = dynamic_cast<const ::CEGUI::WindowEventArgs*>(&args) ;
          if (argument && argument->window)
          {
            ::CEGUI::Window* name = (::CEGUI::Window*)argument->window->getUserData() ;
            std::string axis_name(name->getText().c_str()) ; 

            Model::PlayerConfiguration* configuration = getTrait<Model::PlayerConfiguration>() ;
            Model::PlayerConfiguration::InputAxis axis = configuration->getInputAxis(axis_name) ;

            ++axis ;
            configuration->addMapping(axis,axis_name) ;

            ::CEGUI::Window* value = (::CEGUI::Window*)name->getUserData() ;
            value->setText(axis.toString()) ;
          }
        }
        
        void PlayerConfiguration::simulate(const float& seconds)
        {
          // no recording means nothing to stop
          if (! getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecordingMode())
            return ;
          
          m_remaining_seconds -= seconds ;
          if (m_remaining_seconds<0)
            getObject()->getTrait<Model::PlayerConfiguration>()->stopRecording() ;
        }
      }      
    }
  }
}
