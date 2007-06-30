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
#include <model/force.h>

namespace ProjetUnivers {
  namespace Model {

    Force::Force() 
    : m_value(),
      m_unit(_Newton)
    {}
    
    Force::Force(const Force& i_f) 
    : m_value(i_f.m_value),
      m_unit(i_f.m_unit)
    {}
    
    Force Force::Newton(const float& i_x,
                        const float& i_y,
                        const float& i_z) 
    {
      return Force(_Newton,i_x,i_y,i_z) ;
    }
    
    Force Force::operator +(const Force& i_f) const 
    {
      if (m_unit == i_f.m_unit)
      {
        return Force(m_unit,
                     m_value[0]+i_f.m_value[0],
                     m_value[1]+i_f.m_value[1],
                     m_value[1]+i_f.m_value[1]) ;
                     
      }
    }
    
    Force Force::operator -(const Force& i_f) const 
    {
      if (m_unit == i_f.m_unit)
      {
        return Force(m_unit,
                     m_value[0]-i_f.m_value[0],
                     m_value[1]-i_f.m_value[1],
                     m_value[1]-i_f.m_value[1]) ;
                     
      }
    }

    Ogre::Vector3 Force::Newton() const  
    {
      if (m_unit == _Newton)
      {
        return m_value ;
      }
    }
    
    Force::Force(const Unit&  i_unit,
                 const float& i_x,
                 const float& i_y,
                 const float& i_z) 
    : m_value(i_x,i_y,i_z),
      m_unit(i_unit)
    {}

    Force Force::operator*(const float& i_factor) const
    {
      Force result(*this) ;
      result.m_value *= i_factor ;
      return result ;
    }
    
    Force Force::operator*(const Orientation& i_orientation) const
    {
      Force result(*this) ;
      result.m_value = i_orientation.getQuaternion()* result.m_value ;
      return result ;
      
    }
  }
}
