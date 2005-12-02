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
    Réalisation de la partie modèle du cadre Modele/Vue/controle.
    
    Ce module contient toutes les informations sur les objets manipulés dans 
    le jeu. On y décrire les éléments du jeu sans se soucier ni 
    de leur affichage ni de ce qui déclenche leur modifications. 
    
    En d'autres termes, il s'agit d'un noyau fonctionnel.
    
  */ 
  namespace Modele 
  {}

  /*!
  @page DescriptionModele Description générale du module Modele
  
  @section Proprietes Classes de propriétés
  
  Ces classes abstraites modélisent le fait d'avoir une propriété particulière, 
  c'est le cas de :
  - Destructible
  - ObjetPhysique
  - ObjetAbstrait
  
  
  @section ClassesDeValeur Classes de valeurs
  
  Ces classes modélisent généralement des notions simples du monde :
  - Nom
  - Energie
  - Distance
  - Position
  - Orientation
  - Vitesse
  - Acceleration

  @section ModeleComposition Un modèle d'objets composés
   
  Les objets physiques élémentaires sont assemblés ensemble à l'aide de 
  contraintes.
  
  @subsection Contraintes Contraintes   
  Une contrainte relie 2 objets physiques en restreignant la façon dont ils 
  peuvent bouger l'un par rapport à l'autre, les deux objets doivent se toucher.
   
  Il existe plusieurs types de contraintes :
  - fixe; les deux objets sont physiquement reliés par des boulons l'un à 
    l'autre
  - ...
  
  @subsection Assemblages Assemblages
  Dans un assemblage chaque objet peut éventuellement bouger.
   
  Un assemblage est une composante connexe du graphe formé par : 
  - les objets comme noeuds
  - les contraintes entre objets comme arcs
   
  Un assemblage ne peut exister que si les liens de contraintes entre ses objets 
  font en sorte que forment un graphe connexe.


  @dotfile exemple_objets.dot "Exemple d'assemblage"

  La destruction d'un objet physique peut entrainer la destruction de 
  contraintes (celles où il intervient) et donc la destruction d'un 
  assemblageainsi que l'apparition de nouveaux assemblages; c'est le cas
  lorsqu'un vaisseau se casse en plusieurs morceaux (voir exemple suivant).
  
  @dotfile exemple_objets_casse.dot "L'exemple précédent cassé en 2"
  L'aile 1 a été détruite et est donc désolidarisée du reste, le moteur est 
  intact mais n'est plus relié au vaisseau.
  
  

  
  
    
  */

  
}

#endif

