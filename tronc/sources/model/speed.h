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

#ifndef PU_MODEL_SPEED_H_
#define PU_MODEL_SPEED_H_



namespace ProjetUnivers {
  namespace Model {



    /// Une vitesse.
    /*!
      C'est un vecteur vitesse.
    */
    class Speed {
    public:
    
      // *************************
      /// @name Constructeurs
      // *************************      
      // @{  

     
      /// Speed nulle.
      Speed() ;

      /// Constructeur de copie.
      Speed(const Speed&) ;


      /// Calcul
      Speed operator +(const Speed&) const ;

      /// Calcul
      Speed operator -(const Speed&) const ;
      
      /// Calcul
      Speed operator *(const float&) const ;

      
      // @}

      // *************************
      /// @name Acc�s
      // *************************      
      // @{  
       
     
      /// Donne la vitesse en m.s-1.
      float MeterPerSecond() const ;


      // @}
    
    private:
    
      /// Les diff�rentes unit�s de mesure
      typedef enum 
      {
        /// L'unit� m.s-1
        _MeterPerSecond, 
        
      } Unit ;

      float value ;
      Unit unit ;
  
  
    };
  }
}



#endif
