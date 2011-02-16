/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2010 Mathieu ROGER                                 *
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
#include <tclap/CmdLine.h>

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
#include <model/positioned.h>
#include <model/observer.h>
#include <model/player.h>
#include <model/end_of_simulation.h>
#include <model/player_configuration.h>
#include <model/state.h>
#include <model/active.h>
#include <model/solid.h>
#include <model/universe.h>
#include <model/plays.h>

using namespace ProjetUnivers ;

class CameraOrientation : public Model::Oriented
{};

/*
  Load a ship and display it allowing to test the xml configuration for that file
  inputs are connected so the ship is flyable
*/
int main(int argc,char** argv)
{
  /// init
  Kernel::Parameters::load("demonstration.config") ;
  Kernel::Log::init() ;

  std::string ship_name ;

  try
  {
    TCLAP::CmdLine cmd("Command description message",' ',"1") ;

    TCLAP::ValueArg<std::string> ship("s","ship","ship name",false,"default_ship","string") ;
    cmd.add(ship) ;

    // get values
    cmd.parse(argc,argv) ;
    ship_name = ship.getValue() ;
  }
  catch(...)
  {
    return 1 ;
  }


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
  root->addTrait(new Model::Positioned()) ;
  root->addTrait(new Model::Oriented()) ;
  root->addTrait(new Model::Universe()) ;

  Kernel::Object* player_configuration = Model::createDefaultPlayerConfiguration(root) ;

  Model::PlayerConfiguration* config = player_configuration->getTrait<Model::PlayerConfiguration>() ;

  config->addMapping(Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN),"quit") ;
  config->addMapping(Model::PlayerConfiguration::InputEvent::key(OIS::KC_UP),"Forward") ;
  config->addMapping(Model::PlayerConfiguration::InputEvent::key(OIS::KC_DOWN),"Back") ;
  config->addMapping(Model::PlayerConfiguration::InputEvent::key(OIS::KC_LEFT),"Left") ;
  config->addMapping(Model::PlayerConfiguration::InputEvent::key(OIS::KC_RIGHT),"Right") ;

  config->addMapping(Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseY),"Up/Down") ;
  config->addMapping(Model::PlayerConfiguration::InputAxis(Model::PlayerConfiguration::InputAxis::MouseX),"Left/Right") ;

  Kernel::Object* ship = Model::loadShip(ship_name,root) ;

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
  observer->addTrait(new Model::Positioned(Model::Position::Meter(0,0,distance.Meter()))) ;
  observer->addTrait(new CameraOrientation()) ;
  observer->addTrait(new Model::State()) ;
  observer->addTrait(new Kernel::CommandDelegator()) ;
  Kernel::Link<Model::Plays>(observer,observer) ;

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

/// Camera control
class CameraControl : public Kernel::DeducedTrait
{
public:

  void moveForward()
  {
    move(0,0,-1) ;
  }

  void moveBack()
  {
    move(0,0,1) ;
  }

  void moveLeft()
  {
    move(-1,0,0) ;
  }

  void moveRight()
  {
    move(1,0,0) ;
  }

private:

  void move(const float& x,const float& y,const float& z)
  {
    Model::Positioned* positioned = getObject()->getTrait<Model::Positioned>() ;
    Model::Oriented* oriented = getObject()->getTrait<Model::Oriented>() ;
    Model::Position delta(Model::Position::Meter(x,y,z)) ;
    positioned->setPosition(delta*oriented->getOrientation()+positioned->getPosition()) ;
  }

};

DeclareDeducedTrait(CameraControl,And(HasTrait(Model::Observer),
                                      HasTrait(Model::Positioned))) ;

RegisterCommand("Forward",CameraControl,moveForward) ;
RegisterCommand("Back",CameraControl,moveBack) ;
RegisterCommand("Left",CameraControl,moveLeft) ;
RegisterCommand("Right",CameraControl,moveRight) ;


RegisterAxis("Left/Right","Look",CameraOrientation,setX) ;
RegisterAxis("Up/Down","Look",CameraOrientation,setY) ;

