/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <kernel/string.h>
#include <kernel/parameters.h>

#include <input/implementation/joystick.h>


namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      bool Joystick::buttonPressed(const OIS::JoyStickEvent& event,int button)
      {
        m_events.insert(Model::PlayerConfiguration::InputEvent::joystickButton(button)) ;
        return true ;
      }
      
      bool Joystick::buttonReleased(const OIS::JoyStickEvent& event,int button)
      {
        m_events.erase(Model::PlayerConfiguration::InputEvent::joystickButton(button)) ;
        return true ;
      }
      
      bool Joystick::axisMoved(const OIS::JoyStickEvent& event,int axis)
      {
        m_axes[Model::PlayerConfiguration::InputAxis::joystickAxis(axis)] = 
          float(event.state.mAxes[axis].abs) / OIS::JoyStick::MAX_AXIS ;
        return true ;
      }
      
      bool Joystick::sliderMoved(const OIS::JoyStickEvent&,int)
      {
        return true ;
      }
      
      bool Joystick::povMoved(const OIS::JoyStickEvent&,int)
      {
        return true ;
      }

      Joystick::Joystick(const float& sensibility)
      : m_sensibility(sensibility)
      {}
    }
  }
}

