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
#include <ode/ode.h>

#include <kernel/log.h>
#include <model/laser_beam.h>
#include <physic/implementation/ode/ode.h>
#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/laser_beam.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {
      DeclareDeducedTrait(LaserBeam,
                          And(HasTrait(Implementation::PhysicalObject),
                              HasTrait(Model::LaserBeam))) ;

      namespace Ode
      {

        RegisterControler(LaserBeam, 
                          Implementation::LaserBeam, 
                          PhysicSystem) ;

        /*
          geom is put in the world's space
        */
        void LaserBeam::onInit()
        {
          InternalMessage("Physic","ODE::LaserBeam::onInit") ;
          onInitCollideable() ;
//          dMass ode_mass ;
//          dMassSetSphereTotal(&ode_mass,0.01,1) ;
//          BaseControler::getControler<Implementation::Ode::PhysicalObject>()->getBody()->setMass(&ode_mass) ;
        }

        void LaserBeam::onClose()
        {
          onCloseCollideable() ;
        }

        void LaserBeam::onChangeParent(Kernel::Object* i_old_parent)
        {
        }
        
        void LaserBeam::onUpdate()
        {
        }

        void LaserBeam::createGeometry(const dSpaceID& i_space)
        {
          /// build a cube and a placeable geom
          /*!
            @todo
            - dealt with hardcoded values
            - decal object on front if stretched
          */
          m_geometry1 = dCreateBox(i_space,1,1,50) ;
          dGeomSetCollideBits(m_geometry1,(unsigned long)Collideable::Laser) ;
        }
        
        void LaserBeam::createApproximatedGeometry(const dSpaceID& space)
        {
          createGeometry(space) ;
        }
        
        const Kernel::BaseControler* LaserBeam::getControler() const
        {
          return this ;
        }

        bool LaserBeam::isCollideableWith(const Collideable* collideable) const
        {
          return dynamic_cast<const LaserBeam*>(collideable) == NULL ;
        }

      }
    }
  }
}
