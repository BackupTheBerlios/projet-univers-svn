/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/collideable.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        bool Collideable::canCollide(const dGeomID& g1,const dGeomID& g2)
        {
          unsigned long collision1 = dGeomGetCollideBits(g1) ;
          unsigned long collision2 = dGeomGetCollideBits(g2) ;

          if (collision1 == ApproximatedSolid && collision2 == ApproximatedSolid)
            return true ;
          if ((collision1 == Solid && collision2 == Laser) ||
              (collision2 == Solid && collision1 == Laser))
            return true ;

          return false ;
        }


        void Collideable::onInitCollideable()
        {
          InternalMessage("Physic","Physic::Implementation::Ode::Collideable::onInitCollideable entering "
                          + Kernel::toString(getControler()->getObject()->getIdentifier())) ;

          /*
            We need the parent physical object and parent physical world
          */
          PhysicalObject* body = getControler()->getControler<PhysicalObject>() ;

          // precondition : physical object is initialised

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
            if (m_geometry_placeable)
            {
              dGeomDestroy(m_geometry_placeable) ;
              m_geometry_placeable = 0 ;
            }
          }

          InternalMessage("Physic","Physic::Ode::Collideable::onCloseCollideable leaving") ;
        }

        Collideable::~Collideable()
        {}

        Collideable::Collideable()
        : m_geometry1(0),
          m_geometry2(0),
          m_geometry_placeable(0)
        {}

      }
    }
  }
}

