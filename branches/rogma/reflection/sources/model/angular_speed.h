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
#pragma once

#include <OgreVector3.h>

#include <kernel/reader.h>

namespace ProjetUnivers
{
  namespace Model
  {

    /// An angular speed.
    class AngularSpeed
    {
    public:
    
    /*!
      @name Construct
    */
    // @{  

     
      /// Zero speed.
      AngularSpeed() ;

      /// Build from a vector whose norm is angular speed in turn.s-1.
      static AngularSpeed TurnPerSecond(const float& i_wx,
                                        const float& i_wy,
                                        const float& i_wz) ;

      /// Build from a vector whose norm is angular speed in radian.s-1.
      static AngularSpeed RadianPerSecond(const float& i_wx,
                                          const float& i_wy,
                                          const float& i_wz) ;
  
      /// Copy constructor.
      AngularSpeed(const AngularSpeed&) ;

      /// Sum
      AngularSpeed operator +(const AngularSpeed&) const ;

      /// Difference
      AngularSpeed operator -(const AngularSpeed&) const ;
      
      /// Multiplication
      AngularSpeed operator *(const float&) const ;

    
    // @}
    /*!
      @name Access
    */
    // @{  
   
      /// Speed in rad.s-1.
      Ogre::Vector3 RadianPerSecond() const ;

      /// Speed in turn.s-1.
      Ogre::Vector3 TurnPerSecond() const ;

    // @}

      /// Read angular speed.
      /*!
        stored as 
        @code
          <AngularSpeed x=".." y=".." z=".." 
                        unit="TurnPerSecond|RadianPerSecond"/>
        @endcode
      */          
      static AngularSpeed read(Kernel::Reader* reader) ;
    
    private:
    
      /// Measure units
      typedef enum 
      {
        _RadianPerSecond, 
        _TurnPerSecond        
      } Unit ;

      Ogre::Vector3 m_value ;
      Unit          m_unit ;
    };
  }
}
