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

namespace ProjetUnivers
{
  namespace Kernel
  {

    void BaseTraitView::realInit()
    {
      /*!
        We initialise only if the view point has been initialised.
      */
      if (m_viewpoint)
      {
        if (! m_really_initialised && m_viewpoint->isInitialised())
        {
          onInit() ;
          m_really_initialised = true ;
        }
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
    : Observer(trait),
      m_viewpoint(viewpoint)
    {}

    BaseTraitView::BaseTraitView()
    : m_viewpoint(NULL)
    {}

    void BaseTraitView::setViewPoint(ViewPoint* viewpoint)
    {
      m_viewpoint = viewpoint ;
    }

  }
}
