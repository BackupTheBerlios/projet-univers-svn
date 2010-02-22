/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Mathieu ROGER                                 *
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
#include <kernel/string.h>
#include <kernel/parameters.h>

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/collideable.h>
#include <physic/implementation/ode/laser_beam.h>
#include <model/laser_beam.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      namespace Ode
      {

        bool Collideable::canCollide(const dGeomID& geometry1,const dGeomID& geometry2)
        {
          unsigned long collision1 = dGeomGetCollideBits(geometry1) ;
          unsigned long collision2 = dGeomGetCollideBits(geometry2) ;

          if (collision1 == ApproximatedSolid && collision2 == ApproximatedSolid)
          {
            return true ;
          }

          if (collision1 == Solid && collision2 == Laser)
          {
            Collideable* collideable1 = static_cast<Collideable*>(dGeomGetData(geometry1)) ;
            LaserBeam* laser_beam = dynamic_cast<LaserBeam*>((Collideable*)dGeomGetData(geometry2)) ;
            if (!collideable1 || !laser_beam)
            {
              ErrorMessage("Collideable::canCollide") ;
              throw std::exception() ;
            }
            InternalMessage("Collision","laser/ship collision") ;
            return laser_beam->getTrait<Model::LaserBeam>()->getFiringShip() != collideable1->getControler()->getObject() ;
          }

          if (collision2 == Solid && collision1 == Laser)
          {
            Collideable* collideable2 = static_cast<Collideable*>(dGeomGetData(geometry2)) ;
            Ode::LaserBeam* laser_beam = dynamic_cast<Ode::LaserBeam*>((Collideable*)dGeomGetData(geometry1)) ;
            if (!collideable2 || !laser_beam)
            {
              ErrorMessage("Collideable::canCollide") ;
              throw std::exception() ;
            }

            InternalMessage("Collision","laser/ship collision") ;
            return laser_beam->getTrait<Model::LaserBeam>()->getFiringShip() != collideable2->getControler()->getObject() ;
          }

          return false ;
        }

        float Collideable::getContactSoftConstraintForceMixing(const dGeomID& geometry1,const dGeomID& geometry2)
        {
          unsigned long collision1 = dGeomGetCollideBits(geometry1) ;
          unsigned long collision2 = dGeomGetCollideBits(geometry2) ;

          if (collision1 == ApproximatedSolid && collision2 == ApproximatedSolid)
          {
            return Kernel::Parameters::getValue<float>("Physic","ContactSoftConstraintForceMixingForCollision",1) ;
          }

          if ((collision1 == Solid && collision2 == Laser) || (collision2 == Solid && collision1 == Laser))
          {
            return Kernel::Parameters::getValue<float>("Physic","ContactSoftConstraintForceMixingForImpact",40) ;
          }

          return 1 ;
        }

        void Collideable::onInitCollideable()
        {
          InternalMessage("Physic","Physic::Implementation::Ode::Collideable::onInitCollideable entering "
                          + Kernel::toString(getControler()->getObject()->getIdentifier())) ;

          /*
            We need the parent physical object and parent physical world
          */
          PhysicalObject* body = getControler()->getControler<PhysicalObject>() ;

          // precondition : physical object is initialized

          if (body)
          {

            InternalMessage("Physic","Physic::Implementation::Ode::Collideable::onInit init physical object") ;
            PhysicalWorld* world = body->getAncestorControler<PhysicalWorld>() ;

            if (world)
            {

              InternalMessage("Physic","Physic::Implementation::Ode::Collideable::onInit creating geometry") ;
              dSpaceID space_id = body->getCollisionSpace()->id() ;
              createGeometry(space_id) ;
              InternalMessage("Physic","Physic::Implementation::Ode::Collideable::onInit trace#1") ;

              if (m_geometry1)
              {
                dGeomSetBody(m_geometry1,body->getBody()->id()) ;
                dGeomSetData(m_geometry1,this) ;
              }

              if (m_geometry2)
              {
                dGeomSetBody(m_geometry2,body->getBody()->id()) ;
                dGeomSetData(m_geometry2,this) ;
              }

              InternalMessage("Physic","Physic::Implementation::Ode::Collideable::onInit trace#1") ;
            }
          }
          InternalMessage("Physic","Collideable::onInit leaving") ;
        }

        void Collideable::onCloseCollideable()
        {
          InternalMessage("Physic","Physic::Ode::Collideable::onCloseCollideable entering") ;

          PhysicalObject* body = getControler()->getControler<PhysicalObject>() ;

          if (body)
          {
            if (m_geometry1)
            {
              dGeomDestroy(m_geometry1) ;
              m_geometry1 = 0 ;
            }
            if (m_geometry2)
            {
              dGeomDestroy(m_geometry2) ;
              m_geometry2 = 0 ;
            }
          }

          InternalMessage("Physic","Physic::Ode::Collideable::onCloseCollideable leaving") ;
        }

        Collideable::~Collideable()
        {}

        Collideable::Collideable()
        : m_geometry1(0),
          m_geometry2(0)
        {}

      }
    }
  }
}

