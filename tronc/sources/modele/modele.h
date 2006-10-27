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

#ifndef PU_MODELE_MODELE_H_
#define PU_MODELE_MODELE_H_

#include <base/association.h>

namespace ProjetUnivers {
  
 
  /// Le module contenant le mod�le de donn�es.
  
  /*!
  @par Introduction
  
    R�alisation de la partie mod�le du cadre Modele/Vue/controle, noyau 
    fonctionnel du jeu.
    
    Ce module contient toutes les informations sur les objets manipul�s dans 
    le jeu. Ils sont d�crit sans se soucier ni de leur affichage ni de ce qui 
    d�clenche leur modifications. 
    
  @par Fonctionnement
    
    Pour l'instant, et comme tous les autres modules de ce niveau :
    - c'est un "singleton", c'est � dire qu'il n'y en a qu'un
    - son interface est "non objet"; c'est � dire que ce son des traitements 
      globaux
    
  */ 
  namespace Modele 
  {
    
  class Objet ;
  class Facette ;
  
  // ******************************************************
  /*!
    @name Initialisation/Terminaison.
  */
  // ******************************************************
  //@{        
    
    /// Initialise le module.
    void Initialiser() ;

    /// Termine le module.
    void Terminer() ;

    /// Charge un mod�le depuis le disque.
    /*!
      
    */
    void Charger(const Base::Chaine& _nom) ;

  //@}
  // ******************************************************
  /*!
    @name Op�ration sur les objets
    
    On peut ajouter un objet, surtout utile pour les objets "racines"
  */
  // ******************************************************
  // @{

      
    /// Enregistre un objet dans le gestionnaire.
    Base::Association<Objet> Ajouter(Objet*) ;

    /// Enregistre un objet dans le gestionnaire.
    Base::Association<Objet> Enregistrer(const Base::Association<Objet>&) ;

    /// Supprime un objet.
    void Enlever(const Base::Association<Objet>&) ;


  //@}
  // ******************************************************
  /*!
    @name Acc�s aux objets et facettes.
  */
  // ******************************************************
  //@{
    
    /// Acc�s � un objet par son nom
    Base::Association<Objet> AccesObjet(const Base::Chaine& _nom) ;



  //@}


    
  }

  /*!
  @page DescriptionModele Description g�n�rale du module Modele
  
  @section Proprietes Classes de propri�t�s
  
  Ces classes abstraites mod�lisent le fait d'avoir une propri�t� particuli�re, 
  c'est le cas de :
  - Destructible
  - ObjetPhysique
  - ObjetAbstrait
  
  
  @section ClassesDeValeur Classes de valeurs
  
  Ces classes mod�lisent g�n�ralement des notions simples du monde :
  - Nom
  - Energie
  - Distance
  - Position
  - Orientation
  - Vitesse
  - Acceleration

  @section ModeleComposition Un mod�le d'objets compos�s
   
  Les objets physiques �l�mentaires sont assembl�s ensemble � l'aide de 
  contraintes.
  
  @subsection Contraintes Contraintes   
  Une contrainte relie 2 objets physiques en restreignant la fa�on dont ils 
  peuvent bouger l'un par rapport � l'autre, les deux objets doivent se toucher.
   
  Il existe plusieurs types de contraintes :
  - fixe; les deux objets sont physiquement reli�s par des boulons l'un � 
    l'autre
  - ...
  
  @subsection Assemblages Assemblages
  Dans un assemblage chaque objet peut �ventuellement bouger.
   
  Un assemblage est une composante connexe du graphe form� par : 
  - les objets comme noeuds
  - les contraintes entre objets comme arcs
   
  Un assemblage ne peut exister que si les liens de contraintes entre ses objets 
  font en sorte que forment un graphe connexe.


  @dotfile exemple_assemblage.dot "Exemple d'assemblage"

  La destruction d'un objet physique peut entrainer la destruction de 
  contraintes (celles o� il intervient) et donc la destruction d'un 
  assemblageainsi que l'apparition de nouveaux assemblages; c'est le cas
  lorsqu'un vaisseau se casse en plusieurs morceaux (voir exemple suivant).
  
  @dotfile exemple_assemblage_casse.dot "L'exemple pr�c�dent cass� en 2"
  L'aile 1 a �t� d�truite et est donc d�solidaris�e du reste, le moteur est 
  intact mais n'est plus reli� au vaisseau.
  
  @dotfile gestion_objet_assemblage.dot
    
  */

  
}

#endif

