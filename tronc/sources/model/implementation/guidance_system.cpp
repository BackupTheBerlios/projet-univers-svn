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
#include <model/physical_object.h>
#include <model/guidance_system.h>
#include <model/guidance_control.h>

namespace ProjetUnivers {
  namespace Model {
    
    GuidanceSystem::GuidanceSystem(const float& i_force)
    : m_control(NULL),
      m_force(i_force)
    {}
 
    Ogre::Vector3 GuidanceSystem::NewtonMeter() const
    {
      if (m_control)
      {
        PhysicalObject* physical_object = getObject()->getParent<PhysicalObject>() ;
        if (physical_object)
        {
          Oriented* oriented = physical_object->getObject()->getTrait<Oriented>() ;
          const Ogre::Quaternion& object_orientation 
            = oriented->getOrientation().getQuaternion() ;
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
            = m_control->getStickOrientation().getQuaternion() ;
          
  //        std::cout << "pitch=" << quaternion.getPitch().valueRadians()
  //                  << ",Yaw=" << quaternion.getYaw().valueRadians()
  //                  << ",Roll=" << quaternion.getRoll().valueRadians() 
  //                  << std::endl ;
                    
          Ogre::Vector3 torque(0,0,0) ;
          
          /// up/down, relative to physical object parent
          torque -= (object_orientation.xAxis())*quaternion.getPitch().valueRadians() ;
          
          /// left/rigth
          torque += (object_orientation.yAxis())*quaternion.getYaw().valueRadians() ;        
          
          /// rotation
          torque -= (object_orientation.zAxis())*quaternion.getRoll().valueRadians() ;
  
          return torque*m_force ;        

        }
      }

      // Default return value
      return Ogre::Vector3(0,0,0) ;
    }
      
    void GuidanceSystem::setControler(GuidanceControl* i_control)
    {
      m_control = i_control ;
    }
  }
}
