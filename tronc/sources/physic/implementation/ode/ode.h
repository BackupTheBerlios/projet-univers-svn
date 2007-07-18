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
#ifndef PU_PHYSIC_IMPLEMENTATION_ODE_ODE_H_
#define PU_PHYSIC_IMPLEMENTATION_ODE_ODE_H_

#include <ode/ode.h>
#include <kernel/string.h>
#include <model/mesh.h>


namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {

      /// Physics implementation throught ODE.
      /*!
      @par Physic calculus Conjecture
               
        Objects that are both :
        - Positionned, @c Whole
        are represented by dWorld
        
        Objects that are both :
        - Positionned, Massive, Whole, Mobile 
        are represented by a dBody and submitted to forces, the dBody is 
        inserted in the first ancestor's dWorld.  
        
        Objects that are both 
        - Solid, Positionned 
        are represented by dGeom that are attached to the dBody of their whole. 
        
        @todo validate...
        
      @par Examples
        
      @par 
        A stellar system with a planet and a ship 
        system Positionned  --> dWorld1
          |
          -- planet1 Positionned Massive Mobile Solid Whole --> dBody1(dWorld1), dWorld2
          |
          -- ship Positionned Mobile Composite Massive Solid Whole --> dBody2(dWorld1), dWorld3
          |   |
          |   -- engine Positionned Massive Component Solid --> dGeom1(dBody2)
          |   |
          |   -- wing1 Positionned Massive Component Solid --> dGeom2(dBody2)
          |   |
          |   -- wing2 Positionned Massive Component Solid --> dGeom3(dBody2)
          |   |
          |   -- body Positionned Massive Component Solid --> dGeom4(dBody2)
          |   |
          |   -- person1 Positionned Massive Solid Character --> dBody3(dWorld3)
        
        It works.
      @par
        Another example 
                    
      */
      namespace Ode {
        

      /*!
        @name ODE like functions
      */
      // @{
              
        /// custom implentation for dMassSetTrimesh
        void meshToMass(const Model::Mesh& i_mesh,dMass* io_mass) ;

        
      //@}
      /*!
        @name Print functions
      */
      // @{
      
        std::string printReal(const dReal& i_real) ;
        std::string printVector3(const dVector3& i_vector) ;
        std::string printVector4(const dVector4& i_vector) ;
        std::string printMatrix3(const dMatrix3& i_matrix) ;
        std::string printMass(const dMass& i_mass) ;
      
      //@}
        
      }
    }
  }
}

#endif /*PU_PHYSIC_IMPLEMENTATION_ODE_ODE_H_*/
