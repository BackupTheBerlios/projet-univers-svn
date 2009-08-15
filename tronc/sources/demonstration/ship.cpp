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
#include <iostream>
#include <projet_univers.h>
#include <kernel/log.h>
#include <kernel/model.h>
#include <kernel/parameters.h>
#include <kernel/timer.h>
#include <kernel/command_delegator.h>

#include <artificial_intelligence/artificial_intelligence.h>
#include <display/display.h>
#include <input/input.h>
#include <gui/gui.h>
#include <model/model.h>
#include <physic/physic.h>
#include <sound/sound.h>

#include <model/oriented.h>
#include <model/positionned.h>
#include <model/observer.h>
#include <model/player.h>
#include <model/end_of_simulation.h>
#include <model/player_configuration.h>
#include <model/state.h>
#include <model/active.h>
#include <model/solid.h>
#include <model/universe.h>

using namespace ProjetUnivers ;

std::string getModelName()
{
  return "default_ship" ;
}

/*
  Load a ship and display it

*/
int main()
{
  /// init
  Kernel::Parameters::load("demonstration.config") ;
  Kernel::Log::init() ;

  Model::start() ;
  Physic::start() ;
  Sound::start() ;
  ArtificialIntelligence::start() ;
  Display::start(Display::ChooseRenderer) ;
  Input::start() ;
  GUI::start() ;

  InformationMessage("Demonstration","Starting of projet univers ship test application" +
                                     Version +
                                     " revision " + RevisionNumber) ;

  std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
  model->init() ;

  Kernel::Object* root = model->createObject() ;
  root->addTrait(new Model::State()) ;
  root->addTrait(new Model::Active()) ;
  root->addTrait(new Model::Positionned()) ;
  root->addTrait(new Model::Oriented()) ;
  root->addTrait(new Model::Universe()) ;

  Kernel::Object* player_configuration = Model::createDefaultPlayerConfiguration(root) ;
  player_configuration->getTrait<Model::PlayerConfiguration>()
                      ->addMapping(Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN),"quit") ;

  Kernel::Object* ship = Model::loadShip(getModelName(),root) ;

  // determine a distance that correspond to ship size
  Model::Distance distance(Model::Distance::_Meter,1000) ;
  Model::Solid* solid_ship = ship->getTrait<Model::Solid>() ;
  if (solid_ship)
  {
    distance = solid_ship->getRadius()*2 ;
  }

  Kernel::Object* observer = root->createObject() ;
  observer->addTrait(new Model::Observer()) ;
  observer->addTrait(new Model::Player()) ;
  observer->addTrait(new Model::Positionned(Model::Position::Meter(0,0,distance.Meter()))) ;
  observer->addTrait(new Model::Oriented()) ;
  observer->addTrait(new Model::State()) ;
  observer->addTrait(new Kernel::CommandDelegator()) ;

  observer->getTrait<Model::State>()->addCommandAlias("quit","change(quit,Active)") ;
  observer->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

  root->getTrait<Model::State>()->pushState(observer,new Model::Active()) ;

  Model::Player::connect(observer,player_configuration) ;

  Kernel::Object* quit = root->createObject() ;
  quit->setName("quit") ;
  quit->addTrait(new Model::EndOfSimulation()) ;
  quit->addTrait(new Model::State()) ;


  Kernel::Timer timer ;

  while (! model->getRoots().empty())
  {
    float seconds = timer.getSecond() ;
    if (seconds > 0)
    {
      timer.reset() ;
      model->update(seconds) ;
    }
  }

  model->close() ;

  ArtificialIntelligence::terminate() ;
  Sound::terminate() ;
  GUI::terminate() ;
  Input::terminate() ;
  Display::terminate() ;
  Physic::terminate() ;

  /// out
  InformationMessage("Demonstration","Modules closed") ;
  Kernel::Log::close() ;

  return 0 ;
}
