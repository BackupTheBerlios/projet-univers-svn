/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#include <Ogre.h>

#include <kernel/log.h>
#include <kernel/error.h>

#include <display/exception.h>
#include <display/implementation/ogre/universe.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au mod�le dans ce point de vue
        RegisterView(Ogre::Universe,Model::Universe, Ogre::RealWorldViewPoint) ;


        Universe::Universe(Model::Universe* i_universe,
                           RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Universe,RealWorldViewPoint>(i_universe,i_viewpoint), 
          light(NULL)
        {
          Kernel::Log::InternalMessage("Built Ogre::Universe") ;
        }
        
        /// Initialise la vue.
        void Universe::onInit()
        {
          Kernel::Log::InternalMessage("Display::Universe::onInit Entering") ;
            
          check(getViewPoint(), 
                Exception("Universe::onInit sans point de vue")) ;
          
          this->getViewPoint()->getManager()
              ->setSkyBox( true, "PU/SpaceSkyBox", 50000 );
          
          light = this->getViewPoint()->getManager()
                      ->createLight("MainLight");
                
          /// lumi�re
          this->getViewPoint()->getManager()
                ->setAmbientLight(::Ogre::ColourValue(0.5, 0.5, 0.5));

          Kernel::Log::InternalMessage("Display::Universe::onInit Leaving") ;
        }

        /// Termine la vue.
        void Universe::onClose()
        {
          Kernel::Log::InternalMessage("Display::Universe::onClose Entering") ;

          check(getViewPoint(), 
                Exception("Universe::onClose sans point de vue")) ;
          
          this->getViewPoint()->getManager()->setSkyBox( false, "" );
          this->getViewPoint()->getManager()
               ->destroyLight(light) ;

          Kernel::Log::InternalMessage("Display::Universe::onClose Leaving") ;
        }

        void Universe::onUpdate()
        {
          /*!
            Rien n'a faire
          */
        }

      }
    }
  }
}
       
        
