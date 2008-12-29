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
#ifndef PU_KERNEL_META_H_
#define PU_KERNEL_META_H_

#include <string>
#include <typeinfo>
#include <map>

#include <boost/function.hpp>

namespace ProjetUnivers {
  namespace Kernel {

    class Trait ;
    
    /// Something that identify a type.
    class TypeIdentifier
    {
    public:

      /// Default constructor.
      TypeIdentifier() ;

      /// Constructor.
      TypeIdentifier(const std::type_info& i_name) ;

      /// Copy constructor.
      TypeIdentifier(const TypeIdentifier& i_type_identifier) ;

      /// Constructor.
      TypeIdentifier(const std::type_info& i_name,
                     boost::function1<bool,Trait*> i_object_test) ;
      
      /// Return a string that represents the type identifier. 
      std::string toString() const ;

      /// Comparison.
      bool operator ==(const TypeIdentifier& i_type_identifier) const ;
      
      /// Comparison.
      bool operator !=(const TypeIdentifier& i_type_identifier) const ;

      /// For std::map.
      bool operator <(const TypeIdentifier& i_type_identifier) const ;
      
      /// Returns true iff i_object is instance of that type.
      /*!
        Only work for TypeIdentifiers obtained from getClassTypeIdentifier.
      */
      bool isInstance(Trait* i_object) const ;

      /// gcc typeid name to class name
      std::string className() const ; 

      /// Assignment.
      TypeIdentifier& operator=(const TypeIdentifier& i_type_identifier) ;

    private:
      
      /// For isInstance implementation.
      class StaticStorage
      {
      public:
        
        std::map<TypeIdentifier,boost::function1<bool,Trait*> > m_instance_tests ;
        
        static StaticStorage* get() ;
        
      private:
        
        StaticStorage()
        {}
        
      };

      /// Internal representation.
      const std::type_info* m_type ;
    };
    
    /// Element that represent no type.
    const TypeIdentifier VoidTypeIdentifier = TypeIdentifier() ;
    
    /// Returns true iff @c i_object is instance of @c T.
    template <class T> bool isInstance(Trait* i_object)
    {
      
      if (dynamic_cast<T*>(i_object) != NULL)
      {
        return true ;
      }
      else
      {
        return false ;
      }
    }
    
    /// Get the type identifier for @c i_object
    #define getObjectTypeIdentifier(i_object) \
      ProjetUnivers::Kernel::TypeIdentifier(typeid(*i_object))
    
    /// Get the type identifier for @c i_class
    #define getClassTypeIdentifier(i_class) \
      ProjetUnivers::Kernel::TypeIdentifier(typeid(i_class),&ProjetUnivers::Kernel::isInstance<i_class>)
  }
}

#endif /*PU_KERNEL_META_H_*/
