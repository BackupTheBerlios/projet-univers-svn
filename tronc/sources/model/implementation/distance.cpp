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
#include <stdlib.h>
#include <kernel/log.h>
#include <kernel/error.h>

#include <model/distance.h>

namespace ProjetUnivers {
  namespace Model {


    bool operator<=(Distance::Unit _u1, 
                    Distance::Unit _u2)
    {

      if (_u1 == Distance::_Meter)
        return true ;

      if (_u1 == Distance::_LightYear)
      {
        if (_u2 == Distance::_Parsec || _u2 == Distance::_LightYear)
          return true ;
        else
          return false ;
      }
        
      if (_u1 == Distance::_Parsec && _u2 != Distance::_Parsec)
    
        return false;
      
      return true ;
    }

    Distance::Distance()
    : m_value(0), 
      m_unit(_Meter)
    {}

    Distance::Distance(const Unit& _unit, const float& _value)
    : m_value(_value), m_unit(_unit)
    {}
      
    Distance::Distance(const Distance& _distance)
    : m_value(_distance.m_value), m_unit(_distance.m_unit)
    {}
    
    Distance Distance::operator +(const Distance& distance) const
    {
      return Distance(_Meter,convert(m_value,m_unit,_Meter)+convert(distance.m_value,distance.m_unit,_Meter)) ;
    }

    Distance Distance::operator -(const Distance& distance) const
    {
      return Distance(_Meter,convert(m_value,m_unit,_Meter)-convert(distance.m_value,distance.m_unit,_Meter)) ;
    }

    Distance Distance::read(Kernel::Reader* reader)
    {
      Distance result ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("value") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::Distance::read required attribute : value") ;
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
          ErrorMessage("Model::Distance::read invalid unit : " + finder->second) ;
        }
      }
      else
      {
        ErrorMessage("Model::Distance::read required attribute : unit") ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;
      
      return result ;            
    }   

    float Distance::convert(float i_value,
                            Unit  i_from,
                            Unit  i_to)
    {
      switch (i_from)
      {
      case _Meter:
        {
          switch (i_to)
          {
          case _Meter:
            return i_value ;
          case _LightYear:
            return i_value / 9.46e+15 ;
          case _Parsec:
            return i_value / 3.08e+16 ;
          }
        }
      case _LightYear:
        {
          switch (i_to)
          {
          case _Meter:
            return i_value * 9.46e+15 ;
          case _LightYear:
            return i_value ;
          case _Parsec:
            return i_value / 3.26 ;
          }
        }
      case _Parsec:
        {
          switch (i_to)
          {
          case _Meter:
            return i_value * 3.08e+16 ;
          case _LightYear:
            return i_value * 3.26;
          case _Parsec:
            return i_value ;
          }
        }
      }
      
      return 0 ;
    }
  
    Distance::Unit Distance::bestCompatibleUnit(
        Distance::Unit i_unit1,
        Distance::Unit i_unit2)
    {
      if (i_unit1 <= i_unit2)
      {
        return i_unit2 ;
      }
      else
      {
        return i_unit1 ;
      }
    }
      
    float Distance::Parsec() const
    {
      return convert(m_value,m_unit,_Parsec) ;
    }
      
    float Distance::Meter() const
    {
      return convert(m_value,m_unit,_Meter) ;
    }
     
    float Distance::LightYear() const
    {
      return convert(m_value,m_unit,_LightYear) ;
    }

    std::ostream& operator<<(std::ostream& out,const Distance::Unit& i_unit)
    {
      switch(i_unit)
      {
      case Distance::_Meter:
        out << "Meter" ;
        break ;
      case Distance::_LightYear:
        out << "LightYear" ;
        break ;
      case Distance::_Parsec : 
        out << "Parsec" ;
        break ;
      }
      return out ;
    }

    std::ostream& operator<<(std::ostream& out,const Distance& distance)
    {
      out << "Distance(" << distance.m_unit << "," << distance.m_value << ")" ;
      return out ;
    }
    
    bool Distance::operator <=(const Distance& d) const
    {
      return convert(m_value,m_unit,_Meter) <= convert(d.m_value,d.m_unit,_Meter) ;
    }

    bool Distance::operator >=(const Distance& d) const
    {
      return convert(m_value,m_unit,_Meter) >= convert(d.m_value,d.m_unit,_Meter) ;
    }

    bool Distance::operator >(const Distance& d) const
    {
      return convert(m_value,m_unit,_Meter) > convert(d.m_value,d.m_unit,_Meter) ;
    }

    bool Distance::operator ==(const Distance& d) const
    {
      return convert(m_value,m_unit,_Meter) == convert(d.m_value,d.m_unit,_Meter) ;
    }
    
    Distance operator*(const Distance& distance,const float& numeric)
    {
      Distance result(distance) ;
      result.m_value *= numeric ;
      return result ;
    }

    Distance operator*(const float& numeric,const Distance& distance)
    {
      Distance result(distance) ;
      result.m_value *= numeric ;
      return result ;
    }
    
  }
}
