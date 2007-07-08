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
#include <model/mobile.h>
#include <model/oriented.h>
#include <model/physical_object.h>
#include <model/solid.h>
#include <model/dragger.h>


namespace ProjetUnivers {
  namespace Model {
    

    Dragger::Dragger()
    {}
    
    Force Dragger::getAppliedForce() const
    {
      
      /*!
        The resistance (to get a capped speed) should be put here
        It avoid to define engine without capped speed...
      
        get the PhysicalObject parent, its speed and Cx (Solid)
        and apply a reverse fluid friction : 
          max(speed,speed*speed)*Cx
          
        @todo 
          eventually change coeeficient to tune resulting max speed...
      */
      PhysicalObject* physical_object = getObject()->getParent<PhysicalObject>() ;
      Solid* solid = physical_object ? 
                          physical_object->getObject()->getTrait<Solid>() 
                          : NULL ;
      Oriented* oriented = physical_object ? 
                              physical_object->getObject()->getTrait<Oriented>() 
                              : NULL;

//      std::cout << "Dragger::getAppliedForce physical_object=" << physical_object 
//                << " solid=" << solid 
//                << " oriented=" << oriented 
//                << std::endl ;

      if (physical_object && solid && oriented)
      {
        Mobile* mobile = physical_object->getObject()->getTrait<Mobile>() ;

        /// get the rotation against 
        const Speed& speed = mobile->getSpeed() ;
        Ogre::Vector3 meter_per_second(speed.MeterPerSecond()) ;
        float speed_value = meter_per_second.length() ;

        float drag_coefficient 
          = solid->getDragCoefficient(
            oriented->getOrientation(physical_object->getPhysicalWorld())) ;
        /*!
          result force have lenght = 
          max(speed_value,speed_value*speed_value)*drag_coeff 
          ...
        */
        meter_per_second *= -(std::max((float)1.0,speed_value)*drag_coefficient) ;
        
//        std::cout << "Dragger::getAppliedForce calculate force=" << meter_per_second << std::endl ;
        /// result force....
        return Force::Newton(meter_per_second[0],
                             meter_per_second[1],
                             meter_per_second[2]) ;
        
      }

      /// null force because not applicable.
      return Force() ;
    }
    
    
  }
}
