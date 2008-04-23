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
#include <model/duration.h>

namespace ProjetUnivers {
  namespace Model {
      
    Duration::Duration()
    : m_value(0),
      m_unit(_Second)
    {}
    
    Duration::Duration(Unit i_unit,float i_value)
    : m_value(i_value),
      m_unit(i_unit)
    {}
    
    Duration Duration::Second(float i_seconds)
    {
      return Duration(_Second,i_seconds) ;
    }
    
    Duration::Duration(const Duration& i_duration)
    : m_value(i_duration.m_value),
    m_unit(i_duration.m_unit)

    {}
    
    Duration Duration::operator +(const Duration& i_duration) const
    {
      if (m_unit == i_duration.m_unit)
      {
        return Duration(m_unit,m_value+i_duration.m_value) ;
      }

      /// @todo
      return Duration() ;
    }

    Duration Duration::operator -(const Duration& i_duration) const 
    {
      if (m_unit == i_duration.m_unit)
      {
        return Duration(m_unit,m_value-i_duration.m_value) ;
      }

      /// @todo
      return Duration() ;
    }
    
    float Duration::Second() const
    {
      if (m_unit == _Second)
      {
        return m_value ;
      }
      
      /// @todo
      return 0 ;
    } 
  
    Duration& Duration::operator=(const Duration& duration)
    {
      if (&duration != this)
      {
        m_value = duration.m_value ;
        m_unit = duration.m_unit ;
      }
      
      return *this ;
    }
    
  }
}

