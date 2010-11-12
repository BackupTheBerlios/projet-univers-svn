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

#include <kernel/relation.h>
#include <kernel/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    namespace Implementation
    {
      class Operation ;
    }
    class Model ;

    /// Something that observe a relation.
    class RelationObserver
    {
    public:

      /// initialize the observer after construction.
      void init() ;

      /// closes the observer before destruction.
      void close() ;

      /// update the observer.
      void update() ;

      /// Access to the starting object of the link.
      Object* getObjectFrom() const ;

      /// Access to the ending object of the link.
      Object* getObjectTo() const ;

      /// Access to relation.
      const Relation* getRelation() const ;

      virtual ~RelationObserver() ;

      /// True when onInit has been executed.
      bool isInitialised() const ;

      /// Identify the latest updated trait.
      const TypeIdentifier& getLatestUpdatedTrait() const ;

    protected:

      /// Called after the relation appears.
      virtual void onInit() = 0 ;

      /// Called just before the relation is destroyed.
      virtual void onClose() = 0 ;

      /// Called when the relation has changed.
      virtual void onUpdate() = 0 ;

      virtual void realInit() = 0 ;
      void realClose() ;
      void realUpdate() ;

      /// Constructs
      RelationObserver() ;

      bool       m_initialised ;
      bool       m_really_initialised ;
      Relation   m_relation ;

    private:

      /// Set the observed relation.
      void _setRelation(const Relation&) ;

      friend class ::ProjetUnivers::Kernel::Implementation::Operation ;
      friend class Model ;

      TypeIdentifier m_latest_updated_trait ;
    };
  }
}
