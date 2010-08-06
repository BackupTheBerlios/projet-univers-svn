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
#include <kernel/object.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      Debugger debugger ;

      Debugger::Debugger()
      {
//        EventListener::addListener(this) ;
      }

      void Debugger::startNotify(const Notifiable*)
      {

      }

      void Debugger::endNotify(const Notifiable*)
      {

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

    }
  }
}
