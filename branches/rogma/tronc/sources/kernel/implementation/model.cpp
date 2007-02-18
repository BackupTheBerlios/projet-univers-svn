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

#include <kernel/log.h>

#include <kernel/implementation/base_view.h>
#include <kernel/model.h>

namespace ProjetUnivers {
  namespace Kernel {
    
    void Model::addView(Implementation::BaseView* _view)
    {
      views.insert(_view) ;  
    }
      
    void Model::removeView(Implementation::BaseView* _view)
    {
      views.remove(_view) ;
    }
    
    Model::~Model()
    {
      for(std::set<Implementation::KernelView*>::iterator view = views.begin() ;
          view != views.end() ;
          ++view)
      {
        (*view)->markToDestroy() ;
        (*view)->detach() ;
      }
      
    }
    
    Model::Model()
    {}

    void Model::notify(const Event& _evenement)
    {
      for(std::set<Implementation::KernelView*>::iterator view = views.begin() ;
          view != views.end() ;
          ++view)
      {
        (*view)->markToUpdate(_evenement) ;
      }  
    }
    
    
  }
}


