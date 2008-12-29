/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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

namespace ProjetUnivers {
  namespace Kernel {

    TypeIdentifier::StaticStorage* TypeIdentifier::StaticStorage::get()
    {
      static StaticStorage result ;
      return &result ;
    }
    
    TypeIdentifier::TypeIdentifier()
    : m_type(&typeid(void))
    {}

    TypeIdentifier::TypeIdentifier(const std::type_info& i_name)
    : m_type(&i_name)
    {}

    TypeIdentifier::TypeIdentifier(const TypeIdentifier& i_type_identifier)
    : m_type(i_type_identifier.m_type)
    {}

    TypeIdentifier::TypeIdentifier(
      const std::type_info& i_name,
      boost::function1<bool,Trait*> i_object_test)
    : m_type(&i_name)
    {
      StaticStorage::get()->m_instance_tests.insert(
          std::pair<TypeIdentifier,
                    boost::function1<bool,Trait*> >(*this,
                                                    i_object_test)) ;
    }
    
    std::string TypeIdentifier::toString() const
    {
      return m_type->name() ;
    }
    
    bool TypeIdentifier::operator <(const TypeIdentifier& i_type_identifier) const
    {
      return m_type < (i_type_identifier.m_type) ;
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
      return m_type == i_type_identifier.m_type ;
    }

    bool TypeIdentifier::operator!=(const TypeIdentifier& i_type_identifier) const
    {
      return m_type != i_type_identifier.m_type ;
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

    /*!
      Of the form : 
      
      (N{number}{NamespaceName})*{number}{ClassName}E
    */
    std::string TypeIdentifier::className() const
    {
      std::string::size_type position = 0 ;
      std::string name(m_type->name()) ;
    
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

    TypeIdentifier& TypeIdentifier::operator=(const TypeIdentifier& type_identifier)
    {
      if (this != &type_identifier)
      {
        m_type = type_identifier.m_type ;
      }
      return *this ;
    }
  }
}
