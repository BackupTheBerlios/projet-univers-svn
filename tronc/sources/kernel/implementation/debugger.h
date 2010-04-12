/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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

#include <vector>
#include <kernel/implementation/event_listener.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      /// A debugger.
      class Debugger : public EventListener
      {
      public:

        Debugger() ;

      /*!
      @name Call back methods
      */
      //@{

        /// Called when entering notify
        virtual void startNotify(const Notifiable*) ;
        /// Called when leaving notify
        virtual void endNotify(const Notifiable*) ;

        /// Called when entering createObject
        virtual void startCreateObject() ;
        /// Called when leaving createObject
        virtual void endCreateObject(const Object* created_object) ;

        /// Called when entering destroyObject
        virtual void startDestroyObject(const Object* destroyed_object) ;
        /// Called when leaving destroyObject
        virtual void endDestroyObject() ;

        /// Called when entering addTrait
        virtual void startAddTrait(const Object*,const Trait* added_trait) ;
        /// Called when leaving addTrait
        virtual void endAddTrait(const Object*,const Trait* added_trait) ;

        /// Called when entering destroyTrait
        virtual void startDestroyTrait(const Object*,const Trait* destroyed_trait) ;
        /// Called when leaving destroyTrait
        virtual void endDestroyTrait(const Object*) ;

      //@}
      private:

        /// Debug version for object
        struct _Object
        {
          int identifier ;
        };

        std::vector<_Object> objects ;

      };
    }
  }
}
