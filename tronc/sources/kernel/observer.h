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

#include <set>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {
      class Operation ;
    }
    class Object ;
    class Trait ;
    class Model ;

    /// Something that observes a trait.
    class Observer
    {
    public:

      /// initialize the observer after construction.
      void _init() ;

      /// closes the observer before destruction.
      void _close() ;

      /// update the observer for a change_parent.
      void _changed_parent(Object* old_parent) ;

      /// update the observer.
      void _updated() ;

      /// Access to object.
      Object* getObject() const ;

      /// Access to trait
      Trait* getTrait() const ;

      /// First ancestor (including @c this) with trait T.
      template <class T> T* getParent() const ;

      /// First ancestor (excluding @c this) with trait T.
      template <class T> T* getAncestor() const ;

      /// Get all the descendant (excluding @c this) with trait T.
      template <class T> std::set<T*> getDescendants() const ;

      /// Get all the descendant (including @c this) with trait T.
      template <class T> std::set<T*> getChildren() const ;

      /// Get the descendant (including @c this) with trait T.
      /*!
        Return NULL iff severals.
      */
      template <class T> T* getChild() const ;

      virtual ~Observer() ;

      /// True when onInit has been executed.
      bool isInitialised() const ;

    protected:

      /// Called after the trait appears.
      virtual void onInit() = 0 ;

      /// Called just before the trait is destroyed.
      virtual void onClose() = 0 ;

      /// Called when parent changed.
      virtual void onChangeParent(Object* old_parent) = 0 ;

      /// Called when the model trait has changed.
      virtual void onUpdate() = 0 ;

      virtual void realInit() = 0 ;
      virtual void realClose() ;
      void realUpdate() ;
      void realChangeParent(Object* old_parent) ;

      /// Constructs
      Observer(Trait*) ;
      Observer() ;

      bool       m_initialised ;
      bool       m_really_initialised ;
      Trait*     m_trait ;

    private:

      /// Set the trait observed
      void setObserved(Trait*) ;

      friend class ::ProjetUnivers::Kernel::Implementation::Operation ;
      friend class Model ;
      friend class Trait ;

    };
  }
}

#include <kernel/implementation/observer.cxx>
