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

#include <model/energy.h>

namespace ProjetUnivers {
  namespace Model {

    /// A mass.
    /*!
      Energy forms (light) are also considered to be massive due to 
      mass/energy equivalence.
    */
    class Mass 
    {
    public:
    
    /*! 
      @name Constructors
    */
    // @{  
     
      /// Null mass.
      Mass() ;

      /// copy Ccnstructor.
      Mass(const Mass&) ;
      
      /// contruct from energy.
      Mass(const Energy&) ;

      /// Build in kilograms.
      static Mass Kilogram(const float&) ;
      
      Mass operator +(const Mass&) const ;
      Mass operator -(const Mass&) const ;
      Mass operator /(const float&) const ;
      float operator /(const Mass&) const ;
      Mass operator *(const float&) const ;

      
    // @}
    /*! 
      @name Access
    */
    // @{  
     
      /// Convert to kilograms.
      float Kilogram() const ;

      /// Comparison.
      bool operator <(const Mass&) const ;

    // @}
    
    private:
    
      /// Measure units
      typedef enum 
      {
        _Kilogram
      } Unit ;

      float value ;
      Unit unit ;
  
  
    };
  }
}



#endif
