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

    Relation::StaticStorage* Relation::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

    Relation::Relation(const TypeIdentifier& type,Object* object1,Object* object2)
    : m_object_from(object1),
      m_object_to(object2),
      m_type(type)
    {}

    Relation::Relation()
    : m_object_from(),
      m_object_to(),
      m_type(VoidTypeIdentifier)
    {}

    Relation::~Relation()
    {}

    Relation::Relation(const Relation& relation)
    : m_object_from(relation.m_object_from),
      m_object_to(relation.m_object_to),
      m_type(relation.m_type)
    {}

    bool Relation::operator ==(const Relation& relation) const
    {
      return m_object_from == relation.m_object_from && m_object_to == relation.m_object_to && m_type == relation.m_type ;
    }

    bool Relation::operator <(const Relation& relation) const
    {
      return m_type < relation.m_type ||
             (m_type == relation.m_type && m_object_from < relation.m_object_from) ||
             (m_type == relation.m_type && m_object_from == relation.m_object_from && m_object_to < relation.m_object_to) ;
    }

    const TypeIdentifier& Relation::getType() const
    {
      return m_type ;
    }

    Object* Relation::getObjectFrom() const
    {
      return m_object_from ;
    }

    Object* Relation::getObjectTo() const
    {
      return m_object_to ;
    }

    std::set<Object*> Relation::_getLinked(const TypeIdentifier& relation,Object* object)
    {
      return object->getModel()->getRelations(relation,object) ;
    }

    std::set<Object*> Relation::_getLinked(Object* object)
    {
      return object->getModel()->getRelations(object) ;
    }

    std::set<Object*> Relation::_getInversedLinked(Object* object)
    {
      return object->getModel()->getInverseRelations(object) ;
    }

    bool Relation::_areLinked(const TypeIdentifier& relation,Object* object1,Object* object2)
    {
      std::set<Object*> linked = object1->getModel()->getRelations(relation,object1) ;
      return linked.find(object2) != linked.end() ;
    }

    void Relation::createLink(const TypeIdentifier& type,Object* object1,Object* object2)
    {
      Relation relation(type,object1,object2) ;
      object1->getModel()->addRelation(relation) ;
      if (object1->getModel() != object2->getModel())
        object2->getModel()->addRelation(relation) ;
    }

    void Relation::destroyLink(const TypeIdentifier& type,Object* object1,Object* object2)
    {
      Relation relation(type,object1,object2) ;
      object1->getModel()->removeRelation(relation) ;
      if (object1->getModel() != object2->getModel())
        object2->getModel()->removeRelation(relation) ;

    }

  }
}
