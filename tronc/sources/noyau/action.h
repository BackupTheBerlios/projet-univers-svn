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

#ifndef _PU_NOYAU_ACTION_H_
#define _PU_NOYAU_ACTION_H_

#include "association.h"

namespace ProjetUnivers {

  namespace Noyau {

    using namespace ProjetUnivers::Base ;

    class Modele ;
    
    
    /*
    CLASS
      Action
      
      Une action de jeu pouvant être réalisée par un joueur ou une IA.
      
    TYPE_DE_CLASSE
      Objet
      Abstrait
    */
    class Action {
    public:
      
      
      // *************************
      // GROUP: Méthode principale
      // *************************
      
      
      ////////////////////////
      // Réalise l'action sur le modèle.
      virtual void Realiser(const Association< Modele >&) const = 0 ;
      
      // remarque, peut être il faudrait obtenir le résultat de l'action en 
      // retours...
      
      
      
      // *******************
      // GROUP: Destructeur
      // *******************
      
      
      //////////////////
      // Classe abstraite donc destructeur virtuel.
      virtual ~Action() ;
    

      
    
    protected:
    
      // *******************
      // GROUP: Constructeur
      // *******************
 
 
      //////////////////////
      // Classe abstraite donc constructeur protégé.
      Action() ;
    
    
    
    
    };
  }
}

#endif

