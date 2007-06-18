/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#include <model/ship_control.h>

namespace ProjetUnivers {
  namespace Model {
    
    ShipControl::ShipControl(Oriented* i_stick)
    : m_stick(i_stick)
    {}
 
    Ogre::Vector3 ShipControl::NewtonMeter() const
    {
      if (m_stick)
      {
        /*!
          Convert orientation to a torque....
          
          @todo : 
          choose wiselly the correcpondance between pitch/Yaw/Roll and x/y/z
          and the +/-... seem done ?
          
          @todo 
            multiply result by a sensitivity factor
          
          @todo 
            this is a quite humanly understable calculus :
            find an optimal one.... 
        */
        const Ogre::Quaternion& quaternion 
          = m_stick->getOrientation().getQuaternion() ;
        
        Ogre::Vector3 torque(0,0,0) ;
        
        /// up/down
        torque += Ogre::Vector3::UNIT_X*quaternion.getPitch().valueRadians() ;
        
        /// left/rigth
        torque += Ogre::Vector3::UNIT_Y*quaternion.getYaw().valueRadians() ;        
        
        /// rotation
        torque += Ogre::Vector3::UNIT_Z*quaternion.getRoll().valueRadians() ;

        return torque ;        
        
      }
      else
      {
        // Default return value
        return Ogre::Vector3(0,0,0) ;
      }
    }
      
    
  }
}
