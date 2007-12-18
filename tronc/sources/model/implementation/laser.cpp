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

#include <model/model.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/laser_beam.h>
#include <model/physical_object.h>
#include <model/physical_world.h>
#include <model/solid.h>
#include <model/shot.h>

#include <model/laser.h>

namespace ProjetUnivers {
  namespace Model {
    
    RegisterCommand("fire",Laser,fire) ;

    RegisterTrait(Laser) ;
      
    Laser::Laser(const Position& i_out_position,
                 const Orientation& i_out_orientation)
    : m_out_position(i_out_position),
      m_out_orientation(i_out_orientation)
    {}

    Kernel::Trait* Laser::read(Kernel::Reader* reader)
    {
      Laser* result = new Laser(Position(),Orientation()) ;
      
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
      }
      reader->processNode() ;

      return result ;
    }
    
    void Laser::fire()
    {
      
      Positionned* positionned = getObject()->getParent<Positionned>() ;
      Oriented* oriented = getObject()->getParent<Oriented>() ;
      PhysicalObject* object = getObject()->getParent<PhysicalObject>() ;
      PhysicalWorld* world = object ? object->getObject()->getAncestor<PhysicalWorld>() : NULL ; 
      
      if (world && positionned && oriented)
      {
        // create a laserbeam object
        Kernel::Object* beam = createObject(world->getObject()) ;
        
        // should apply local rotation to have correct position decal..
        Orientation orientation_of_laser = oriented->getOrientation(world->getObject()) ;

        Position position_of_the_beam = 
          positionned->getPosition(world->getObject()) + m_out_position*orientation_of_laser ;
        
        // maybe we should add a little delta ??
        // --> no the position of the laser out should integrate that factor 
        addTrait(beam,new Positionned(position_of_the_beam)) ;
        
        Orientation orientation_of_the_beam =
          orientation_of_laser*m_out_orientation ;
          
        addTrait(beam,new Oriented(orientation_of_the_beam)) ;

        // orientation gives speed vector
        // basic_speed(full Z oriented) * orientation
        Speed speed = Speed::MeterPerSecond(0,0,Kernel::Parameters::getValue<float>("Model","LaserBeamSpeed"))*orientation_of_the_beam ;
        // maybe we should add the object speed ??
         
        addTrait(beam,new Mobile(speed)) ;
        addTrait(beam,new Massive(Mass(Energy::Joule(10)))) ;
        
        /*!
          Here we have a limitation : 
          laserbeam collision need to be applied on a physical object 
          thus the beam need to be a physical object before being a beam
        */
        addTrait(beam,new LaserBeam()) ;
        
        // shot
        Kernel::Object* shot = createObject(world->getObject()) ;
        addTrait(shot,new Positionned(position_of_the_beam)) ;
        addTrait(shot,new Shot()) ;
        
        // done
        
      }
      // else : not much sense thus do nothing      
    }
  }
}
