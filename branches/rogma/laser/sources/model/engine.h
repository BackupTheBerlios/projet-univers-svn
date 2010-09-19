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
#pragma once

#include <kernel/object_reference.h>
#include <kernel/reader.h>

#include <model/force_generator.h>
#include <model/force.h>
#include <model/position.h>
#include <model/distance.h>

namespace ProjetUnivers
{
  namespace Model
  {

    namespace Test
    {
      class TestLoad ;
    }

    class EngineControler ;

    /// Ship/Other objects engine.
    class Engine : public ForceGenerator
    {
    public:

      /// Constructor.
      Engine(const Force& force) ;

      /// Read an Engine trait.
      /*!
        stored as
        @code
          <Engine>
            <Force ... />
            <Position .../>
            <Distance .../>
          </Engine>
        @endcode
      */
      static Kernel::Trait* read(Kernel::Reader* reader) ;

      /// The zone where gas comes out
      void setOutputPosition(const Position&) ;

      /// The radius of the zone where gas comes out
      void setOutputRadius(const Distance&) ;

      /// Get the force.
      virtual Force getAppliedForce() ;

      /// The percentage of power of the engine
      float getPowerPercentage() const ;

      /// The zone where gas comes out
      const Position& getOutputPosition() const ;

      /// The radius of the zone where gas comes out
      const Distance& getOutputRadius() const ;


    private:

      /// The percentage of power of the engine
      void calculatePowerPercentage() ;

      /// Maximal "force".
      /*!
        Orientation is relative to parent physical object.
        Thus normally a ship force is : (0,0,-100) or something.
      */
      Force m_full_thrust ;

      /// The output thrust of the engine
      Position m_output_position ;
      Distance m_output_radius ;

      float m_percentage ;

      friend void connectControlerEngine(Kernel::Object*,Kernel::Object*) ;
      friend class ProjetUnivers::Model::Test::TestLoad ;
    };


  }
}
