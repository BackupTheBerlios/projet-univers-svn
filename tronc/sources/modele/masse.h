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

#ifndef _PU_MODELE_MASSE_H_
#define _PU_MODELE_MASSE_H_

#include <base/types.h>


namespace ProjetUnivers {

  namespace Modele {



    /// Une quantité de matière.
    class Masse 
    {
    public:
    
      /// @name Constructeurs
      // @{  

     
      /// Masse nulle.
      Masse() ;

      /// Constructeur de copie.
      Masse(const Masse&) ;

      /// Constructeur avec des kilogrammes
      Masse Kilogramme(const Base::Reel& _kilogramme) ;


      /// Calcul
      Masse operator +(const Masse&) const ;

      /// Calcul
      Masse operator -(const Masse&) const ;
      
      /// Calcul
      Base::Reel operator /(const Masse&) const ;

      /// Calcul
      Masse operator *(const Base::Reel&) const ;

      
      // @}

      // *************************
      /// @name Accès
      // *************************      
      // @{  
       
     
      /// Converti en kilogrammes.
      Base::Reel Kilogramme() const ;

      /// Comparaison
      Base::Booleen operator <(const Masse&) const ;

      // @}
    
    private:
    
      /// Les différentes unités de mesure
      typedef enum 
      {
        /// L'unité kilogramme
        _Kilogramme, 
        
      } Unite ;

      Base::Reel valeur ;
      Unite unite ;
  
  
    };
  }
}



#endif
