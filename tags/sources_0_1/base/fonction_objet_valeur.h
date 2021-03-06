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
 
#ifndef FONCTION_OBJET_VALEUR_H
#define FONCTION_OBJET_VALEUR_H


#include "association.h"
#include "string.h"


namespace ProjetUnivers {

  namespace Base {

    
    
    /*
    CLASS
      FonctionObjetValeur
    
      Une fonction qui associe un �l�ment de VALEUR � un �l�ment de OBJET. 
      OBJET doit �tre une classe d'objets et VALEUR une classe de valeurs.
     
    
    */
    template <class OBJET, class VALEUR > class FonctionObjetValeur {
    public:
    
      // *******************
      // GROUP: Constructeur
      // *******************
    
    
      //////////////////
      // Constructeur.
      FonctionObjetValeur() ;
    
      ///////////////
      // Constructeur de copie.
      FonctionObjetValeur(const FonctionObjetValeur& _v);
    
      
      // *******************
      // GROUP: Modification
      // *******************
    
      //////////////////
      // Ajoute un �l�ment identifi� par le nom du param�tre.
      void ajoute(const Association< OBJET >&, const VALEUR&) ;
    
      /////////////////
      // Modifie l'�l�ment associ� au param�tre de type OBJET. Si l'�l�ment
      // n'existe pas alors cela a l'effet de add.
      void change(const Association< OBJET >&, const VALEUR&) ;
    
    
      // *******************
      // GROUP: Acc�s
      // *******************
    
      //////////////////
      // Acc�s � un �l�ment en fonction de l'identifiant.
      VALEUR acces(const Association< OBJET >&) const ;
    
      ////////////////////////
      // Op�rateur de comparaison
    	Booleen operator==(const FonctionObjetValeur< OBJET,VALEUR >& _right) const ;
    
    
    private:
    
    
    
      ////////////////////
      // Donn�es stok�es dans un tableau de listes.
      //ObValueArray< ObValueList< ObValuePair< String, VALEUR > > > dictionaire ;
    
      ///////////////////
      // Fonction de hashage.
      //static UnsignedInteger hashFonction(const String&) ;
    
      //friend class ObValueDictionaryIterator< OBJET,VALEUR> ;
    
    };
    
#include "implantation/fonction_objet_valeur.cxx"

  }
}



#endif
