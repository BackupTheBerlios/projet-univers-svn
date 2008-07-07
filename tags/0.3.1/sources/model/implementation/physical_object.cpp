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
#include <kernel/deduced_trait.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/positionned.h>
#include <model/whole.h>

#include <model/physical_world.h>

#include <model/physical_object.h>

namespace ProjetUnivers {
  namespace Model {

    DeclareDeducedTrait(PhysicalObject,
                        And(HasTrait(Mobile),
                            HasTrait(Positionned),
                            HasTrait(Massive),
                            HasTrait(Whole))) ;

    Kernel::Object* PhysicalObject::getPhysicalWorld() const
    {
      Kernel::Object* parent = getObject()->getParent() ;
      if (parent)
      {
        Model::PhysicalWorld* 
            world = parent->getParent<Model::PhysicalWorld>() ;
        
        return world->getObject() ;
      }
      
      return NULL ;
    }

  }
}
