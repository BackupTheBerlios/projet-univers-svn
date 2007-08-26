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

    std::map<TypeIdentifier,boost::function1<bool,Trait*> > 
      TypeIdentifier::m_instance_tests ;

    TypeIdentifier::TypeIdentifier()
    : m_representation(typeid(void))
    {}

    TypeIdentifier::TypeIdentifier(const std::type_info& i_name)
    : m_representation(i_name)
    {}

    TypeIdentifier::TypeIdentifier(const TypeIdentifier& i_type_identifier)
    : m_representation(i_type_identifier.m_representation)
    {}

    TypeIdentifier::TypeIdentifier(
      const std::type_info& i_name,
      boost::function1<bool,Trait*> i_object_test)
    : m_representation(i_name)
    {
      m_instance_tests.insert(std::pair<TypeIdentifier,boost::function1<bool,Trait*> >(TypeIdentifier(i_name),i_object_test)) ;
    }
    
    std::string TypeIdentifier::toString() const
    {
      return m_representation.name() ;
    }
    
    bool TypeIdentifier::operator <(const TypeIdentifier& i_type_identifier) const
    {
      return m_representation.before(i_type_identifier.m_representation) ;
    }

    bool TypeIdentifier::isInstance(Trait* i_object) const 
    {
      std::map<TypeIdentifier,boost::function1<bool,Trait*> >::iterator finder 
      = m_instance_tests.find(*this) ;
      
      if (finder != m_instance_tests.end() && ! finder->second.empty())
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
      return m_representation == i_type_identifier.m_representation ;
    }

    bool TypeIdentifier::operator!=(const TypeIdentifier& i_type_identifier) const
    {
      return m_representation != i_type_identifier.m_representation ;
    }

  }
}
