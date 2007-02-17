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

#ifndef _PU_MODELE_ENERGIE_H_
#define _PU_MODELE_ENERGIE_H_

#include <base/types.h>


namespace ProjetUnivers {
  namespace Model {



    /// Une quantit� d'�nergie.
    /*!
    @par Etat
      planning

    */
    class Energie {
    public:
    
    // *************************
    /// @name Constructeurs
    // *************************      
    // @{  

     
      /// Energie nulle.
      Energie() ;

      /// Constructeur de copie.
      Energie(const Energie&) ;

      /// Constructeur avec des Joules
      static Energie Joule(const Base::Reel& _joules) ;

      /// Constructeur avec des �lectron-volts
      static Energie ElectronVolt(const Base::Reel& _eV) ;

      /// Affectation
      Energie& operator=(const Energie&) ;

      /// Calcul
      Energie operator +(const Energie&) const ;

      /// Calcul
      Energie operator -(const Energie&) const ;
      
      /// Calcul
      Base::Reel operator /(const Energie&) const ;

      /// Calcul
      Energie operator *(const Base::Reel&) const ;

      
    // @}
    // *************************
    /// @name Acc�s
    // *************************      
    // @{  
       
     
      /// Donne l'�nergie en Joules.
      Base::Reel Joule() const ;

      /// Comparaison
      Base::Booleen operator <(const Energie&) const ;

    // @}
    
    private:
    
      /// Les diff�rentes unit�s de mesure
      typedef enum 
      {
        /// L'unit� Joule
        _Joule, 
        
        /// L'�lectron-volt ~= 1,602 177 33 x 10-19 Joules
        _eV
      } Unite ;
 

      Base::Reel valeur ;
      Unite unite ;
  

      /// M�thode interne de conversion d'unit�s.
      static Base::Reel Convertir(const Energie& _energie, 
                                  const Energie::Unite& _unite) ;

  
    };
  }
}



#endif
