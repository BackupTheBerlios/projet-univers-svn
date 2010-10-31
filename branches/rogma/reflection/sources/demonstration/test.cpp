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
#include <kernel/implementation/profiler.h>

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

  places n ships each one in a different team and simulate during a given period

  -n number of ships
  -t duration of simulation
  -p if set print profile information
  at the end display fps

*/
int main(int argc,char** argv)
{
  /// init
  Kernel::Parameters::load("demonstration.config") ;
  Kernel::Log::init() ;

  bool print_profile = false ;
  bool round_mode = false ;
  float round_duration = 0.1 ;

  try
  {
    TCLAP::CmdLine cmd("Command description message",' ',"1") ;

    // declare options
    TCLAP::SwitchArg profile("p","profile","print profiling information") ;
    cmd.add(profile) ;

    TCLAP::SwitchArg round("r","round","execute simulation in a round by round mode") ;
    cmd.add(round) ;

    TCLAP::ValueArg<float> rd("d","duration","duration of a round",false,0.1,"float") ;
    cmd.add(rd) ;

    TCLAP::ValueArg<int> number("n","number","number of ships",false,5,"integer") ;
    cmd.add(number) ;

    TCLAP::ValueArg<int> time("t","time","duration in seconds or in round (default 1)",false,1,"integer") ;
    cmd.add(time) ;

    // get values
    cmd.parse(argc,argv) ;
    Kernel::Parameters::setValue<float>("Test","numberOfShips",number.getValue()) ;
    Kernel::Parameters::setValue<float>("Test","Duration",time.getValue()) ;
    print_profile = profile.getValue() ;
    round_mode = round.getValue() ;
    round_duration = rd.getValue() ;
  }
  catch(...)
  {
    return 1 ;
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

  int duration = (int)Kernel::Parameters::getValue<float>("Test","Duration",1) ;

  if (print_profile)
    Kernel::Implementation::Profiler::reset() ;

  int n = 0 ;

  if (round_mode)
  {
    while (n < duration)
    {
      model->update(round_duration) ;
      ++n ;
    }
//    std::cout << model->toGraphviz() ;
  }
  else
  {
    Kernel::Timer global_timer ;
    Kernel::Timer timer ;

    while (global_timer.getSecond() < duration)
    {
      float seconds = timer.getSecond() ;
      if (seconds > 0)
      {
        timer.reset() ;
        model->update(seconds) ;
        ++n ;
      }
    }
    std::cout << "number of frame per second " << (float)n/duration << std::endl ;
  }


  if (print_profile)
    Kernel::Implementation::Profiler::print() ;

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


