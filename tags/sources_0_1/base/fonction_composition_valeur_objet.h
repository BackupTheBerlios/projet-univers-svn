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


 
#ifndef _PU_BASE_FONCTION_COMPOSITION_VALEUR_OBJET_H_
#define _PU_BASE_FONCTION_COMPOSITION_VALEUR_OBJET_H_


#include "association.h"


namespace ProjetUnivers {

  namespace Base {

    /*
    CLASS
      FonctionCompositionValeurObjet
    
      Une fonction, au sens mathématique, qui associe à tout élément de VALEUR 
      un élément de OBJET. 
      
      VALEUR doit être une classe de valeur, et OBJET une classe d'objet. 
      
      Cette fonction est en composition : lorsqu'elle est detruite, les 
      éléments de OBJET le sont aussi.
      
    
    */
    template <class VALEUR, class OBJET > 
              class FonctionCompositionValeurObjet {
    public:
    
      // *******************
      // GROUP: Construction
      // *******************
    
    
      //////////////////
      // Constructeur.
      FonctionCompositionValeurObjet() ; 

      //////////////////
      // Ajoute un élément.
      void Ajouter(const VALEUR& , const OBJET*) ;
    
      /////////////////
      // Modifie l'élément associé à VALEUR. Si l'élément
      // n'existe pas dans la fonction alors cela a l'effet de add.
      void Modifier(const VALEUR&, const OBJET&) ;
    
    
      // *******************
      // GROUP: Accès
      // *******************
    

      //////////////////
      // Accès à un élément en fonction de l'identifiant.
      Association< OBJET > Image(const VALEUR&) const ;
    
      ////////////////////////
      // Opérateur de comparaison
    	Booleen operator==(
        const FonctionCompositionValeurObjet< VALEUR, OBJET >& _right) 
        const ;
    
    
    private:
    
    
    
    
    };
    
    #include "fonction_composition_valeur_objet.cxx"


  }
}



#endif
