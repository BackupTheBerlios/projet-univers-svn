/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PU_BASE_IMPLANTATION_ITERATEUR_LISTE_H_
#define _PU_BASE_IMPLANTATION_ITERATEUR_LISTE_H_

#include <base/implantation/iterateur_liste_abstrait.h>


namespace ProjetUnivers {

  namespace Base {
      
    namespace Implantation {
        
      class NoeudAbstrait ;
      class ListeAbstraite ;
      
      
      ///	Classe des it�rateurs non constants sur les listes
      
      /// EXPLICATION
      ///	Cet it�rateur est � utiliser lorsqu'on d�sire modifier 
      ///	la structure de la liste.
      class IterateurListe : public IterateurListeAbstrait {
      
      public:
      
      	/// Constructeur.
      	IterateurListe(const ListeAbstraite& _list) ;
      
      	/// Constructeur.
      	IterateurListe(const ListeAbstraite& _list, const Booleen& _inversee) ;
      
      	/// Enl�ve le noeud courant.
      	void Enlever() ;
      
      protected:
      
        /// Ajoute un noeud apr�s.
        void AjouterApres(NoeudAbstrait* _n) ;
      
        /// Ajoute un noeud avant.
        void AjouterAvant(NoeudAbstrait* _n) ;
      
      };
      
    }
  }
}

#endif


