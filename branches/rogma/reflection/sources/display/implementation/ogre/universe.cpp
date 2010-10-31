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
#include <Ogre.h>

#include <kernel/log.h>
#include <kernel/error.h>

#include <display/implementation/ogre/universe.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Ogre::Universe,
                     Model::Universe,
                     Ogre::RealWorldViewPoint) ;


        void Universe::onInit()
        {
          InternalMessage("Display","Display::Universe::onInit Entering") ;
            
          CHECK(getViewPoint(),"Universe::onInit sans point de vue") ;
          
          this->getViewPoint()->getManager()
              ->setSkyBox( true, "PU/SpaceSkyBox", 50000 );
          
          light = this->getViewPoint()->getManager()
                      ->createLight("MainLight");
                
          /// light
          this->getViewPoint()->getManager()
                ->setAmbientLight(::Ogre::ColourValue(0.5, 0.5, 0.5));

          InternalMessage("Display","Display::Universe::onInit Leaving") ;
        }

        void Universe::onClose()
        {
          InternalMessage("Display","Display::Universe::onClose Entering") ;

          CHECK(getViewPoint(),"Universe::onClose sans point de vue") ;
          
          this->getViewPoint()->getManager()->setSkyBox( false, "" );
          this->getViewPoint()->getManager()
               ->destroyLight(light) ;

          InternalMessage("Display","Display::Universe::onClose Leaving") ;
        }

      }
    }
  }
}
       
        
