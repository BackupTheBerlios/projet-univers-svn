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



    /// An amount of energy.
    /*!
    @par Etat
      planning

    */
    class Energy {
    public:
    
    // *************************
    /// @name Construct
    // *************************      
    // @{  

     
      /// Null energy.
      Energy() ;

      /// Copy constructor.
      Energy(const Energy&) ;

      /// Joules to energy.
      static Energy Joule(const float& _joules) ;

      /// Electron volt to energy.
      static Energy ElectronVolt(const float& _eV) ;

      /// Assignment.
      Energy& operator=(const Energy&) ;

      /// Calculus
      Energy operator +(const Energy&) const ;

      /// Calculus
      Energy operator -(const Energy&) const ;
      
      /// Calculus
      float operator /(const Energy&) const ;

      /// Calculus
      Energy operator *(const float&) const ;

      
    // @}
    // *************************
    /// @name Access
    // *************************      
    // @{  
       
     
      /// Convert to Joules.
      float Joule() const ;

      /// Comparison
      bool operator <(const Energy&) const ;

    // @}
    
    private:
    
      /// Measure units.
      typedef enum 
      {
        /// Joule
        _Joule, 
        
        /// Electron-volt ~= 1,602 177 33 x 10-19 Joules
        _eV
      } Unit ;
 

      float value ;
      Unit unit ;
  

      /// Internal unit conversion.
      static float convert(const Energy& _energy, 
                           const Energy::Unit& _unit) ;

  
    };
  }
}



#endif
