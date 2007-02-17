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

#include <modele/distance.h>

namespace ProjetUnivers {

  namespace Model {


    /// opérateur d'ordre sur les unité de distances
    Base::Booleen operator<=(Distance::Unite _u1, 
                            Distance::Unite _u2)
    {

      if (_u1 == Distance::_Metre)
        return Base::VRAI ;

      if (_u1 == Distance::_AnneeLumiere)
      {
        if (_u2 == Distance::_Parsec || _u2 == Distance::_AnneeLumiere)
          return Base::VRAI ;
        else
          return Base::FAUX ;
      }
        
      if (_u1 == Distance::_Parsec && _u2 != Distance::_Parsec)
    
        return Base::FAUX;
      
      return Base::VRAI ;
    }

    Distance::Distance()
    : distance(0), unite(_Metre)
    {}

    Distance::Distance(const Unite& _unite, const Base::Reel& _valeur)
    : distance(_valeur), unite(_unite)
    {}
      
    Distance::Distance(const Distance& _distance)
    : distance(_distance.distance), unite(_distance.unite)
    {}
    
    Distance Distance::operator +(const Distance& _distance) const
    {
      
    }

    Distance Distance::operator -(const Distance& _distance) const
    {
      
    }

      
    Base::Reel Distance::Parsec() const
    {
      switch (unite)
      {
      case _Metre:
        return distance / 3.08e+16 ;
      case _AnneeLumiere:
        return distance / 3.26  ;
      case _Parsec:
        return distance ;
      }
      
    }
      
    Base::Reel Distance::Metre() const
    {
      switch (unite)
      {
      case _Metre:
        return distance  ;
      case _AnneeLumiere:
        return distance * 9.46e+15 ;
      case _Parsec:
        return distance * 3.08e+16 ;
      }
      
    }
     
    Base::Reel Distance::AnneeLumiere() const
    {
      switch (unite)
      {
      case _Metre:
        return distance / 9.46e+15 ;
      case _AnneeLumiere:
        return distance ;
      case _Parsec:
        return distance * 3.26 ;
      }
    }

  }
}
