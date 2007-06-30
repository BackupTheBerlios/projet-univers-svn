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
#include <algorithm>
#include <OgreQuaternion.h>

#include <kernel/log.h>

#include <model/torque_generator.h>
#include <model/mobile.h>
#include <model/oriented.h>
#include <model/physical_object.h>

#include <model/stabilizer.h>

namespace ProjetUnivers {
  namespace Model {
    
    Stabilizer::Stabilizer(const float& i_x,  
                           const float& i_y,
                           const float& i_z)
    : m_axis(i_x,i_y,i_z)
    {}

    /// Applies resistance to rotation.
    /*!
      Generate a torque.
    */
    Ogre::Vector3 Stabilizer::NewtonMeter() const
    {
      PhysicalObject* physical_object = getObject()->getParent<PhysicalObject>() ;
      Oriented* oriented = physical_object->getObject()->getTrait<Oriented>() ;

      if (physical_object && oriented)
      {
        
        Mobile* mobile = physical_object->getObject()->getTrait<Mobile>() ;
        
        /// get the rotation against 
        const AngularSpeed& speed = mobile->getAngularSpeed() ;
        
        InternalMessage("Model::Stabilizer::NewtonMeter angular speed="
                        + toString(speed.RadianPerSecond()[0]) + ","
                        + toString(speed.RadianPerSecond()[1]) + ","
                        + toString(speed.RadianPerSecond()[2])) ;
        
        
        Ogre::Quaternion object_orientation = 
          oriented->getOrientation(physical_object->getPhysicalWorld()).getQuaternion() ;
        
        
        InternalMessage("Model::Stabilizer::NewtonMeter object orientation="
                        + toString(object_orientation.w) + ","
                        + toString(object_orientation.x) + ","
                        + toString(object_orientation.y) + ","
                        + toString(object_orientation.z)) ;
        
        /// calculate 
        Ogre::Vector3 global_axis = object_orientation*m_axis ;

        InternalMessage("Model::Stabilizer::NewtonMeter global_axis="
                        + toString(global_axis[0]) + ","
                        + toString(global_axis[1]) + ","
                        + toString(global_axis[2])) ;

        
        // projection of speed onto the axis. 
        float force = global_axis.dotProduct(speed.TurnPerSecond()) ;

        /// sign of force is : positive when axis and speed are oriented same way
        float sign ;
        if (force < 0)
        {
          sign = -1 ;    
        }
        else
        {
          sign = +1 ;    
        }
          

        InternalMessage("Model::Stabilizer::NewtonMeter force="
                        + toString((float)force)) ;
        
        global_axis.normalise() ;
        
        global_axis *= -sign*std::max(std::max(force,-force),(force*force)) ;

        InternalMessage("Model::Stabilizer::NewtonMeter result="
                        + toString(global_axis[0]) + ","
                        + toString(global_axis[1]) + ","
                        + toString(global_axis[2])) ;
        
        return global_axis ;
      }
      
      /// return value for not applicable.
      return Ogre::Vector3(0,0,0) ;
    }
    
  }
}

