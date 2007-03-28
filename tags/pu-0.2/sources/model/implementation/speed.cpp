/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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
#include <model/speed.h>


namespace ProjetUnivers {
  namespace Model {

    Speed::Speed()
    : m_unit(_MeterPerSecond),
      m_value(0,0,0)
    {}

    Speed::Speed(const Speed& i_speed)
    : m_unit(i_speed.m_unit), 
      m_value(i_speed.m_value)
    {}

    Speed Speed::MeterPerSecond(const float& i_x,
                                const float& i_y,
                                const float& i_z)
    {
      return Speed(_MeterPerSecond,i_x,i_y,i_z) ;
    }

    Ogre::Vector3 Speed::MeterPerSecond() const
    {
      if (m_unit == _MeterPerSecond)
      {
        return m_value ;
      }
      
      /// @todo
      return m_value ;
    }
    
    Speed Speed::operator +(const Speed& i_speed) const
    {
      Speed result(*this) ;
      
      /// @todo dealt with different units
      result.m_value += i_speed.m_value ;  
      
      return result ;
    }

    /// Substraction.
    Speed Speed::operator -(const Speed& i_speed) const 
    {
      Speed result(*this) ;
      
      /// @todo dealt with different units
      result.m_value -= i_speed.m_value ;  
      
      return result ;
      
    }
    
    /// Multiplication.
    Speed Speed::operator *(const float& i_value) const 
    {
      Speed result(*this) ;
      result.m_value *= i_value ;  
      return result ;
    }

    Speed Speed::operator /(const float& i_value) const
    {
      Speed result(*this) ;
      result.m_value *= i_value ;  
      return result ;
      
    }
    


    
    Speed::Speed(const Unit&  i_unit,
                 const float& i_x,
                 const float& i_y,
                 const float& i_z)
    : m_unit(i_unit),
      m_value(i_x,i_y,i_z)
    {}


  }
}

