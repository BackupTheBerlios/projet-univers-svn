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

#include <affichage/implantation/ogre/destructible.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implantation {
      namespace Ogre {


        /// Constructeur.
        Destructible::Destructible
                    (const Base::Association<Model::Destructible>& _objet)
        : Vue<Model::Destructible>(_objet)
        {}
      
        /// Initialise la vue.
        void Destructible::init()
        {
        }

        /// Termine la vue.
        void Destructible::close()
        {
        }
      
        /// Mise à jour.
        void Destructible::update(const Base::Evenement&)
        {
        }
        
      }
    }
  }
}
