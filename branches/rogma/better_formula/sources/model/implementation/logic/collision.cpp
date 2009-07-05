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
#include <kernel/object.h>

#include <model/model.h>

#include <model/destroyable.h>
#include <model/laser_beam.h>
#include <model/implementation/logic/collision.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Implementation
    {
      namespace Logic
      {
        
        RegisterControler(Logic::Collision, 
                          Model::Collision, 
                          LogicSystem) ;
        
        void Collision::simulate(const float& i_seconds)
        {
          InternalMessage("Model","Collision::simulate entering") ;
          
          /*
            if one object is a laser beam
            - destroy it 
            and if the other is destroyable
            - manage damage 
          */
          LaserBeam* laser1 = getTrait()->getObject1()->getTrait<LaserBeam>() ;
          LaserBeam* laser2 = getTrait()->getObject2()->getTrait<LaserBeam>() ;
          LaserBeam* laser = NULL ; 
          
          Destroyable* destroyable1 = getTrait()->getObject1()->getTrait<Destroyable>() ;
          Destroyable* destroyable2 = getTrait()->getObject2()->getTrait<Destroyable>() ;
          Destroyable* destroyable = NULL ;
          
          if (laser1)
          {
            laser = laser1 ;
            getTrait()->getObject1()->destroyObject() ;
          }

          if (laser2)
          {
            laser = laser2 ;
            getTrait()->getObject2()->destroyObject() ;
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
            InternalMessage("Model","Collision::simulate damaging " + Kernel::toString(laser->getEnergy().Joule())) ;
            destroyable->damage(laser->getEnergy()) ;
          }          
          
          // mark the collision object for destruction
          getObject()->destroyObject() ;
          
          InternalMessage("Model","Collision::simulate leaving") ;
        }
      }      
    }
  }
}
