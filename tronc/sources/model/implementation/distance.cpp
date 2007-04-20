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

#include <kernel/error.h>

#include <model/distance.h>

namespace ProjetUnivers {
  namespace Model {


    /// opérateur d'ordre sur les unité de distances
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
    
    Distance Distance::operator +(const Distance& _distance) const
    {
      /// @todo
      check(false,"note yet implemented") ;
    }

    Distance Distance::operator -(const Distance& _distance) const
    {
      /// @todo
      check(false,"note yet implemented") ;
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

  }
}
