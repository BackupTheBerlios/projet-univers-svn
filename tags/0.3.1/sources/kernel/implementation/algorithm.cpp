/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <OgreStringConverter.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/algorithm.h>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Algorithm {

      /*
        distance(target_positon+t*target_speed) = t*interceptor_speed
        formal solver gives :
          
        delta = 
            (-target_positon.y^2-target_positon.x^2)*target_speed.z^2
            +(2*target_positon.y*target_positon.z*target_speed.y+2*target_positon.x*target_positon.z*target_speed.x)*target_speed.z
            +(-target_positon.z^2-target_positon.x^2)*target_speed.y^2
            +2*target_positon.x*target_positon.y*target_speed.x*target_speed.y
            +(-target_positon.z^2-target_positon.y^2)*target_speed.x^2
            +interceptor_speed^2*target_positon.z^2
            +interceptor_speed^2*target_positon.y^2
            +interceptor_speed^2*target_positon.x^2
        
        if delta > 0
        t = (sqrt(delta)
              -target_positon.z*target_speed.z-target_positon.y*target_speed.y-target_positon.x*target_speed.x)
            /(target_speed.z^2+target_speed.y^2+target_speed.x^2-laser_speed^2)
        
        special case for delta=0 when equation becomes linear
      */
      std::pair<bool,float> calculateInterceptionTime(
          const Ogre::Vector3& target_position,
          const Ogre::Vector3& target_speed,
          const float& interceptor_speed)
      {
        
		InternalMessage("Kernel","calculateInterceptionTime(" + Ogre::StringConverter::toString(target_position) + 
		                         "," + Ogre::StringConverter::toString(target_speed) + "," + toString(interceptor_speed)) ;
        // result ;
        float time = 0 ;
        
        if (target_speed.length() != 0)
        {
          
          float delta = 
                  (-pow(target_position.y,2)-pow(target_position.x,2))*pow(target_speed.z,2)
                  +(2*target_position.y*target_position.z*target_speed.y+2*target_position.x*target_position.z*target_speed.x)*target_speed.z
                  +(-pow(target_position.z,2)-pow(target_position.x,2))*pow(target_speed.y,2)
                  +2*target_position.x*target_position.y*target_speed.x*target_speed.y
                  +(-pow(target_position.z,2)-pow(target_position.y,2))*pow(target_speed.x,2)
                  +pow(interceptor_speed,2)*pow(target_position.z,2)
                  +pow(interceptor_speed,2)*pow(target_position.y,2)
                  +pow(interceptor_speed,2)*pow(target_position.x,2) ;

		  InternalMessage("Kernel","target_speed.squaredLength()=" + toString(target_speed.squaredLength())) ; 
          
          float divisor = target_speed.squaredLength()-pow(interceptor_speed,2) ;
          
          if (delta > 0 && fabs(divisor) > 1e-10)
          {
            float b = -target_position.z*target_speed.z-target_position.y*target_speed.y-target_position.x*target_speed.x ;
            time = (sqrt(delta)+b)/divisor ;
            if (time < 0)
              time = (-sqrt(delta)+b)/divisor ;
          }
          else
          {
            /// no real solution : target is unreachable by interceptor
            return std::pair<bool,float>(false,0) ;
          }
        }
        else
        {
          time = target_position.length()/interceptor_speed ;
        }
        
        return std::pair<bool,float>(true,time) ;
      }
      
    }
  }
}
