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

#ifndef PU_MODEL_MASS_H_
#define PU_MODEL_MASS_H_



namespace ProjetUnivers {
  namespace Model {

    /// Une quantit� de mati�re.
    /*!
    @par Etat
      planning
    
    */
    class Mass 
    {
    public:
    
    /*! 
      @name Constructeurs

      Fonctions de conversion, calculs dimensionn�s,...
    */
    // @{  

     
      /// Mass nulle.
      Mass() ;

      /// Constructeur de copie.
      Mass(const Mass&) ;

      /// Constructeur avec des kilogrammes
      static Mass Kilogram(const float&) ;


      /// Calcul
      Mass operator +(const Mass&) const ;

      /// Calcul
      Mass operator -(const Mass&) const ;
      
      /// Calcul
      Mass operator /(const float&) const ;

      /// Calcul
      float operator /(const Mass&) const ;

      /// Calcul
      Mass operator *(const float&) const ;

      
    // @}
    // *************************
    /// @name Acc�s
    // *************************      
    // @{  
       
     
      /// Converti en kilogrammes.
      float Kilogram() const ;

      /// Comparaison
      bool operator <(const Mass&) const ;

    // @}
    
    private:
    
      /// Les diff�rentes unit�s de mesure
      typedef enum 
      {
        /// L'unit� kilogramme
        _Kilogram, 
        
      } Unit ;

      float value ;
      Unit unit ;
  
  
    };
  }
}



#endif
