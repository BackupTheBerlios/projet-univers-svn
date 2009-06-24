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
#include <kernel/relation.h>
namespace ProjetUnivers
{
  namespace Kernel
  {
    Relation::Relation(const TypeIdentifier& type,Object* object1,Object* object2)
    : m_object1(object1),
      m_object2(object2),
      m_type(type)
    {}

    Relation::~Relation()
    {}

    Relation::Relation(const Relation& relation)
    : m_object1(relation.m_object1),
      m_object2(relation.m_object2),
      m_type(relation.m_type)
    {}

    bool Relation::operator ==(const Relation& relation) const
    {
      return m_object1 == relation.m_object1 && m_object2 == relation.m_object2 && m_type == relation.m_type ;
    }

    bool Relation::operator <(const Relation& relation) const
    {
      return m_type < relation.m_type ||
             (m_type == relation.m_type && m_object1 < relation.m_object1) ||
             (m_type == relation.m_type && m_object1 == relation.m_object1 && m_object2 < relation.m_object2) ;
    }

    const TypeIdentifier& Relation::getType() const
    {
      return m_type ;
    }

    Object* Relation::getObject1() const
    {
      return m_object1 ;
    }

    Object* Relation::getObject2() const
    {
      return m_object2 ;
    }

    std::set<Object*> Relation::_getLinked(const TypeIdentifier& relation,Object* object)
    {
      return object->getModel()->getRelations(relation,object) ;
    }


  }
}
