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

#include <kernel/implementation/base_view.h>
#include <kernel/view_point.h>


namespace ProjetUnivers {
  namespace Kernel {

    void ViewPoint::update()
    {
      
      for(std::vector<Update>::iterator update = updates.begin() ;
          update != updates.end() ;
          ++update)
      {
        update->view->update(update->event) ;
      }
      updates.clear() ;

      for (std::vector<Implementation::BaseView*>::iterator view = viewsToDestroy.begin() ;
           view != viewsToDestroy.end() ;
           ++view)
      {
        this->destroy(*view) ;
      }
      
      /// on vide sans détruire l'espace alloué
      viewsToDestroy.resize(0) ;
    }
  
    ViewPoint::ViewPoint()
    {}

    void ViewPoint::add(Implementation::BaseView* _view)
    {
      if (_view)
      {
        _view->viewPoint = this ;
        views.insert(_view) ;
      }
      // sinon ... ???
    }
    
    void ViewPoint::remove(Implementation::BaseView* _view)
    {
      destroy(_view) ;
    }
    
    void ViewPoint::markToUpdate(Implementation::BaseView* _view,
                                  const Event& _event)
    {
      updates.push_back(Update(_view,_event)) ;
    }
    
    void ViewPoint::markToDestroy(Implementation::BaseView* _view)
    {
      viewsToDestroy.push_back(_view) ;
    }
    void ViewPoint::destroy(Implementation::BaseView* _view)
    {
      if (this->views.erase(_view) != 0)
      {
        delete _view ;
      }
    }
    
    
  }
}

