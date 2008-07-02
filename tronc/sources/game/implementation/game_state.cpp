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

#include <model/game_state.h>
#include <model/model.h>

#include <game/game.h>
#include <game/implementation/controler/game_controler_set.h>
#include <game/game_state.h>

namespace ProjetUnivers {
  namespace Game {

    GameState::GameState(const std::string& name)
    : m_name(name),
      m_is_active(false),
      m_next_state(NULL),
      m_game(NULL),
      m_model(new Kernel::Model(name)),
      m_root(NULL)
    {
      m_root = m_model->createObject() ;
      m_root->addTrait(new Model::GameState()) ;
    }
  
    void GameState::setNextState(GameState* state)
    {
      m_next_state = state ;
    }
    
    void GameState::setGame(Game* game)
    {
      m_game = game ;
    }
    
    void GameState::activate()
    {
      if (!m_is_active)
      {
        m_is_active = true ;
        
        if (m_game)
          m_game->addActiveState(this) ;
      }
    }
    
    void GameState::init()
    {
      m_model->init() ;
      m_model->getControlerSet<Implementation::Controler::GameControlerSet>()
             ->setGameState(this) ;
    }

    void GameState::close()
    {
      m_model->close() ;
    }

    void GameState::desactivate()
    {
      InternalMessage("Game","GameState::desactivate entering") ;
      if (m_is_active)
      {
        if (m_game)
          m_game->removeActiveState(this) ;
        
        InternalMessage("Game","GameState::desactivate removed from game") ;
        if (m_next_state)
        {
          InternalMessage("Game","GameState::desactivate activivating next state") ;
          m_next_state->activate() ;
        }
        
      }
      InternalMessage("Game","GameState::desactivate leaving") ;
    }
    
    void GameState::load(const std::string& scene_name)
    {
      Model::load(scene_name,m_root) ;
    }
    
    void GameState::update(const float& seconds)
    {
      if (m_is_active)
      {
        m_model->update(seconds) ;
      }
    }
    
    Kernel::Object* GameState::getRoot() const
    {
      return m_root ;
    }
    
  }
}
