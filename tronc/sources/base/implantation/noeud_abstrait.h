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

#ifndef _PU_BASE_NOEUD_ABSTRAIT_H_
#define _PU_BASE_NOEUD_ABSTRAIT_H_

#include <base/composition.h>
#include <base/association.h>


namespace ProjetUnivers {

  namespace Base {
      
    
    ///	Classe de base représentant le chainage des noeuds d'une liste.
    class NoeudAbstrait {
    public:
    
    	/// Elément suivant.
    	Composition< NoeudAbstrait > suivant ;
    
    	/// Elément précédent.
    	Association< NoeudAbstrait > precedent ;
    
    	/// Constructeur par défaut.
      /// \todo
      ///   vérifier que ce constructeur est utile..
    	NoeudAbstrait() ;
    
    	/// Classe de base donc destructeur virtuel.
    	virtual ~NoeudAbstrait() ;
    
    	/// Ajoute un noeud avant le noeud courant.
    	void AjouterAvant(NoeudAbstrait *_p_nouv_n_);
    
    	/// Ajoute un noeud après le noeud courant.
    	void AjouterApres(NoeudAbstrait *_p_nouv_n_);
    };

  }
}
#endif


