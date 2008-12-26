/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_AREA_H_
#define PU_MODEL_AREA_H_

#include <set>
#include <OgreAxisAlignedBox.h>
#include <model/position.h>

namespace ProjetUnivers 
{
  namespace Model 
  {

    /// An area in 3 dimensions.
    class Area
    {
    public:
      
      /// Empty Area
      Area() ;
      
      /// An area that contains the given positions.
      Area(const std::set<Position>&) ;
      
      /// True if position is in the area.
      bool contains(const Position&) const ;
      
      /// Center of the area.
      Position getCenter() const ;
      
      /// Radius of the area.
      Distance getRadius() const ;
      
    private:
      
      /// Ogre has already it!
      Ogre::AxisAlignedBox m_box ;
    };
    
  }
}
#endif /*PU_MODEL_AREA_H_*/
