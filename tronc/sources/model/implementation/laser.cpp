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
#include <kernel/parameters.h>
#include <kernel/log.h>

#include <model/model.h>
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/laser_beam.h>
#include <model/physical_object.h>
#include <model/physical_world.h>
#include <model/solid.h>
#include <model/shot.h>
#include <model/with_lifetime.h>

#include <model/laser.h>

namespace ProjetUnivers
{
  namespace Model
  {

    std::string Laser::Fire = "Fire" ;

    RegisterCommand(Laser::Fire,Laser,fire) ;

    RegisterTrait(Laser) ;

    Laser::Laser(const Position&    out_position,
                 const Orientation& out_orientation,
                 const Energy&      beam_energy)
    : m_out_position(out_position),
      m_out_orientation(out_orientation),
      m_laser_beam_energy(beam_energy),
      m_beam_lifetime(Duration::Second(2)),
      m_beam_length(Distance(Distance::_Meter,20)),
      m_beam_radius(Distance(Distance::_Meter,5))
    {
      m_laser_speed_meter_per_second = Kernel::Parameters::getValue<float>("Model","LaserBeamSpeed",600) ;
    }

    void Laser::setShotTimeDelay(const Duration& duration)
    {
      m_time_between_shots = duration ;
    }

    void Laser::setLaserSpeedMeterPerSecond(const float& value)
    {
      m_laser_speed_meter_per_second = value ;
    }

    void Laser::removeTimeToNextShot(const Duration& duration)
    {
      m_time_to_fire = m_time_to_fire - duration ;
    }


    void Laser::setOrientation(const Orientation& orientation)
    {
      m_out_orientation = orientation ;
      notify() ;
    }

    Kernel::Trait* Laser::read(Kernel::Reader* reader)
    {
      Laser* result = new Laser(Position(),Orientation(),Energy()) ;

      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() &&
            reader->getTraitName() == "Position")
        {
          result->m_out_position = Position::read(reader) ;
        }
        else if (reader->isTraitNode() &&
                 reader->getTraitName() == "Orientation")
        {
          result->m_out_orientation = Orientation::read(reader) ;
        }
        else if (reader->isTraitNode() &&
                 reader->getTraitName() == "Energy")
        {
          result->m_laser_beam_energy = Energy::read(reader) ;
        }
        else if (reader->isTraitNode() &&
                 reader->getTraitName() == "Duration")
        {
          if (reader->getName() == "beam_lifetime")
            result->m_beam_lifetime = Duration::read(reader) ;
          else if (reader->getName() == "shot_delay")
            result->m_time_between_shots = Duration::read(reader) ;
        }
        else if (reader->isTraitNode() &&
                 reader->getTraitName() == "Distance")
        {
          if (reader->getName() == "beam_length")
            result->m_beam_length = Distance::read(reader) ;
          else if (reader->getName() == "beam_radius")
            result->m_beam_radius = Distance::read(reader) ;
        }
        else if (reader->isTraitNode() &&
                 reader->getTraitName() == "Speed")
        {
          float value = 0 ;
          std::map<std::string,std::string>::const_iterator finder ;
          finder = reader->getAttributes().find("value") ;
          if (finder != reader->getAttributes().end())
          {
            value = atof(finder->second.c_str()) ;
          }
          else
          {
            ErrorMessage("Model::Speed::read required attribute : value") ;
          }
          finder = reader->getAttributes().find("unit") ;
          if (finder != reader->getAttributes().end() && finder->second == "MeterPerSecond")
          {
            result->m_laser_speed_meter_per_second = value ;
          }
          else
          {
            ErrorMessage("Model::Speed::read required attribute : unit") ;
          }
          reader->processNode() ;

        }
      }
      reader->processNode() ;

      return result ;
    }

    void Laser::fire()
    {
      InternalMessage("Model","entering fire") ;

      // handle firing rate
      if (m_time_to_fire.Second() > 0)
        return ;

      Positioned* positioned = getObject()->getParent<Positioned>() ;
      Oriented* oriented = getObject()->getParent<Oriented>() ;
      PhysicalObject* object = getObject()->getParent<PhysicalObject>() ;
      PhysicalWorld* world = object ? object->getObject()->getAncestor<PhysicalWorld>() : NULL ;

      if (world && positioned && oriented)
      {
        InternalMessage("Model","firing") ;
        // create a laser beam object
        Kernel::Object* beam = world->getObject()->createObject() ;

        // should apply local rotation to have correct local position..
        Orientation orientation_of_laser = oriented->getOrientation(world->getObject()) ;

        Position position_of_the_beam =
          positioned->getPosition(world->getObject()) + m_out_position*orientation_of_laser ;

        beam->addTrait(new Positioned(position_of_the_beam)) ;

        Orientation orientation_of_the_beam =
          orientation_of_laser*m_out_orientation ;

        beam->addTrait(new Oriented(orientation_of_the_beam)) ;

        // orientation gives speed vector
        // basic_speed(full Z oriented) * orientation
        Speed speed = Speed::MeterPerSecond(0,0,-getLaserSpeedMeterPerSecond())*orientation_of_the_beam ;

        // maybe we should add the object speed ?? (i.e. the speed of the ship)

        beam->addTrait(new Mobile(speed)) ;
        beam->addTrait(new Massive(Mass(m_laser_beam_energy,speed))) ;

        beam->addTrait(new LaserBeam(object->getObject(),m_beam_length,m_beam_radius)) ;
        beam->addTrait(new WithLifetime(getLaserBeamLifeDuration())) ;

        // shot
        Kernel::Object* shot = world->getObject()->createObject() ;
        shot->addTrait(new Positioned(position_of_the_beam)) ;
        shot->addTrait(new Shot()) ;

        // re-init timer
        m_time_to_fire = m_time_between_shots ;
        // done

      }
      // else : not much sense thus do nothing
      InternalMessage("Model","leaving fire") ;
    }

    float Laser::getLaserSpeedMeterPerSecond() const
    {
      return m_laser_speed_meter_per_second ;
    }

    const Position& Laser::getOutPosition() const
    {
      return m_out_position ;
    }

    const Orientation& Laser::getOutOrientation() const
    {
      return m_out_orientation ;
    }

    const Duration& Laser::getTimeBetweenShots() const
    {
      return m_time_between_shots ;
    }

    const Duration& Laser::getLaserBeamLifeDuration() const
    {
      return m_beam_lifetime ;
    }

    const Distance& Laser::getBeamRadius() const
    {
      return m_beam_radius ;
    }

    const Distance& Laser::getBeamLength() const
    {
      return m_beam_length ;
    }

    void Laser::setBeamRadius(const Distance& radius)
    {
      m_beam_radius = radius ;
    }

    void Laser::setBeamLength(const Distance& length)
    {
      m_beam_length = length ;
    }

  }
}
