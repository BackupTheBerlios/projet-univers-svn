/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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
#include <kernel/string.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/observer.h>
#include <kernel/implementation/operation.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      Operation::Operation(const Operation& operation)
      : m_type(operation.m_type),
        m_object(operation.m_object),
        m_observer(operation.m_observer),
        m_debug_display(operation.m_debug_display)
      {}

      Operation::Operation()
      : m_type(None),
        m_object(),
        m_observer(NULL)
      {}

      Operation Operation::init(Observer* observer)
      {
        Operation result ;
        result.m_type = Init ;
        result.m_object = observer->getObject() ;
        result.m_observer = observer ;
        result.m_debug_display = "Init(" + Kernel::toString(result.m_object->getIdentifier()) + "," + getObjectTypeIdentifier(result.m_observer).fullName() +")" ;
        return result ;
      }

      Operation Operation::close(Observer* observer)
      {
        Operation result ;
        result.m_type = Close ;
        result.m_object = observer->getObject() ;
        result.m_observer = observer ;
        result.m_debug_display = "Close(" + Kernel::toString(result.m_object->getIdentifier()) + "," + getObjectTypeIdentifier(result.m_observer).fullName() +")" ;
        return result ;
      }

      Operation Operation::update(Observer* observer)
      {
        Operation result ;
        result.m_type = Update ;
        result.m_object = observer->getObject() ;
        result.m_observer = observer ;
        result.m_debug_display = "Update(" + Kernel::toString(result.m_object->getIdentifier()) + "," + getObjectTypeIdentifier(result.m_observer).toString() +")" ;
        return result ;
      }

      void Operation::execute() const
      {
        switch(m_type)
        {
        case Init:
          m_observer->realInit() ;
          break ;
        case Close:
          m_observer->realClose() ;
          break ;
        case Update:
          m_observer->realUpdate() ;
          break ;
        case None:
          break ;
        }
      }

      std::string Operation::toString() const
      {
        return m_debug_display ;
      }

    }
  }
}
