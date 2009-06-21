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
#ifndef PU_KERNEL_TRAIT_REFERENCE_H_
#define PU_KERNEL_TRAIT_REFERENCE_H_

#include <kernel/object_reference.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    class Model ;
    
    /// Used to reference an object's trait.
    /*!
      Use this instead of pointer to trait, for it checks for object and trait 
      existence.
      
      @todo add a test that demonstrates that.
      
      @see ObjectReference
    */
    template <class Trait> class TraitReference
    {
    public:

      /// Constructor.      
      TraitReference() ;
      
      /// Constructor.      
      TraitReference(Object* object) ;
      
      /// Copy constructor.      
      TraitReference(const TraitReference<Trait>&) ;
      
      /// Assignment.
      TraitReference<Trait>& operator=(Object*) ;

      /// Assignment.
      TraitReference<Trait>& operator=(const TraitReference<Trait>&) ;
            
      /// Conversion back to trait.
      operator Trait*() const ;

      /// Access to object.
      Trait* operator->() ;

      /// Access to object.
      const Trait* operator->() const ;
      
      /// Comparison
      bool operator==(const TraitReference<Trait>&) const ;
      
      /// Is NULL.
      bool operator!() const ;
      
      /// Is not NULL.
      operator bool() const ;
    
    private:
      
      ObjectReference m_object ;      
    };

  }
}

#include <kernel/implementation/trait_reference.cxx>

#endif /*PU_KERNEL_TRAIT_REFERENCE_H_*/
