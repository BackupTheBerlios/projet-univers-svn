/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

#include <kernel/model.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Object ;

    namespace Implementation
    {

      /// A element on which we perform deduction
      class DeductionElement
      {
      public:

        /// Convert from an object.
        DeductionElement(Object* object) ;

        /// Convert from a relation.
        DeductionElement(const ObjectPair& pair) ;

        /// Copy constructor.
        DeductionElement(const DeductionElement& element) ;

        /// True iff it is an object.
        bool isObject() const ;

        /// The object in case it is one.
        Object* getObject() const ;

        /// The source object in case it is a relation.
        Object* getObjectFrom() const ;

        /// The destination object in case it is a reation.
        Object* getObjectTo() const ;

      private:

        Object* m_object ;
        ObjectPair m_pair ;
      };
    }
  }
}
