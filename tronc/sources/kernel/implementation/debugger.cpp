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
#include <kernel/implementation/debugger.h>
#include <kernel/observer.h>
#include <kernel/object.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      Debugger Debugger::debugger ;

      Debugger::Debugger()
      {
      }

      Debugger& Debugger::getDebugger()
      {
        return debugger ;
      }

      void Debugger::activate()
      {
        EventListener::addListener(this) ;
      }

      void Debugger::startOnInit(const Observer* listener)
      {
        std::string event ;
        event += getObjectTypeIdentifier(listener).fullName() ;
        event += "::onInit()" ;
        m_stack.push_back(event) ;
      }

      void Debugger::endOnInit(const Observer*)
      {
        m_stack.pop_back() ;
      }

      void Debugger::startOnUpdate(const Observer* listener)
      {
        std::string event ;
        event += getObjectTypeIdentifier(listener).fullName() ;
        event += "::onUpdate()" ;
        m_stack.push_back(event) ;
      }

      void Debugger::endOnUpdate(const Observer*)
      {
        m_stack.pop_back() ;
      }

      void Debugger::startOnClose(const Observer* listener)
      {
        std::string event ;
        event += getObjectTypeIdentifier(listener).fullName() ;
        event += "::onClose()" ;
        m_stack.push_back(event) ;
      }

      void Debugger::endOnClose(const Observer*)
      {
        m_stack.pop_back() ;
      }

      void Debugger::startCreateObject()
      {

      }

      void Debugger::endCreateObject(const Object* created_object)
      {
        _Object debug_object ;
        debug_object.identifier = created_object->getIdentifier() ;

        objects.push_back(debug_object) ;
      }

      void Debugger::startDestroyObject(const Object* /*destroyed_object*/)
      {

      }

      void Debugger::endDestroyObject()
      {

      }

      void Debugger::startAddTrait(const Object*,const Trait* /*added_trait*/)
      {

      }

      void Debugger::endAddTrait(const Object*,const Trait* /*added_trait*/)
      {

      }

      void Debugger::startDestroyTrait(const Object*,const Trait* /*destroyed_trait*/)
      {

      }

      void Debugger::endDestroyTrait(const Object*)
      {

      }

      std::string Debugger::getStack() const
      {
        std::string result("stack...\n") ;
        ///@todo
        for (std::vector<std::string>::const_iterator listener = m_stack.begin() ; listener != m_stack.end() ; ++listener)
          result += (*listener + "\n") ;

        return result ;
      }

    }
  }
}
