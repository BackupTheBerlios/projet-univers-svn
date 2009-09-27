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

#include <model/oriented.h>
#include <model/positioned.h>


namespace ProjetUnivers
{
  namespace Model
  {

    RegisterTrait(Positioned) ;

    Positioned::Positioned(const Position& i_position)
    : Kernel::Trait(), 
      m_position(i_position)
    {}

    Positioned::Positioned()
    : Kernel::Trait(), 
      m_position()
    {}

    Kernel::Trait* Positioned::read(Kernel::Reader* reader)
    {
      Positioned* result = new Positioned() ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "Position")
        {
          result->m_position = Position::read(reader) ;
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;

      return result ;
    }

    const Position& Positioned::getPosition() const 
    {
      return m_position ;
    }

    Position Positioned::getPosition(const Kernel::Object* object) const 
    {
      const Kernel::Object* ancestor = getObject()->getCommonAncestor(object) ;
      
      if (object == ancestor)
      {
        return getPositionRelativeToAncestor(object) ;
      }
      
      Positioned* positioned = object->getParent<Positioned>() ;
      
      if (ancestor && positioned)
      {
        
        Orientation orientation = getRelativeOrientation(object,ancestor) ;
        
        return (getPositionRelativeToAncestor(ancestor) 
               - positioned->getPositionRelativeToAncestor(ancestor))*orientation.inverse() ; 
      }
      return Position() ;
    }
    
    Position Positioned::getPositionRelativeToAncestor(const Kernel::Object* i_ancestor) const 
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
        
        // first positioned ancestor 
        Positioned* ancestor = getObject()->getParent()
                                ->getParentUpTo<Positioned>(i_ancestor) ;
        
        if (ancestor)
        {
          Orientation orientation = getRelativeOrientation(ancestor->getObject(),i_ancestor) ;
          
          return m_position*orientation + ancestor->getPositionRelativeToAncestor(i_ancestor) ;          
        }
        else
        {
          return m_position ;
        }
      }
    }

    void Positioned::setPosition(const Position& i_position)
    {
      if (m_position != i_position)
      {
        m_position = i_position ;
        notify() ;
      }
    }
    
    void Positioned::setPosition(
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
        // first positioned ancestor 
        Positioned* ancestor = getObject()->getParent()
                                ->getParentUpTo<Positioned>(i_reference) ;
        
        if (ancestor)
        {
          m_position = i_position - ancestor->getPosition(i_reference) ;
          notify() ;
        }
      }
    }
    
    Position getRelativePosition(const Kernel::Object* o1,const Kernel::Object* o2)
    {
      Positioned* positioned = o1->getParent<Positioned>() ; 
      if (! positioned)
      {
        return Position() ;
      }
      
      Position position = positioned->getPosition(o2) ;
      return position ;
    }
    
    Distance getDistance(const Kernel::Object* o1,const Kernel::Object* o2)
    {
      return getRelativePosition(o1,o2).calculateDistance(Position()) ;
    }

    DeclareDeducedTrait(RecursivelyPositioned,
                        Or(HasTrait(Positioned),
                           HasAncestor(HasTrait(RecursivelyPositioned)))) ;

  }
}
