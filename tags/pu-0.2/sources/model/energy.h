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

#ifndef PU_MODEL_ENERGY_H_
#define PU_MODEL_ENERGY_H_



namespace ProjetUnivers {
  namespace Model {



    /// Une quantit� d'�nergie.
    /*!
    @par Etat
      planning

    */
    class Energy {
    public:
    
    // *************************
    /// @name Constructeurs
    // *************************      
    // @{  

     
      /// Energy nulle.
      Energy() ;

      /// Constructeur de copie.
      Energy(const Energy&) ;

      /// Constructeur avec des Joules
      static Energy Joule(const float& _joules) ;

      /// Constructeur avec des �lectron-volts
      static Energy ElectronVolt(const float& _eV) ;

      /// Affectation
      Energy& operator=(const Energy&) ;

      /// Calcul
      Energy operator +(const Energy&) const ;

      /// Calcul
      Energy operator -(const Energy&) const ;
      
      /// Calcul
      float operator /(const Energy&) const ;

      /// Calcul
      Energy operator *(const float&) const ;

      
    // @}
    // *************************
    /// @name Acc�s
    // *************************      
    // @{  
       
     
      /// Donne l'�nergie en Joules.
      float Joule() const ;

      /// Comparaison
      bool operator <(const Energy&) const ;

    // @}
    
    private:
    
      /// Les diff�rentes unit�s de mesure
      typedef enum 
      {
        /// L'unit� Joule
        _Joule, 
        
        /// L'�lectron-volt ~= 1,602 177 33 x 10-19 Joules
        _eV
      } Unit ;
 

      float value ;
      Unit unit ;
  

      /// M�thode interne de conversion d'unit�s.
      static float convert(const Energy& _energy, 
                           const Energy::Unit& _unit) ;

  
    };
  }
}



#endif
