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
#include <kernel/implementation/event_listener.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {
      std::set<EventListener*> EventListener::m_listeners ;

      void EventListener::addListener(EventListener* listener)
      {
        m_listeners.insert(listener) ;
      }

      void EventListener::removeListener(EventListener* listener)
      {
        m_listeners.erase(listener) ;
      }

      const std::set<EventListener*>& EventListener::getListeners()
      {
        return m_listeners ;
      }

      EventListener::~EventListener()
      {
        removeListener(this) ;
      }

      EventListener::EventListener()
      {}

      void EventListener::startNotify(const Notifiable*)
      {}
      void EventListener::endNotify(const Notifiable*)
      {}
      void EventListener::startCreateObject()
      {}
      void EventListener::endCreateObject(const Object*)
      {}
      void EventListener::startDestroyObject(const Object*)
      {}
      void EventListener::endDestroyObject()
      {}
      void EventListener::startAddTrait(const Object*,const Trait*)
      {}
      void EventListener::endAddTrait(const Object*,const Trait*)
      {}
      void EventListener::startDestroyTrait(const Object*,const Trait*)
      {}
      void EventListener::endDestroyTrait(const Object*)
      {}

    }
  }
}
