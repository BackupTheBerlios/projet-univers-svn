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

#include <kernel/object_reference.h>
#include <kernel/trait.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Observer ;
    class RelationObserver ;

    namespace Implementation
    {
      /// Operation that modifies a model.
      class Operation
      {
      public:
      /*!
        @name Callbacks on view/controlers
      */
      // @{

        static Operation init(Observer*) ;
        static Operation close(Observer*) ;
        static Operation update(Observer*) ;
        static Operation changeParent(Observer*,Object*) ;
        static Operation init(RelationObserver*) ;
        static Operation close(RelationObserver*) ;
        static Operation update(RelationObserver*) ;

      // @}

        Operation(const Operation&) ;

        /// Really execute the operation
        void execute() const ;

        std::string toString() const ;

      private:

        Operation() ;

        enum Type
        {
          Init,
          Close,
          Update,
          ChangeParent,
          InitRelation,
          CloseRelation,
          UpdateRelation,
          None
        };

        Type      m_type ;
        Object*   m_object ;
        Observer* m_observer ;
        Object*   m_old_parent ;
        RelationObserver* m_relation_observer ;

        std::string m_debug_display ;
      };
    }
  }
}
