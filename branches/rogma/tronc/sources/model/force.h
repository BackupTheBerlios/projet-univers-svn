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

#ifndef _PU_MODELE_FORCE_H_
#define _PU_MODELE_FORCE_H_

#include <base/types.h>

namespace ProjetUnivers {

  namespace Model {

      
    /// Une force.
    /*!  
      @par Type de classe :
      - Valeur
      
      @par Etat 
        planning

    */
    class Force 
    {
    public:
    
    // ********************
    /// @name Constructeurs
    // ********************
    // @{   
  

      /// Force nulle.
      Force() ;
      
      /// Constructeur de copie.
      Force(const Force&) ;
    
      /// Calcul
      Force operator +(const Force&) const ;

      /// Calcul
      Force operator -(const Force&) const ;

      
      // @}
      // ******************
      /// @name Conversions
      // ******************
      // @{
      

      /// Convertit la distance en newton.
      Base::Reel Newton() const ; 
      

    
      // @}    
      // ************
      /// @name Acc�s
      // ************
      // @{
      
      

      /// Comparaison avec une autre dur�e. 
      /*!
      */
      // BooleenEtendu Comparer(const Force&) const ;
    
      // @}
      
    private:
    
      /// Les diff�rentes unit�s
      typedef enum {
        _Newton
      } Unite ;


      Base::Reel valeur ;
      Unite unite ;    
  
    };



  }
}




#endif
