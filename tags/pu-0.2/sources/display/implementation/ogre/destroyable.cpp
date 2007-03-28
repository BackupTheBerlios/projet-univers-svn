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

#include <display/implementation/ogre/destroyable.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        RegisterView(Ogre::Destroyable, 
                     Model::Destroyable, 
                     Ogre::RealWorldViewPoint) ;

        /// Constructeur.
        Destroyable::Destroyable(Model::Destroyable* i_object,
                                 RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Destroyable,RealWorldViewPoint>(i_object,i_viewpoint)
        {}
      
        /// Initialise la vue.
        void Destroyable::onInit()
        {
        }

        /// Termine la vue.
        void Destroyable::onClose()
        {
        }
      
        /// Mise à jour.
        void Destroyable::onUpdate()
        {
        }
        
      }
    }
  }
}
