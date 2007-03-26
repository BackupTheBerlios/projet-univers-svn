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
#include <kernel/object.h>

#include <model/positionned.h>


namespace ProjetUnivers {
  namespace Model {


    Positionned::Positionned(const Position& i_position)
    : Kernel::Trait(), 
      m_position(i_position),
      m_orientation()
    {}

    Positionned::Positionned(
        const Position&    i_position,
        const Orientation& i_orientation)
    : Kernel::Trait(), 
      m_position(i_position),
      m_orientation(i_orientation)
    {}


    Positionned::Positionned()
    : Kernel::Trait(), 
      m_position(),
      m_orientation()
    {
      
    }

    const Position& Positionned::getPosition() const 
    {
      return m_position ;
    }

    const Orientation& Positionned::getOrientation() const
    {
      return m_orientation ;
    }


    Position Positionned::getPosition(Kernel::Object* i_ancestor) const 
    {
      if (! getObject()->getParent() || i_ancestor == getObject())
      {
        return Position() ;
      }
      
      if (i_ancestor == getObject()->getParent())
      {
        return m_position ;
      }
      else
      {
        Positionned* 
          positionned = getObject()->getParent()->getTrait<Positionned>() ;
        
        if (positionned)
        {
          return m_position + positionned->getPosition(i_ancestor) ;          
        }
        else
        {
          return m_position ;
        }
      }
    }

    Orientation Positionned::getOrientation(Kernel::Object* i_ancestor) const
    {
      if (! getObject()->getParent() || i_ancestor == getObject())
      {
        return Orientation() ;
      }
      
      if (i_ancestor == getObject()->getParent())
      {
        return m_orientation ;
      }
      else
      {
        Positionned* 
          positionned = getObject()->getParent()->getTrait<Positionned>() ;
        
        if (positionned)
        {
          return positionned->getOrientation(i_ancestor)*m_orientation ;          
        }
        else
        {
          return m_orientation ;
        }
      }
    }


    void Positionned::changeOrientation(const Orientation& i_orientation)
    {
      m_orientation = i_orientation ;
      notify() ;
    }

    void Positionned::changePosition(const Position& i_position)
    {
      m_position = i_position ;
      notify() ;
    }

    
  }
}
