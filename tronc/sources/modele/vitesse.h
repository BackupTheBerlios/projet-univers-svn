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

#ifndef _PU_MODELE_VITESSE_H_
#define _PU_MODELE_VITESSE_H_

#include <base/types.h>


namespace ProjetUnivers {

  namespace Modele {



    /// Une vitesse.
    /*!
      C'est un vecteur vitesse.
    */
    class Vitesse {
    public:
    
      // *************************
      /// @name Constructeurs
      // *************************      
      // @{  

     
      /// Vitesse nulle.
      Vitesse() ;

      /// Constructeur de copie.
      Vitesse(const Vitesse&) ;

      /// Constructeur avec des m.s-1
//      Vitesse MetreSecondesMoins1(const Base::Reel& _ms1, const Vecteur&) ;


      /// Calcul
      Vitesse operator +(const Vitesse&) const ;

      /// Calcul
      Vitesse operator -(const Vitesse&) const ;
      
      /// Calcul
      Vitesse operator *(const Base::Reel&) const ;

      
      // @}

      // *************************
      /// @name Accès
      // *************************      
      // @{  
       
     
      /// Donne la vitesse en m.s-1.
      Base::Reel MetreSecondesMoins1() const ;


      // @}
    
    private:
    
      /// Les différentes unités de mesure
      typedef enum 
      {
        /// L'unité m.s-1
        _MetreSecondeMoins1, 
        
      } Unite ;

      Base::Reel valeur ;
      Unite unite ;
  
  
    };
  }
}



#endif
