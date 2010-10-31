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
#include <kernel/implementation/deduction_element.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      DeductionElement::DeductionElement(Object* object)
      : m_object(object),
        m_pair()
      {}

      DeductionElement::DeductionElement(const ObjectPair& pair)
      : m_object(NULL),
        m_pair(pair)
      {}

      DeductionElement::DeductionElement(const DeductionElement& element)
      : m_object(element.m_object),
        m_pair(element.m_pair)
      {}

      bool DeductionElement::isObject() const
      {
        return m_object != NULL ;
      }

      Object* DeductionElement::getObject() const
      {
        return m_object ;
      }

      Object* DeductionElement::getObjectFrom() const
      {
        return m_pair.getObjectFrom() ;
      }

      Object* DeductionElement::getObjectTo() const
      {
        return m_pair.getObjectTo() ;
      }
    }
  }
}
