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

#ifndef _PU_NOYAU_DISTANCE_H_
#define _PU_NOYAU_DISTANCE_H_

#include "types.h"

namespace ProjetUnivers {

  namespace Noyau {

    using namespace ProjetUnivers::Base ;
    /*
    CLASS
      Distance
      
      Une distance éloignant deux points.
      
    EXPLICATION
      
      La distance est stockée dans n'importe quelle unité pour des raisons de 
      précision. Ainsi, de grandes distances pouront être stokées en parsecs et
      de petites distances en mètres.
    TYPE_DE_CLASSE
      Objet
      Valeur
    */
    class Distance {
    public:
    
      ///////////////////
      // Distance zéro.
      Distance() ;
      
      ///////////////////
      // Constructeur de copie.
      Distance(const Distance&) ;
      
      //////////////////
      // Convertit la distance en parsecs.
      Reel Parsec() const ; 
      
      //////////////////
      // Convertit la distance en mètres.
      Reel Metre() const ; 
      
      //////////////////
      // Convertit la distance en années lumières.
      Reel AnneeLumiere() const ; 
    
    private:
    
      typedef enum {_AnneeLumiere, _Parsec, _Metre} Unite ;
    
      ///////////////
      // Valeur.
      Reel distance ;
  
      ////////////////
      // Unité de la distance
      Unite unite ;    
  
    };
  }
}
#endif
