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
#include <model/destroyable.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(Destroyable) ;
      
    float Destroyable::getLife() const 
    {
      return (m_remaining_hit_points/m_max_hit_points) ;
    }
   
    void Destroyable::damage(const Energy& energy)
    {

      m_remaining_hit_points = m_remaining_hit_points - energy ;

      if (m_remaining_hit_points < Energy())
      {
        m_remaining_hit_points = Energy() ;
      }
      
      notify() ;
      
    }
   
    Destroyable::~Destroyable()
    {}
    
    Destroyable::Destroyable(const Energy& max_hit_points)
    : Kernel::Trait(),
      m_max_hit_points(max_hit_points), 
      m_remaining_hit_points(max_hit_points)
    {}

    Kernel::Trait* Destroyable::read(Kernel::Reader* reader)
    {
      Destroyable* result = new Destroyable(Energy()) ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "Energy")
        {
          if (reader->getName() == "max_hit_points")
          {
            result->m_max_hit_points = Energy::read(reader) ;
          }
          else if (reader->getName() == "current_hit_points")
          {
            result->m_remaining_hit_points = Energy::read(reader) ;
          }
        }
        else
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;

      return result ;
    }

  }
}

