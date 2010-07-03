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
#include <kernel/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    TypeIdentifier::StaticStorage* TypeIdentifier::StaticStorage::get()
    {
      static StaticStorage result ;
      return &result ;
    }

    TypeIdentifier::TypeIdentifier()
    : m_representation(&typeid(void))
    {}

    TypeIdentifier::TypeIdentifier(const std::type_info& i_name)
    : m_representation(&i_name)
    {}

    TypeIdentifier::TypeIdentifier(const TypeIdentifier& i_type_identifier)
    : m_representation(i_type_identifier.m_representation)
    {}

    TypeIdentifier::TypeIdentifier(
      const std::type_info& i_name,
      boost::function1<bool,Trait*> i_object_test)
    : m_representation(&i_name)
    {

      TypeIdentifier id(i_name) ;

      if (StaticStorage::get()->m_instance_tests.find(id) ==
          StaticStorage::get()->m_instance_tests.end())
      {
        StaticStorage::get()->m_instance_tests.insert(
            std::make_pair<TypeIdentifier,
                      boost::function1<bool,Trait*> >(id,i_object_test)) ;
      }
    }

    std::string TypeIdentifier::toString() const
    {
      std::map<const std::type_info*,std::string>::const_iterator finder =
          StaticStorage::get()->m_names.find(m_representation) ;

      if (finder != StaticStorage::get()->m_names.end())
        return finder->second ;

      return StaticStorage::get()->m_names[m_representation] = m_representation->name() ;
    }

    bool TypeIdentifier::operator <(const TypeIdentifier& i_type_identifier) const
    {
      return m_representation->before(*i_type_identifier.m_representation) ;
    }

    bool TypeIdentifier::isInstance(Trait* i_object) const
    {
      std::map<TypeIdentifier,boost::function1<bool,Trait*> >::iterator finder
        = StaticStorage::get()->m_instance_tests.find(*this) ;

      if (finder != StaticStorage::get()->m_instance_tests.end() &&
          ! finder->second.empty())
      {
        return finder->second(i_object) ;
      }
      else
      {
        return false ;
      }
    }

    bool TypeIdentifier::operator==(const TypeIdentifier& i_type_identifier) const
    {
      // idea taken from http://stackoverflow.com/questions/579887/how-expensive-is-rtti
      return m_representation == i_type_identifier.m_representation ||
             *m_representation == *i_type_identifier.m_representation ;
    }

    bool TypeIdentifier::operator!=(const TypeIdentifier& i_type_identifier) const
    {
      return *m_representation != *i_type_identifier.m_representation ;
    }

    std::pair<int,int> getNumber(const std::string& name, const std::string::size_type& position)
    {
      std::string result ;
      std::string::size_type current = position ;

      int number = 0 ;

      while(current < name.length() && name[current] >= '0' && name[current] <= '9')
      {
        result += name[current++] ;
        number++ ;
      }

      if (result != "")
      {
        return std::pair<int,int>(number,atoi(result.c_str())) ;
      }
      else
      {
        return std::pair<int,int>(1,1) ;
      }
    }

    std::string TypeIdentifier::className() const
    {
      std::map<const std::type_info*,std::string>::const_iterator finder =
          StaticStorage::get()->m_class_names.find(m_representation) ;

      if (finder != StaticStorage::get()->m_class_names.end())
        return finder->second ;

      return StaticStorage::get()->m_class_names[m_representation] = calculateClassName() ;
    }

    std::string TypeIdentifier::fullName() const
    {
      std::map<const std::type_info*,std::string>::const_iterator finder =
          StaticStorage::get()->m_full_names.find(m_representation) ;

      if (finder != StaticStorage::get()->m_full_names.end())
        return finder->second ;

      return StaticStorage::get()->m_full_names[m_representation] = calculateFullName() ;
    }

    /*!
      Of the form :

      (N{number}{NamespaceName})*{number}{ClassName}E
    */
    std::string TypeIdentifier::calculateClassName() const
    {
      std::string::size_type position = 0 ;
      std::string name(m_representation->name()) ;

      if (name[position] == 'N')
      {
        ++position ;
      }
      else
      {
        std::pair<int,int> temp(getNumber(name,position)) ;
        return name.substr(position+temp.first,temp.second) ;
      }

      while(position <= name.length())
      {
        /// a number and a class...
        std::pair<int,int> temp(getNumber(name,position)) ;
        if (name[position+temp.first+temp.second] == 'E')
        {
          return name.substr(position+temp.first,temp.second) ;
        }
        position = position+temp.first+temp.second ;
      }

      return "" ;
    }

    std::string TypeIdentifier::calculateFullName() const
    {
      std::string::size_type position = 0 ;
      std::string name(m_representation->name()) ;

      std::string result ;

      if (name[position] == 'N')
      {
        ++position ;
      }
      else
      {
        std::pair<int,int> temp(getNumber(name,position)) ;
        return name.substr(position+temp.first,temp.second) ;
      }
      bool first = true ;

      while(position <= name.length())
      {
        /// a number and a class...
        std::pair<int,int> temp(getNumber(name,position)) ;
        if (name[position+temp.first+temp.second] == 'E')
        {
          result = result + name.substr(position+temp.first,temp.second) ;
          break ;
        }
        if (first)
          first = false ;
        else
          result = result + name.substr(position+temp.first,temp.second) + "::" ;
        position = position+temp.first+temp.second ;
      }

      return result ;
    }

    TypeIdentifier& TypeIdentifier::operator=(const TypeIdentifier& type_identifier)
    {
      if (this != &type_identifier)
      {
        m_representation = type_identifier.m_representation ;
      }
      return *this ;
    }

    int TypeIdentifier::getIdentifier() const
    {
      return (int)m_representation ;
    }
  }
}
