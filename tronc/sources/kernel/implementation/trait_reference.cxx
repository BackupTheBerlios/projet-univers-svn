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
    TraitReference<Trait>::TraitReference(Trait* trait)
    : m_trait(trait)
    {
      if (m_trait)
      {
        m_trait->_registerReference(this) ; 
      }
    }

    template <class Trait>
    TraitReference<Trait>::~TraitReference()
    {
      if (m_trait)
      {
        m_trait->_unregisterReference(this) ; 
      }
    }
        
    template <class Trait>
    TraitReference<Trait>::TraitReference(const TraitReference<Trait>& reference)
    : m_trait(reference.m_trait)
    {
      if (m_trait)
      {
        m_trait->_registerReference(this) ; 
      }
    }
      
    template <class Trait>
    TraitReference<Trait>::operator Trait*() const
    {
      return m_trait ;
    }

    template <class Trait>
    TraitReference<Trait>& 
    TraitReference<Trait>::operator=(const TraitReference<Trait>& reference)
    {
      if (&reference != this)
      {
        if (m_trait)
        {
          m_trait->_unregisterReference(this) ; 
        }
        m_trait = reference.m_trait ;
        if (m_trait)
        {
          m_trait->_registerReference(this) ; 
        }
      }
    }
    
    template <class Trait>
    TraitReference<Trait>& 
    TraitReference<Trait>::operator=(Trait* reference)
    {
      if (m_trait)
      {
        m_trait->_unregisterReference(this) ; 
      }
      m_trait = reference ;
      if (m_trait)
      {
        m_trait->_registerReference(this) ; 
      }
    }
    
    template <class Trait>
    Trait* TraitReference<Trait>::operator->()
    {
      return m_trait ;
    }

    template <class Trait>
    const Trait* TraitReference<Trait>::operator->() const 
    {
      return m_trait ;
    }
    
    template <class Trait>
    bool 
    TraitReference<Trait>::operator==(const TraitReference<Trait>& reference) const
    {
      return m_trait == reference.m_trait ;
    }
    
    template <class Trait>
    bool TraitReference<Trait>::operator!() const
    {
      return m_trait == NULL ; 
    }
    
    template <class Trait>
    TraitReference<Trait>::operator bool() const
    {
      return m_trait != NULL ; 
    }
    
    template <class Trait>
    void TraitReference<Trait>::_reset()
    {
      m_trait = NULL ;
    }
    
  }
}

