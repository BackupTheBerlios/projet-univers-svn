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

#ifndef _PU_BASE_NOEUD_ASSOCIATION_H_
#define _PU_BASE_NOEUD_ASSOCIATION_H_

#include "noeud_abstrait.h"


namespace ProjetUnivers {

  namespace Base {
      
    
    template <class OBJET> class IterateurListeAssociation ;
    template <class OBJET> class IterateurTamponListeAssociation ;
   
    /*
    CLASS
      NoeudAssociation
    
      Classe représentant un noeud d'une liste en association.
    */
    template <class OBJET> class NoeudAssociation 
      : public NoeudAbstrait {
    
     public:
    
      /////////////
      // Constructeur.
      NoeudAssociation(const Association< OBJET > _elt) ;

    private:
    
      ////////////
      // Elément.
      Association< OBJET > element ;

      friend class IterateurListeAssociation< OBJET > ;
      friend class IterateurTamponListeAssociation<OBJET> ;
    
    };
    
    #ifdef _INC_TEMP_CODE_
    #include "noeud_association.cxx"
    #endif
  }
}
#endif


