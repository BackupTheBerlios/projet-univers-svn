/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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

#include <kernel/view_point.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/base_trait_view.h>

namespace ProjetUnivers {
  namespace Kernel {

    void BaseTraitView::_init()
    {
      /*!
        We initialise only if the view point has been initialised.
      */
      if (viewpoint)
      {
        if (! initialised && viewpoint->initialised)
        {
          onInit() ;
          initialised = true ;        
        }
      }
    }
    
    void BaseTraitView::_close()
    {
      if (initialised)
      {
        onClose() ;
        initialised = false ;        
      }
    }
    
    void BaseTraitView::_changed_parent(Object* i_old_parent)
    {
      if (initialised)
      {
        onChangeParent(i_old_parent) ;
      }
    }
    
    void BaseTraitView::_updated()
    {
      if (initialised)
      {
        onUpdate() ;
      }
      
    }
    
    
    BaseTraitView::~BaseTraitView()
    {
      _close() ;
      if (trait)
      {
        trait->views.erase(viewpoint) ;
      }
      
    }

    BaseTraitView::BaseTraitView(Trait* i_trait,ViewPoint* i_viewpoint)
    : trait(i_trait), 
      viewpoint(i_viewpoint),
      initialised(false)
    {
      trait->views.insert(std::pair<ViewPoint*,BaseTraitView*>(i_viewpoint,this)) ;
    }

    Object* BaseTraitView::getObject() const
    {
      return trait->getObject() ;
    }
  }
}
