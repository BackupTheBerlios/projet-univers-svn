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
#include <model/area.h>

namespace ProjetUnivers 
{
  namespace Model 
  {

    Area::Area()
    {}
    
    Area::Area(const std::set<Position>& positions)
    {
      bool first = true ;
      
      for(std::set<Position>::const_iterator position = positions.begin() ;
          position != positions.end() ;
          ++position)
      {
        if (first)
        {
          m_box.setExtents(position->Meter(),position->Meter()) ;
          first = false ;
        }
        else
        {
          m_box.merge(position->Meter()) ;
        }
      }
    }
    
    bool Area::contains(const Position& position) const
    {
      return m_box.contains(position.Meter()) ;
    }
    
    Position Area::getCenter() const
    {
      if (m_box.isNull())
        return Position() ;
      
      Ogre::Vector3 center(m_box.getCenter()) ;
      return Position::Meter(center.x,center.y,center.z) ;
    }
    
    Distance Area::getRadius() const
    {
      if (m_box.isNull())
        return Distance() ;
      
      return Distance(Distance::_Meter,m_box.getHalfSize().length()) ;
    }
    
  }
}
