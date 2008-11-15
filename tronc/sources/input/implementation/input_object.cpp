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
#include <kernel/parameters.h>
#include <input/implementation/ois/input_controler_set.h>
#include <input/implementation/input_internal.h>
#include <input/implementation/input_object.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      InputObject::InputObject()
      {
        registerObject(this) ;
      }
      
      InputObject::~InputObject()
      {
        unregisterObject(this) ;
      }
      
      const std::set<Model::PlayerConfiguration::InputEvent>& InputObject::getEvents() const
      {
        return m_events ;
      }
      
      const std::map<Model::PlayerConfiguration::InputAxis,
                     Kernel::Percentage>& InputObject::getAxes() const
      {
        return m_axes ;
      }
      
      void InputObject::initAxes()
      {
        for(std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage>::iterator axis = m_axes.begin() ;
            axis != m_axes.end() ;
            ++axis)
        {
          axis->second = 0 ;
        }
      }
      
      void InputObject::addInterpretedKeyButtonPressed(
          const int& code,const Model::PlayerConfiguration::InputEvent& event)
      {
        m_interpreted_key_button_pressed.push_back(code) ;
        m_interpreted_key_button_released.remove(code) ;
        
        m_time_remaining_to_next_press[code] = Kernel::Parameters::getValue<float>("Input","AutoRepeatDelay",OIS::default_autorepeat_delay) ;
        m_events.insert(event) ;
      }
      
      void InputObject::addInterpretedKeyButtonReleased(
          const int& code,const Model::PlayerConfiguration::InputEvent& event)
      {
        m_interpreted_key_button_pressed.remove(code) ;
        m_interpreted_key_button_released.push_back(code) ;
        
        m_events.erase(event) ;
      }
      
      const std::list<int>& InputObject::getKeyButtonPressed() const
      {
        return m_interpreted_key_button_pressed ;
      }

      const std::list<int>& InputObject::getKeyButtonReleased() const
      {
        return m_interpreted_key_button_released ;
      }
      
      void InputObject::clear()
      {
        m_interpreted_key_button_pressed.clear() ;
        m_interpreted_key_button_released.clear() ;
        m_events.clear() ;
      }
      
      void InputObject::addRealKeyButtonPressed(const int& code)
      {
        m_key_button_pressed.push_back(code) ;
        m_key_button_released.remove(code) ;
        addInterpretedKeyButtonPressed(code,buildEvent(code)) ;
      }
      
      void InputObject::addRealKeyButtonReleased(const int& code)
      {
        m_key_button_pressed.remove(code) ;
        m_key_button_released.push_back(code) ;
        addInterpretedKeyButtonReleased(code,buildEvent(code)) ;
      }

      void InputObject::update(const float& time)
      {
        for(std::map<int,float>::iterator 
                 remain = m_time_remaining_to_next_press.begin() ;
            remain != m_time_remaining_to_next_press.end() ;
            ++remain)
        {
          remain->second = std::max(float(0),remain->second-time) ;
          
          // auto_repeat handling
          if (remain->second == 0 && 
              std::find(m_key_button_pressed.begin(),
                        m_key_button_pressed.end(),
                        remain->first) != 
              m_key_button_pressed.end())
          {
            addInterpretedKeyButtonPressed(remain->first,buildEvent(remain->first)) ;
          }
        }
      }
      
    }
  }
}
