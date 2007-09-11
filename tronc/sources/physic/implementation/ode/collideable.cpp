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

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/collideable.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
          
        void Collideable::onInitCollideable()
        {
          InternalMessage("Physic::Implementation::Ode::Collideable::onInitCollideable entering "
                          + getControler()->getObject()->getName()) ;
          
          /*
            We need the parent physical object and parent physical world 
          */
          PhysicalObject* body = getPhysicalObject(getControler()) ;

          // precondition : physical object is initialised
          
          if (body)
          {
            
            InternalMessage("Physic::Implementation::Ode::Collideable::onInit init physical object") ;
            body->_init() ;
            PhysicalWorld* world = getPhysicalWorld(body) ;
            
            if (world)
            {

              InternalMessage("Physic::Implementation::Ode::Collideable::onInit creating geometry") ;
              dSpaceID space_id = body->getCollisionSpace()->id() ; 
              createGeometry(space_id) ;
              if (m_geometry_id)
              {
                InternalMessage("Physic::Implementation::Ode::Collideable::onInit trace#1") ;
                
                dGeomSetBody(m_geometry_id,body->getBody()->id()) ;
                                
                // user data of the geom is the controler.
                dGeomSetData(m_geometry_id,this) ;

                InternalMessage("Physic::Implementation::Ode::Collideable::onInit trace#1") ;

              }
            }
          }
          InternalMessage("Collideable::onInit leaving") ;
        }
        
        void Collideable::onCloseCollideable()
        {
          InternalMessage("Physic::Ode::Collideable::onCloseCollideable entering") ;

          if (m_geometry_id)
          {
            dGeomDestroy(m_geometry_id) ;
            m_geometry_id = 0 ;
          }
          if (m_geometry_placeable)
          {
            dGeomDestroy(m_geometry_placeable) ;
            m_geometry_placeable = 0 ;
          }

          InternalMessage("Physic::Ode::Collideable::onCloseCollideable leaving") ;
        }

        Collideable::~Collideable()
        {}

        Collideable::Collideable()
        : m_geometry_id(0),
          m_geometry_placeable(0)
        {}

      }
    }
  }
}

