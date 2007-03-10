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

#ifndef PU_MODEL_ACCELERATION_H_
#define PU_MODEL_ACCELERATION_H_


namespace ProjetUnivers {
  namespace Model {

    /// Une acceleration.
    /*!
      C'est un vecteur d'accélération.
    @par Etat
      planning
    */
    class Acceleration {
    public:
    
    // *************************
    /// @name Constructeurs
    // *************************      
    // @{  

     
      /// Acceleration nulle.
      Acceleration() ;

      /// Constructeur de copie.
      Acceleration(const Acceleration&) ;

      /// Constructeur avec des m.s^-2
//      Acceleration MetreSecondesMoins2(const float& _ms2, const Vecteur&) ;


      /// Calcul
      Acceleration operator +(const Acceleration&) const ;

      /// Calcul
      Acceleration operator -(const Acceleration&) const ;
      
      /// Calcul
      Acceleration operator *(const float&) const ;

      
    // @}
    // *************************
    /// @name Accès
    // *************************      
    // @{  
       
     
      /// Donne l'acceleration en m.s-2.
      float MeterPerSecondSquared() const ;


    // @}
    
    private:
    
      /// Les différentes unités de mesure
      typedef enum 
      {
        /// L'unité m.s^-2
        _MeterPerSecondSquared, 
        
      } Unit ;

      float value ;
      Unit unit ;
  
  
    };
  }
}



#endif
