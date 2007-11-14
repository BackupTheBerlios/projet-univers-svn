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
#include <kernel/object.h>

#include <model/positionned.h>


namespace ProjetUnivers {
  namespace Model {


    Positionned::Positionned(const Position& i_position)
    : Kernel::Trait(), 
      m_position(i_position)
    {}

    Positionned::Positionned()
    : Kernel::Trait(), 
      m_position()
    {}

    const Position& Positionned::getPosition() const 
    {
      return m_position ;
    }

    Position Positionned::getPosition(const Kernel::Object* object) const 
    {
      const Kernel::Object* ancestor = getObject()->getCommonAncestor(object) ;
      
      if (object == ancestor)
      {
        return getPositionAncestor(object) ;
      }
      
      Positionned* positionned = object->getParent<Positionned>() ;
      
      if (ancestor && positionned)
      {
        return getPositionAncestor(ancestor) 
               - positionned->getPositionAncestor(ancestor) ; 
      }
      return Position() ;
    }
    
    Position Positionned::getPositionAncestor(const Kernel::Object* i_ancestor) const 
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
        // recursive case 
        
        // first positionned ancestor 
        Positionned* ancestor = getObject()->getParent()
                                ->getParentUpTo<Positionned>(i_ancestor) ;
        
        if (ancestor)
        {
          return m_position + ancestor->getPosition(i_ancestor) ;          
        }
        else
        {
          return m_position ;
        }
      }
    }

    void Positionned::setPosition(const Position& i_position)
    {
      if (m_position != i_position)
      {
        m_position = i_position ;
        notify() ;
      }
    }
    
    void Positionned::setPosition(
        const Position& i_position,
        Kernel::Object* i_reference)
    {
      if (! getObject()->getParent() || i_reference == getObject())
      {
        return ;
      }
      if (i_reference == getObject()->getParent())
      {
        m_position = i_position ;
        notify() ;
      }
      else
      {
        // first positionned ancestor 
        Positionned* ancestor = getObject()->getParent()
                                ->getParentUpTo<Positionned>(i_reference) ;
        
        if (ancestor)
        {
          m_position = i_position - ancestor->getPosition(i_reference) ;
          notify() ;
        }
      }
    }
    
    Position getRelativePosition(const Kernel::Object* o1,const Kernel::Object* o2)
    {
      Positionned* positionned = o1->getParent<Positionned>() ; 
      if (! positionned)
      {
        return Position() ;
      }
      
      Position position = positionned->getPosition(o2) ;
      return position ;
    }
    
  }
}
