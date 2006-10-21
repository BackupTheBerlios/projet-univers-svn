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
  Base::Traceur::Initialiser() ;
  Base::Traceur::MessageInformation("Demarrage de projet univers") ;
  Modele::Initialiser() ;
  Affichage::Initialiser() ;
  Action::Initialiser() ;
  Entrees::Initialiser() ;

  Base::Traceur::MessageInformation("Modules initialisés") ;

  Modele::Charger("TestDemonstration") ;

  Base::Association<Modele::Objet> observateur(Modele::AccesObjet("Observateur")) ;
  
  /// Création d'un point de vue sur ce modèle
  Base::Association<Affichage::PointDeVue> pdv(
      Affichage::AjouterPointDeVue(Affichage::PointDeVue::Construire(observateur))) ;

  Affichage::ActiverPointDeVue(pdv) ;

  Base::Traceur::MessageInformation("Demarrage de la boucle principale") ;

  /// boucle principale
  while (! Action::Termine())
  {
    Entrees::Traiter() ;
    Action::Traiter() ;
    Affichage::Raffraichir() ;
  }

  Base::Traceur::MessageInformation("Sortie de la boucle principale") ;
    
  /// sortie
  Entrees::Terminer() ;
  Action::Terminer() ;
  Affichage::Terminer() ;
  Modele::Terminer() ;
  Base::Traceur::MessageInformation("Modules desinitialisés") ;
  Base::Traceur::Terminer() ;
  
  return 0 ;
  
}
