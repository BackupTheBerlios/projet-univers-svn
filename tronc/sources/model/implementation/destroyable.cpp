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

#include <model/destroyable.h>

namespace ProjetUnivers {
  namespace Model {

    
      
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
      



  }

}

