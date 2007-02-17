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

#include <base/traceur.h>
#include <affichage/affichage.h>
#include <affichage/point_de_vue.h>

#include <entrees/entrees.h>
#include <action/action.h>
#include <modele/modele.h>

using namespace ProjetUnivers ;

/*
  Programme de démonstration
  
  

*/
int main() {


  /// initialisation
  Base::Traceur::init() ;
  Base::Traceur::MessageInformation("Demarrage de projet univers") ;
  Model::init() ;
  Display::init() ;
  Action::init() ;
  Entrees::init() ;

  Base::Traceur::MessageInformation("Modules initialisés") ;

  Model::load("TestDemonstration") ;

  Base::Association<Model::Object> observateur(Model::AccesObject("Observateur")) ;
  
  /// Création d'un point de vue sur ce modèle
  Base::Association<Display::ViewPoint> pdv(
      Display::addViewPoint(Display::ViewPoint::Construire(observateur))) ;

  Display::ActiverViewPoint(pdv) ;

  Base::Traceur::MessageInformation("Demarrage de la boucle principale") ;

  /// boucle principale
  while (! Action::Termine())
  {
    Entrees::Traiter() ;
    Action::Traiter() ;
    Display::update() ;
  }

  Base::Traceur::MessageInformation("Sortie de la boucle principale") ;
    
  /// sortie
  Entrees::close() ;
  Action::close() ;
  Display::close() ;
  Model::close() ;
  Base::Traceur::MessageInformation("Modules desinitialisés") ;
  Base::Traceur::close() ;
  
  return 0 ;
  
}
