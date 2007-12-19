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
#include <model/implementation/logic/laser_beam.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {
          
        const float laser_duration = 2 ;
          
        RegisterControler(LaserBeam, 
                          Model::LaserBeam, 
                          LogicSystem) ;
        
        LaserBeam::LaserBeam(Model::LaserBeam* i_object,
                             LogicSystem*      i_system)
        : Kernel::Controler<Model::LaserBeam,
                            LogicSystem>(i_object,i_system),
          m_seconds_remaining(laser_duration)
        {
          InternalMessage("Model","Logic::LaserBeam controler built") ;
        }
        
        void LaserBeam::simulate(const float& i_seconds)
        {
          // remove some mass percentage to massive trait
          // if reaches zero or negative : destroy the object (maybe in destructible controler instead?)
          InternalMessage("Model","Logic::LaserBeam::simulate entering") ;
          
          m_seconds_remaining -= i_seconds ;
  
          InternalMessage("Model","Logic::LaserBeam::simulate remaining : " + Kernel::toString(m_seconds_remaining)) ;
          
          if (m_seconds_remaining < 0)
          {
            InternalMessage("Model","Logic::LaserBeam::simulate destroying object") ;
  
            // mark the object for destruction
            getControlerSet()->addObjectToDestroy(getModel()->getObject()) ;
          }
  
          InternalMessage("Model","Logic::LaserBeam::simulate leaving") ;
          
        }
      }      
    }
  }
}
