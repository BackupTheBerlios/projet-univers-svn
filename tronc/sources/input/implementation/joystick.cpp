/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <input/implementation/joystick.h>


namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      namespace
      {
        /// local data
        const int max = 100 ;
        const int maximum_X = max ;
        const int maximum_Y = max ;
        const float pi = 3.1415926535 ;
      }

      bool Joystick::buttonPressed(
        const OIS::JoyStickEvent&,
        int)
      {
        return true ;
      }
      
      bool Joystick::buttonReleased(const OIS::JoyStickEvent&,int)
      {
        return true ;
      }
      
      /*!
      @todo 
        configuration depends of joystick
        I do not know how we can determine mapping between axix numbers
        and X/Y/Z ?
        
        
      */ 
      bool Joystick::axisMoved(const OIS::JoyStickEvent& event,int i_axis)
      {
        if (m_controled_object)
        {
          X = 100 * event.state.mAxes[0].abs / OIS::JoyStick::MAX_AXIS ;
          Y = - 100 * event.state.mAxes[1].abs / OIS::JoyStick::MAX_AXIS ;
          Z = 100 * event.state.mAxes[5].abs / OIS::JoyStick::MAX_AXIS ; 
          
          m_controled_object->call("set_axis_X",X) ;
          m_controled_object->call("set_axis_Y",Y) ;
          m_controled_object->call("set_axis_Z",Z) ;

        }
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
      

      Joystick::Joystick(const float& i_sensibility)
      : m_time_delay(0.0),
        m_controled_object(NULL),
        m_sensibility(i_sensibility),
        X(0),
        Y(0),
        Z(0)
      {}
      
      Joystick::~Joystick()
      {}
      
      void Joystick::setTimeDelay(const float& i_seconds)
      {
        m_time_delay = i_seconds ;
      }
      
      void Joystick::setControledObject(Kernel::Object* i_object)
      {
        m_controled_object = i_object ;
      }
    }
  }
}

