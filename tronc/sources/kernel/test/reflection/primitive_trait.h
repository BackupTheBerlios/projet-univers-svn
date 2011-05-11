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

#include <map>
#include <ostream>
#include <set>
#include <vector>
#include <list>
#include <OgreVector3.h>
#include <kernel/trait.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {
      namespace Reflection
      {
        /// A testing trait
        class PrimitiveTrait : public Trait
        {
        public:

          void setName(const std::string&) ;
          const std::string& getName() const ;

          void setValue(const float&) ;
          const float& getValue() const ;

        private:

          std::string m_name ;
          float m_value ;
        };

        /// A testing trait
        class ReferenceTrait : public Trait
        {
        public:

          void setReference(const ObjectReference&) ;
          const ObjectReference& getReference() const ;

        private:

          ObjectReference m_reference ;
        };

        /// A testing trait
        class BoolTrait : public Trait
        {
        public:

          void setBoolean(const bool&) ;
          const bool& getBoolean() const ;

        private:

          bool m_value ;
        };

        /// A testing trait
        class Ogre3DTrait : public Trait
        {
        public:

          void setVector(const ::Ogre::Vector3&) ;
          const ::Ogre::Vector3& getVector() const ;

        private:

          ::Ogre::Vector3 m_value ;
        };

        /// A testing trait
        class QuaternionTrait : public Trait
        {
        public:

          void setValue(const ::Ogre::Quaternion&) ;
          const ::Ogre::Quaternion& getValue() const ;

        private:

          ::Ogre::Quaternion m_value ;
        };

        class Value
        {
        public:

          int m_value ;

          bool operator==(const Value& value) const
          {
            return m_value == value.m_value ;
          }
        };

        std::ostream& operator<<(std::ostream& out,const Value& value) ;

        /// A testing trait
        class ValueTrait : public Trait
        {
        public:

          void setValue(const Value&) ;
          const Value& getValue() const ;

        private:

          Value m_value ;
        };

        /// A testing trait
        class EnumTrait : public Trait
        {
        public:

          enum Type
          {
            _Value1,
            _Value2
          };

          void setValue(const Type&) ;
          const Type& getValue() const ;

        private:

          Type m_value ;
        };

        /// A testing trait
        class SetTrait : public Trait
        {
        public:

          void setValue(const std::set<int>&) ;
          const std::set<int>& getValue() const ;

        private:

          std::set<int> m_value ;
        };

        /// A testing trait
        class VectorTrait : public Trait
        {
        public:

          void setValue(const std::vector<int>&) ;
          const std::vector<int>& getValue() const ;

        private:

          std::vector<int> m_value ;
        };

        /// A testing trait
        class ListTrait : public Trait
        {
        public:

          void setValue(const std::list<int>&) ;
          const std::list<int>& getValue() const ;

        private:

          std::list<int> m_value ;
        };

        /// A testing trait
        class MapTrait : public Trait
        {
        public:

          void setValue(const std::map<int,float>&) ;
          const std::map<int,float>& getValue() const ;

        private:

          std::map<int,float> m_value ;
        };

      }
    }
  }
}
