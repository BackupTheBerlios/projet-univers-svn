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


#ifndef _PU_BASE_ITERATEUR_TAMPON_LISTE_ASSOCIATION_H_
#define _PU_BASE_ITERATEUR_TAMPON_LISTE_ASSOCIATION_H_



#include "iterateur_liste.h"
#include "noeud_association.h"
#include "association_virtuelle.h"

namespace ProjetUnivers {

  namespace Base {
      
    
    template <class OBJET> class TamponListeAssociation ;
    
    /*
    CLASS
      IterateurTamponListeAssociation
    
      Classe g�n�rique fournissant un it�rateur sur les listes AssociationListBuffer.
    
    */
    template <class OBJET> class IterateurTamponListeAssociation
      : public IterateurListe {
    
    public: 
    
      // **********************************************
      // GROUP: Constructeur, m�thodes de modifications
      // **********************************************
    
    
      //////////////////
      // Constructeur, prenant la liste sur laquelle on va it�rer.
      IterateurTamponListeAssociation(const TamponListeAssociation<OBJET> &_l);
    
    
      ////////////
      // Ajoute un �l�ment apr�s.
      void AjouterApres(const Association< OBJET > _n) ;
    
      /////////////
      // Ajoute un �l�ment avant.
      void AjouterAvant(const Association< OBJET > _n) ;
    
    
      // ***********************
      // GROUP: M�thodes d'acc�s
      // ***********************
    
      ///////////////
      // Renvoie l'�l�ment courant en association.
      operator Association< OBJET >() ;
    
      ///////////////
      // Renvoie l'�l�ment courant en r�f�rence.
      operator const OBJET&() ;
  
      /////////////
      // Acc�s � l'objet courant.
      OBJET& operator *() const ;
    
      /////////////
      // Op�rateur de d�r�f�renciation.
      OBJET* operator ->() const ;
    
    
    
    protected:
    
      /////////////
      // Conversion dynamique de noeudCourant qui est un NoeudAbstrait 
      // en un NoeudAssociation<OBJET>.
      UTILISATION_ASSOCIATION_VIRTUELLE(NoeudAssociation<OBJET>,noeudCourant)
    
    
    };
    
    
    // inclure le code des template dans la spec 
    // n�cessaire sur certains compilos
    #ifdef _INC_TEMP_CODE_
      #include "iterateur_tampon_liste_association.cxx"
    #endif
  }
}

#endif 
