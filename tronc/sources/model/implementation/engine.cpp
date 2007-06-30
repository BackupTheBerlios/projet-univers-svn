/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#include <model/physical_world.h>
#include <model/oriented.h>
#include <model/engine.h>


namespace ProjetUnivers {
  namespace Model {
    

    Engine::Engine(const Force& i_force)
    : m_full_thrust(i_force),
      m_percentage_thrust(0)
    {}
    
    Force Engine::getAppliedForce() const
    {
      // orient the force according to orientation of the parent physical world
      PhysicalWorld* physical_world = getObject()->getParent<PhysicalWorld>() ;
      if (physical_world)
      {
        Oriented* oriented = getObject()->getParent<Oriented>() ;

        /// local orientation relative to world's one
        const Orientation& orientation 
          = oriented->getOrientation(physical_world->getObject()) ;
        
        return m_full_thrust*orientation*(((float)m_percentage_thrust)*0.01) ;
      }
      
      // no physical world --> useless to push...
      return Force() ;
    }
    
    void Engine::setPowerPercentage(const int& i_new)
    {
      m_percentage_thrust = i_new ;
    }
  }
}
