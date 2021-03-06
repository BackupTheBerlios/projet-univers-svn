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

#include <OgreVector3.h>

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

      
    // @}
    /*!
      @name Access.
    */
    // @{  
     
      /// Speed vector in m.s-1.
      Ogre::Vector3 MeterPerSecond() const ;


    // @}
    
    private:

      /// Les diff�rentes unit�s de mesure
      typedef enum 
      {
        /// L'unit� m.s-1
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
