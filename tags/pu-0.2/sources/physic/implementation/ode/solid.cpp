/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#include <ode/ode.h>

#include <kernel/log.h>

#include <model/positionned.h>
#include <model/physical_world.h>
#include <model/physical_object.h>

#include <physic/implementation/ode/physical_object.h>

#include <physic/implementation/ode/solid.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        Solid::Solid(Model::Solid* i_object,
                     RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Solid,RealWorldViewPoint>(i_object,i_viewpoint),
          m_geometry(NULL),
          m_geometry_placeable(NULL)
        {}

        void Solid::onInit()
        {
          Kernel::Log::InternalMessage("Solid::onInit entering") ;

          m_geometry = new dGeom() ;
          m_geometry_placeable = new dGeomTransform() ;

          /// body attachment : need to get the physical object 
          Model::PhysicalObject* 
              body = getObject()->getParent<Model::PhysicalObject>() ; 
          check(body,"Solid::onInit no body parent") ;
          
          m_geometry_placeable->setBody(
              body->getView<PhysicalObject>(getViewPoint())->getBody()->id()) ;

          m_geometry_placeable->setGeom(m_geometry->id()) ;
          
          /// geom placement is relative to body 
          Ogre::Vector3 position = 
            getObject()->getTrait<Model::Positionned>()
                       ->getPosition(body->getObject()).Meter() ;
          
          m_geometry_placeable->setPosition(position.x,
                                            position.y,
                                            position.z) ; 

          Kernel::Log::InternalMessage("Solid::onInit leaving") ;
          
        }

        void Solid::onClose()
        {
          Kernel::Log::InternalMessage("Solid::onClose entering") ;
          if (m_geometry)
          {
            delete m_geometry ;
            m_geometry = NULL ;
          }
          if (m_geometry_placeable)
          {
            delete m_geometry_placeable ;
            m_geometry_placeable = NULL ;
          }
          Kernel::Log::InternalMessage("Solid::onClose leaving") ;
        }

        void Solid::onChangeParent(Kernel::Object* i_old_parent)
        {
        }
        void Solid::onUpdate()
        {
        }


      }
    }
  }
}
