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


#ifndef _PU_BASE_TAMPON_LISTE_ASSOCIATION_H_
#define _PU_BASE_TAMPON_LISTE_ASSOCIATION_H_

#include "association.h"
#include "iterateur_tampon_liste_association.h"


namespace ProjetUnivers {

  namespace Base {
  
    
    template <class OBJET> class ListeAssociation ;
    
    
    /*
    CLASS
      TamponListeAssociation
    
      Classe g�n�rique des listes internes d'association. Cette classe ne doit 
      pas �tre utilis�e directement. D'ailleurs tout est priv� pour emp�cher 
      de vouloir l'utiliser. 
    
      Elle permet de partager les listes en association, et de construire des 
      listes temporaires qui ne sont pas d�truites lorsqu'on it�re dessus.
    
    
    
    */
    template <class OBJET> class TamponListeAssociation 
      : public ListeAbstraite {
    
    private:
    
    
      // ********************
      // GROUP: Constructeurs
      // ********************
    
    
      //////////////
      // Constructeur.
      TamponListeAssociation() ;
    
      //////////////
      //Destructeur.
      ~TamponListeAssociation() ;
    
      //////////////
      // Constructeur de copie.
      TamponListeAssociation(const TamponListeAssociation< OBJET >& _l) ;
    
      ///////////////
      // Ajoute un nouvel �l�ment en d�but de liste.
      void AjouterEnTete(const Association< OBJET > _elt) ;
    
      ///////////////
      // Ajoute un nouvel �l�ment en fin de liste.
      void AjouterEnQueue(const Association< OBJET > _elt) ;
    
      ////////////////
      // Obtient une r�f�rence, et donc augmente le nombre de r�f�rencants.
      TamponListeAssociation< OBJET >* Prendre() ;
    
      ////////////////
      // Relache une r�f�rence et renvoie 
      // vrai s'il faut la d�truire.
      Booleen Laisser() ;
    
      
    
    
      // ***********************
      // GROUP: M�thodes d'acc�s
      // ***********************
    
    
      ///////////////////
      // Determine si _el fait partie de la liste et renvoie sa position.
      unsigned int TrouverPosition(const Association< OBJET >& _el) const ;
    
      //////////////////
      // Enl�ve l'�l�ment � la position _pos;
      void Enlever(unsigned int _pos) ;
    
      ////////////////////
      // renvoie le nombre de r�f�rences.
      unsigned int NombreDeReferences() const ;
      
      
      // ********************
      // GROUP: Attributs
      // ********************
    
     
      ////////////////////
      // Nombre de r�f�rences � la liste, 
      // lorsque ce nombre tombe � z�ro, il y a destruction.
      unsigned int nombreDeReferences ;
    
      ///////////////
      // Ce sont les seules classes qui ont le droit d'utiliser 
      // les fonctionnalit�s de ce tampon
      friend class ListeAssociation<OBJET> ;
      friend class IterateurListeAssociation<OBJET> ;
    
    };
    
    
    
    // inclure le code des template dans la spec 
    // n�cessaire sur certains compilos
    #include "tampon_liste_association.cxx"

  }
}


#endif
