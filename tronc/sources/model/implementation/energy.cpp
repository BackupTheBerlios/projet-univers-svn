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
#include <kernel/error.h>
#include <kernel/log.h>

#include <model/energy.h>
#include <model/exception.h>

namespace ProjetUnivers {
  namespace Model {

    Energy::Energy()
    : m_value(0),
      m_unit(_Joule)
    {}

    Energy::Energy(const Energy& _energie)
    : m_value(_energie.m_value), 
      m_unit(_energie.m_unit)
    {}

    Energy Energy::Joule(const float& _joules)
    {
      Energy result ;
      
      result.m_value = _joules ;
      result.m_unit = _Joule ;
      
      return result ;  
    }
    
    Energy& Energy::operator=(const Energy& _energie)
    {
      this->m_value = _energie.m_value ;
      this->m_unit = _energie.m_unit ;
      
      return *this ;
    }
    
    float Energy::convert(const Energy& _energy, const Energy::Unit& _unit)
    {
      if (_energy.m_unit == _unit)
      {
        return _energy.m_value ;
      }
      else if (_energy.m_unit == _Joule && _unit == _eV)
      {
        return _energy.m_value * 6.24150974e18 ;
      }
      // ici on a : _energy.unit == _eV && _unit == _Joule
      else
      {
        return _energy.m_value * 1.60217733e-19 ; 
      }
      
      /*! 
        @todo ici erreur
      */
      ErrorMessage("Model::Energy::convert") ;
      return 0 ;
    }
    
    Energy Energy::operator -(const Energy& _operande) const
    {
      Energy result(*this) ;
      
      // le cas facile
      if (this->m_unit == _operande.m_unit)
      {
        result.m_value -= _operande.m_value ;  
      }
      // il faut choisir une unité de conversion
      // ici : on prend lle Joule
      else
      {
        
        result.m_value = convert(result,Energy::_Joule) - 
                       convert(_operande,Energy::_Joule) ;
        result.m_unit = Energy::_Joule ;
        
      }
      
      return result ;
      
    }

    float Energy::operator /(const Energy& _operande) const
    {
      
      // le cas division par zéro.
      CHECK(_operande.m_value != 0, 
                       Exception("division par zero")) ;
      
      // le cas normal
      if (this->m_unit == _operande.m_unit)
      {
        return this->m_value / _operande.m_value ;
      }
      else
      {
        return convert(*this, Energy::_eV) / 
               convert(_operande, Energy::_eV) ;
      }
      
    }

    bool Energy::operator<(const Energy& _operande) const
    {
      if (this->m_unit == _operande.m_unit)
      {
        return this->m_value < _operande.m_value ;
      }
      else
      {
        return convert(*this, Energy::_eV) < 
               convert(_operande, Energy::_eV) ;
      }
    }
    
    float Energy::Joule() const
    {
      return convert(*this,_Joule) ;
    }

    Energy Energy::read(Kernel::Reader* reader)
    {
      Energy result ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("value") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::Energy::read required attribute : value") ;
      }

      
      finder = reader->getAttributes().find("unit") ;
      if (finder != reader->getAttributes().end())
      {
        if (finder->second == "Joule")
        {
          result.m_unit = _Joule ;
        }
        else if (finder->second == "eV")
        {
          result.m_unit = _eV ;
        }
        else 
        {
          ErrorMessage("Model::Energy::read invalid unit : " + finder->second) ;
        }
      }
      else
      {
        ErrorMessage("Model::Energy::read required attribute : unit") ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;
      
      return result ;            
    }   

  }
}
