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
#pragma once

#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/observer.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    class ViewPoint ;

    /// A view on a trait.
    class BaseTraitView : public Observer
    {
    public:

      /// init the view after construction.
      virtual void realInit() ;

      /// abstract class means virtual destructor.
      virtual ~BaseTraitView() ;

      /// Access to the first parent view of the same viewpoint.
      /*!
        @return the first (up, by parentship) initialised view
      */
      template <class _View> _View* getView() const ;

      /// Access to the first ancestor view of the same viewpoint.
      template <class _View> _View* getAncestorView() const ;

    protected:

      /// abstract class means protected constructor.
      BaseTraitView(Trait* trait,ViewPoint* viewpoint) ;

    /*!
      @name data
    */
    //@{

      ViewPoint* m_viewpoint ;

    //@}

      friend class Trait ;
      friend class Model ;

    };
  }
}
#include <kernel/implementation/base_trait_view.cxx>
