/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <kernel/object.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Kernel {

    template <class Trait>
    TraitReference<Trait>::TraitReference()
    : m_object()
    {}

    template <class Trait>
    TraitReference<Trait>::TraitReference(Object* object)
    : m_object(object)
    {}
    
    template <class Trait>
    TraitReference<Trait>::TraitReference(const TraitReference<Trait>& reference)
    : m_object(reference.m_object)
    {}
      
    template <class Trait>
    TraitReference<Trait>::operator Trait*() const
    {
      Object* object = m_object ;
      if (object)
      {
        return object->getTrait<Trait>() ;
      }
      return NULL ;
    }

    template <class Trait>
    TraitReference<Trait>& TraitReference<Trait>::operator=(Object* object)
    {
      m_object = object ;
      return *this ;
    }

    template <class Trait>
    TraitReference<Trait>& 
    TraitReference<Trait>::operator=(const TraitReference<Trait>& reference)
    {
      if (this != &reference)
      {
        m_object = reference.m_object ;
      }
      
      return *this ;
    }

    template <class Trait>
    Trait* TraitReference<Trait>::operator->()
    {
      return (Trait*)*this ;
    }

    template <class Trait>
    const Trait* TraitReference<Trait>::operator->() const 
    {
      return (Trait*)*this ;
    }
    
    template <class Trait>
    bool 
    TraitReference<Trait>::operator==(const TraitReference<Trait>& reference) const
    {
      return m_object == reference.m_object ;
    }
    
    template <class Trait>
    bool TraitReference<Trait>::operator!() const
    {
      Object* object = m_object ;
      if (object)
      {
        return object->getTrait<Trait>() == NULL ;
      }
      
      return true ;
    }
    
    template <class Trait>
    TraitReference<Trait>::operator bool() const
    {
      Object* object = m_object ;
      if (object)
      {
        return object->getTrait<Trait>() != NULL ;
      }
      
      return false ;
    }
    
  }
}

