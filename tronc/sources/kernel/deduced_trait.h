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
#ifndef PU_KERNEL_DEDUCED_TRAIT_H_
#define PU_KERNEL_DEDUCED_TRAIT_H_

#include <vector>
#include <string>
#include <set>
#include <map>

#include <kernel/helper_macros.h>
#include <kernel/meta.h>

#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Kernel {
    
    /// Declare @c trait as a deduced trait defined by @c formula 
    /*!
      @param trait the trait class being defined
      @param formula any combination of And, Or, Not HasTrait
             see below.
    */
    #define DeclareDeducedTrait(trait,formula)  \
      namespace PU_MAKE_UNIQUE_NAME(local)      \
      {                                         \
        Kernel::DeducedTrait* builder()         \
        {                                       \
          return new trait() ;                  \
        }                                       \
                                                \
        Kernel::DeducedTraitDeclaration temp(   \
          formula::build(),                     \
          &builder,                             \
          getClassTypeIdentifier(trait)) ;      \
      }

    /// Conjunction of formulaes    
    #define And(...) Kernel::TemplateAnd< __VA_ARGS__ >

    /// Disjunction of formulaes    
    #define Or(...) Kernel::TemplateOr< __VA_ARGS__ >
    
    /// Negation of formula.
    #define Not(f) Kernel::TemplateNot<f>
    
    /// Elementary formula true iff object has trait @c t
    #define HasTrait(t) Kernel::TemplateHasTrait<t>


  }
}
#include <kernel/implementation/deduced_trait.cxx>

#endif /*PU_KERNEL_DEDUCED_TRAIT_H_*/
