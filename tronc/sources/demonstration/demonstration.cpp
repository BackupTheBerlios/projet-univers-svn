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
#include <kernel/model.h>
#include <kernel/parameters.h>
#include <kernel/timer.h>

#include <artificial_intelligence/artificial_intelligence.h>
#include <display/display.h>
#include <input/input.h>
#include <gui/gui.h>
#include <model/model.h>
#include <physic/physic.h>
#include <sound/sound.h>


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

  Model::start() ;
  Physic::start() ;
  Sound::start() ;
  ArtificialIntelligence::start() ;
  Display::start(Display::ChooseRenderer) ;
  Input::start() ;
  GUI::start() ;
  
  
  InformationMessage("Demonstration","Starting of projet univers") ;
  
  std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
  model->init() ;
  Model::load(getModelName(),model.get()) ;

  
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
