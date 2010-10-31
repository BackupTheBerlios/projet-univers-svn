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
#include <kernel/log.h>
#include <kernel/object.h>

#include <model/model.h>

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
        
        void Collision::onInit()
        {
          InternalMessage("Model","Collision::onInit entering") ;
          m_beam = NULL ;
          m_destroyable = NULL ;
          /*
            if one object is a laser beam
            - destroy it 
            and if the other is destroyable
            - manage damage 
          */
          LaserBeam* beam1 = getTrait()->getObject1()->getTrait<LaserBeam>() ;
          LaserBeam* beam2 = getTrait()->getObject2()->getTrait<LaserBeam>() ;
          
          Destroyable* destroyable1 = getTrait()->getObject1()->getTrait<Destroyable>() ;
          Destroyable* destroyable2 = getTrait()->getObject2()->getTrait<Destroyable>() ;
          
          if (beam1)
          {
            m_beam = beam1 ;
            getTrait()->getObject1()->destroyObject() ;
          }

          if (beam2)
          {
            m_beam = beam2 ;
            getTrait()->getObject2()->destroyObject() ;
          }
          
          if (destroyable1)
          {
            m_destroyable = destroyable1 ;
          }

          if (destroyable2)
          {
            m_destroyable = destroyable2 ;
          }
          
          // handle beam/destroyable collision
          if (m_beam && m_destroyable)
          {
            InternalMessage("Model","Collision::onInit damaging " + Kernel::toString(m_beam->getEnergy().Joule())) ;
            m_destroyable->damage(m_beam->getEnergy()) ;
            Kernel::Object* hit = m_destroyable->getObject()->createObject() ;
            hit->addTrait(new Hit()) ;
            Position position(getRelativePosition(getObject(),m_destroyable->getObject())) ;

            InternalMessage("Model","Collision::onInit creating hit at " + ::Ogre::StringConverter::toString(position.Meter())) ;

            hit->addTrait(new Positioned(position)) ;
            hit->addTrait(new WithLifetime(Duration::Second(0))) ;
            hit->addTrait(new Sized(Distance(Distance::_Meter,60))) ;
            hit->addTrait(new Oriented(Orientation(position))) ;
          }          
          
          InternalMessage("Model","Collision::onInit leaving") ;
        }

        void Collision::simulate(const float&)
        {
          // mark the collision object for destruction
          getObject()->destroyObject() ;
        }

      }      
    }
  }
}
