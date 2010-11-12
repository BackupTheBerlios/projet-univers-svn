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

#include <string>
#include <kernel/trait.h>
#include <kernel/relation.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Object ;
    class Model ;

    /// Maps tobjects to serialisation identifiers
    /*!
    Deserialisation means that we need to have 'temporary' identifiers that will
    be resolved to objects later.
    Serialisation may also need to have to use another set of identifiers,
    for example during network transmition.
    */
    class ObjectMapper
    {
    public:

      /// Map from objects to identifiers.
      virtual int getIdentifier(Object*) = 0 ;

      /// Map from identifiers to objects.
      virtual ObjectReference getObject(Model*,const int&) = 0 ;

      virtual ~ObjectMapper() ;
    };

    /// Serialise framework data
    class Serialiser
    {
    public:

      /// Serialize a trait
      virtual std::string serialiseTrait(const Trait&) = 0 ;

      /// Deserialize a trait
      virtual Trait* deserialiseTrait(const std::string&) = 0 ;

      /// Deserialize a trait given an existing one
      virtual void deserialiseTrait(const std::string&,Trait*) = 0 ;

      /// Serialize a relation
      virtual std::string serialiseRelation(const Relation&) = 0 ;

      /// Deserialize a relation
      virtual void deserialiseRelation(const std::string&,Model*) = 0 ;

      virtual ~Serialiser() ;

    protected:

      Serialiser(ObjectMapper*) ;

      ObjectMapper* m_mapper ;
    };
  }
}
