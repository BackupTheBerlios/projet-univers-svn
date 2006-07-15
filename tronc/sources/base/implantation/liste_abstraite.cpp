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

#include <base/implantation/liste_abstraite.h>
#include <base/implantation/iterateur_liste.h>
#include <base/implantation/noeud_abstrait.h>

namespace ProjetUnivers {

  namespace Base {
    
    namespace Implantation {
        
      ListeAbstraite::ListeAbstraite()
        :premierNoeud(),dernierNoeud(),nombreDElements(0)
      {}
      
      ListeAbstraite::~ListeAbstraite() 
      {}
      
      void ListeAbstraite::AjouterEnTete(NoeudAbstrait* _n) {
      
        ++nombreDElements ;
      
        if (dernierNoeud) {
      
          _n->suivant = premierNoeud.Liberer() ;
          premierNoeud = _n ;
          _n->suivant->precedent = premierNoeud ;
      	
        } else {
      
          premierNoeud = _n ;
          dernierNoeud = premierNoeud ;
        }
      
      }
      
      
      void ListeAbstraite::AjouterEnQueue(NoeudAbstrait* _n) {
      
        ++nombreDElements ;
      
        if (dernierNoeud) {
      
          _n->precedent = dernierNoeud ;
          dernierNoeud->suivant = _n ;
          dernierNoeud = dernierNoeud->suivant ;
      
        } else {
      
          premierNoeud = _n ;
          dernierNoeud = premierNoeud ;
        }
      }
      
      unsigned int ListeAbstraite::NombreDElements() const {
      
        return nombreDElements ;
      
      }
      
      void ListeAbstraite::Vider() {
      
        for(IterateurListe i(*this) ; i.Valide() ; )
      
          i.Enlever() ;
      
      }
    }
  }
}
