/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <model/hit.h>
#include <model/with_lifetime.h>
#include <model/positioned.h>
#include <model/sized.h>
#include <model/oriented.h>
#include <model/implementation/logic/collision.h>
#include <OgreStringConverter.h>

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
          LaserBeam* beam1 = getTrait()->getObject1()->getTrait<LaserBeam>() ;
          LaserBeam* beam2 = getTrait()->getObject2()->getTrait<LaserBeam>() ;
          LaserBeam* beam = NULL ;
          
          Destroyable* destroyable1 = getTrait()->getObject1()->getTrait<Destroyable>() ;
          Destroyable* destroyable2 = getTrait()->getObject2()->getTrait<Destroyable>() ;
          Destroyable* destroyable = NULL ;
          
          if (beam1)
          {
            beam = beam1 ;
            getTrait()->getObject1()->destroyObject() ;
          }

          if (beam2)
          {
            beam = beam2 ;
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
          
          // handle beam/destroyable collision
          if (beam && destroyable)
          {
            InternalMessage("Model","Collision::simulate damaging " + Kernel::toString(beam->getEnergy().Joule())) ;
            destroyable->damage(beam->getEnergy()) ;
            Kernel::Object* hit = destroyable->getObject()->createObject() ;
            hit->addTrait(new Hit()) ;
            Position position(getRelativePosition(getObject(),destroyable->getObject())) ;

            InternalMessage("Model","Collision::simulate creating hit at " + ::Ogre::StringConverter::toString(position.Meter())) ;

            hit->addTrait(new Positioned(position)) ;
            hit->addTrait(new WithLifetime(Duration::Second(0))) ;
            hit->addTrait(new Sized(Distance(Distance::_Meter,600))) ;
            hit->addTrait(new Oriented(Orientation(position))) ;
          }          
          
          // mark the collision object for destruction
          /// @todo pull up an event system or use the withLifeTime
          getObject()->destroyObject() ;
          
          InternalMessage("Model","Collision::simulate leaving") ;
        }
      }      
    }
  }
}
