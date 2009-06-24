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
#pragma once

#include <set>
#include <kernel/object_reference.h>
#include <kernel/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Object ;
    template <class Relation> class Link ;
    template <class Relation> class UnLink ;

    /// A relation 'type' between objects.
    /*!
      The relation is destroyed when one of object is.

      Create a sub-class of Relation to define a new relation type.
      Use Link<RelationType>(object1,object2) ; to link two objects
      Use UnLink<RelationType>(object1,object2) ; to un-link two objects
    */
    class Relation
    {
    public:

      /// Returns the linked objects of @c object through @c _Relation.
      template <class _Relation>
      static std::set<Object*> getLinked(Object* object) ;

      /// Returns the linked objects of @c object through @c relation.
      static std::set<Object*> _getLinked(const TypeIdentifier& relation,Object* object) ;

      /// Acess to relation type.
      const TypeIdentifier& getType() const ;

      Object* getObject1() const ;
      Object* getObject2() const ;

      Relation(const Relation&) ;
      virtual ~Relation() ;
      bool operator ==(const Relation&) const ;
      bool operator <(const Relation&) const ;

    protected:

      Relation() ;

      Relation(const TypeIdentifier&,Object*,Object*) ;

      ObjectReference m_object1 ;
      ObjectReference m_object2 ;
      TypeIdentifier  m_type ;

      template <class Relation> friend class Link ;
      template <class Relation> friend class UnLink ;

    };

    /// The act of linking two objects
    template <class Relation> class Link
    {
    public:

      /// Create a link between two objects.
      Link(Object*,Object*) ;
    };

    /// The act of un-linking two objects
    template <class Relation> class UnLink
    {
    public:

      /// Create a link between two objects.
      UnLink(Object*,Object*) ;
    };

    /// Inverse relation of @c _Relation
    template <class _Relation> class Inverse : public Relation
    {};

  }
}

#include <kernel/implementation/relation.cxx>
