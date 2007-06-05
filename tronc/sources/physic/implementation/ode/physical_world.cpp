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

#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/physical_world.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        RegisterControler(PhysicalWorld, 
                          Model::PhysicalWorld, 
                          PhysicSystem) ;

        PhysicalWorld::PhysicalWorld(Model::PhysicalWorld* i_object,
                                     PhysicSystem*         i_physic)
        : Kernel::Controler<Model::PhysicalWorld,
                            PhysicSystem>(i_object,i_physic),
          m_world(NULL)
        {}

        void PhysicalWorld::onInit()
        {
          InternalMessage("PhysicalWorld::onInit entering") ;
          if (m_world)
          {
            delete m_world ;
          }
          m_world = new dWorld() ;
          
          InternalMessage("PhysicalWorld::onInit leaving") ;
        }

        void PhysicalWorld::onClose()
        {
          InternalMessage("Physic::PhysicalWorld::onClose entering " + getObject()->getName()) ;
          if (m_world)
          {
            delete m_world ;
          }

          InternalMessage("Physic::PhysicalWorld::onClose leaving " + getObject()->getName()) ;
        }

        void PhysicalWorld::onChangeParent(Kernel::Object* i_old_parent)
        {
        }

        void PhysicalWorld::onUpdate()
        {
        }
        
        dWorld* PhysicalWorld::getWorld() const
        {
          return m_world ;
        }
        
        void PhysicalWorld::simulate(const float& i_seconds)
        {
          InternalMessage("PhysicalWorld::simulate " + getObject()->getName() + " Entering") ;
          /// simulate
          if (m_world)
          {
            dWorldStep(m_world->id(),i_seconds) ;
          }

          InternalMessage("PhysicalWorld::simulate " + getObject()->getName() + " Leaving") ;
        }
        
      }
    }
  }
}
