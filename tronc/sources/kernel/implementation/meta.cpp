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

    TypeIdentifier::TypeIdentifier(const std::string& full_name)
    : m_representation(&Reflex::Type::ByName(full_name).TypeInfo())
    {}

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

    bool TypeIdentifier::inherits(const TypeIdentifier& type_identifier) const
    {
      if (!StaticStorage::get()->m_has_inheritance)
        StaticStorage::get()->calculateInheritance() ;

      if (StaticStorage::get()->m_inheritance.find(std::make_pair(*this,type_identifier))
          != StaticStorage::get()->m_inheritance.end())
        return true ;

      return false ;
    }

    const std::set<TypeIdentifier>& TypeIdentifier::subTypes() const
    {
      if (!StaticStorage::get()->m_has_inheritance)
        StaticStorage::get()->calculateInheritance() ;

      std::set<TypeIdentifier>& result = StaticStorage::get()->m_sub_types[*this] ;
      if (result.empty())
        result.insert(*this) ;
      return result ;
    }

    const std::set<TypeIdentifier>& TypeIdentifier::superTypes() const
    {
      if (!StaticStorage::get()->m_has_inheritance)
        StaticStorage::get()->calculateInheritance() ;

      std::set<TypeIdentifier>& result = StaticStorage::get()->m_super_types[*this] ;
      if (result.empty())
        result.insert(*this) ;
      return result ;
    }

    void TypeIdentifier::StaticStorage::calculateInheritance()
    {
      // we do not need to recalculate
      m_has_inheritance = true ;

      for(Reflex::Type_Iterator type = Reflex::Type::Type_Begin() ;
          type != Reflex::Type::Type_End() ;
          ++type)
      {
        TypeIdentifier current ;
        current.m_representation = &type->TypeInfo() ;

        for(Reflex::Base_Iterator base = type->Base_Begin() ;
            base != type->Base_End() ;
            ++base)
        {
          TypeIdentifier inherited ;
          inherited.m_representation = &base->ToType().TypeInfo() ;

          addInheritance(current,inherited) ;
        }
      }
      for(Reflex::Type_Iterator type = Reflex::Type::Type_Begin() ;
          type != Reflex::Type::Type_End() ;
          ++type)
      {
        TypeIdentifier current ;
        current.m_representation = &type->TypeInfo() ;
        // a type inherits from itself
        m_sub_types[current].insert(current) ;
        m_super_types[current].insert(current) ;
      }

    }

    void TypeIdentifier::StaticStorage::addInheritance(const TypeIdentifier& inheriting,const TypeIdentifier& inherited)
    {
      if (inheriting == TypeIdentifier() || inherited == TypeIdentifier())
        return ;

      // recurse for transitivity of inheritance
      for(std::set<TypeIdentifier>::iterator type = m_sub_types[inheriting].begin() ;
          type != m_sub_types[inheriting].end() ; ++type)
      {
        addInheritance(*type,inherited) ;
      }
      for(std::set<TypeIdentifier>::iterator type = m_super_types[inherited].begin() ;
          type != m_super_types[inherited].end() ; ++type)
      {
        addInheritance(inheriting,*type) ;
      }

      m_inheritance.insert(std::make_pair(inheriting,inherited)) ;
      m_sub_types[inherited].insert(inheriting) ;
      m_super_types[inheriting].insert(inherited) ;
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
