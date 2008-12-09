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
#include <map>
#include <iostream>
#include <math.h>
#include <OISKeyboard.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <model/player_configuration.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
  
    RegisterTrait(PlayerConfiguration) ;
    
    PlayerConfiguration::InputEvent::InputEvent()
    : type(InputEvent::none),
      key_or_bouton(0)
    {}
    
    PlayerConfiguration::InputEvent PlayerConfiguration::InputEvent::joystickButton(int button)
    {
      InputEvent result ;
      result.type = InputEvent::joystick ;
      result.key_or_bouton = button ;
      return result ;
    }
    
    PlayerConfiguration::InputEvent PlayerConfiguration::InputEvent::mouseButton(int button)
    {
      InputEvent result ;
      result.type = InputEvent::mouse ;
      result.key_or_bouton = button ;
      return result ;
    }
    
    PlayerConfiguration::InputEvent PlayerConfiguration::InputEvent::key(int key)
    {
      InputEvent result ;
      result.type = InputEvent::keyboard ;
      result.key_or_bouton = key ;
      return result ;
    }
    
    bool PlayerConfiguration::InputEvent::operator < (const PlayerConfiguration::InputEvent& event) const
    {
      return type < event.type || (type == event.type && key_or_bouton < event.key_or_bouton) ;
    }

    bool PlayerConfiguration::InputEvent::operator==(const PlayerConfiguration::InputEvent& event) const
    {
      return type == event.type && key_or_bouton == event.key_or_bouton ;
    }
    
    std::string PlayerConfiguration::InputEvent::toString(OIS::Keyboard* ois_keyboard) const
    {
      InternalMessage("Model","PlayerConfiguration::InputEvent::toString") ;
      
      std::string result ;
      switch(type)
      {
      case joystick:
        InternalMessage("Model","PlayerConfiguration::InputEvent::toString joystick") ;
        return "Joystick Button " + Kernel::toString(key_or_bouton) ;
      case mouse:
        InternalMessage("Model","PlayerConfiguration::InputEvent::toString mouse") ;
        return "Mouse Button " + Kernel::toString(key_or_bouton) ;
      case keyboard:
        InternalMessage("Model","PlayerConfiguration::InputEvent::toString keyboard") ;
        return ois_keyboard->getAsString(OIS::KeyCode(key_or_bouton)) ;
      default:
        InternalMessage("Model","PlayerConfiguration::InputEvent::toString none") ;
        return "" ;
      }
    }

    PlayerConfiguration::InputAxis::InputAxis()
    :m_axis(Unassigned)
    {}
    
    PlayerConfiguration::InputAxis::InputAxis(int _axis)
    :m_axis(_axis)
    {}
    
    PlayerConfiguration::InputAxis::InputAxis& PlayerConfiguration::InputAxis::operator++()
    {
      if (m_axis == PlayerConfiguration::InputAxis::MouseWheel)
        m_axis = -PlayerConfiguration::InputAxis::MouseWheel ;
      else
        m_axis = (PlayerConfiguration::InputAxis::Axis)(m_axis + 1) ;
      return *this ; 
    }

    PlayerConfiguration::InputAxis::InputAxis& PlayerConfiguration::InputAxis::operator--()
    {
      if (m_axis == -PlayerConfiguration::InputAxis::MouseWheel)
        m_axis = PlayerConfiguration::InputAxis::MouseWheel ;
      else
        m_axis = (PlayerConfiguration::InputAxis::Axis)(m_axis - 1) ;
      return *this ;
    }
    
    bool PlayerConfiguration::InputAxis::operator < (const PlayerConfiguration::InputAxis& axis) const
    {
      return this->m_axis < axis.m_axis ;
    }

    bool PlayerConfiguration::InputAxis::operator==(const PlayerConfiguration::InputAxis& axis) const
    {
      return this->m_axis == axis.m_axis ;
    }

    bool PlayerConfiguration::InputAxis::isInversed() const
    {
      return m_axis < 0 ;
    }
    
    int PlayerConfiguration::InputAxis::getAxis() const
    {
      return m_axis ;
    }
    
    PlayerConfiguration::InputAxis PlayerConfiguration::InputAxis::operator-() const
    {
      return InputAxis(m_axis) ;
    }
    
    PlayerConfiguration::PlayerConfiguration()
    : m_event_recording_mode(false),
      m_event_recorded(false),
      m_has_joystick(false),
      m_has_mouse(false)
    {}
    
    void PlayerConfiguration::declareJoystick()
    {
      m_has_joystick = true ;
    }

    void PlayerConfiguration::declareMouse()
    {
      m_has_mouse = true ;
    }

    bool PlayerConfiguration::hasJoystick() const
    {
      return m_has_joystick ;
    }

    bool PlayerConfiguration::hasMouse() const
    {
      return m_has_mouse ;
    }
    
    void PlayerConfiguration::addMapping(const InputEvent&  event,
                                         const std::string& command)
    {
      InternalMessage("PlayerConfiguration","PlayerConfiguration::addMapping") ;
      m_input_event_to_commands[event] = command ;
      m_command_to_input_events[command] = event ;
      notify() ;
    }
    
    void PlayerConfiguration::addMapping(const InputAxis&   axis,
                                         const std::string& axis_command)
    {
      InternalMessage("PlayerConfiguration","PlayerConfiguration::addMapping " + axis_command + "=" + axis.toString() ) ;
      m_input_axis_to_axes[axis] = axis_command ;
      m_axis_to_input_axes[axis_command] = axis ;
      notify() ;
    }
    
    std::string PlayerConfiguration::getCommand(const InputEvent& event) const
    {
      std::map<InputEvent,std::string>::const_iterator finder = m_input_event_to_commands.find(event) ;
      
      if (finder != m_input_event_to_commands.end())
        return finder->second ;
      else
        return "" ;
    }

    std::string PlayerConfiguration::getAxis(const InputAxis& axis) const
    {
      std::map<InputAxis,std::string>::const_iterator finder = m_input_axis_to_axes.find(axis) ;
      
      if (finder != m_input_axis_to_axes.end())
        return finder->second ;
      else
        return "" ;
    }

    const PlayerConfiguration::InputEvent& InputEventNone = PlayerConfiguration::InputEvent() ;
    
    const PlayerConfiguration::InputEvent& PlayerConfiguration::getInputEvent(const std::string& command) const
    {
      InternalMessage("Model","PlayerConfiguration::getInputEvent " + command + " on " + Kernel::toString(m_command_to_input_events.size())) ;
      std::map<std::string,InputEvent>::const_iterator finder = m_command_to_input_events.find(command) ;
      
      if (finder != m_command_to_input_events.end())
        return finder->second ;
      else
        return InputEventNone ;
    }
    
    const PlayerConfiguration::InputAxis& InputAxisNone = PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::Unassigned) ;
    
    const PlayerConfiguration::InputAxis& PlayerConfiguration::getInputAxis(const std::string& axis) const
    {
      InternalMessage("PlayerConfiguration","PlayerConfiguration::getInputAxis for " + axis + 
                      " on " + Kernel::toString(m_axis_to_input_axes.size())) ;   
      std::map<std::string,InputAxis>::const_iterator finder = m_axis_to_input_axes.find(axis) ;
      
      if (finder != m_axis_to_input_axes.end())
        return finder->second ;
      else
        return InputAxisNone ;
    }

    void PlayerConfiguration::setEventRecordingMode()
    {
      InternalMessage("PlayerConfiguration","PlayerConfiguration::setEventRecordingMode") ;
      m_event_recording_mode = true ;
      notify() ;
    }
    
    void PlayerConfiguration::recordEvent(const PlayerConfiguration::InputEvent& event)
    {
      InternalMessage("PlayerConfiguration","PlayerConfiguration::recordEvent") ;
      m_event_recorded = true ;
      m_event_recording_mode = false ;
      m_recorded_event = event ;
      notify() ;
    }

    bool PlayerConfiguration::isEventRecordingMode() const
    {
      return m_event_recording_mode ;
    }
    
    bool PlayerConfiguration::isEventRecorded() const
    {
      return m_event_recorded ;
    }
    
    const PlayerConfiguration::InputEvent& PlayerConfiguration::getRecordedEvent() const
    {
      return m_recorded_event ;
    }
    
    void PlayerConfiguration::stopRecording()
    {
      InternalMessage("PlayerConfiguration","PlayerConfiguration::stopRecording") ;
      m_event_recorded = false ;
      m_event_recording_mode = false ;
      notify() ;
    }
    
    std::string PlayerConfiguration::InputAxis::toString() const
    {
      std::string mode ;
      if (m_axis < 0)
      {
        mode = "Inverted " ;
      }
      
      int axis = (int)fabs(m_axis) ;
      switch(axis)
      {
      case JoystickX:
        return mode + "Joystick X" ;
      case JoystickY:
        return mode + "Joystick Y" ;
      case JoystickRudder:
        return mode + "Joystick Rudder" ;
      case JoystickThrottle:
        return mode + "Joystick Throttle" ;
      case MouseX:
        return mode + "Mouse X" ;
      case MouseY:
        return mode + "Mouse Y" ;
      case MouseWheel :
        return mode + "Mouse Wheel" ;
      default:
        return "" ;
      
      }
    }
    
    Kernel::Trait* PlayerConfiguration::read(Kernel::Reader* reader)
    {
      PlayerConfiguration* result = new PlayerConfiguration() ;
      
      while (! (reader->isEndNode() && reader->getTraitName() == "PlayerConfiguration") && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "Mapping")
        {
          std::string command_name ;
          std::map<std::string,std::string>::const_iterator finder ; 
          finder = reader->getAttributes().find("command") ;
          if (finder != reader->getAttributes().end())
          {
            command_name = finder->second ;
          }
          
          while (reader->processNode() && !reader->isTraitNode()) 
          {}
          
          bool is_event = false ;
          bool is_axis = false ;
          InputEvent event ;
          InputAxis axis ;
          
//          std::cout << "reading mapping " << command_name << std::endl ; 
//          std::cout << "next is " << reader->getTraitName() << std::endl ;
          
          if (reader->getTraitName() == "Key")
          {
            is_event = true ;
            finder = reader->getAttributes().find("number") ;
            if (finder != reader->getAttributes().end())
            {
              event = InputEvent::key(atoi(finder->second.c_str())) ;
            }
          }
          else if (reader->getTraitName() == "JoystickButton")
          {
            is_event = true ;
            finder = reader->getAttributes().find("number") ;
            if (finder != reader->getAttributes().end())
            {
              event = InputEvent::joystickButton(atoi(finder->second.c_str())) ;
            }
          }
          else if (reader->getTraitName() == "MouseButton")
          {
            is_event = true ;
            finder = reader->getAttributes().find("number") ;
            if (finder != reader->getAttributes().end())
            {
              event = InputEvent::mouseButton(atoi(finder->second.c_str())) ;
            }
          }
          else if (reader->getTraitName() == "JoystickX")
          {
            is_axis = true ;
            axis = InputAxis(InputAxis::JoystickX) ;
          }
          else if (reader->getTraitName() == "JoystickY")
          {
            is_axis = true ;
            axis = InputAxis(InputAxis::JoystickY) ;
          }
          else if (reader->getTraitName() == "JoystickRudder")
          {
            is_axis = true ;
            axis = InputAxis(InputAxis::JoystickRudder) ;
          }
          else if (reader->getTraitName() == "JoystickThrottle")
          {
            is_axis = true ;
            axis = InputAxis(InputAxis::JoystickThrottle) ;
          }
          else if (reader->getTraitName() == "MouseX")
          {
            is_axis = true ;
            axis = InputAxis(InputAxis::MouseX) ;
          }
          else if (reader->getTraitName() == "MouseY")
          {
            is_axis = true ;
            axis = InputAxis(InputAxis::MouseY) ;
          }
          else if (reader->getTraitName() == "MouseWheel")
          {
            is_axis = true ;
            axis = InputAxis(InputAxis::MouseWheel) ;
          }
          
          if (is_event)
          {
            result->addMapping(event,command_name) ;
          }
          else if (is_axis)
          {
            result->addMapping(axis,command_name) ;
          }
          reader->processNode() ;
        }
      }
      reader->processNode() ;

      return result ;
    }
    
  }
}
