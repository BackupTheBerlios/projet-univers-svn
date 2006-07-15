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

#include <modele/exception.h>


#include <modele/masse.h>


namespace ProjetUnivers {

  namespace Modele {


    Masse::Masse()
    : valeur(), unite(_Kilogramme)
    {}

    Masse::Masse(const Masse& _m)
    : valeur(_m.valeur), unite(_m.unite)
    {}

    /// Constructeur avec des kilogrammes
    Masse Masse::Kilogramme(const Base::Reel& _k)
    {
      Masse resultat ;
      resultat.unite = _Kilogramme ;
      resultat.valeur = _k ;
      return resultat ;
    }


    /// Calcul
    Masse Masse::operator +(const Masse& _m) const
    {
      Masse resultat ;

      if (this->unite == _m.unite)
      {
        resultat.unite = _m.unite ;
        resultat.valeur = this->valeur + _m.valeur ;

      }
      else
      {
        throw Exception("Masse::operator + pas encore implanté") ;
      }

      return resultat ;
      
    }

    /// Calcul
    Masse Masse::operator -(const Masse& _m) const
    {
      Masse resultat ;

      if (this->unite == _m.unite)
      {
        resultat.unite = _m.unite ;
        resultat.valeur = this->valeur - _m.valeur ;

      }
      else
      {
        throw Exception("Masse::operator - pas encore implanté") ;
      }

      return resultat ;
    }
    
    Base::Reel Masse::operator /(const Masse& _m) const
    {

      if (this->unite == _m.unite)
      {
        return this->valeur / _m.valeur ;

      }
      else
      {
        throw Exception("Masse::operator / pas encore implanté") ;
        return 0 ;
      }

    }
    
    /// Calcul
    Masse Masse::operator /(const Base::Reel& _n) const
    {
      Masse resultat ;

      resultat.unite = this->unite ;
      resultat.valeur = this->valeur / _n ;

      return resultat ;
    }

    /// Calcul
    Masse Masse::operator *(const Base::Reel& _n) const
    {
      Masse resultat ;

      resultat.unite = this->unite ;
      resultat.valeur = this->valeur * _n ;

      return resultat ;
    }
   
    /// Converti en kilogrammes.
    Base::Reel Masse::Kilogramme() const
    {
      if (this->unite == _Kilogramme)
      {
        return this->valeur ;
      }
      else
      {
        throw Exception("Masse::Kilogramme pas encore implanté") ;
      }
    }

    /// Comparaison
    Base::Booleen Masse::operator <(const Masse& _m) const
    {
      if (this->unite == _m.unite)
      {
        return this->valeur < _m.valeur ;
      }
      else
      {
        throw Exception("Masse::operator < pas encore implanté") ;
      }
    }

  }
}

