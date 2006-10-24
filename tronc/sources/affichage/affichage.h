/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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
#ifndef _PU_AFFICHAGE_AFFICHAGE_H_
#define _PU_AFFICHAGE_AFFICHAGE_H_

#include <stddef.h>

#include <base/association.h>
#include <base/types.h>

namespace ProjetUnivers {
 
  /// Le module réalisant l'affichage des objets de Modele.
  /*!
    C'est la Vue de Modele qui réalise l'affichage à l'écran.
    
    - l'affichage possède l'écran et la racine
    - il a des points de vues qui eux possèdent des scene manager
    - un est affiché (actif), les autres sont maintenus mais ne sont pas affichés
  */ 
  namespace Affichage {
  
    class PointDeVue ;
  
    /// Initialisation de l'affichage
    /*!
      Fait le choix :
      - de la résolution d'affichage
      - de la technique d'affichage, par exemple OpenGL, DirectX
        
      Crée une fenêtre d'affichage et affiche le point de vue actif.
      
      @return FAUX si on doit arreter
      @return VRAI si on peut et si on doit continuer
    
      @remark
        c'est ici qu'on peut faire le choix de l'implantation

    */
    Base::Booleen Initialiser() ;
    
    /// Termine l'affichage
    /*!
    */
    void Terminer() ;

    /// Accès aux descripteur de la fenetre d'affichage
    /*!
      Utilisé pour initialiser le module Entrees
    */
    size_t DescripteurFenetre() ;

    /// Accès à la taille de la fenêtre
    void TailleFenetre(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top );

    /// Ajoute un point de vue.
    Base::Association<PointDeVue> AjouterPointDeVue(PointDeVue*) ;

    /// Supprime le point de vue.
    void SupprimerPointDeVue(const Base::Association<PointDeVue>&) ;
    
    
    /// 
    void DesactiverPointDeVue(const Base::Association<PointDeVue>&) ;
    
    /// Le point de vue devient celui actif.
    void ActiverPointDeVue(const Base::Association<PointDeVue>&) ;
    

    /// Rafraichi l'affichage
    /*!
      Met à jour tout ce qui doit être affiché
    */
    void Rafraichir() ;
    
  }
  
}



#endif //_PU_AFFICHAGE_AFFICHAGE_H_
