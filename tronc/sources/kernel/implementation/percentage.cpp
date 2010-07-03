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
#include <algorithm>
#include <cmath>
#include <kernel/percentage.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    Percentage::Percentage()
    : m_value(0)
    {}
    
    Percentage::Percentage(const int& value)
    : m_value((value<0?-0.01f:+0.01f)*(float)std::min(abs(value),100))
    {}
    
    Percentage& Percentage::operator=(const int& value)
    {
      m_value = (value<0?-0.01f:+0.01f)*(float)std::min(abs(value),100) ;
      if (!finite(m_value))
        m_value = 0 ;
      return *this ;
    }
    
    Percentage::Percentage(const float& value)
    : m_value((float)(value<0?-1:+1)*std::min((float)fabs(value),1.0f))
    {}
  
    Percentage& Percentage::operator=(const float& value)
    {
      m_value = (float)(value<0?-1:+1)*std::min((float)fabs(value),1.0f) ;
      if (!finite(m_value))
        m_value = 0 ;
      return *this ;
    }

    Percentage& Percentage::operator+=(const Percentage& value)
    {
      m_value += value.m_value ;
      
      m_value = (float)(m_value<0?-1:+1)*std::min((float)fabs(m_value),1.0f) ;
      if (!finite(m_value))
        m_value = 0 ;
      return *this ;
    }

    Percentage Percentage::operator+(const Percentage& value)
    {
      Percentage result(*this) ; 
      return (result+=value) ; 
    }

    
    Percentage::operator int() const
    {
      return int(m_value*100) ;
    }
    
    Percentage::operator float() const
    {
      return m_value ;
    }
    
    bool Percentage::operator==(const Percentage& value) const
    {
      return m_value == value.m_value ;
    }

    bool Percentage::operator==(const int& value) const
    {
      return m_value == Percentage(value).m_value ;
    }

    bool Percentage::operator==(const float& value) const
    {
      return m_value == Percentage(value).m_value ;
    }

    bool Percentage::operator!=(const Percentage& value) const
    {
      return m_value != value.m_value ;
    }

    bool Percentage::operator!=(const int& value) const
    {
      return m_value != Percentage(value).m_value ;
    }

    bool Percentage::operator!=(const float& value) const
    {
      return m_value != Percentage(value).m_value ;
    }
    
  }
}
