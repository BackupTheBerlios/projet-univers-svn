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
      
      Classe abstraite des �tats d'une partie.
      
    EXPLICATION
      Un �tat caract�rise le fait d'�tre dans une certaine �tape du 
      d�roulement d'une partie, il s'agit par exemple 
      du fait d'�tre dans un menu, 
      ou dans une certaine situation au cours d'une partie. 
       
      Un �tat peut avoir des sous-�tats, mais un seul est alors activ�. 
       
      Un �tat poss�de une donn�e utilisateur, qui contient les 
      informations fonctionnelles. 
       
      Un �tat de jeu poss�de aussi une vue qui sera affich�e � l'�cran.
      
      Un �tat a des contr�les qui sont ex�cut�s p�riodiquement.
    */
    class Etat {
    public:
    
      
    
    
    protected:
    
      ////////////////////
      // Sous �tat �ventuels.
      EnsembleComposition< Etat > sousEtats ;
            
      //////////////////////
      // Sur �tat �ventuel.
      Association< Etat > surEtat ;
      
      ///////////////////
      // Donn�e utilisateur.
      Composition< Modele > modele ;
      
      ///////////////////
      // Les contr�les � appliquer dans l'�tat, ils sont appel�s p�riodiquement.
      EnsembleComposition< Controle > controle ;
      
      //////////////////
      // Ce qu'il faut afficher � l'�cran pour cet �tat. 
      // Il peut ne pas y en avoir.
      Composition< Vue > vue ;
    
    };
  
  }
}

#endif
