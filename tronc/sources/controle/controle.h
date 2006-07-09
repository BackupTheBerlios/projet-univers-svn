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

#ifndef PU_CONTROLE_H_
#define PU_CONTROLE_H_

namespace ProjetUnivers {
  
 
  /// Le module réalisant le controle des objets de Modele.
  
  /*!
    Réalisation de la partie vue du cadre
    
    modèle (Modele), vue (Affichage), contrôleur (Controle)
    
    Ce module reçoit les informations des entrées et modifie Affichage et 
    Modele.
    
    @deprecated
     
  */ 
  namespace Controle 
  {
      
    class Action ;
    
    void Initialiser() ;

    void Terminer() ;
    
    /// Execute les actions en cours.
    /*!
      @post
        Il n'y a plus d'actions à traiter
    */
    void Traiter() ;
    
    void Ajouter(Action*) ;
  }

  
}

#endif //PU_CONTROLE_H_
