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
#include <kernel/log.h>

#include <model/position.h>
#include <model/positionned.h>

namespace ProjetUnivers {
  namespace Model {


    Position::Position()
    : m_value(0,0,0),
      m_unit(Distance::_Meter)
    {}

    Position::Position(const Position& i_position)
    : m_value(i_position.m_value),
      m_unit(i_position.m_unit)
    {}

    Position::Position(Distance::Unit i_unit,
                       float          i_x, 
                       float          i_y, 
                       float          i_z)
    : m_value(i_x,i_y,i_z),
      m_unit(i_unit)
      
    {}

    Position Position::Meter(float i_x, 
                             float i_y, 
                             float i_z)
    {
      return Position(Distance::_Meter,i_x,i_y,i_z) ;
    }


    Ogre::Vector3 Position::Meter() const
    {
      if (m_unit == Distance::_Meter)
      {
        return m_value ;
      }
      return Ogre::Vector3(Distance::convert(m_value[0],
                                             m_unit,
                                             Distance::_Meter),
                           Distance::convert(m_value[1],
                                             m_unit,
                                             Distance::_Meter),
                           Distance::convert(m_value[2],
                                             m_unit,
                                             Distance::_Meter)) ;                                            
    }
    
    Position Position::operator+(const Position& i_position) const
    {
      Distance::Unit result_unit = Distance::bestCompatibleUnit(m_unit,
                                                                i_position.m_unit) ;
      /// convert all data into the result_unit
      return Position(result_unit,
                      Distance::convert(m_value[0],
                                        m_unit,
                                        result_unit) +
                      Distance::convert(i_position.m_value[0],
                                        i_position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[1],
                                        m_unit,
                                        result_unit) +
                      Distance::convert(i_position.m_value[1],
                                        i_position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[2],
                                        m_unit,
                                        result_unit) +
                      Distance::convert(i_position.m_value[2],
                                        i_position.m_unit,
                                        result_unit)) ;
      
    }

    Position Position::operator-(const Position& i_position) const
    {
      
      Distance::Unit result_unit = Distance::bestCompatibleUnit(m_unit,
                                                                i_position.m_unit) ;
      /// convert all data into the result_unit
      return Position(result_unit,
                      Distance::convert(m_value[0],
                                        m_unit,
                                        result_unit) -
                      Distance::convert(i_position.m_value[0],
                                        i_position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[1],
                                        m_unit,
                                        result_unit) -
                      Distance::convert(i_position.m_value[1],
                                        i_position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[2],
                                        m_unit,
                                        result_unit) -+
                      Distance::convert(i_position.m_value[2],
                                        i_position.m_unit,
                                        result_unit)) ;
      
    }
    
    Distance Position::getXCoordinate() const
    {
      return Distance(m_unit,m_value[0]) ;
    }

    Distance Position::getYCoordinate() const
    {
      return Distance(m_unit,m_value[1]) ;
    }
    
    Distance Position::getZCoordinate() const
    {
      return Distance(m_unit,m_value[2]) ;
    }
    
    std::ostream& operator<<(std::ostream& out,const Position& i_position)
    {
      out << "Position(Unit=" << i_position.m_unit << "," << i_position.m_value << ")" ;
      return out ;
    }
  }
}
