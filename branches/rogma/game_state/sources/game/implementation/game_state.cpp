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
#include <kernel/view_point.h>
#include <kernel/controler_set.h>

#include <model/model.h>

#include <game/game_state.h>

namespace ProjetUnivers {
  namespace Game {

    GameState::GameState(const std::string& name)
    : m_name(name),
      m_is_active(false),
      m_model(new Kernel::Model(name))
    {
      // should build every viewpoints and controler sets
      Kernel::ViewPoint::buildRegistered(m_model.get()) ;
      Kernel::ControlerSet::buildRegistered(m_model.get()) ;
    }
  
    void GameState::activate()
    {
      if (!m_is_active)
      {
        const std::set<Kernel::ViewPoint*>& viewpoints = m_model->getViewPoints() ;
        for(std::set<Kernel::ViewPoint*>::const_iterator viewpoint = viewpoints.begin() ;
            viewpoint != viewpoints.end() ;
            ++viewpoint)
        {
          (*viewpoint)->init() ;
        }

        const std::set<Kernel::ControlerSet*>& controlersets = m_model->getControlerSets() ;
        for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = controlersets.begin() ;
            controlerset != controlersets.end() ;
            ++controlerset)
        {
          (*controlerset)->init() ;
        }
      }
    }
    
    void GameState::desactivate()
    {
      if (m_is_active)
      {
        const std::set<Kernel::ViewPoint*>& viewpoints = m_model->getViewPoints() ;
        for(std::set<Kernel::ViewPoint*>::const_iterator viewpoint = viewpoints.begin() ;
            viewpoint != viewpoints.end() ;
            ++viewpoint)
        {
          (*viewpoint)->close() ;
        }

        const std::set<Kernel::ControlerSet*>& controlersets = m_model->getControlerSets() ;
        for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = controlersets.begin() ;
            controlerset != controlersets.end() ;
            ++controlerset)
        {
          (*controlerset)->close() ;
        }
      }
    }
    
    bool GameState::isActive() const
    {
      return m_is_active ;
    }
    
    void GameState::load(const std::string& scene_name)
    {
      Model::load(scene_name,m_model.get()) ;
    }
    
    void GameState::update(const float& seconds)
    {
      if (m_is_active)
      {
        // first update controler sets then viewpoints
        const std::set<Kernel::ControlerSet*>& controlersets = m_model->getControlerSets() ;
        for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = controlersets.begin() ;
            controlerset != controlersets.end() ;
            ++controlerset)
        {
          (*controlerset)->simulate(seconds) ;
        }

        const std::set<Kernel::ViewPoint*>& viewpoints = m_model->getViewPoints() ;
        for(std::set<Kernel::ViewPoint*>::const_iterator viewpoint = viewpoints.begin() ;
            viewpoint != viewpoints.end() ;
            ++viewpoint)
        {
          (*viewpoint)->update(seconds) ;
        }

      }
    }
    
  }
}
