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

#include <kernel/view_point.h>
#include <kernel/implementation/base_view.h>


namespace ProjetUnivers {
  namespace Kernel {
    
    class ViewPoint ;
    
    namespace Implementation {


      void BaseView::markToUpdate(const Event& _event)
      {
        if (viewPoint)
        {
          viewPoint->markToUpdate(this,_event) ;
        }
      }

      void BaseView::markToDestroy()
      {
        if (viewPoint)
        {
          viewPoint->markToDestroy(this) ;
        } 
        // cette vue n'a pas de point de vue... elle ne sera pas 
        // rafraichie
      }


      BaseView::BaseView()
      : viewPoint(NULL)
      {}

      BaseView::~BaseView()
      {
        /// @todo : supprimer des vues du modèle et du point de vue... ?
      }

    }
  }
}
