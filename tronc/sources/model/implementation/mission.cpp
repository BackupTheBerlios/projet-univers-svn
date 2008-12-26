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
#include <model/implementation/model_internal.h>
#include <model/mission.h>

namespace ProjetUnivers {
  namespace Model {
  
    Mission::Mission(const std::string& name,
                     Kernel::Object* player_configuration,
                     Kernel::Object* main_menu)
    : m_name(name),
      m_player_configuration(player_configuration),
      m_main_menu(main_menu)
    {}
    
    void Mission::setStartingDistance(const Distance& distance)
    {
      m_starting_distance = distance ;
    }
    
    void Mission::load()
    {
      Model::loadMission(m_name,getObject(),m_player_configuration,m_main_menu) ;
    }
    
    Kernel::Object* Mission::getSystem() const
    {
      return m_system ;
    }
    
    Kernel::Object* Mission::getPlayerConfiguration() const
    {
      return m_player_configuration ;
    }

    Distance Mission::getStartingDistance() const
    {
      return m_starting_distance ;
    }
    
  }
}
