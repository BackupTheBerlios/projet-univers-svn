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
#include <Reflex/Reflex.h>
#include <kernel/text_serialiser.h>
#include <kernel/string.h>
#include <kernel/error.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    TextSerialiser::TextSerialiser(ObjectMapper* mapper)
    : Serialiser(mapper)
    {}

    std::string TextSerialiser::valueToString(const Reflex::Object& value)
    {
      Reflex::Type value_type = value.TypeOf() ;
      if (value_type == Reflex::Type::ByName("std::string"))
      {
        return Reflex::Object_Cast<std::string>(value) ;
      }
      else if (value_type == Reflex::Type::ByName("float"))
      {
        return toString(Reflex::Object_Cast<float>(value)) ;
      }
      else if (value_type == Reflex::Type::ByName("int"))
      {
        return toString(Reflex::Object_Cast<int>(value)) ;
      }
      else if (value_type == Reflex::Type::ByName("unsigned int"))
      {
        return toString(Reflex::Object_Cast<unsigned int>(value)) ;
      }
      else if (value_type == Reflex::Type::ByName("ProjetUnivers::Kernel::ObjectReference"))
      {
        return toString(Reflex::Object_Cast<ObjectReference>(value).m_object_identifier) ;
      }
      else if (value_type == Reflex::Type::ByName("bool"))
      {
        return toString(Reflex::Object_Cast<bool>(value)) ;
      }
      ErrorMessage("TextSerialiser Unsupported type " + value_type.Name(Reflex::SCOPED)) ;
      return "" ;
    }

    void TextSerialiser::setValue(Reflex::Object object,const Reflex::Member& member,const std::string& value,Model* model)
    {
      if (member.TypeOf() == Reflex::Type::ByName("std::string"))
      {
        Reflex::Object target_value(member.Get(object)) ;
        *(std::string*)target_value.Address() = value ;
      }
      else if (member.TypeOf() == Reflex::Type::ByName("float"))
      {
        static float real_value ;
        real_value = (float)atof(value.c_str()) ;
        member.Set(object,&real_value) ;
      }
      else if (member.TypeOf() == Reflex::Type::ByName("int"))
      {
        static int real_value ;
        real_value = (int)atoi(value.c_str()) ;
        member.Set(object,&real_value) ;
      }
      else if (member.TypeOf() == Reflex::Type::ByName("unsigned int"))
      {
        static unsigned int real_value ;
        real_value = (unsigned int)atoi(value.c_str()) ;
        member.Set(object,&real_value) ;
      }
      else if (member.TypeOf() == Reflex::Type::ByName("ProjetUnivers::Kernel::ObjectReference"))
      {
        Reflex::Object target_value(member.Get(object)) ;
        *(ObjectReference*)target_value.Address() = m_mapper->getMappedObject(model,atoi(value.c_str())) ;
      }
      else if (member.TypeOf() == Reflex::Type::ByName("bool"))
      {
        static bool real_value ;
        real_value = (bool)atoi(value.c_str()) ;
        member.Set(object,&real_value) ;
      }
      else
      {
        ErrorMessage("TextSerialiser Unsupported type " + member.TypeOf().Name(Reflex::SCOPED)) ;
        std::cerr << "TextSerialiser Unsupported type " << member.TypeOf().Name(Reflex::SCOPED) << std::endl ;
      }
    }

    std::string TextSerialiser::serialiseTrait(const Trait& trait)
    {
      Reflex::Type type(Reflex::Type::ByTypeInfo(typeid(trait))) ;

      Reflex::Object object(type,const_cast<Trait*>(&trait)) ;

      std::string result(type.Name(Reflex::SCOPED)) ;
      result += "(" ;

      bool has_member = false ;

      for(Reflex::Member_Iterator member = type.Member_Begin() ; member != type.Member_End() ; ++member)
      {
        if (member->IsDataMember())
        {
          if (has_member)
            result += "," ;
          else
            has_member = true ;
          result += member->Name() ;
          result += "=" ;
          result += valueToString(member->Get(object)) ;
        }
      }

      result += ")" ;
      return result ;
    }

    Trait* TextSerialiser::deserialiseTrait(const std::string& text,Model* model)
    {
      std::string trait_name ;
      std::string::size_type position_of_parenthesis = text.find('(') ;
      if (position_of_parenthesis == std::string::npos)
        return NULL ;

      trait_name = text.substr(0,position_of_parenthesis) ;
      Reflex::Type type(Reflex::Type::ByName(trait_name)) ;

      if (!type)
        return NULL ;

      // create the result
      Reflex::Object instance = type.Construct() ;

      fillTrait(text,instance,type,model) ;

      return static_cast<Trait*>(instance.Address()) ;
    }

    void TextSerialiser::deserialiseTrait(const std::string& text,Trait* trait)
    {
      std::string trait_name ;
      std::string::size_type position_of_parenthesis = text.find('(') ;
      if (position_of_parenthesis == std::string::npos)
        return ;

      trait_name = text.substr(0,position_of_parenthesis) ;
      Reflex::Type type(Reflex::Type::ByName(trait_name)) ;

      if (!type)
        return ;

      Reflex::Object instance(type,trait) ;
      fillTrait(text,instance,type,trait->getObject()->getModel()) ;

      trait->notify() ;
    }

    void TextSerialiser::fillTrait(const std::string& text,Reflex::Object instance,const Reflex::Type& type,Model* model)
    {
      std::string::size_type position_of_parenthesis = text.find('(') ;
      std::string::size_type begin_member = position_of_parenthesis ;
      std::string::size_type end_member ;
      // fill members
      do
      {
        ++begin_member ;
        end_member = text.find('=',begin_member) ;
        if (end_member == std::string::npos)
          break ;

        std::string member_name = text.substr(begin_member,end_member-begin_member) ;

        Reflex::Member meta_member = type.MemberByName(member_name) ;

        CHECK(meta_member && meta_member.IsDataMember(),"cannot find member") ;

        std::string::size_type end_member_value = text.find_first_of(",)",end_member) ;
        std::string member_value = text.substr(end_member+1,end_member_value-end_member-1) ;

        // deserialise value
        setValue(instance,meta_member,member_value,model) ;

        begin_member = text.find(',',begin_member) ;

      }
      while (begin_member != std::string::npos) ;
    }

    std::string TextSerialiser::serialiseRelation(const Relation& relation)
    {
      std::string result("ProjetUnivers::") ;
      const TypeIdentifier& type = relation.getType() ;
      result += type.fullName() ;
      result += "(" ;
      result += toString(m_mapper->getMappedIdentifier(relation.getObjectFrom())) ;
      result += "," ;
      result += toString(m_mapper->getMappedIdentifier(relation.getObjectTo())) ;
      result += ")" ;

      return result ;
    }

    void TextSerialiser::addRelation(const std::string& text,Model* model)
    {
      std::string relation_name ;
      std::string::size_type position_of_parenthesis = text.find('(') ;
      if (position_of_parenthesis == std::string::npos)
        return ;

      relation_name = text.substr(0,position_of_parenthesis) ;
      TypeIdentifier type(relation_name) ;

      std::string::size_type position_of_column = text.find(',',position_of_parenthesis) ;

      std::string identifier1 = text.substr(position_of_parenthesis+1,
                                            position_of_column-position_of_parenthesis-1) ;

      std::string identifier2 = text.substr(position_of_column+1,
                                            text.length()-position_of_column-2) ;


      Object* object1 = m_mapper->getMappedObject(model,atoi(identifier1.c_str())) ;
      Object* object2 = m_mapper->getMappedObject(model,atoi(identifier2.c_str())) ;

      Relation::createLink(TypeIdentifier(type),object1,object2) ;
    }

    void TextSerialiser::removeRelation(const std::string& text,Model* model)
    {
      std::string relation_name ;
      std::string::size_type position_of_parenthesis = text.find('(') ;
      if (position_of_parenthesis == std::string::npos)
        return ;

      relation_name = text.substr(0,position_of_parenthesis) ;
      TypeIdentifier type(relation_name) ;

      std::string::size_type position_of_column = text.find(',',position_of_parenthesis) ;

      std::string identifier1 = text.substr(position_of_parenthesis+1,
                                            position_of_column-position_of_parenthesis-1) ;

      std::string identifier2 = text.substr(position_of_column+1,
                                            text.length()-position_of_column-2) ;


      Object* object1 = m_mapper->getMappedObject(model,atoi(identifier1.c_str())) ;
      Object* object2 = m_mapper->getMappedObject(model,atoi(identifier2.c_str())) ;

      Relation::destroyLink(TypeIdentifier(type),object1,object2) ;
    }

  }
}

