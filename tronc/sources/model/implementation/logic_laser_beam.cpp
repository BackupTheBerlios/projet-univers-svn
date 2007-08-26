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
#include <kernel/log.h>
#include <model/model.h>
#include <model/implementation/logic_laser_beam.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      
      const float laser_duration = 2 ;
        
      RegisterControler(LogicLaserBeam, 
                        Model::LaserBeam, 
                        LogicSystem) ;
      
      LogicLaserBeam::LogicLaserBeam(Model::LaserBeam* i_object,
                                     LogicSystem*      i_system)
      : Kernel::Controler<Model::LaserBeam,
                          LogicSystem>(i_object,i_system),
        m_seconds_remaining(laser_duration)
      {
        InternalMessage("LogicLaserBeam controler built") ;
      }
      
      void LogicLaserBeam::simulate(const float& i_seconds)
      {
        // remove some mass percentage to massive trait
        // if reaches zero or negative : destroy the object (maybe in destructible controler instead?)
        InternalMessage("LogicLaserBeam::simulate entering") ;
        
        m_seconds_remaining -= i_seconds ;

        InternalMessage("LogicLaserBeam::simulate remaining : " + Kernel::toString(m_seconds_remaining)) ;
        
        if (m_seconds_remaining < 0)
        {
          InternalMessage("LogicLaserBeam::simulate destroying object") ;

          // mark the object for destruction
          getControlerSet()->addObjectToDestroy(getModel()->getObject()) ;
        }

        InternalMessage("LogicLaserBeam::simulate leaving") ;
        
      }
      
    }
  }
}
