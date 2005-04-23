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
    
    
      
    /// Repr�sente le type d'un composant.
    
    /*!
      
      Un Composant repr�sente une instance r��lle d'un TypeDeComposant. C'est 
      la m�me diff�rence qu'entre une voiture donn�e (la mi�nne par exemple) et 
      le mod�le de cette voiture (une renault clio mod�le xxx). 
    
      Type de classe
        - Objet
        - Abstrait
    */
    class TypeDeComposant : public TypeDeBien {
    public:

      /// Simule l'action de ce type de composant.
      /*
        Simule l'action pendant une certaine dur�e d'une instance de ce type de 
        composant �tant dans certain �tat.
        
        
      */
      virtual void Simuler(const EtatComposant& etat, const Duree& _duree) = 0 ;


    
      /// Les diff�rentes cat�gories d'un type de composant.
      
      /*!
        \todo
          supprimer et remplacer par des sous classes...
      */
      typedef enum 
        {
          /// cat�gorie des moteurs
          Moteur, 
          
          /// cat�gorie des lasers
          Laser,
          
          /// cat�gories des commandes.
          
          /*!
            Boutons et autres manches � balais.
          */
          Commande,
          
          /// G�n�rateur d'�nergie.
          GenerateurEnergie,
          
          /// G�n�rateur de bouclier.
          GenerateurBouclier, 
          
          /// Morceau de coque.
          
          /*!
            C'ets une cat�gorie assez g�n�rale o� on peut mettre tout ce qu'on 
            ne sait pas o� mettre.
          */
          MorceauCoque, 
          
          /// R�partiteur d'�n�rgie.
          
          /*!
            Distribue l'�n�rgie produite entre les divers autres composants.
          */
          RepartiteurDEnergie
        }
        CategorieTypeDeComposant ;


    private:    
    
      /// Cat�gorie effective du type.
      
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
