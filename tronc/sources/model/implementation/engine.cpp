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
#include <kernel/object.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/oriented.h>
#include <model/engine_controler.h>
#include <model/engine.h>

namespace ProjetUnivers {
  namespace Model {
    
    RegisterTrait(Engine) ;

    Engine::Engine(const Force& i_force)
    : m_full_thrust(i_force),
      m_controler(NULL)
    {}

    Kernel::Trait* Engine::read(Kernel::Reader* reader)
    {
      Engine* result = new Engine(Force()) ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "ObjectReference")
        {
          result->m_controler = Kernel::ObjectReference::read(reader) ;
        }
        else if (reader->isTraitNode() && 
                 reader->getTraitName() == "Force")
        {
          result->m_full_thrust = Force::read(reader) ;
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;

      return result ;
    }
    
    Force Engine::getAppliedForce() const
    {
      int percentage = 0 ;

      if (m_controler)
      {
        percentage = m_controler->getPowerPercentage() ;
      }
      else
      {
        ErrorMessage("Engine::getAppliedForce no controler") ;
      }
      
      // orient the force according to orientation of the parent physical world
      PhysicalObject* physical_object = getObject()->getParent<PhysicalObject>() ;
      if (physical_object)
      {
        PhysicalWorld* physical_world = physical_object->getObject()->getAncestor<PhysicalWorld>() ;
        if (physical_world)
        {
          Oriented* oriented = getObject()->getParent<Oriented>() ;
  
          /// local orientation relative to world's one
          const Orientation& orientation 
            = oriented->getOrientation(physical_world->getObject()) ;
          
          return m_full_thrust*orientation*(((float)percentage)*0.01) ;
        }
      }      
      // no physical world --> useless to push...
      InternalMessage("Model::Engine::getAppliedForce no force") ;
      return Force() ;
    }

  }
}
