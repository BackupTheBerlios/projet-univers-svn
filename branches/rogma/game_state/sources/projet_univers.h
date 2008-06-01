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


#ifndef _PROJET_UNIVERS_H_
#define _PROJET_UNIVERS_H_


/*!
  @mainpage
  
  @section Developpement
  
  ProjetUnivers
  
*/


/// ProjetUnivers est un jeu de combat spatial multi-joueur.
/*!
  Voir : 
  
  - http://www.punivers.net/
  - https://developer.berlios.de/projects/projet-univers
  
  Les diff�rents modules sont les suivants :
  
  - Base\n
    Des types C++ et des templates utilis�s dans toute l'application.\n
    Le cadre g�n�ral de l'application et notament le patron MVC.
    
  - Affichage\n
    L'affichage 3D et 2D.
  
  - Modele\n
    Le mod�le statique de donn�e de l'univers.
    
  - Controle\n
    Les controleurs.
    
  - Action\n
    Le mod�le de donn�es dynamique de l'univers, contient les diff�rentes 
    actions qui peuvent �tre r�alis�es.
    
  @dotfile architecture.dot "Architecture Globale"
  
*/ 
namespace ProjetUnivers
{}


#endif //_PROJET_UNIVERS_H_
