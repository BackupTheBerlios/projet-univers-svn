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

#include <Reflex/Type.h>
#include <Reflex/Object.h>
#include <kernel/serialiser.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {
      class TestTextSerialiser ;
    }

    /// Serialise an object
    class TextSerialiser : public Serialiser
    {
    public:

      TextSerialiser(ObjectMapper* mapper = NULL) ;

      /// Transform a trait to a string
      virtual std::string serialiseTrait(const Trait&) ;

      /// Transform a string to a trait
      virtual Trait* deserialiseTrait(const std::string&,Model* model) ;

      /// Deserialize a trait given an existing one
      virtual void deserialiseTrait(const std::string&,Trait*) ;

      /// Serialize a relation
      virtual std::string serialiseRelation(const Relation&) ;

      /// Deserialize a relation
      virtual void addRelation(const std::string&,Model*) ;

      /// Deserialize a relation
      virtual void removeRelation(const std::string&,Model*) ;

    private:

      std::string serialiseObject(const Reflex::Type&,Reflex::Object object) ;

      /// Fill a given trait with values.
      void fillTrait(const std::string&,Reflex::Object,const Reflex::Type&,Model* model) ;

      /// Convert generic value to string.
      std::string valueToString(const Reflex::Object& value) ;

      /// Affect a serialised value to an object.
      void setValue(Reflex::Object object,const std::string& value,Model* model) ;

      /// Parse key=value list.
      std::list<std::pair<std::string,std::string> > parseValues(const std::string&) const ;
      std::list<std::string> parseListValues(const std::string&) const ;
      std::map<std::string,std::string> parseMapValues(const std::string&) const ;

      friend class ::ProjetUnivers::Kernel::Test::TestTextSerialiser ;

    };
  }
}

