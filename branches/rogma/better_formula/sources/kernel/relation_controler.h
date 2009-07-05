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

#include <kernel/base_relation_controler.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    class ControlerSet ;


    /// A controler on a relation.
    /*!
    @par Usage

      Inherit from this class and implement :
      - onInit, called at creation
      - onClose, called before destruction
      - onUpdate, called when the relation has changed (according to the formula)

    */
    template <class _ControlerSet> class RelationControler : public BaseRelationControler
    {
    public:

      /// Access to specialized viewpoint.
      _ControlerSet* getControlerSet() const ;

      /// Abstract class means virtual destructor.
      virtual ~RelationControler() ;

    protected:

    /*!
      @name To be redefined methods

      Default implementation is a empty stub.
      Each specific view should override some of these methods.
    */
    // @{

      /// Called after the view is created on a initialized viewpoint.
      virtual void onInit() ;

      /// Called just before the view is destroyed.
      virtual void onClose() ;

      /// Called when the relation has changed.
      virtual void onUpdate() ;

    // @}

      /// Abstract class means protected constructor.
      RelationControler() ;

    };
  }
}

#include <kernel/implementation/relation_controler.cxx>
