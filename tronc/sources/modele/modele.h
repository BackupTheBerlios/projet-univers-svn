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

#ifndef _MODELE_MODELE_H_
#define _MODELE_MODELE_H_

namespace ProjetUnivers {
  
 
  /// Le module contenant le modèle de données.
  
  /*!
    Réalisation de la partie modèle du cadre :
    
      - modèle (Modele), 
      - vue (Vue), 
      - contrôleur (Controle)
    
    Ce module contient toutes les informations sur les objets manipulés dans 
    le jeu. L'idée est d'y décrire les éléments du jeu sans se soucier ni 
    de leur affichage ni de ce qui déclenche leur modifications. 
    
    En d'autres termes, il s'agit d'un noyau fonctionnel.
     
  */ 
  namespace Modele 
  {}

  
}

#endif

