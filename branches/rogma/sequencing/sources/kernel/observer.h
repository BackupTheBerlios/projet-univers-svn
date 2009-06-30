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
      void realClose() ;
      void realUpdate() ;
      void realChangeParent(Object* old_parent) ;

      /// Constructs
      Observer(Trait*) ;

      bool       m_initialised ;
      bool       m_really_initialised ;
      Trait*     m_trait ;

      friend class ::ProjetUnivers::Kernel::Implementation::Operation ;
      friend class Model ;

    };
  }
}
