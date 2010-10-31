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

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Algorithm 
    {

      /*
        solve an equation system :
          position+t*target_speed = t*interceptor_speed_vector
          norm(interceptor_speed_vector)=interceptor_speed

        Maxima (http://maxima.sourceforge.net/) session for solving this :
        writefile("result.txt");
        grind(algsys([target_position_x+t*target_speed_x = t*interceptor_speed_x,target_position_y+t*target_speed_y = t*interceptor_speed_y,target_position_z+t*target_speed_z = t*interceptor_speed_z,interceptor_speed_x^2+ interceptor_speed_y^2+ interceptor_speed_z^2 = interceptor_speed^2],[t,interceptor_speed_x,interceptor_speed_y,interceptor_speed_z])) ;
        --> result :
[t = -(target_position_z^2+target_position_y^2+target_position_x^2)
    /(sqrt(-target_position_y^2*target_speed_z^2
            -target_position_x^2*target_speed_z^2
            +2*target_position_y*target_position_z*target_speed_y
              *target_speed_z
            +2*target_position_x*target_position_z*target_speed_x
              *target_speed_z-target_position_z^2*target_speed_y^2
            -target_position_x^2*target_speed_y^2
            +2*target_position_x*target_position_y*target_speed_x
              *target_speed_y-target_position_z^2*target_speed_x^2
            -target_position_y^2*target_speed_x^2
            +interceptor_speed^2*target_position_z^2
            +interceptor_speed^2*target_position_y^2
            +interceptor_speed^2*target_position_x^2)
     +target_position_z*target_speed_z+target_position_y*target_speed_y
     +target_position_x*target_speed_x)

t = -(target_position_z^2+target_position_y^2+target_position_x^2)
    /(-sqrt(-target_position_y^2*target_speed_z^2
             -target_position_x^2*target_speed_z^2
             +2*target_position_y*target_position_z*target_speed_y
               *target_speed_z
             +2*target_position_x*target_position_z*target_speed_x
               *target_speed_z-target_position_z^2*target_speed_y^2
             -target_position_x^2*target_speed_y^2
             +2*target_position_x*target_position_y*target_speed_x
               *target_speed_y-target_position_z^2*target_speed_x^2
             -target_position_y^2*target_speed_x^2
             +interceptor_speed^2*target_position_z^2
             +interceptor_speed^2*target_position_y^2
             +interceptor_speed^2*target_position_x^2)
     +target_position_z*target_speed_z+target_position_y*target_speed_y
     +target_position_x*target_speed_x)
      */
      std::pair<bool,float> calculateInterceptionTime(
          const Ogre::Vector3& target_position,
          const Ogre::Vector3& target_speed,
          const float& interceptor_speed)
      {
        double square_target_position_x = pow(target_position.x,2) ;
        double square_target_position_y = pow(target_position.y,2) ;
        double square_target_position_z = pow(target_position.z,2) ;

        double square_interceptor_speed = pow(interceptor_speed,2) ;
        double a =
            -square_target_position_y*pow(target_speed.z,2)
            -square_target_position_x*pow(target_speed.z,2)
            -square_target_position_z*pow(target_speed.y,2)
            -square_target_position_x*pow(target_speed.y,2)
            -square_target_position_z*pow(target_speed.x,2)
            -square_target_position_y*pow(target_speed.x,2)
            +2*target_position.y*target_position.z*target_speed.y*target_speed.z
            +2*target_position.x*target_position.z*target_speed.x*target_speed.z
            +2*target_position.x*target_position.y*target_speed.x*target_speed.y
            +square_interceptor_speed*square_target_position_z
            +square_interceptor_speed*square_target_position_y
            +square_interceptor_speed*square_target_position_x ;

        if (a < 0)
        {
          /// no real solution : target is unreachable by interceptor
          return std::pair<bool,float>(false,0) ;
        }

        double b = target_position.z*target_speed.z+target_position.y*target_speed.y+target_position.x*target_speed.x ;

        double divisor1 = sqrt(a) + b ;
        double divisor2 = -sqrt(a) + b ;

        double divided = -(square_target_position_z+square_target_position_y+square_target_position_x) ;

        double time1 = -1 ;
        double time2 = -1 ;

        if (fabs(divisor1) > 1e-10)
        {
          time1 = divided/divisor1 ;
        }
        if (fabs(divisor2) > 1e-10)
        {
          time2 = divided/divisor2 ;
        }

        if (time1 > 0)
          return std::pair<bool,float>(true,(float)time1) ;
        if (time2 > 0)
          return std::pair<bool,float>(true,(float)time2) ;

        return std::pair<bool,float>(false,0) ;
      }
    }
  }
}
