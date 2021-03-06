/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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

#ifndef PU_MODEL_POSITION_H_
#define PU_MODEL_POSITION_H_

#include <OgreVector3.h>

#include <model/distance.h>

namespace ProjetUnivers {
  namespace Model {

    /// A position in a three dimention world.
    /*!
      A position is relative to the Positionned parent (if exists).
      
      Position are held in a (right/left?) hand coordinate:
      - x axe : positive to rigth
      - y axe : positive to front 
      - z axe : positive to up 
      
      @see Positionned
    */
    class Position 
    {
    public:
    
    /*!
      @name Construction
    */
    // @{  

      /// Constructor.
      Position() ;
      
      /// Build position in meter.
      static Position Meter(float i_x, 
                            float i_y, 
                            float i_z) ;
      
      
      /// Copy constructor.
      Position(const Position&) ;
      
      /// Addition.
      Position operator+(const Position& i_position) const ;

      /// Substraction.
      Position operator-(const Position& i_position) const ;

      
    // @}
    /*!
      @name Access
    */
    // @{  

      /// Coordinates in meter
      Ogre::Vector3 Meter() const ;
      
      // Distance between 2 Position.
      Distance calculateDistance(const Position&) const ; 

      /// ????
      bool operator==(const Position&) const ;
      
      /// @deprecated    
      Distance getXCoordinate() const ;
      Distance getYCoordinate() const ;
      Distance getZCoordinate() const ;
      
    // @}
    
    private:
      
      Ogre::Vector3   m_value ;
      Distance::Unit  m_unit ;

      /// Internal constructor.
      Position(Distance::Unit i_unit,
               float          i_x, 
               float          i_y, 
               float          i_z) ;
      
      
    };
  }
}
#endif
