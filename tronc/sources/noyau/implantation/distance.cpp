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

#include "distance.h"

namespace ProjetUnivers {

  namespace Noyau {

    using namespace ProjetUnivers::Base ;
  
    ///////////////////
    // Distance zéro: on peut mettre n'importe qu'elle unité.
    Distance::Distance()
    : distance(), unite()
    {}
    
    ///////////////////
    // Constructeur de copie.
    Distance::Distance(const Distance& _d)
    : distance(_d.distance), unite(_d.unite)
    {}
    
    //////////////////
    // Convertit la distance en parsecs.
    Reel Distance::Parsec() const
    {
      switch(unite) 
      {
        case _Parsec:
          return distance ;
        
        case _AnneeLumiere:
        
          return distance / 3.26 ;
          
        case _Metre:

          return distance / 3.08567758128e16 ;
      }
    } 
    
    //////////////////
    // Convertit la distance en mètres.
    Reel Distance::Metre() const 
    {
      switch(unite) 
      {
        case _Parsec:
          
          return distance * 3.08567758128e16 ;
        
        case _AnneeLumiere:
        
          return distance * 3.26 ;
          
        case _Metre:

          return distance ;
      }
    
    }
    
    //////////////////
    // Convertit la distance en années lumières.
    Reel Distance::AnneeLumiere() const 
    {
      switch(unite) 
      {
        case _Parsec:
          
          return distance * 3.26 ;
        
        case _AnneeLumiere:
        
          return distance ;
          
        case _Metre:

          return distance *  9.4607304725808e16 ;
      }
     
    }
    
  }
}

