/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <model/flying_group.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    FlyingGroup::FlyingGroup(const std::string& name)
    : m_name(name),
      m_has_player(false),
      m_initial_number_of_ships(1),
      m_number_of_ships(0),
      m_ship_name("razor"),
      m_objective(Objective::attackAllEnemies()),
      m_number_of_spawn(1)
    {}

    void FlyingGroup::setName(const std::string& name)
    {
      m_name = name ;
      notify() ;
    }
    
    const std::string& FlyingGroup::getName() const
    {
      return m_name ;
    }
   
    void FlyingGroup::setShipName(const std::string& name)
    {
      m_ship_name = name ;
    }
    
    void FlyingGroup::setInitialNumberOfShips(const unsigned int& number)
    {
      m_initial_number_of_ships = number ;
    }
    
    void FlyingGroup::setHasPlayer(const bool& has_player)
    {
      m_has_player = has_player ;
    }
    
    void FlyingGroup::removeShip()
    {
      if (m_number_of_ships > 0)
      {
        --m_number_of_ships ;
        notify() ;
      }
    }
    
    void FlyingGroup::addShip()
    {
      ++m_number_of_ships ;
      notify() ;
    }
    
    void FlyingGroup::setNumberOfSpawn(const unsigned int& number)
    {
      m_number_of_spawn = number ;
      notify() ;
    }
    
    const std::string& FlyingGroup::getShipName() const
    {
      return m_ship_name ;
    }
    
    const unsigned int& FlyingGroup::getInitialNumberOfShips() const
    {
      return m_initial_number_of_ships ;
    }
    
    const bool& FlyingGroup::hasPlayer() const
    {
      return m_has_player ;
    }
    
    const Objective& FlyingGroup::getObjective() const
    {
      return m_objective ;
    }
    
    const unsigned int& FlyingGroup::getNumberOfShips() const
    {
      return m_number_of_ships ;
    }
    
    const unsigned int& FlyingGroup::getNumberOfSpawn() const
    {
      return m_number_of_spawn ;
    }
    
  }
}
