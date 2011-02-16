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
#include <kernel/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    template <class T>
    TraitReference<T>::TraitReference(T* trait)
    : m_trait(trait)
    {}

    template <class T>
    TraitReference<T>::TraitReference()
    : m_trait(NULL)
    {}

    template <class T>
    TraitReference<T>::~TraitReference()
    {}

    template <class T>
    TraitReference<T>::TraitReference(const TraitReference<T>& reference)
    : m_trait(reference.m_trait)
    {}

    template <class T>
    TraitReference<T>& TraitReference<T>::operator=(const TraitReference<T>& reference)
    {
      m_trait = reference.m_trait ;
    }

    template <class T>
    TraitReference<T>& TraitReference<T>::operator=(T* trait)
    {
      m_trait = trait ;
    }

    template <class T>
    T* TraitReference<T>::operator->() const
    {
      if (!m_trait)
      {
        std::string message ;
        message += "TraitReference<" ;
        message += getClassTypeIdentifier(T).fullName() ;
        message += ">::operator->()" ;
        throw Kernel::ExceptionKernel(message) ;
      }
      return m_trait ;
    }

    template <class T>
    bool TraitReference<T>::operator==(const TraitReference<T>& reference) const
    {
      return m_trait == reference.m_trait ;
    }

    template <class T>
    bool TraitReference<T>::operator<(const TraitReference<T>& reference) const
    {
      return m_trait < reference.m_trait ;
    }

    template <class T>
    TraitReference<T>::operator T*() const
    {
      return m_trait ;
    }

    template <class T>
    bool TraitReference<T>::operator!() const
    {
      return !m_trait ;
    }

    template <class T>
    TraitReference<T>::operator bool() const
    {
      return m_trait ;
    }
  }
}
