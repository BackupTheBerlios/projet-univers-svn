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

#include <model/energy.h>
#include <model/exception.h>



namespace ProjetUnivers {
  namespace Model {

    Energy::Energy()
    : unit(_Joule)
    {}


    Energy::Energy(const Energy& _energie)
    : value(_energie.value), unit(_energie.unit)
    {}


    Energy Energy::Joule(const float& _joules)
    {
      Energy result ;
      
      result.value = _joules ;
      result.unit = _Joule ;
      
      return result ;  
    }
    
    
    Energy& Energy::operator=(const Energy& _energie)
    {
      this->value = _energie.value ;
      this->unit = _energie.unit ;
      
      return *this ;
    }
    
    
    /// Donne la value convertie de _energie en _unit
    float Energy::convert(const Energy& _energy, const Energy::Unit& _unit)
    {
      if (_energy.unit == _unit)
      {
        return _energy.value ;
      }
      else if (_energy.unit == _Joule && _unit == _eV)
      {
        return _energy.value * 6.24150974e18 ;
      }
      // ici on a : _energy.unit == _eV && _unit == _Joule
      else
      {
        return _energy.value * 1.60217733e-19 ; 
      }
      
      /*! 
        @todo ici erreur
      */
    }
    
    
    Energy Energy::operator -(const Energy& _operande) const
    {
      Energy result(*this) ;
      
      // le cas facile
      if (this->unit == _operande.unit)
      {
        result.value -= _operande.value ;  
      }
      // il faut choisir une unité de conversion
      // ici : on prend lle Joule
      else
      {
        
        result.value = convert(result,Energy::_Joule) - 
                       convert(_operande,Energy::_Joule) ;
        result.unit = Energy::_Joule ;
        
      }
      
      return result ;
      
    }


    float Energy::operator /(const Energy& _operande) const
    {
      
      // le cas division par zéro.
      check(_operande.value != 0, 
                       Exception("division par zero")) ;
      
      // le cas normal
      if (this->unit == _operande.unit)
      {
        return this->value / _operande.value ;
      }
      else
      {
        return convert(*this, Energy::_eV) / 
               convert(_operande, Energy::_eV) ;
      }
      
    }



    bool Energy::operator<(const Energy& _operande) const
    {
      if (this->unit == _operande.unit)
      {
        return this->value < _operande.value ;
      }
      else
      {
        return convert(*this, Energy::_eV) < 
               convert(_operande, Energy::_eV) ;
      }
    }
    
  }
}
