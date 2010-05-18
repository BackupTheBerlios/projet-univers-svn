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
#include <model/model.h>
#include <model/explosion.h>
#include <model/solid.h>
#include <model/with_lifetime.h>
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
            Solid* solid = getObject()->getTrait<Solid>() ;
            Distance explosion_radius ;
            
            if (solid)
              explosion_radius = 4*solid->getRadius() ;
            
            Duration explosion_duration(Duration::Second(2)) ;
            getObject()->addTrait(new Explosion(explosion_radius,explosion_duration)) ;
            
            // add a life time trait
            getObject()->addTrait(new WithLifetime(explosion_duration)) ;
            
            m_marked_to_destroy = true ;
          }
        }
      
      }
    }
  }
}

