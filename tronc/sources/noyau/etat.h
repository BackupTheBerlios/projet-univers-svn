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


namespace ProjetUnivers {

  namespace Noyau {
  
    #include "composition.h"
    #include "ensemble_composition.h"
  
    /*
    CLASS
      Etat
      
      Classe abstraite des �tats d'une partie.
      
    EXPLICATION
      Un �tat caract�rise le fait d'�tre dans une certaine �tape du 
      d�roulement d'une partie, il s'agit par exemple du fait d'�tre dans un 
      menu, ou dans une certaine situation au cours d'une partie. 
       
      Un �tat peut avoir des sous-�tats, mais un seul est alors activ�. 
       
      Un �tat poss�de une donn�e utilisateur, qui contient les 
      informations fonctionnelles. 
       
      Un �tat de jeu poss�de aussi une vue qui sera affich�e � l'�cran.
    */
    class Etat {
    public:
    
    
    
    
    protected:
    
      ////////////////////
      // Sous �tat �ventuels.
      EnsembleComposition< EtatDeJeu > sousEtats ;
            
    
      ///////////////////
      // Donn�e utilisateur.
      Composition< Modele > modele ;
      
      ///////////////////
      //
      Composition<Controle> controle ;
      
      //////////////////
      // Ce qu'il faut afficher � l'�cran pour cet �tat.
      Composition< Vue > vue ;
    
    };
  
  }
}