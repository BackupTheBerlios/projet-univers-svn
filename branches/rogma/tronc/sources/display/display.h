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
 
  /// Le module r�alisant l'affichage des objets de Model.
  /*!
    C'est la Vue de Model qui r�alise l'affichage � l'�cran.
    
    - l'affichage poss�de l'�cran et la racine
    - il a des points de vues qui eux poss�dent des scene manager
    - un est affich� (actif), les autres sont maintenus mais ne sont pas affich�s
  */ 
  namespace Display {
  
    class ViewPoint ;
  
    /// Initialisation de l'affichage
    /*!
      Fait le choix :
      - de la r�solution d'affichage
      - de la technique d'affichage, par exemple OpenGL, DirectX
        
      Cr�e une fen�tre d'affichage et affiche le point de vue actif.
      
      @return FAUX si on doit arreter
      @return VRAI si on peut et si on doit continuer
    
      @remark
        c'est ici qu'on peut faire le choix de l'implantation

    */
    Base::Booleen init() ;
    
    /// Termine l'affichage
    /*!
    */
    void close() ;

    /// Acc�s aux descripteur de la fenetre d'affichage
    /*!
      Utilis� pour initialiser le module Entrees
    */
    size_t DescripteurFenetre() ;

    /// Acc�s � la taille de la fen�tre
    void TailleFenetre(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top );

    /// Ajoute un point de vue.
    Base::Association<ViewPoint> addViewPoint(ViewPoint*) ;

    /// Supprime le point de vue.
    void SupprimerViewPoint(const Base::Association<ViewPoint>&) ;
    
    
    /// 
    void DesactiverViewPoint(const Base::Association<ViewPoint>&) ;
    
    /// Le point de vue devient celui actif.
    void ActiverViewPoint(const Base::Association<ViewPoint>&) ;
    

    /// Rafraichi l'affichage
    /*!
      Met � jour tout ce qui doit �tre affich�
    */
    void update() ;
    
  }
  
}



#endif //_PU_AFFICHAGE_AFFICHAGE_H_
