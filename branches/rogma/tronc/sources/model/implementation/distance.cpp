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
    : distance(0), unit(_Meter)
    {}

    Distance::Distance(const Unit& _unit, const float& _value)
    : distance(_value), unit(_unit)
    {}
      
    Distance::Distance(const Distance& _distance)
    : distance(_distance.distance), unit(_distance.unit)
    {}
    
    Distance Distance::operator +(const Distance& _distance) const
    {
      
    }

    Distance Distance::operator -(const Distance& _distance) const
    {
      
    }

      
    float Distance::Parsec() const
    {
      switch (unit)
      {
      case _Meter:
        return distance / 3.08e+16 ;
      case _LightYear:
        return distance / 3.26  ;
      case _Parsec:
        return distance ;
      }
      
    }
      
    float Distance::Meter() const
    {
      switch (unit)
      {
      case _Meter:
        return distance  ;
      case _LightYear:
        return distance * 9.46e+15 ;
      case _Parsec:
        return distance * 3.08e+16 ;
      }
      
    }
     
    float Distance::LightYear() const
    {
      switch (unit)
      {
      case _Meter:
        return distance / 9.46e+15 ;
      case _LightYear:
        return distance ;
      case _Parsec:
        return distance * 3.26 ;
      }
    }

  }
}
