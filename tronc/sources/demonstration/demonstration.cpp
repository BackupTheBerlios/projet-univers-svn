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
#include <entrees/entrees.h>
#include <action/action.h>
#include <modele/modele.h>


/*
  Programme de démonstration
  
  

*/
int main() {


  /// initialisation
  ProjetUnivers::Base::Traceur::Initialiser() ;
  ProjetUnivers::Base::Traceur::MessageInformation("demarrage de projet univers") ;
//  ProjetUnivers::Affichage::Initialiser() ;
//  ProjetUnivers::Action::Initialiser() ;
//  ProjetUnivers::Entrees::Initialiser() ;
  ProjetUnivers::Modele::Initialiser() ;
  ProjetUnivers::Modele::Charger("TestDemonstration") ;

  /// boucle principale
//  while (! ProjetUnivers::Action::Termine())
//  {
//    ProjetUnivers::Entrees::Traiter() ;
//    ProjetUnivers::Action::Traiter() ;
//
//    ProjetUnivers::Affichage::Raffraichir() ;
//  }
    
  /// sortie
  ProjetUnivers::Modele::Terminer() ;
//  ProjetUnivers::Entrees::Terminer() ;
//  ProjetUnivers::Action::Terminer() ;
//  ProjetUnivers::Affichage::Terminer() ;
  ProjetUnivers::Base::Traceur::Terminer() ;
  
  

  
}
