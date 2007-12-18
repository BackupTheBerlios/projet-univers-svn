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

namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(Oriented) ;

    Oriented::Oriented(
        const Orientation& i_orientation)
    : Kernel::Trait(), 
      m_orientation(i_orientation)
    {}

    Oriented::Oriented()
    : Kernel::Trait(), 
      m_orientation()
    {}

    Kernel::Trait* Oriented::read(Kernel::Reader* reader)
    {
      Oriented* result = new Oriented() ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "Orientation")
        {
          result->m_orientation = Orientation::read(reader) ;
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;

      return result ;
    }

    const Orientation& Oriented::getOrientation() const
    {
      return m_orientation ;
    }

    Orientation Oriented::getOrientation(Kernel::Object* i_ancestor) const
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
        Oriented* ancestor = getObject()->getParent()
                             ->getParentUpTo<Oriented>(i_ancestor) ;
        
        if (ancestor)
        {
          return ancestor->getOrientation(i_ancestor)*m_orientation ;          
        }
        else
        {
          return m_orientation ;
        }
      }
    }

    void Oriented::setOrientation(const Orientation& i_orientation)
    {
      m_orientation = i_orientation ;
      notify() ;
    }

    void Oriented::setOrientation(
        const Orientation& i_orientation,
        Kernel::Object*    i_reference)
    {
      if (! getObject()->getParent() || i_reference == getObject())
      {
        return ;
      }
      if (i_reference == getObject()->getParent())
      {
        m_orientation = i_orientation ;
        notify() ;
      }
      else
      {
        Oriented* ancestor = getObject()->getParent()
                             ->getParentUpTo<Oriented>(i_reference) ;
        
        if (ancestor)
        {
          m_orientation = ancestor->getOrientation(i_reference).inverse()*i_orientation ;
          notify() ;
        }
      }
    }
  }
}
