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
#include <algorithm>
#include <iostream>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/parameters.h>

#include <input/implementation/ois/mouse.h>


namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      namespace OIS {
        
        bool Mouse::mouseMoved(const ::OIS::MouseEvent& event)
        {
          m_axes[Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseX)] += event.state.X.rel*m_sensibility ;
          m_axes[Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseY)] += event.state.Y.rel*m_sensibility ;
          m_axes[Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseWheel)] += event.state.Z.rel*m_sensibility ;
          return true ;
        }
        
        bool Mouse::mousePressed(const ::OIS::MouseEvent&, 
                                 ::OIS::MouseButtonID button)
        {
          addRealKeyButtonPressed(button) ;
          return true ;
        }
        
        bool Mouse::mouseReleased(const ::OIS::MouseEvent&,
                                  ::OIS::MouseButtonID button)
        {
          addRealKeyButtonReleased(button) ;
          return true ;
        }
  
        Mouse::Mouse()
        : m_sensibility(1)
        {
          m_sensibility = Kernel::Parameters::getValue<float>("Input","MouseSensibility",1);
          
          m_sensibility /= 100 ;
          
          m_axes[Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseX)] = 0 ;
          m_axes[Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseY)] = 0 ;
          m_axes[Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseWheel)] = 0 ;
        }
        
        Model::PlayerConfiguration::InputEvent Mouse::buildEvent(const int& code) const
        {
          return Model::PlayerConfiguration::InputEvent::mouseButton(code) ;
        }
        
        void Mouse::indicatePresence(Model::PlayerConfiguration* configuration) const
        {
          configuration->declareMouse() ;
        }
        
      }
    }
  }
}

