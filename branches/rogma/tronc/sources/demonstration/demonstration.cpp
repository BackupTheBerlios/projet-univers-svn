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
#include <display/display.h>
#include <display/view_point.h>

#include <input/entrees.h>
#include <action/action.h>
#include <model/model.h>

using namespace ProjetUnivers ;

/*
  Programme de démonstration
  
  

*/
int main() {


  /// initialisation
  Kernel::Log::init() ;
  Kernel::Log::InformationMessage("Demarrage de projet univers") ;
  Model::init() ;
  Display::init() ;
  Action::init() ;
  Input::init() ;

  Kernel::Log::InformationMessage("Modules initialisés") ;

  Model::load("TestDemonstration") ;

  Model::Object* observer(Model::getObject("Observer")) ;
  
  /// Création d'un point de vue sur ce modèle
  Kernel::Association<Display::ViewPoint> pdv(
      Display::addViewPoint(Display::ViewPoint::build(observateur))) ;

  Display::activateViewPoint(pdv) ;

  Kernel::Log::InformationMessage("Demarrage de la boucle principale") ;

  /// boucle principale
  while (! Action::finished())
  {
    Input::update() ;
    Action::update() ;
    Display::update() ;
  }

  Kernel::Log::InformationMessage("Sortie de la boucle principale") ;
    
  /// sortie
  Input::close() ;
  Action::close() ;
  Display::close() ;
  Model::close() ;
  Kernel::Log::InformationMessage("Modules desinitialisés") ;
  Kernel::Log::close() ;
  
  return 0 ;
  
}
