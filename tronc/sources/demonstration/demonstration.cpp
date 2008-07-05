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
#include <iostream>
#include <kernel/log.h>
#include <kernel/parameters.h>

#include <model/duration.h>
#include <model/image.h>
#include <model/observer.h>
#include <model/player.h>
#include <model/positionned.h>
#include <model/with_lifetime.h>
#include <model/model.h>

#include <game/game.h>
#include <game/game_state.h>

#include <physic/physic.h>
#include <artificial_intelligence/artificial_intelligence.h>
#include <sound/sound.h>
#include <input/input.h>

using namespace ProjetUnivers ;

std::string getModelName()
{
  try 
  {
    return Kernel::Parameters::getValue<std::string>("Demonstration","loadedModel") ;
  }
  catch(...)
  {
    std::cout << "failed to load parameter loadedModel" << std::endl ;
    
    return "TestDemonstration" ;
  }
}

/*
  Demonstration program

*/
int main() {


  /// init
  Kernel::Parameters::load("demonstration.config") ;
  Kernel::Log::init() ;
  Physic::start() ;
  Input::start() ;
  Sound::start() ;
  ArtificialIntelligence::start() ;
  Model::start() ;
  
  InformationMessage("Demonstration","Starting of projet univers") ;
  Game::Game game ;

  Game::GameState* welcome = game.addState(new Game::GameState("welcome")) ;
  Kernel::Object* welcome_model = welcome->getRoot() ;
  welcome_model->addTrait(new Model::WithLifetime(Model::Duration::Second(2))) ;
  welcome_model->addTrait(new Model::Image("intro.png")) ;
  
  Kernel::Object* observer = welcome_model->createObject() ;
  observer->addTrait(new Model::Observer()) ;
  observer->addTrait(new Model::Player()) ;
  observer->addTrait(new Model::Positionned()) ;
  
  InformationMessage("Demonstration","Modules inited") ;

  std::string model_name(getModelName()) ;
  std::cout << "loading " << model_name << std::endl ;
  
  Game::GameState* gamestate = game.addState(new Game::GameState("game")) ;
  gamestate->load(getModelName()) ;

  welcome->setNextState(gamestate) ;
  welcome->activate() ;
  game.run() ;

  /// out
  InformationMessage("Demonstration","Modules closed") ;
  Kernel::Log::close() ;
  
  return 0 ;
}
