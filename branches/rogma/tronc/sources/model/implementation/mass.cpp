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

#include <model/exception.h>
#include <model/mass.h>

namespace ProjetUnivers {
  namespace Model {


    Mass::Mass()
    : value(), unit(_Kilogram)
    {}

    Mass::Mass(const Mass& _m)
    : value(_m.value), unit(_m.unit)
    {}

    /// Constructeur avec des kilogrammes
    Mass Mass::Kilogramme(const float& _k)
    {
      Mass result ;
      result.unit = _Kilogram ;
      result.value = _k ;
      return result ;
    }


    /// Calcul
    Mass Mass::operator +(const Mass& _m) const
    {
      Mass result ;

      if (this->unit == _m.unit)
      {
        result.unit = _m.unit ;
        result.value = this->value + _m.value ;

      }
      else
      {
        throw Exception("Mass::operator+ @todo") ;
      }

      return result ;
      
    }

    /// Calcul
    Mass Mass::operator -(const Mass& _m) const
    {
      Mass result ;

      if (this->unit == _m.unit)
      {
        result.unit = _m.unit ;
        result.value = this->value - _m.value ;

      }
      else
      {
        throw Exception("Mass::operator- @todo") ;
      }

      return result ;
    }
    
    float Mass::operator /(const Mass& _m) const
    {

      if (this->unit == _m.unit)
      {
        return this->value / _m.value ;

      }
      else
      {
        throw Exception("Mass::operator/ @todo") ;
        return 0 ;
      }

    }
    
    /// Calcul
    Mass Mass::operator /(const float& _n) const
    {
      Mass result ;

      result.unit = this->unit ;
      result.value = this->value / _n ;

      return result ;
    }

    /// Calcul
    Mass Mass::operator *(const float& _n) const
    {
      Mass result ;

      result.unit = this->unit ;
      result.value = this->value * _n ;

      return result ;
    }
   
    /// Converti en kilogrammes.
    float Mass::Kilogram() const
    {
      if (this->unit == _Kilogram)
      {
        return this->value ;
      }
      else
      {
        throw Exception("Mass::Kilogram @todo") ;
      }
    }

    /// Comparaison
    bool Mass::operator <(const Mass& _m) const
    {
      if (this->unit == _m.unit)
      {
        return this->value < _m.value ;
      }
      else
      {
        throw Exception("Mass::operator< @todo") ;
      }
    }

  }
}

