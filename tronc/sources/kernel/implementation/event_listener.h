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

#include <set>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Object ;
    class Observer ;
    class Trait ;

    namespace Implementation
    {

      /// A call-back interface for internal engine events.
      /*!
      To be used for internal purpose : debugging, profiling, statistics...
      The main idea is that if no listener is registered, the overhead is low.

      For example, as a debugger : listen all events and display the current
      status : list of existing objects, ...
      */
      class EventListener
      {
      public:

        static void addListener(EventListener*) ;
        static void removeListener(EventListener*) ;

        static const std::set<EventListener*>& getListeners() ;

        virtual ~EventListener() ;

      /*!
      @name Call back methods
      */
      //@{


        /// Called when entering onInit
        virtual void startOnInit(const Observer*) ;
        /// Called when leaving onInit
        virtual void endOnInit(const Observer*) ;

        /// Called when entering onUpdate
        virtual void startOnUpdate(const Observer*) ;
        /// Called when leaving onUpdate
        virtual void endOnUpdate(const Observer*) ;

        /// Called when entering onClose
        virtual void startOnClose(const Observer*) ;
        /// Called when leaving onClose
        virtual void endOnClose(const Observer*) ;

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

      protected:

        EventListener() ;

      private:

        static std::set<EventListener*> m_listeners ;

      };

#define invokeListenerMethod(method,...) \
  do { \
  for(std::set<Implementation::EventListener*>::const_iterator listener = Implementation::EventListener::getListeners().begin() ; listener != Implementation::EventListener::getListeners().end() ; ++listener) \
    (*listener)->method(__VA_ARGS__) ; \
  } while(0)

#define notifyStartOnInit(notifiable) invokeListenerMethod(startOnInit,notifiable)
#define notifyEndOnInit(notifiable) invokeListenerMethod(endOnInit,notifiable)
#define notifyStartOnUpdate(notifiable) invokeListenerMethod(startOnUpdate,notifiable)
#define notifyEndOnUpdate(notifiable) invokeListenerMethod(endOnUpdate,notifiable)
#define notifyStartOnClose(notifiable) invokeListenerMethod(startOnClose,notifiable)
#define notifyEndOnClose(notifiable) invokeListenerMethod(endOnClose,notifiable)
#define notifyStartCreateObject() invokeListenerMethod(startCreateObject)
#define notifyEndCreateObject(object) invokeListenerMethod(endCreateObject,object)
#define notifyStartDestroyObject(object) invokeListenerMethod(startDestroyObject,object)
#define notifyEndDestroyObject() invokeListenerMethod(endDestroyObject)
#define notifyStartAddTrait(object,trait) invokeListenerMethod(startAddTrait,object,trait)
#define notifyEndAddTrait(object,trait) invokeListenerMethod(endAddTrait,object,trait)
#define notifyStartDestroyTrait(object,trait) invokeListenerMethod(startDestroyTrait,object,trait)
#define notifyEndDestroyTrait(object) invokeListenerMethod(endDestroyTrait,object)

    }
  }
}

