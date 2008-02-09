/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
      if (m_viewpoint)
      {
        if (! m_initialised && m_viewpoint->isInitialised())
        {
          onInit() ;
          m_initialised = true ;        
        }
      }
    }
    
    void BaseTraitView::_close()
    {
      if (m_initialised)
      {
        onClose() ;
        m_initialised = false ;        
      }
    }
    
    void BaseTraitView::_changed_parent(Object* i_old_parent)
    {
      if (m_initialised)
      {
        onChangeParent(i_old_parent) ;
      }
    }
    
    void BaseTraitView::_updated()
    {
      if (m_initialised)
      {
        onUpdate() ;
      }
    }
    
    BaseTraitView::~BaseTraitView()
    {
      _close() ;
      if (m_trait)
      {
        m_trait->_remove_view(m_viewpoint,this) ;
      }
    }

    BaseTraitView::BaseTraitView(Trait* trait,ViewPoint* viewpoint)
    : m_initialised(false),
      m_trait(trait), 
      m_viewpoint(viewpoint)
    {}

    Object* BaseTraitView::getObject() const
    {
      return m_trait->getObject() ;
    }
    
    Trait* BaseTraitView::getTrait() const
    {
      return m_trait ;
    }
  }
}
