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
#include <kernel/object.h>

#include <model/massive.h>
#include <model/mobile.h>

#include <model/laser_beam.h>

namespace ProjetUnivers {
  namespace Model {
      
    LaserBeam::LaserBeam()
    {}
  
    Energy LaserBeam::getEnergy() const
    {
      Massive* massive = getObject()->getTrait<Massive>() ;
      Mobile* mobile = getObject()->getTrait<Mobile>() ;
      if (massive && mobile)
      {
        float mass_kilogram = massive->getMass().Kilogram() ;
        float speed_meter_per_second = mobile->getSpeed().MeterPerSecond().length() ;
        
        return Energy::Joule(0.5*mass_kilogram
                             *speed_meter_per_second*speed_meter_per_second) ;
      }
      else
      {
        return Energy() ;
      }
    }
  }
}
