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

#ifndef _PU_MODELE_TYPE_COMPOSANT_H_
#define _PU_MODELE_TYPE_COMPOSANT_H_

#include <modele/type_de_bien.h>

namespace ProjetUnivers {

  namespace Modele {
    
    
      
    /// Représente le type d'un composant.
    
    /*!
      
      Un Composant représente une instance réélle d'un TypeDeComposant. C'est 
      la même différence qu'entre une voiture donnée (la miènne par exemple) et 
      le modèle de cette voiture (une renault clio modèle xxx). 
    
      Type de classe
        - Objet
        - Abstrait
    */
    class TypeDeComposant : public TypeDeBien {
    public:

      /// Simule l'action de ce type de composant.
      /*
        Simule l'action pendant une certaine durée d'une instance de ce type de 
        composant étant dans certain état.
        
        
      */
      virtual void Simuler(const EtatComposant& etat, const Duree& _duree) = 0 ;


    
      /// Les différentes catégories d'un type de composant.
      
      /*!
        \todo
          supprimer et remplacer par des sous classes...
      */
      typedef enum 
        {
          /// catégorie des moteurs
          Moteur, 
          
          /// catégorie des lasers
          Laser,
          
          /// catégories des commandes.
          
          /*!
            Boutons et autres manches à balais.
          */
          Commande,
          
          /// Générateur d'énergie.
          GenerateurEnergie,
          
          /// Générateur de bouclier.
          GenerateurBouclier, 
          
          /// Morceau de coque.
          
          /*!
            C'ets une catégorie assez générale où on peut mettre tout ce qu'on 
            ne sait pas où mettre.
          */
          MorceauCoque, 
          
          /// Répartiteur d'énérgie.
          
          /*!
            Distribue l'énérgie produite entre les divers autres composants.
          */
          RepartiteurDEnergie
        }
        CategorieTypeDeComposant ;


    private:    
    
      /// Catégorie effective du type.
      
      /*!
      */
      CategorieTypeDeComposant categorie ;
      
      
      /// Nom du type de composant.
      Base::Chaine nom ;

      
      /// inventeur.
      
      /// date d'invention.
      

    };
    
  }
}

#endif
