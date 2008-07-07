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

#include <model/exception.h>
#include <model/speed.h>
#include <model/mass.h>

namespace ProjetUnivers {
  namespace Model {

    Mass::Mass()
    : m_value(), 
      m_unit(_Kilogram)
    {}

    Mass::Mass(const Mass& _m)
    : m_value(_m.m_value), m_unit(_m.m_unit)
    {}

    /// Here we use E=1/2m.v²
    Mass::Mass(const Energy& energy,const Speed& speed)
    : m_value(2*energy.Joule()/(speed.MeterPerSecond().length()*speed.MeterPerSecond().length())), 
      m_unit(_Kilogram)
    {}

    Mass Mass::Kilogram(const float& _k)
    {
      Mass result ;
      result.m_unit = _Kilogram ;
      result.m_value = _k ;
      return result ;
    }

    Mass Mass::operator +(const Mass& _m) const
    {
      Mass result ;

      if (this->m_unit == _m.m_unit)
      {
        result.m_unit = _m.m_unit ;
        result.m_value = this->m_value + _m.m_value ;

      }
      else
      {
        throw Exception("Mass::operator+ @todo") ;
      }

      return result ;
      
    }

    Mass Mass::operator -(const Mass& _m) const
    {
      Mass result ;

      if (this->m_unit == _m.m_unit)
      {
        result.m_unit = _m.m_unit ;
        result.m_value = this->m_value - _m.m_value ;

      }
      else
      {
        throw Exception("Mass::operator- @todo") ;
      }

      return result ;
    }
    
    float Mass::operator /(const Mass& _m) const
    {

      if (this->m_unit == _m.m_unit)
      {
        return this->m_value / _m.m_value ;

      }
      else
      {
        throw Exception("Mass::operator/ @todo") ;
        return 0 ;
      }

    }
    
    Mass Mass::operator /(const float& _n) const
    {
      Mass result ;

      result.m_unit = this->m_unit ;
      result.m_value = this->m_value / _n ;

      return result ;
    }

    Mass Mass::operator *(const float& _n) const
    {
      Mass result ;

      result.m_unit = this->m_unit ;
      result.m_value = this->m_value * _n ;

      return result ;
    }
   
    float Mass::Kilogram() const
    {
      if (this->m_unit == _Kilogram)
      {
        return this->m_value ;
      }
      else
      {
        throw Exception("Mass::Kilogram @todo") ;
      }
    }

    bool Mass::operator <(const Mass& _m) const
    {
      if (this->m_unit == _m.m_unit)
      {
        return this->m_value < _m.m_value ;
      }
      else
      {
        throw Exception("Mass::operator< @todo") ;
      }
    }

    Mass Mass::read(Kernel::Reader* reader)
    {
      Mass result ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("value") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::Mass::read required attribute : value") ;
      }

      finder = reader->getAttributes().find("unit") ;
      if (finder != reader->getAttributes().end())
      {
        if (finder->second == "Kilogram")
        {
          result.m_unit = _Kilogram ;
        }
        else 
        {
          ErrorMessage("Model::Mass::read invalid unit : " + finder->second) ;
        }
      }
      else
      {
        ErrorMessage("Model::Mass::read required attribute : unit") ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;
      
      return result ;            
    }   

  }
}

