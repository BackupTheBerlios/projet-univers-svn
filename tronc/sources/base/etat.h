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

#ifndef _PU_BASE_ETAT_H_
#define _PU_BASE_ETAT_H_


#include "composition.h"
#include "ensemble_composition.h"


namespace ProjetUnivers {

  namespace Base {
  
  
    /*
    CLASS
      Etat
      
      Classe abstraite des états d'une partie.
      
    EXPLICATION
      Un état caractérise le fait d'être dans une certaine étape du 
      déroulement d'une partie, il s'agit par exemple 
      du fait d'être dans un menu, 
      ou dans une certaine situation au cours d'une partie. 
       
      Un état peut avoir des sous-états, mais un seul est alors activé. 
       
      Un état possède une donnée utilisateur, qui contient les 
      informations fonctionnelles. 
       
      Un état de jeu possède aussi une vue qui sera affichée à l'écran.
      
      Un état a des contrôles qui sont exécutés périodiquement.
    */
    class Etat {
    public:
    
      
    
    
    protected:
    
      ////////////////////
      // Sous état éventuels.
      EnsembleComposition< Etat > sousEtats ;
            
      //////////////////////
      // Sur état éventuel.
      Association< Etat > surEtat ;
      
      ///////////////////
      // Donnée utilisateur.
      Composition< Modele > modele ;
      
      ///////////////////
      // Les contrôles à appliquer dans l'état, ils sont appelés périodiquement.
      EnsembleComposition< Controle > controle ;
      
      //////////////////
      // Ce qu'il faut afficher à l'écran pour cet état. 
      // Il peut ne pas y en avoir.
      Composition< Vue > vue ;
    
    };
  
  }
}

#endif
