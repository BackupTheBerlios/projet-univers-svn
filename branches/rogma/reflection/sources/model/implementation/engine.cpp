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
#include <kernel/object.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/oriented.h>
#include <model/engine_controler.h>
#include <model/engine.h>
#include <kernel/relation.h>
#include <model/control_connection.h>

namespace ProjetUnivers
{
  namespace Model
  {

    RegisterTrait(Engine) ;

    Engine::Engine(const Force& force)
    : m_full_thrust(force),
      m_percentage(0)
    {}

    Kernel::Trait* Engine::read(Kernel::Reader* reader)
    {
      Engine* result = new Engine(Force()) ;

      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && reader->getTraitName() == "Force")
        {
          result->m_full_thrust = Force::read(reader) ;
        }
        else if (reader->isTraitNode() && reader->getTraitName() == "Position")
        {
          result->m_output_position = Position::read(reader) ;
        }
        else if (reader->isTraitNode() && reader->getTraitName() == "Distance")
        {
          result->m_output_radius = Distance::read(reader) ;
        }
        else
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;

      return result ;
    }

    void Engine::calculatePowerPercentage()
    {
      int percentage = 0 ;

      Kernel::Object* controler = Kernel::Relation::getUniqueLinked<Kernel::Inverse<ControlConnection> >(getObject()) ;

      if (controler && controler->getTrait<EngineControler>())
      {
        percentage = controler->getTrait<EngineControler>()->getPowerPercentage() ;

        float result = ((float)percentage)*0.01 ;

        if (result != m_percentage)
        {
          m_percentage = result ;
          notify() ;
        }
      }
    }

    float Engine::getPowerPercentage() const
    {
      return m_percentage ;
    }

    Force Engine::getAppliedForce()
    {
      calculatePowerPercentage() ;
      float percentage = getPowerPercentage() ;

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

          return m_full_thrust*orientation*percentage ;
        }
      }
      // no physical world --> useless to push...
      InternalMessage("Model","Model::Engine::getAppliedForce no force") ;
      return Force() ;
    }

    const Position& Engine::getOutputPosition() const
    {
      return m_output_position ;
    }

    const Distance& Engine::getOutputRadius() const
    {
      return m_output_radius ;
    }

    void Engine::setOutputPosition(const Position& position)
    {
      m_output_position = position ;
      notify() ;
    }

    void Engine::setOutputRadius(const Distance& radius)
    {
      m_output_radius = radius ;
      notify() ;
    }

  }
}
