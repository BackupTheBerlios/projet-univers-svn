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
#include <model/player_configuration.h>

namespace ProjetUnivers {
  namespace Model {
  
    PlayerConfiguration::InputEvent::InputEvent()
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

    PlayerConfiguration::InputAxis::InputAxis()
    {}
    
    PlayerConfiguration::InputAxis PlayerConfiguration::InputAxis::joystickAxis(int axis)
    {
      InputAxis result ;
      result.type = InputAxis::joystick ;
      result.axis = axis ;
      return result ;
    }
    
    PlayerConfiguration::InputAxis PlayerConfiguration::InputAxis::mouseAxis(int axis)
    {
      InputAxis result ;
      result.type = InputAxis::mouse ;
      result.axis = axis ;
      return result ;
    }
    
    bool PlayerConfiguration::InputAxis::operator < (const PlayerConfiguration::InputAxis& axis) const
    {
      return type < axis.type || (type == axis.type && this->axis < axis.axis) ;
    }
    
    PlayerConfiguration::InputAxis PlayerConfiguration::InputAxis::operator-() const
    {
      InputAxis result ;
      result.type = type ;
      result.axis = -axis ;
      return result ;
    }
    
    PlayerConfiguration::PlayerConfiguration()
    {}
      
    void PlayerConfiguration::addMapping(const InputEvent&  event,
                                         const std::string& command)
    {
      m_commands[event] = command ;
    }
    
    void PlayerConfiguration::addMapping(const InputAxis&   axis,
                                         const std::string& axis_command)
    {
      m_axes[axis] = axis_command ;
    }
    
    std::string PlayerConfiguration::getCommand(const InputEvent& event) const
    {
      std::map<InputEvent,std::string>::const_iterator finder = m_commands.find(event) ;
      
      if (finder != m_commands.end())
        return finder->second ;
      else
        return "" ;
    }

    std::string PlayerConfiguration::getAxis(const InputAxis& axis) const
    {
      std::map<InputAxis,std::string>::const_iterator finder = m_axes.find(axis) ;
      
      if (finder != m_axes.end())
        return finder->second ;
      else
        return "" ;
    }
        
  }
}
