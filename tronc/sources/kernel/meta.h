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
#include <typeinfo>
#include <map>
#include <set>

#include <boost/function.hpp>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Trait ;

    /// Something that identify a type.
    /*!
    Replace std::type_info because can be used inside maps.

    Some types are reflexive through reflex library included in that module.
    Reflexive types are needed for some features like :
    - inherits()
    - subTypes()
    */
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


      /// Constructor from a full name
      /*!
      Only work for traits with reflex reflection.
      */
      TypeIdentifier(const std::string& full_name) ;

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

      /// True iff @c this inherits from @c type_identifier.
      /*!
      Need reflex reflection.
      */
      bool inherits(const TypeIdentifier& type_identifier) const ;

      /// Return the sub types for @c this
      /*!
      Need reflex reflection.
      */
      const std::set<TypeIdentifier>& subTypes() const ;

      /// Return the super types for @c this
      /*!
      Need reflex reflection.
      */
      const std::set<TypeIdentifier>& superTypes() const ;

      /// Class name, i.e., if the fullname of the class is A::B::C returns C
      std::string className() const ;

      /// Full class name without the first namespace
      /*!
        If fullname of the class is ProjetUnivers::A::B returns A::B.
      */
      std::string fullName() const ;

      /// Assignment.
      TypeIdentifier& operator=(const TypeIdentifier& type_identifier) ;

      /// Get a unique identifier for that type.
      int getIdentifier() const ;

    private:

      /// gcc typeid name to class name
      std::string calculateClassName() const ;
      std::string calculateFullName() const ;

      /// On usage static storage.
      class StaticStorage
      {
      public:

        /// Singleton
        static StaticStorage* get() ;

        /// Probably deprecated?
        std::map<TypeIdentifier,boost::function1<bool,Trait*> > m_instance_tests ;

        /// Caching for type names
        std::map<const std::type_info*,std::string> m_names ;
        std::map<const std::type_info*,std::string> m_class_names ;
        std::map<const std::type_info*,std::string> m_full_names ;

        /// Calculate inheritance graph from Reflex information
        void calculateInheritance() ;

        /// Tells that @c t1 inherits from @c t2.
        void addInheritance(const TypeIdentifier& t1,const TypeIdentifier& t2) ;

        /// Record inheritance graph (recursive)
        std::set<std::pair<TypeIdentifier,TypeIdentifier> > m_inheritance ;

        /// Record sub types (recursive)
        std::map<TypeIdentifier,std::set<TypeIdentifier> > m_sub_types ;

        /// Record super types (recursive)
        std::map<TypeIdentifier,std::set<TypeIdentifier> > m_super_types ;

        /// True when the inheritance graph has been calculated
        bool m_has_inheritance ;

      private:

        StaticStorage()
        : m_has_inheritance(false)
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


    class TypeIdentifierPair
    {
    public:


    };

  }
}
