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

#include <map>

#include <base/association.h>


namespace ProjetUnivers {

  namespace Base {

    ///  Une fonction de Valeur vers Objet en composition.
      
    /*!
      Valeur doit être une classe de valeur, et Objet une classe d'objet. 

      Cette fonction est en composition : lorsqu'elle est detruite, les 
      éléments de Objet le sont aussi.
      @par Test
        Testé le 02/04/2006 avec TestFonctionCompositionValeurObjet :
        - Constructeur
        - Ajouter
        - Acces (à un existant et à un non existant)
 

    */
    template <typename Valeur, class Objet > 
              class FonctionCompositionValeurObjet {
    public:
    
    /// @name Construction
    // @{      
    
    
      /// Constructeur.
      FonctionCompositionValeurObjet() ; 

      /// Destructeur.
      ~FonctionCompositionValeurObjet() ; 


      /// Ajoute un élément.
      void Ajouter(const Valeur& , Objet*) ;
    
      /// Modifie l'élément associé à Vakeur.
      /*!
        Si l'élément n'existe pas dans la fonction alors cela a l'effet de 
        Ajouter.
      */
      void Modifier(const Valeur&, Objet*) ;

      /// Libère et enlève l'image de @c _element.
      Objet* Liberer(const Valeur& _element) ;
      Objet* Enlever(const Valeur& _element) ;
    
    
    // @}
    /// @name Accès
    // @{      
  

      /// Accès à un élément en fonction de l'identifiant.
      Association<Objet>  operator[](const Valeur&) const ;
    
      /// Opérateur de comparaison
    	Booleen operator==(
        const FonctionCompositionValeurObjet<Valeur,Objet >& _right) 
        const ;
    
    // @}


    private:
    
      std::map<Valeur,Objet*> fonction ;
    
    };

  }
}

#include <base/implantation/fonction_composition_valeur_objet.cxx>


#endif
