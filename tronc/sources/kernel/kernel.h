/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef PU_KERNEL_KERNEL_H_
#define PU_KERNEL_KERNEL_H_

namespace ProjetUnivers {
  
  /// Technical framework
  /*!
    This module contains the technical implementation for Model/View/control 
    used throughout the project. 
    
  @par The model part

    It defines Kernel::Model that represent a set of Kernel::Object organised 
    in a hierarchical manner. Each Kernel::Object has Kernel::Trait that 
    contains the various semantic informations. 
    
    The system has some deduction capabilmities some Kernel::Trait may be 
    deduced from other, and their adding removal is completelly automatic.
    
    For now (0.2.2) only logic formulas (And, Or, Not) over the traits of the same 
    object are allowed. 
    
    Examples :
    - <code>DeclareDeducedTrait(Whole,Not(HasTrait(Component))) ;</code>
      It states that every object that does not have the Component trait 
      have the whole trait. If one add the component trait on an object 
      the Whole trait is removed
    - <code>DeclareDeducedTrait(PhysicalObject,
                                And(HasTrait(Mobile),
                                    HasTrait(Positionned),
                                    HasTrait(Massive),
                                    HasTrait(Whole))) ;</code>
      PhysicalObject are exactly those objects that are both Mobile, 
      Positionned, Massive and Whole.
      
    
    Formulaes cannot be recursive (i.e. one cannot define a trait from itself).
    
  @par The view part
    
    A Kernel::ViewPoint represents a set of coherent Kernel::TraiView on a 
    Kernel::Model. 
        
    Kernel::TraiView are automatically attached to Kernel::Trait by using  
    DeclareView declaration :
    
    Declaration : <code>RegisterView(ViewClass,TraitClass,ViewPointClass) ;
    </code> will generate the following behaviour :
    - for each initialised object of class @c ViewPointClass a new instance of  
      @c ViewClass will be attached on every instance of @c TraitClass
    - these instances will be notified of @c TraitClass object changes, 
      removal, ... 
    
  @par The Controler part
    
    Same as view part except :
    - Kernel::ControlerSet may be bottom-up or top-down browse to call 
      operations on the Kernel::Controler
    
  */ 
  namespace Kernel {
  }
}

#endif
