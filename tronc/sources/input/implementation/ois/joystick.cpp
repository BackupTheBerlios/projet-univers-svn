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
#include <stdlib.h>
#include <plateform.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/parameters.h>

#include <input/implementation/ois/joystick.h>


namespace ProjetUnivers 
{
  namespace Input 
  {
    namespace Implementation 
    {
      namespace OIS 
      {

        bool Joystick::buttonPressed(const ::OIS::JoyStickEvent& event,int button)
        {
          if (Kernel::Parameters::getValue<float>("Input","PrintButtons",false))
          {
            std::cout << "button number " << button << std::endl ;          
          }
          addRealKeyButtonPressed(button) ;
          return true ;
        }
        
        bool Joystick::buttonReleased(const ::OIS::JoyStickEvent& event,int button)
        {
          addRealKeyButtonReleased(button) ;
          return true ;
        }
        
        bool Joystick::axisMoved(const ::OIS::JoyStickEvent& event,int axis)
        {
          if (Kernel::Parameters::getValue<float>("Input","PrintAxes",false))
          {
            std::cout << "axis number " << axis << "=" << event.state.mAxes[axis].abs
                      << std::endl ;          
          }
          
          m_axes[Model::PlayerConfiguration::InputAxis::joystickAxis(m_ois_to_axes[axis])] = 
            float(event.state.mAxes[axis].abs) / ::OIS::JoyStick::MAX_AXIS ;
          return true ;
        }
        
        bool Joystick::sliderMoved(const ::OIS::JoyStickEvent&,int)
        {
          return true ;
        }
        
        bool Joystick::povMoved(const ::OIS::JoyStickEvent& event,int number)
        {
//          std::cout << "pov number " << number << "" 
//                    <<  event.state.mPOV[number].direction << std::endl ;
          
          return true ;
        }
        
        Joystick::Joystick(const float& sensibility)
        : m_sensibility(sensibility)
        {
          // launch automatic configuration, should work because a joystick 
          // was found by OIS...
#if PU_PLATEFORM == PU_PLATEFORM_WIN32
          std::string command("autoconfig_joystick.exe") ;
#elif PU_PLATEFORM == PU_PLATEFORM_LINUX
          std::string command("./autoconfig_joystick") ;
#endif
          command += " > joystick_configuration.ini" ;
          system(command.c_str()) ;
          
          // load the config
          Kernel::Parameters::load("joystick_configuration.ini") ;
          m_ois_to_axes[(unsigned int)Kernel::Parameters::getValue<float>("Joystick","OIS.X",0)] = Model::PlayerConfiguration::InputAxis::JoystickX ;
          m_ois_to_axes[(unsigned int)Kernel::Parameters::getValue<float>("Joystick","OIS.Y",1)] = Model::PlayerConfiguration::InputAxis::JoystickY ;
          m_ois_to_axes[(unsigned int)Kernel::Parameters::getValue<float>("Joystick","OIS.RZ",2)] = Model::PlayerConfiguration::InputAxis::JoystickRudder ;
          m_ois_to_axes[(unsigned int)Kernel::Parameters::getValue<float>("Joystick","OIS.Slider",3)] = Model::PlayerConfiguration::InputAxis::JoystickThrottle ; 
        }

        Model::PlayerConfiguration::InputEvent Joystick::buildEvent(const int& code) const
        {
          return Model::PlayerConfiguration::InputEvent::joystickButton(code) ;
        }
        
        void Joystick::indicatePresence(Model::PlayerConfiguration* configuration) const
        {
          configuration->hasJoystick() ;
        }
        
      }
    }
  }
}

