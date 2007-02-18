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
#include <kernel/log.h>

#include <model/position.h>
#include <model/positionned.h>

#include <model/object.h>

namespace ProjetUnivers {
  namespace Model {


    Position::Position()
    {}

    Position::Position(const Position& _position)
    : coordonneeX(_position.xCoordinate),
      coordonneeY(_position.yCoordinate),
      zCoordinate(_position.zCoordinate)
    {}

    Position::Position(const Distance& x, 
                       const Distance& y, 
                       const Distance& z)
    : xCoordinate(x),
      yCoordinate(y),
      zCoordinate(z)
    {}

    Distance Position::getXCoordinate() const
    {
      return this->xCoordinate ;
    }

    Distance Position::getYCoordinate() const
    {
      return this->yCoordinate ;
    }
    
    Distance Position::getZCoordinate() const
    {
      return this->zCoordinate ;
    }
    
  }
}
