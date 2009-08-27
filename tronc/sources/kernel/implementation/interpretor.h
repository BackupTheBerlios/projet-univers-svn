/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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

#include <list>
#include <set>
#include <kernel/relation.h>
#include <kernel/implementation/operation.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Trait ;
    namespace Implementation
    {
      /// Model command interpretor.
      /*!
        Memorize init/close/update on observer to play them afterwards.
      */
      class Interpretor
      {
      public:
      /*!
        @name Modification functions
      */
      // @{

        /// All observers callbacks performed during a transaction are delayed.
        void startTransaction() ;

        /// Add an operation to be performed locally
        void addOperation(const Implementation::Operation&) ;

        /// Put the trait in a pool of trait to destroy.
        void recordTraitToDestroy(Trait*) ;

        /// Undo the trait destroying.
        void removeTraitToDestroy(Object*,const TypeIdentifier&) ;

        /// True iff the trait is to be destroyed.
        bool isToBeDestroyed(Trait*) const ;

        /// Really executes the callbacks
        void endTransaction() ;

      // @}

        virtual ~Interpretor() ;

        /// Prints the operations remaining in @c module.
        std::string toString(const char* module) const ;

      protected:

        Interpretor() ;

        /// Put the relation in a pool of relation to destroy.
        void recordRelationToDestroy(const Relation&) ;

        /// True if the relation is marked to be destroyed
        bool isToDestroy(const Relation&) const ;

        /// Reverse of recordRelationToDestroy
        void unRecordRelationToDestroy(const Relation&) ;

        /// Add an object to be destroyed.
        void addObjectToDestroy(Object*) ;

        /// Destroy the traits.
        void destroyTraits() ;

        /// Destroy the objects.
        void destroyObjects() ;

        /// Destroy the objects.
        void destroyRelations() ;

        /// true during destruction.
        bool m_destroying ;

      private:

        int m_number_of_openned_transaction ;

        /// True when we are finishing the oppened transactions
        bool m_is_finishing ;
        std::list<Implementation::Operation> m_operations ;
        std::set<Trait*> m_traits_to_destroy ;
        /// Objects to be destroyed.
        std::list<ObjectReference> m_objects_to_destroy ;
        bool m_destroying_traits ;
        std::set<Relation> m_relation_to_destroy ;

        std::list<Implementation::Operation> m_performed_operations ;
      };
    }
  }
}
