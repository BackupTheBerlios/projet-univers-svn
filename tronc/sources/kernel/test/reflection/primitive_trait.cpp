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
#include <kernel/test/reflection/primitive_trait.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {
      namespace Reflection
      {
        void PrimitiveTrait::setName(const std::string& name)
        {
          m_name = name ;
        }

        const std::string& PrimitiveTrait::getName() const
        {
          return m_name ;
        }

        void PrimitiveTrait::setValue(const float& value)
        {
          m_value = value ;
        }

        const float& PrimitiveTrait::getValue() const
        {
          return m_value ;
        }

        void ReferenceTrait::setReference(const ObjectReference& reference)
        {
          m_reference = reference ;
        }

        const ObjectReference& ReferenceTrait::getReference() const
        {
          return m_reference ;
        }

        void BoolTrait::setBoolean(const bool& value)
        {
          m_value = value ;
        }

        const bool& BoolTrait::getBoolean() const
        {
          return m_value ;
        }

        void Ogre3DTrait::setVector(const ::Ogre::Vector3& value)
        {
          m_value = value ;
        }

        const ::Ogre::Vector3& Ogre3DTrait::getVector() const
        {
          return m_value ;
        }

        void QuaternionTrait::setValue(const ::Ogre::Quaternion& value)
        {
          m_value = value ;
        }

        const ::Ogre::Quaternion& QuaternionTrait::getValue() const
        {
          return m_value ;
        }

        std::ostream& operator<<(std::ostream& out,const Value& value)
        {
          out << "Value(m_value=" << value.m_value << ")" ;
          return out ;
        }

        void ValueTrait::setValue(const Value& value)
        {
          m_value = value ;
        }

        const Value& ValueTrait::getValue() const
        {
          return m_value ;
        }

        void EnumTrait::setValue(const Type& value)
        {
          m_value = value ;
        }

        const EnumTrait::Type& EnumTrait::getValue() const
        {
          return m_value ;
        }

        void SetTrait::setValue(const std::set<int>& value)
        {
          m_value = value ;
        }

        const std::set<int>& SetTrait::getValue() const
        {
          return m_value ;
        }

      }
    }
  }
}
