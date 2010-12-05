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

#include <model/torque_generator.h>

namespace ProjetUnivers
{
  namespace Model
  {
    
    /// For objects that resist rotation.
    /*!
      A stabilizer is made of a direction. It will resist against its 
      physical object rotation in that direction. 
    */
    class Stabilizer : public TorqueGenerator
    {
    public:

      /// Constructor.
      Stabilizer(const float& i_x,  
                 const float& i_y,
                 const float& i_z) ;

      /// Read a Stabilizer trait.
      /*!
        stored as 
        @code
          <Stabilizer axis_x=".." axis_y=".." axis_z=".."/>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
 
      /// get the torque in newton.meter.
      virtual Ogre::Vector3 NewtonMeter() const ;
      
    private:
      
      /// Resist against rotation around that axis. 
      Ogre::Vector3 m_axis ;
      
    };
  }
}
