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

#include "iterateur_liste.h"

namespace ProjetUnivers {

  namespace Base {
      
    IterateurListe::IterateurListe(const ListeAbstraite& _liste) 
    : IterateurListeAbstrait(_liste.premierNoeud,_liste)
    {}
    
    
    IterateurListe::IterateurListe(const ListeAbstraite& _liste,
    			       const Booleen& _inversee) 
    : IterateurListeAbstrait((! _inversee) ? _liste.premierNoeud : _liste.dernierNoeud,
    			 (ListeAbstraite &)_liste)
    {}
    
    
    
    void IterateurListe::Enlever() {
    
    
    	if (Valide()) {
    
    		liste()->nombreDElements-- ;
    
    		// pointeur sur le noeud courant après le remove :
    		Association<NoeudAbstrait> c = noeudCourant()->suivant ;
    
    		// sert à prendre le noeud courant et à la detruire :
    		Composition<NoeudAbstrait> det ;
    
    
    		// 1.on remmet les associations de possession :
    
    		if (noeudCourant() == liste()->premierNoeud) {
    		// si le noeud courant est le premier noeud
    		
    			det = liste()->premierNoeud.Liberer() ;
    			liste()->premierNoeud = noeudCourant()->suivant.Liberer() ;
    
    		} else {
    		// sinon
    
    			det = noeudCourant()->precedent->suivant.Liberer() ;
    			noeudCourant()->precedent->suivant = noeudCourant()->suivant.Liberer() ;
    		}
    
    		// 2.on remmet les associations sur le précédent :
    
    		if (noeudCourant() == liste()->dernierNoeud) 
    		// si le noeud courant est le dernier noeud
    			
    			liste()->dernierNoeud = noeudCourant()->precedent ;
    
    		else 
    		// sinon
    
    			c->precedent = noeudCourant()->precedent ;
    
    
    		// 3.l'ancien suivant est le courant :
    
    		BASE_VREF(noeudCourant) = c ;
    
    
    	} else
    
    		throw ExceptionBase("Iterlist()::remove") ;
    
    }
    
    void IterateurListe::AjouterApres(NoeudAbstrait* _n) {
    
    
    	if (Valide()) {
    
    		++liste()->nombreDElements ;
    
    		if (noeudCourant() == liste()->dernierNoeud) {
    		// si le noeud courant est le dernier noeud
    			
    			noeudCourant()->suivant = _n ;
    			_n->precedent = noeudCourant() ;
    			liste()->dernierNoeud = noeudCourant()->suivant ;
    
    		} else 
    		// sinon
    
    			noeudCourant()->AjouterApres(_n) ;
    		
    	} else
    
    		throw ExceptionBase("IterateurListe::AjouterApres") ;
    
    }
    
    void IterateurListe::AjouterAvant(NoeudAbstrait* _n) {
    
    
    	if (Valide()) {
    
    		++liste()->nombreDElements ;
    
    		if (noeudCourant() == liste()->premierNoeud) {
    		// si le noeud courant est le premier noeud
    			
    			_n->suivant = liste()->premierNoeud.Liberer() ;
    			_n->precedent = Association<NoeudAbstrait>() ;
    			liste()->premierNoeud = _n ;
    			_n->suivant->precedent = liste()->premierNoeud ;
    
    		}
    		else 
    		// sinon
    
    			noeudCourant()->AjouterAvant(_n) ;
    
    	} else
    
    		throw ExceptionBase("IterateurListe::add_before") ;
    
    }
  }
}
