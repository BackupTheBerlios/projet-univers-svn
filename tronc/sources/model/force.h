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
#ifndef PU_MODEL_FORCE_H_
#define PU_MODEL_FORCE_H_

#include <OgreVector3.h>
#include <model/orientation.h>

namespace ProjetUnivers {
  namespace Model {

      
    /// A force.
    /*!  
    */
    class Force 
    {
    public:
    
    /// @name Constuctors
    // @{   
  

      /// Null force.
      Force() ;
      
      /// Copy constructor.
      Force(const Force&) ;
      
      /// Build a force in newton.
      static Force Newton(const float& i_x,
                          const float& i_y,
                          const float& i_z) ;
      
      /// Calculus
      Force operator +(const Force&) const ;

      /// Calculus
      Force operator -(const Force&) const ;

      /// Calculus
      Force operator*(const float&) const ;
      
      /// Re-orient a force
      Force operator*(const Orientation&) const ;
      
    // @}
    /// @name Convertions
    // @{
      

      /// Convert to newton.
      Ogre::Vector3 Newton() const ; 

    // @}
      
    private:
    
      /// Units
      typedef enum {
        _Newton
      } Unit ;

      /// internal purpose constructor.
      Force(const Unit&  i_unit,
            const float& i_x,
            const float& i_y,
            const float& i_z) ;


      Ogre::Vector3 m_value ;
      Unit          m_unit ;    
  
    };

  }
}




#endif
