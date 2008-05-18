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
#include <kernel/object.h>
#include <kernel/timer.h>
#include <kernel/parameters.h>
#include <model/model.h>
#include <model/duration.h>
#include <display/display.h>
#include <action/action.h>
#include <input/input.h>
#include <physic/physic.h>
#include <artificial_intelligence/artificial_intelligence.h>

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

  InformationMessage("Demonstration","Demarrage de projet univers") ;
  Model::init() ;
  Physic::init() ;
  Display::init() ;
  Action::init() ;
  
  InformationMessage("Demonstration","Modules initialisÚs") ;

  std::string model_name(getModelName()) ;
  std::cout << "loading " << model_name << std::endl ;
  
  Model::load(model_name) ;

  InformationMessage("Demonstration","Model loaded") ;
  
  Kernel::Object* observer(Model::getObject("Observer")) ;
  
  Display::buildRealWorldViewPoint(observer) ;

  Physic::build(observer) ;

  Input::build(observer) ;
  Input::init() ;

  ArtificialIntelligence::build(observer) ;
  ArtificialIntelligence::init() ;

  InternalMessage("Demonstration","Activating Viewpoint") ;

  InformationMessage("Demonstration","Demarrage de la boucle principale") ;

  Kernel::Timer timer ;

  /// main loop
  while (! Action::finished())
  {
    float seconds = timer.getSecond() ;
    Model::Duration elapsed(Model::Duration::Second(seconds)) ;
    Input::update(seconds) ;
    
    /// ...accuracy problem...
    if (seconds != 0)
    {
      timer.reset() ;
    }
    Model::update(elapsed) ;
    Physic::update(elapsed) ;
    Action::update() ;
    ArtificialIntelligence::update(elapsed) ;
    Display::update() ;
  }

  InformationMessage("Demonstration","Sortie de la boucle principale") ;
    
  /// sortie
  ArtificialIntelligence::close() ;
  Input::close() ;
  Action::close() ;
  Display::close() ;
  Physic::close() ;
  Model::close() ;
  InformationMessage("Demonstration","Modules desinitialisÚs") ;
  Kernel::Log::close() ;
  
  return 0 ;
  
}
