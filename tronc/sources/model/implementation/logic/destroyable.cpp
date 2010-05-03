/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <model/model.h>
#include <model/explosion.h>
#include <model/solid.h>
#include <model/with_lifetime.h>
#include <model/positioned.h>
#include <model/implementation/logic/destroyable.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Implementation
    {
      namespace Logic
      {


        RegisterControler(Logic::Destroyable, 
                          Model::Destroyable, 
                          LogicSystem) ;

        void Destroyable::onInit()
        {
          m_marked_to_destroy = false ;
        }

        void Destroyable::simulate(const float& i_seconds)
        {
          if (getTrait()->getLife() <= 0 && !m_marked_to_destroy)
          {
            InternalMessage("Model","Logic::Destroyable destroying object") ;
            
            // create explosion
            Solid* solid = getTrait<Solid>() ;
            Distance explosion_radius ;
            
            if (solid)
              explosion_radius = 4*solid->getRadius() ;
            
            // duration may depend on size ?
            Duration explosion_duration(Duration::Second(2)) ;

            Kernel::Object* world(getObject()->getParent()) ;
            const Model::Position& world_position = getRelativePosition(getObject(),world) ;

            //a new object with same position under physical world
            Kernel::ObjectReference explosion(world->createObject()) ;
            explosion->addTrait(new Positioned(world_position)) ;
            explosion->addTrait(new Explosion(explosion_radius,explosion_duration)) ;
            // add speed of destroyed object ?
            // add a life time trait
            explosion->addTrait(new WithLifetime(explosion_duration)) ;
            
            getObject()->destroyObject() ;

            m_marked_to_destroy = true ;
          }
        }
      
      }
    }
  }
}

