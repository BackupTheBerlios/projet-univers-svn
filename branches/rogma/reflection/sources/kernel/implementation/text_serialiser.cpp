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

namespace ProjetUnivers
{
  namespace Kernel
  {

    std::string valueToString(const Reflex::Object& value)
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
      return "" ;
    }

    void setValue(Reflex::Object object,const Reflex::Member& member,const std::string& value)
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

    Trait* TextSerialiser::deserialiseTrait(const std::string& text)
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

      // fill members
      std::string::size_type begin_member = position_of_parenthesis ;
      std::string::size_type end_member ;
      do
      {
        ++begin_member ;
        end_member = text.find('=',begin_member) ;
        if (end_member == std::string::npos)
          break ;

        std::string member_name = text.substr(begin_member,end_member-begin_member) ;

        Reflex::Member meta_member = type.MemberByName(member_name) ;

        if (!meta_member || !meta_member.IsDataMember())
        {
          std::cout << "cannot find member " << member_name << std::endl ;
          return NULL ;
        }

        std::string::size_type end_member_value = text.find_first_of(",)",end_member) ;
        std::string member_value = text.substr(end_member+1,end_member_value-end_member-1) ;

        // deserialise value
        setValue(instance,meta_member,member_value) ;

        begin_member = text.find(',',begin_member) ;

      } while (begin_member != std::string::npos) ;

      return static_cast<Trait*>(instance.Address()) ;
    }
  }
}

