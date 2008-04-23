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
#ifndef PU_MODEL_PHYSICAL_OBJECT_H_
#define PU_MODEL_PHYSICAL_OBJECT_H_

#include <kernel/object.h>
#include <kernel/deduced_trait.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that are physical.
    /*!
      @todo
        here we have quite a bug : take an object that is Positionned and Mobile 
        it will not be moved, and will be considered as a PhysicalWorld
        --> Massive whould be removed from PhysicalObject conditions
        Forces and torque would only be applied on PhysicalObject that are also 
        Massives. 
        
    */
    class PhysicalObject : public Kernel::DeducedTrait
    {
    public:
      
      /// Access to the physical world of the object.
      Kernel::Object* getPhysicalWorld() const ;
      
    };
  }
}

#endif /*PU_MODEL_PHYSICAL_OBJECT_H_*/
