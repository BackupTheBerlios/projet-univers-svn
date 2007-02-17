/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <base/point_de_vue.h>
#include <base/implantation/base_vue.h>


namespace ProjetUnivers {
  namespace Base {
    
    class ViewPoint ;
    
    namespace Implantation {


      void BaseVue::MarquerAupdate(const Evenement& _evenement)
      {
        if (pointDeVue)
        {
          pointDeVue->PenserAupdate(*this,_evenement) ;
        }
      }

      void BaseVue::MarquerAdestroy()
      {
        if (pointDeVue)
        {
          pointDeVue->PenserAdestroy(*this) ;
        } 
        // cette vue n'a pas de point de vue... elle ne sera pas 
        // rafraichie
      }


      BaseVue::BaseVue()
      : pointDeVue()
      {}

      BaseVue::~BaseVue()
      {
        /// @todo : supprimer des vues du modèle et du point de vue... ?
      }

    }
  }
}
