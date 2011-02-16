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

namespace ProjetUnivers
{
  namespace Kernel
  {

    class Trait ;

    /// Used to reference a trait.
    /*!
      Help catching null pointer.
    */
    template <class T>
    class TraitReference
    {
    public:

      /// Constructor.
      TraitReference(T*) ;

      /// Constructor.
      TraitReference() ;

      /// Destructor.
      ~TraitReference() ;

      /// Copy constructor.
      TraitReference(const TraitReference<T>&) ;

      /// Assignment.
      TraitReference<T>& operator=(const TraitReference<T>&) ;

      /// Assignment.
      TraitReference<T>& operator=(T*) ;

      /// Access to object.
      /*!
      Throws exception if NULL. That's the purpose of this class.
      */
      T* operator->() const ;

      /// Comparison
      bool operator==(const TraitReference<T>&) const ;

      /// Comparison
      bool operator<(const TraitReference<T>&) const ;

      /// Conversion back to trait.
      operator T*() const ;

      /// Is NULL.
      bool operator!() const ;

      /// Is not NULL.
      operator bool() const ;

    private:

      T* m_trait ;
    };

  }
}

#include <kernel/implementation/trait_reference.cxx>

