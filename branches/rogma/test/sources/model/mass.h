/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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

#include <kernel/reader.h>
#include <model/energy.h>
#include <model/speed.h>

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
      
      /// Mass of a moving object, energy equals cinetic energy.
      Mass(const Energy&,const Speed&) ;

      /// Build in kilograms.
      static Mass Kilogram(const float&) ;
      
      Mass operator +(const Mass&) const ;
      Mass operator -(const Mass&) const ;
      Mass operator /(const float&) const ;
      float operator /(const Mass&) const ;
      Mass operator *(const float&) const ;

      /// Read Mass.
      /*!
        stored as 
        @code
          <Mass value=".." unit="Kilogram"/>
        @endcode
      */          
      static Mass read(Kernel::Reader* reader) ;
      
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

      float m_value ;
      Unit  m_unit ;
  
  
    };
  }
}



#endif
