/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <kernel/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    template <class _View> _View* BaseTraitView::getView() const
    {
      // 1. get the trait type associated with the view for that viewpoint
      TypeIdentifier trait_name = Trait::getTraitTypeOfView(getClassTypeIdentifier(_View),
                                                            getObjectTypeIdentifier(m_viewpoint)) ;

      // 2. get the parent object that has this trait
      // 3. if the view is really initialised returns the view otherwise back to 2
      Trait* trait = getObject()->getParent(trait_name) ;
      while (trait && trait->getView<_View>(m_viewpoint) && !trait->getView<_View>(m_viewpoint)->isInitialised())
      {
        trait = trait->getObject()->getAncestor(trait_name) ;
      }

      if (trait && trait->getView<_View>(m_viewpoint))
        return trait->getView<_View>(m_viewpoint) ;
      return NULL ;
    }

    template <class _View> _View* BaseTraitView::getAncestorView() const
    {
      // 1. get the trait type associated with the view for that viewpoint
      TypeIdentifier trait_name = Trait::getTraitTypeOfView(getClassTypeIdentifier(_View),
                                                            getObjectTypeIdentifier(m_viewpoint)) ;

      // 2. get the parent object that has this trait
      // 3. if the view is really initialised returns the view otherwise back to 2
      Trait* trait = getObject()->getAncestor(trait_name) ;
      while (trait && trait->getView<_View>(m_viewpoint) && !trait->getView<_View>(m_viewpoint)->isInitialised())
      {
        trait = trait->getObject()->getAncestor(trait_name) ;
      }

      if (trait && trait->getView<_View>(m_viewpoint))
        return trait->getView<_View>(m_viewpoint) ;
      return NULL ;
    }

  }
}


