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
      
    }
  }
}
