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
#pragma once

#include <string>
#include <typeinfo>
#include <map>

#include <boost/function.hpp>

namespace ProjetUnivers
{
  namespace Kernel
  {

    class Trait ;

    /// Something that identify a type.
    class TypeIdentifier
    {
    public:

      /// Default constructor.
      TypeIdentifier() ;

      /// Constructor.
      TypeIdentifier(const std::type_info& name) ;

      /// Copy constructor.
      TypeIdentifier(const TypeIdentifier& type_identifier) ;

      /// Constructor.
      TypeIdentifier(const std::type_info& name,
                     boost::function1<bool,Trait*> object_test) ;

      /// Return a string that represents the type identifier.
      std::string toString() const ;

      /// Comparison.
      bool operator ==(const TypeIdentifier& type_identifier) const ;

      /// Comparison.
      bool operator !=(const TypeIdentifier& type_identifier) const ;

      /// For std::map.
      bool operator <(const TypeIdentifier& type_identifier) const ;

      /// Returns true iff object is instance of that type.
      /*!
        Only work for TypeIdentifiers obtained from getClassTypeIdentifier.
      */
      bool isInstance(Trait* object) const ;

      /// gcc typeid name to class name
      std::string className() const ;
      std::string fullName() const ;

      /// Assignment.
      TypeIdentifier& operator=(const TypeIdentifier& type_identifier) ;

      /// Get a unique identifier for that type.
      int getIdentifier() const ;

    private:

      /// gcc typeid name to class name
      std::string calculateClassName() const ;
      std::string calculateFullName() const ;

      /// For isInstance implementation.
      class StaticStorage
      {
      public:

        std::map<TypeIdentifier,boost::function1<bool,Trait*> > m_instance_tests ;

        std::map<const std::type_info*,std::string> m_names ;
        std::map<const std::type_info*,std::string> m_class_names ;
        std::map<const std::type_info*,std::string> m_full_names ;

        static StaticStorage* get() ;

      private:

        StaticStorage()
        {}

      };

      /// Internal representation.
      const std::type_info* m_representation ;

    };

    /// Element that represent no type.
    const TypeIdentifier VoidTypeIdentifier = TypeIdentifier() ;

    /// Returns true iff @c object is instance of @c T.
    template <class T> bool isInstance(Trait* object)
    {

      if (dynamic_cast<T*>(object) != NULL)
      {
        return true ;
      }
      else
      {
        return false ;
      }
    }

    /// Get the type identifier for @c object
    #define getObjectTypeIdentifier(object) \
      ProjetUnivers::Kernel::TypeIdentifier(typeid(*object))

    /// Get the type identifier for @c class
    #define getClassTypeIdentifier(i_class) \
      ProjetUnivers::Kernel::TypeIdentifier(typeid(i_class),&ProjetUnivers::Kernel::isInstance<i_class>)
  }
}
