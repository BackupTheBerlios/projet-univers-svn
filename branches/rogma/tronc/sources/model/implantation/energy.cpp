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

#include <base/erreur.h>

#include <modele/energie.h>
#include <modele/exception.h>



namespace ProjetUnivers {

  namespace Model {

    Energie::Energie()
    : unite(_Joule)
    {}


    Energie::Energie(const Energie& _energie)
    : valeur(_energie.valeur), unite(_energie.unite)
    {}


    Energie Energie::Joule(const Base::Reel& _joules)
    {
      Energie resultat ;
      
      resultat.valeur = _joules ;
      resultat.unite = _Joule ;
      
      return resultat ;  
    }
    
    
    Energie& Energie::operator=(const Energie& _energie)
    {
      this->valeur = _energie.valeur ;
      this->unite = _energie.unite ;
      
      return *this ;
    }
    
    
    /// Donne la valeur convertie de _energie en _unite
    Base::Reel Energie::Convertir(const Energie& _energie, const Energie::Unite& _unite)
    {
      if (_energie.unite == _unite)
      {
        return _energie.valeur ;
      }
      else if (_energie.unite == _Joule && _unite == _eV)
      {
        return _energie.valeur * 6,24150974e18 ;
      }
      // ici on a : _energie.unite == _eV && _unite == _Joule
      else
      {
        return _energie.valeur * 1,60217733e-19 ; 
      }
      
      /*! 
        @todo ici erreur
      */
    }
    
    
    Energie Energie::operator -(const Energie& _operande) const
    {
      Energie resultat(*this) ;
      
      // le cas facile
      if (this->unite == _operande.unite)
      {
        resultat.valeur -= _operande.valeur ;  
      }
      // il faut choisir une unité de conversion
      // ici : on prend lle Joule
      else
      {
        
        resultat.valeur = Convertir(resultat,Energie::_Joule) - 
                          Convertir(_operande,Energie::_Joule) ;
        resultat.unite = Energie::_Joule ;
        
      }
      
      return resultat ;
      
    }


    Base::Reel Energie::operator /(const Energie& _operande) const
    {
      
      // le cas division par zéro.
      VerifieCondition(_operande.valeur != 0, 
                       Exception("division par zero")) ;
      
      // le cas normal
      if (this->unite == _operande.unite)
      {
        return this->valeur / _operande.valeur ;
      }
      else
      {
        return Convertir(*this, Energie::_eV) / 
               Convertir(_operande, Energie::_eV) ;
      }
      
    }



    Base::Booleen Energie::operator<(const Energie& _operande) const
    {
      if (this->unite == _operande.unite)
      {
        return this->valeur < _operande.valeur ;
      }
      else
      {
        return Convertir(*this, Energie::_eV) < 
               Convertir(_operande, Energie::_eV) ;
      }
    }
    
  }
}
