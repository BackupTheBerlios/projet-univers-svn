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
#ifndef PU_MODEL_SPEED_H_
#define PU_MODEL_SPEED_H_

#include <OgreVector3.h>

#include <kernel/reader.h>

#include <model/orientation.h>

namespace ProjetUnivers {
  namespace Model {

    /// A speed.
    /*!
      Implementation with Ogre::Vector3.
    */
    class Speed {
    public:
    
    /*! 
      @name Constructeurs
    */
    // @{  

     
      /// Zero speed.
      Speed() ;

      /// Copy constructor.
      Speed(const Speed&) ;
      
      /// Constructor.
      static Speed MeterPerSecond(const float& i_x,
                                  const float& i_y,
                                  const float& i_z) ;

      /// Addition.
      Speed operator +(const Speed&) const ;

      /// Substraction.
      Speed operator -(const Speed&) const ;
      
      /// Multiplication.
      Speed operator *(const float&) const ;
      Speed operator /(const float&) const ;
      Speed operator *(const Orientation&) const ;
      
      /// Speed of light.
      static const Speed c ;
      
    // @}
    /*!
      @name Access.
    */
    // @{  
     
      /// Speed vector in m.s-1.
      Ogre::Vector3 MeterPerSecond() const ;

    // @}

      /// Read speed.
      /*!
        stored as 
        @code
          <Speed x=".." y=".." z=".." unit="MeterPerSecond|..."/>
        @endcode
      */          
      static Speed read(Kernel::Reader* reader) ;
    
    private:

      /// Units.
      typedef enum 
      {
        /// m.s-1
        _MeterPerSecond, 
        
      } Unit ;

      /// internal purpose constructor.
      Speed(const Unit& i_unit,
            const float& i_x,
            const float& i_y,
            const float& i_z) ;

      Ogre::Vector3 m_value ;
      Unit          m_unit ;
  
  
    };
  }
}



#endif
