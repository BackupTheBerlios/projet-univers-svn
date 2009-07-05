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
#include <kernel/log.h>

#include <model/position.h>
#include <model/positionned.h>

namespace ProjetUnivers
{
  namespace Model
  {

    Position::Position()
    : m_value(0,0,0),
      m_unit(Distance::_Meter)
    {}

    Position::Position(const Position& position)
    : m_value(position.m_value),
      m_unit(position.m_unit)
    {}

    Position::Position(Distance::Unit unit,
                       const float&   x,
                       const float&   y,
                       const float&   z)
    : m_value(x,y,z),
      m_unit(unit)
    {}

    Position Position::Meter(const float& x,
                             const float& y,
                             const float& z)
    {
      return Position(Distance::_Meter,x,y,z) ;
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

    Position Position::operator+(const Position& position) const
    {
      Distance::Unit result_unit = Distance::bestCompatibleUnit(m_unit,
                                                                position.m_unit) ;
      /// convert all data into the result_unit
      return Position(result_unit,
                      Distance::convert(m_value[0],
                                        m_unit,
                                        result_unit) +
                      Distance::convert(position.m_value[0],
                                        position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[1],
                                        m_unit,
                                        result_unit) +
                      Distance::convert(position.m_value[1],
                                        position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[2],
                                        m_unit,
                                        result_unit) +
                      Distance::convert(position.m_value[2],
                                        position.m_unit,
                                        result_unit)) ;

    }

    Position Position::operator-(const Position& position) const
    {

      Distance::Unit result_unit = Distance::bestCompatibleUnit(m_unit,
                                                                position.m_unit) ;
      /// convert all data into the result_unit
      return Position(result_unit,
                      Distance::convert(m_value[0],
                                        m_unit,
                                        result_unit) -
                      Distance::convert(position.m_value[0],
                                        position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[1],
                                        m_unit,
                                        result_unit) -
                      Distance::convert(position.m_value[1],
                                        position.m_unit,
                                        result_unit),
                      Distance::convert(m_value[2],
                                        m_unit,
                                        result_unit) -+
                      Distance::convert(position.m_value[2],
                                        position.m_unit,
                                        result_unit)) ;

    }

    Position Position::operator*(const Orientation& orientation) const
    {
      Position result(*this) ;
      result.m_value = orientation.getQuaternion()*result.m_value ;

      return result ;
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

    Distance Position::calculateDistance(const Position& position) const
    {
      Position temp(position - *this) ;
      return Distance(temp.m_unit,temp.m_value.length()) ;
    }

    std::ostream& operator<<(std::ostream& out,const Position& position)
    {
      out << "Position(Unit=" << position.m_unit << "," << position.m_value << ")" ;
      return out ;
    }

    bool Position::operator!=(const Position& position) const
    {
      return ! (*this == position) ;
    }

    bool Position::operator==(const Position& position) const
    {
      Ogre::Vector3 this_meter(Meter()) ;
      Ogre::Vector3 position_meter(position.Meter()) ;
      return this_meter == position_meter ;
    }

    bool Position::operator<(const Position& position) const
    {
      Ogre::Vector3 this_meter(Meter()) ;
      Ogre::Vector3 position_meter(position.Meter()) ;

      return (this_meter.x < position_meter.x) ||
             (this_meter.x == position_meter.x && this_meter.y < position_meter.y) ||
             (this_meter.x == position_meter.x && this_meter.y == position_meter.y && this_meter.y < position_meter.y) ;
    }

    Position Position::read(Kernel::Reader* reader)
    {
      Position result(Distance::_Meter,0,0,0) ;

      std::map<std::string,std::string>::const_iterator finder ;

      finder = reader->getAttributes().find("x") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value.x = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::Position::read required attribute : x") ;
      }

      finder = reader->getAttributes().find("y") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value.y = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::Position::read required attribute : y") ;
      }

      finder = reader->getAttributes().find("z") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value.z = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::Position::read required attribute : z") ;
      }

      finder = reader->getAttributes().find("unit") ;
      if (finder != reader->getAttributes().end())
      {
        if (finder->second == "LightYear")
        {
          result.m_unit = Distance::_LightYear ;
        }
        else if (finder->second == "Parsec")
        {
          result.m_unit = Distance::_Parsec ;
        }
        else if (finder->second == "Meter")
        {
          result.m_unit = Distance::_Meter ;
        }
        else
        {
          ErrorMessage("Model::Position::read invalid unit : " + finder->second) ;
        }
      }
      else
      {
        ErrorMessage("Model::Position::read required attribute : unit") ;
      }

      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}

      reader->processNode() ;

      return result ;
    }

  }
}
