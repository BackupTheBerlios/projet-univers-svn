/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

using namespace ProjetUnivers ;

/*
  Demonstration program
  
  

*/
int main() {


  /// init
  Kernel::Log::init() ;
  Kernel::Parameters::load("demonstration.config") ;

  InformationMessage("Demarrage de projet univers") ;
  Model::init() ;
  Physic::init() ;
  Display::init() ;
  Action::init() ;
  
  InformationMessage("Modules initialis�s") ;

  Model::load("TestDemonstration") ;

  Kernel::Object* observer(Model::getObject("Observer")) ;
  
  Display::buildRealWorldViewPoint(observer) ;

  Physic::build(observer) ;

  Input::build(observer) ;
  Input::init() ;
  InternalMessage("Activating Viewpoint") ;

  InformationMessage("Demarrage de la boucle principale") ;

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
    
    Physic::update(elapsed) ;
    Action::update() ;
    Display::update() ;
  }

  InformationMessage("Sortie de la boucle principale") ;
    
  /// sortie
  Input::close() ;
  Action::close() ;
  Display::close() ;
  Physic::close() ;
  Model::close() ;
  InformationMessage("Modules desinitialis�s") ;
  Kernel::Log::close() ;
  
  return 0 ;
  
}
