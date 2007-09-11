/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <model/mobile.h>

namespace ProjetUnivers {
  namespace Model {

    Mobile::Mobile()
    : Kernel::Trait(), 
      m_speed(), 
      m_angular_speed()
    {}

    Mobile::Mobile(const Speed& speed)
    : Kernel::Trait(), 
      m_speed(speed), 
      m_angular_speed()
    {}

    void Mobile::setSpeed(const Speed& i_new_speed)
    {
      m_speed = i_new_speed ;
      notify() ;
    }

    const Speed& Mobile::getSpeed() const
    {
      return m_speed ;
    }

    const AngularSpeed& Mobile::getAngularSpeed() const
    {
      return m_angular_speed ;
    }

    void Mobile::setAngularSpeed(const AngularSpeed& i_new_angular_speed)
    {
      m_angular_speed = i_new_angular_speed ;
      notify() ;
    }

  }
}
