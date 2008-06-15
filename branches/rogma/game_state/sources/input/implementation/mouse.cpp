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
#include <kernel/log.h>
#include <kernel/string.h>

#include <input/implementation/mouse.h>


namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      bool Mouse::mouseMoved(const OIS::MouseEvent& event)
      {
        m_axes[Model::PlayerConfiguration::InputAxis::mouseAxis(X)] += event.state.X.rel ;
        m_axes[Model::PlayerConfiguration::InputAxis::mouseAxis(Y)] += event.state.Y.rel ;
        m_axes[Model::PlayerConfiguration::InputAxis::mouseAxis(Z)] += event.state.Z.rel ;
        return true ;
      }
      
      bool Mouse::mousePressed(const OIS::MouseEvent&, 
                               OIS::MouseButtonID button)
      {
        m_events.insert(Model::PlayerConfiguration::InputEvent::mouseButton(button)) ;
        
        return true ;
      }
      
      bool Mouse::mouseReleased(const OIS::MouseEvent&,
                                OIS::MouseButtonID button)
      {
        m_events.erase(Model::PlayerConfiguration::InputEvent::mouseButton(button)) ;
        return true ;
      }

      Mouse::Mouse(const float& i_sensibility)
      : m_sensibility(i_sensibility)
      {
        m_axes[Model::PlayerConfiguration::InputAxis::mouseAxis(X)] = 0 ;
        m_axes[Model::PlayerConfiguration::InputAxis::mouseAxis(Y)] = 0 ;
        m_axes[Model::PlayerConfiguration::InputAxis::mouseAxis(Z)] = 0 ;
      }
      
    }
  }
}

