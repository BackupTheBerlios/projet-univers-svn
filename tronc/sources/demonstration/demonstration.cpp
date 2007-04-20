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
#include <model/model.h>
#include <model/duration.h>
#include <display/display.h>
#include <action/action.h>
#include <input/input.h>
#include <physic/physic.h>

using namespace ProjetUnivers ;

/*
  Programme de d�monstration
  
  

*/
int main() {


  /// initialisation
//  Kernel::Log::init() ;
  Kernel::Log::InformationMessage("Demarrage de projet univers") ;
  Model::init() ;
  Physic::init() ;
  Display::init() ;
  Action::init() ;
  Input::init() ;

  Kernel::Log::InformationMessage("Modules initialis�s") ;

  Model::load("TestDemonstration") ;

  Kernel::Object* observer(Model::getObject("Observer")) ;
  
  /// Cr�ation d'un point de vue sur ce mod�le
  Display::buildRealWorldViewPoint(observer) ;
  Physic::buildRealWorldViewPoint(observer) ;
  Physic::init() ;
  
  Kernel::Log::InternalMessage("Activating Viewpoint") ;

  Kernel::Log::InformationMessage("Demarrage de la boucle principale") ;

  Kernel::Timer timer ;

  /// boucle principale
  while (! Action::finished())
  {
    Input::update() ;
    Model::Duration elapsed(Model::Duration::Second(timer.getSecond())) ;
    timer.reset() ;
    Physic::update(elapsed) ;
    Action::update() ;
    Display::update() ;
  }

  Kernel::Log::InformationMessage("Sortie de la boucle principale") ;
    
  /// sortie
  Input::close() ;
  Action::close() ;
  Display::close() ;
  Physic::close() ;
  Model::close() ;
  Kernel::Log::InformationMessage("Modules desinitialis�s") ;
//  Kernel::Log::close() ;
  
  return 0 ;
  
}
