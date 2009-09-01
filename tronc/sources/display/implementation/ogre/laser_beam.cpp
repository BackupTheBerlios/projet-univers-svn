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
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/laser_beam.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Ogre::LaserBeam,
                     Model::LaserBeam,
                     Ogre::RealWorldViewPoint) ;


        void LaserBeam::onInit()
        {
          InternalMessage("Display","Entering Ogre::LaserBeam::onInit") ;

          Positioned* positioned(getView<Positioned>()) ;

          // build 3D object
          mesh = this->getViewPoint()->getManager()
                  ->createEntity(Utility::getUniqueName(),
                                 "laser.mesh") ;

          // put it on the node
          positioned->getNode()->attachObject(mesh) ;

          // reset scale factor
          positioned->getNode()->setScale(::Ogre::Vector3(1.0/conversion_factor,
                                                          1.0/conversion_factor,
                                                          1.0/conversion_factor)) ;

          InternalMessage("Display","Leaving Ogre::LaserBeam::onInit") ;
        }

        void LaserBeam::onClose()
        {
          InternalMessage("Display","Display::LaserBeam::onClose Entering") ;

          this->getViewPoint()->getManager()
               ->destroyEntity(mesh) ;

          InternalMessage("Display","Display::LaserBeam::onClose Leaving") ;
        }

        void LaserBeam::onUpdate()
        {

        }


      // @}

      }
    }
  }
}
