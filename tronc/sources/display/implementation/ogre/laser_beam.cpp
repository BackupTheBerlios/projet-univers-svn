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
#include <OgreVector3.h>

#include <kernel/log.h>

#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/laser_beam.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        RegisterView(Ogre::LaserBeam,
                     Model::LaserBeam,
                     Ogre::RealWorldViewPoint) ;


        LaserBeam::LaserBeam(Model::LaserBeam* i_object,
                             RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::LaserBeam,RealWorldViewPoint>(i_object,i_viewpoint), 
          mesh(NULL)
        {}
      
        void LaserBeam::onInit()
        {
          InternalMessage("Entering Ogre::LaserBeam::onInit") ;

          Positionned* positionned(getView<Positionned>()) ;
          positionned->_init() ;
          
          // build 3D object
          mesh = this->getViewPoint()->getManager()
                  ->createEntity(Utility::getUniqueName(),
                                 "laser.mesh") ;
          
          // put it on the node
          positionned->getNode()->attachObject(mesh) ;
          
          // reset scale factor
          positionned->getNode()->setScale(::Ogre::Vector3(1.0/conversion_factor,
                                                           1.0/conversion_factor,
                                                           1.0/conversion_factor)) ;
          
          InternalMessage("Leaving Ogre::LaserBeam::onInit") ;
        }
        
        void LaserBeam::onClose()
        {
          InternalMessage("Display::LaserBeam::onClose Entering") ;
          Positionned* positionned(getView<Positionned>()) ;
          if (positionned)
          {
            positionned->_close() ;
          }  
          
          this->getViewPoint()->getManager()
               ->destroyEntity(mesh) ;

          InternalMessage("Display::LaserBeam::onClose Leaving") ;
        }
      
        void LaserBeam::onUpdate()
        {
          
        }


      // @}
    
      }
    }
  }
}
