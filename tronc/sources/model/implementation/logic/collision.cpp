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

#include <model/destroyable.h>
#include <model/laser_beam.h>
#include <model/implementation/logic/collision.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {      
        
        RegisterControler(Logic::Collision, 
                          Model::Collision, 
                          LogicSystem) ;
        
        Collision::Collision(Model::Collision* i_object,
                             LogicSystem*      i_system)
        : Kernel::Controler<Model::Collision,
                            LogicSystem>(i_object,i_system)
        {
          InternalMessage("Collision controler built") ;
        }
        
        void Collision::simulate(const float& i_seconds)
        {
          InternalMessage("Collision::simulate entering") ;
          
          /*
            if one object is a laser beam
            - destroy it 
            and if the other is destroyable
            - manage damage 
          */
          LaserBeam* laser1 = getModel()->getObject1()->getTrait<LaserBeam>() ;
          LaserBeam* laser2 = getModel()->getObject2()->getTrait<LaserBeam>() ;
          LaserBeam* laser = NULL ; 
          
          Destroyable* destroyable1 = getModel()->getObject1()->getTrait<Destroyable>() ;
          Destroyable* destroyable2 = getModel()->getObject2()->getTrait<Destroyable>() ;
          Destroyable* destroyable = NULL ;
          
          if (laser1)
          {
            laser = laser1 ;
            getControlerSet()->addObjectToDestroy(getModel()->getObject1()) ;
//            std::cout << "touche" << std::endl ;
          }

          if (laser2)
          {
            laser = laser2 ;
            getControlerSet()->addObjectToDestroy(getModel()->getObject2()) ;
//            std::cout << "touche" << std::endl ;
          }
          
          if (destroyable1)
          {
            destroyable = destroyable1 ;
          }

          if (destroyable2)
          {
            destroyable = destroyable2 ;
          }
          
          // handle laser/destroyable collision
          if (laser && destroyable)
          {
            destroyable->damage(laser->getEnergy()) ;
          }          
          
          // mark the collision object for destruction
          getControlerSet()->addObjectToDestroy(getModel()->getObject()) ;
          
          InternalMessage("Collision::simulate leaving") ;
        }
      }      
    }
  }
}
