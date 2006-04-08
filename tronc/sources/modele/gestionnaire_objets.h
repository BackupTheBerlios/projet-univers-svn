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

#ifndef _PU_MODELE_GESTIONNAIRE_OBJET_H_
#define _PU_MODELE_GESTIONNAIRE_OBJET_H_

#include <base/ensemble_composition.h>
#include <base/chaine.h>




namespace ProjetUnivers {

  namespace Modele {
    
    class Objet ;
    class Contrainte ;    
    class EnsembleDObjet ;
    class TypeContrainte ;
      
    ///  Gère les objets.
    
    /*!

    @par Fonctionnement
    
    @par Questions
    
      Est-ce un objet physique ?
        - si oui alors un assemblage peut être un élément d'un autre assemblage
      
    */
    namespace GestionnaireObjets {
      
    // ******************************************************
    /*!
      @name Opération sur les objets
      
      On peut 
      - ajouter une contrainte entre 2 objets (Assembler)
      - supprimer une contriante entre 2 objets (Desassembler)
      - détruire un objet (Detruire)
      - construire une objet
    */
    // ******************************************************
    // @{

      
      /// Enregistre l'objet dans le gestionnaire.
      Base::Association<Objet> Ajouter(Objet*) ;
      
      /// Retire l'objet du gestionnaire.
      /*!
        L'objet est renvoyé.
      */
      Objet* Enlever(const Base::Association<Objet>&) ;
      
      
      /// Crée un objet élément d'un ensemble.
      /*!
        L'objet est géré par le gestionnaire.
        Si le modèle de l'objet est trop vague, comme par exemple 
        "un vaisseau", en prend un au hasard.
        
      */
//      Base::Association<Objet> 
//          CreerInstance(const Base::Association<EnsembleDObjet>&) ;

      /// Affiche l'état du gestionnaire.
      Base::Chaine AfficherObjets() ;
      
    // @}
    // *************************************
    /*!
      @name Opération sur les types d'objets
      
    */
    // *************************************
    // @{


      /// Enregistre un type de contrainte.
//      void Ajouter(TypeContrainte*) ;

      /// Enregistre un type d'objet.
//      void Ajouter(TypeObjet*) ;
                             
      
    // @}
      
            
    }


  }

}

#endif 
