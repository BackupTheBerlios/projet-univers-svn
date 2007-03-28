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

#include <model/massive.h>
#include <model/mobile.h>
#include <model/positionned.h>
#include <model/physical_world.h>

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

      RegisterView(PhysicalObject, 
                   Model::PhysicalObject, 
                   RealWorldViewPoint) ;


        PhysicalObject::PhysicalObject(Model::PhysicalObject* i_object,
                                       RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::PhysicalObject,
                            RealWorldViewPoint>(i_object,i_viewpoint),
          m_body(NULL)
        {}

        void PhysicalObject::onInit()
        {
          Kernel::Log::InternalMessage("PhysicalObject::onInit entering") ;
          
          /// get the first parent having the PhysicalWorld property
          Model::PhysicalWorld* 
              world = getObject()->getParent<Model::PhysicalWorld>() ; 
          check(world,"PhysicalObject::onInit no world parent") ;
          
          m_body = new dBody() ;
          m_body->create(
              world->getView<PhysicalWorld>(getViewPoint())
                                      ->getWorld()->id()) ;

          /// set the inital values :
          updatePositionned() ;          
          updateMobile() ;
          updateMassive() ;

          Kernel::Log::InternalMessage("PhysicalObject::onInit leaving") ;

        }

        void PhysicalObject::updateMobile()
        {
          Model::Mobile* mobile = getObject()->getTrait<Model::Mobile>() ;

          Ogre::Vector3 speed = mobile->getSpeed().MeterPerSecond() ;
          
          Kernel::Log::InternalMessage("PhysicalObject::updateMobile initial speed=" 
                                       + toString(speed[0]) + ","
                                       + toString(speed[1]) + ","
                                       + toString(speed[2])) ;

          m_body->setLinearVel(speed[0],speed[1],speed[2]) ;

          Ogre::Vector3 angularSpeed = mobile->getAngularSpeed().RadianPerSecond() ;
          Kernel::Log::InformationMessage("PhysicalObject::updateMobile angular speed=" 
                                          + toString(angularSpeed.length())) ; 

          m_body->setAngularVel(angularSpeed[0],angularSpeed[1],angularSpeed[2]) ;
        }
        
        void PhysicalObject::updateMassive()
        {
          Model::Massive* massive = getObject()->getTrait<Model::Massive>() ;
          check(massive,"PhysicalObject::updateMassive no Massive trait") ;
          Model::Mass mass = massive->getMass() ;
          
          //m_body->setMass
          
        }
        
        void PhysicalObject::updatePositionned()
        {
          Model::Positionned* positionned = getObject()->getTrait<Model::Positionned>() ;
          
          /// have to take the position relatively to the physical_world parent 
          Model::PhysicalWorld* 
              world = getObject()->getParent<Model::PhysicalWorld>() ; 
          check(world,"PhysicalObject::onInit no world parent") ;
          
          Ogre::Vector3 position = positionned->getPosition(world->getObject()).Meter() ;
          m_body->setPosition((dReal)position.x,
                              (dReal)position.y,
                              (dReal)position.z) ;

          /// set orientation
        }

        void PhysicalObject::onClose()
        {
          Kernel::Log::InternalMessage("PhysicalObject::onClose entering") ;
          if (m_body)
          {
            delete m_body ;
            m_body = NULL ;
          }
          Kernel::Log::InternalMessage("PhysicalObject::onClose leaving") ;
        }

        void PhysicalObject::onChangeParent(Kernel::Object* i_old_parent)
        {
        }
        void PhysicalObject::onUpdate()
        {
        }
        
        dBody* PhysicalObject::getBody() const
        {
          return m_body ;
        }
      }
    }
  }
}
