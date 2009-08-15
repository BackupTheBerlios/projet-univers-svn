/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

#include <artificial_intelligence/artificial_intelligence.h>
#include <display/display.h>
#include <input/input.h>
#include <gui/gui.h>
#include <model/model.h>
#include <physic/physic.h>
#include <sound/sound.h>


using namespace ProjetUnivers ;

/*
  Test program for performances

  places n ships each one in a different team and simulate during a period

*/
int main(int argc,char** argv)
{
  /// init
  Kernel::Parameters::load("demonstration.config") ;
  Kernel::Log::init() ;

  try
  {
    TCLAP::CmdLine cmd("Command description message",' ',"1") ;
    TCLAP::ValueArg<int> number("n","number","number of ships",true,5,"integer") ;
    cmd.add(number) ;

    TCLAP::ValueArg<int> frame("f","frame","number of frame",false,1000,"integer") ;
    cmd.add(frame) ;

    cmd.parse(argc,argv) ;
    Kernel::Parameters::setValue<float>("Test","numberOfShips",number.getValue()) ;
    Kernel::Parameters::setValue<float>("Test","NumberOfFrame",frame.getValue()) ;
  }
  catch(...)
  {
  }


  Model::start() ;
  Physic::start() ;
  Sound::start() ;
  ArtificialIntelligence::start() ;
  Display::start() ;
  Input::start() ;
  GUI::start() ;

  std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
  model->init() ;
  Model::load("test",model.get()) ;

  int number_of_frame = (int)Kernel::Parameters::getValue<float>("Test","NumberOfFrame",3) ;

  Kernel::Timer timer ;
  int n = 0 ;

  Kernel::Timer global_timer ;

  while (n <= number_of_frame)
  {
    float seconds = timer.getSecond() ;
    if (seconds > 0)
    {
      timer.reset() ;
      model->update(seconds) ;
      ++n ;
    }
  }

  std::cout << global_timer.getSecond() << std::endl ;

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


