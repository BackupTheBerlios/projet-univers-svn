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

#include <OgreQuaternion.h>

#include <kernel/reader.h>

namespace ProjetUnivers
{
  namespace Model
  {
    class Position ;

    /// An orientation of an object in space.
    /*!
      A quaternion.         
    */
    class Orientation
    {
    public:
    
    /*! 
      @name Constructors
    */
    // @{  

     
      /// Default orientation.
      Orientation() ;

      /// Copy constructor.
      Orientation(const Orientation&) ;

      /// Construct from a points.
      Orientation(const Position&) ;

      /// Construct from a quaternion.
      Orientation(const Ogre::Quaternion& _orientation) ; 

      /// COnstruct a random orientation.
      static Orientation random() ;
      
      /// Read an Orientation.
      /*!
        stored as 
          <Orientation [angle_degree=".." axis_x=".." axis_y=".." axis_z=".."]/>
          an axis and an angle
      */     
      static Orientation read(Kernel::Reader* reader) ;
      
    // @}
      
      /// Access to quaternion.
      const Ogre::Quaternion& getQuaternion() const ;

      /// Composed orientation : first @c orientation then @this.
      Orientation operator*(const Orientation& orientation) const ;

      /// Q^-1.
      Orientation inverse() const ;
    
    private:

      // orientation.
      Ogre::Quaternion m_orientation ;
  
    };
  }
}
