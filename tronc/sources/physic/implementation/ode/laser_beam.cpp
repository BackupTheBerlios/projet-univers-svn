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
#include <model/mobile.h>

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
        }

        void LaserBeam::onClose()
        {
          onCloseCollideable() ;
        }

        void LaserBeam::createGeometry(const dSpaceID& space)
        {
          /// build a ray
          Model::LaserBeam* beam = getTrait<Model::LaserBeam>() ;
          Model::Mobile* mobile = getTrait<Model::Mobile>() ;

          float collision_beam_length =
              std::max(mobile->getSpeed().MeterPerSecond().length()*getControlerSet()->getTimeStep(),
                       beam->getLength().Meter()) ;

          m_ray = dCreateRay(0,2*collision_beam_length) ;

          /// we use -z as forward @see Model::Orientation
          dGeomRaySet(m_ray,0,0,0,0,0,-1) ;
          dGeomRaySetParams(m_ray,false,false) ;
          dGeomRaySetClosestHit(m_ray,true) ;

          /// a geometry transform allows to have a local z axis inversion
          m_geometry1 = dCreateGeomTransform(space) ;
          dGeomTransformSetGeom(m_geometry1,m_ray) ;
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
