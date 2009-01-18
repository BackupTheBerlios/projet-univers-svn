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
#include <boost/function.hpp>
#include <ode/ode.h>

#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/base_controler.h>

#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/physic_system.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      namespace Ode
      {
        
        RegisterControlerSet(PhysicSystem) ;
        
        PhysicSystem::PhysicSystem(Kernel::Model* model)
        : Kernel::ControlerSet(model)
        {}

        void PhysicSystem::simulate(const float& seconds)
        {
          InternalMessage("Physic","Ode::PhysicSystem::simulate preparation") ;
          
          /// 1. apply all force/torque on objects
          applyTopDown(&Kernel::BaseControler::prepare) ;
          
          /// 2. simulate all world top down and update model
          boost::function2<void,
                           Kernel::BaseControler*,
                           float> f 
                              = &Kernel::BaseControler::simulate ;

          applyTopDown(std::bind2nd(f,m_timestep)) ;
        }
        
        void PhysicSystem::onInit()
        {
          Implementation::Ode::init() ;
        }

        void PhysicSystem::onClose()
        {
          Implementation::Ode::close() ;
        }
        
        /*!
          To be visible an object needs :
          - being positionned and (mobile or solid) 
          - ??? 
          not too far from the observer....
        */
        bool PhysicSystem::isVisible(Kernel::Object* i_object) const
        {
          /// @temp
          return true ;          
        }
      }
    }
  }
}
