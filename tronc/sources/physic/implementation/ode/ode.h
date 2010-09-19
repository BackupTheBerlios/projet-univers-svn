/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Mathieu ROGER                                 *
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

#include <ode/ode.h>

#include <kernel/string.h>
#include <kernel/base_controler.h>

#include <model/mesh.h>


namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {

      /// Physics implementation through ODE.
      /*!
      @par Physic calculus Conjecture

        Objects that are both :
        - Positioned, @c Whole
        are represented by dWorld

        Objects that are both :
        - Positioned, Massive, Whole, Mobile
        are represented by a dBody and submitted to forces, the dBody is
        inserted in the first ancestor's dWorld.

        Objects that are both
        - Solid, Positioned
        are represented by dGeom that are attached to the dBody of their whole.

        @todo validate...

      @par Examples

      @par
        A stellar system with a planet and a ship
        system Positioned  --> dWorld1
          |
          -- planet1 Positioned Massive Mobile Solid Whole --> dBody1(dWorld1), dWorld2
          |
          -- ship Positioned Mobile Massive Solid Whole --> dBody2(dWorld1), dWorld3
          |   |
          |   -- engine Positioned Massive Component Solid --> dGeom1(dBody2)
          |   |
          |   -- wing1 Positioned Massive Component Solid --> dGeom2(dBody2)
          |   |
          |   -- wing2 Positioned Massive Component Solid --> dGeom3(dBody2)
          |   |
          |   -- body Positioned Massive Component Solid --> dGeom4(dBody2)
          |   |
          |   -- person1 Positioned Massive Solid Character --> dBody3(dWorld3)

        It works.
      @par
        Another example

      */
      namespace Ode
      {

        class PhysicalObject ;
        class PhysicalWorld ;

        /// Initialization of ODE specific.
        void init() ;

        /// Termination of ODE specific.
        void close() ;


      /*!
        @name ODE like functions
      */
      //@{

        /// custom implementation for dMassSetTrimesh
        void meshToMass(const Model::Mesh& i_mesh,dMass* io_mass) ;

      //@}
      /*!
        @name Print functions
      */
      //@{

        std::string printReal(const dReal& i_real) ;
        std::string printVector3(const dVector3& i_vector) ;
        std::string printVector4(const dVector4& i_vector) ;
        std::string printMatrix3(const dMatrix3& i_matrix) ;
        std::string printMass(const dMass& i_mass) ;

      //@}
      /*!
        @name Contacts.
      */
      //@{

        /// Array of contact points.
        extern dContactGeom* contact_points ;

        /// Maximum size of contact_points.
        extern int maximum_contact_points ;

      //@}

      }
    }
  }
}
