/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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
 
#ifndef FONCTION_OBJET_VALEUR_H
#define FONCTION_OBJET_VALEUR_H


#include "association.h"
#include "string.h"


namespace ProjetUnivers {

  namespace Base {

    
    
    /*
    CLASS
      FonctionObjetValeur
    
      Une fonction qui associe un élément de VALEUR à un élément de OBJET. 
      OBJET doit être une classe d'objets et VALEUR une classe de valeurs.
     
    
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
      // Ajoute un élément identifié par le nom du paramètre.
      void ajoute(const Association< OBJET >&, const VALEUR&) ;
    
      /////////////////
      // Modifie l'élément associé au paramètre de type OBJET. Si l'élément
      // n'existe pas alors cela a l'effet de add.
      void change(const Association< OBJET >&, const VALEUR&) ;
    
    
      // *******************
      // GROUP: Accès
      // *******************
    
      //////////////////
      // Accès à un élément en fonction de l'identifiant.
      VALEUR acces(const Association< OBJET >&) const ;
    
      ////////////////////////
      // Opérateur de comparaison
    	Booleen operator==(const FonctionObjetValeur< OBJET,VALEUR >& _right) const ;
    
    
    private:
    
    
    
      ////////////////////
      // Données stokées dans un tableau de listes.
      //ObValueArray< ObValueList< ObValuePair< String, VALEUR > > > dictionaire ;
    
      ///////////////////
      // Fonction de hashage.
      //static UnsignedInteger hashFonction(const String&) ;
    
      //friend class ObValueDictionaryIterator< OBJET,VALEUR> ;
    
    };
    
    #ifdef _INC_TEMP_CODE_
    #include "implantation/fonction_objet_valeur.cxx"
    #endif

  }
}



#endif
