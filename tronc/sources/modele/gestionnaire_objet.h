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




namespace ProjetUnivers {

  namespace Modele {
    
    class ObjetPhysique ;
    class Assemblage ;
    class Contrainte ;    
    class TypeObjet ;
    class TypeContrainte ;
      
    ///  G�re les objets.
    
    /*!

    @par Fonctionnement
    
    @par Questions
    
      Est-ce un objet physique ?
        - si oui alors un assemblage peut �tre un �l�ment d'un autre assemblage
      
    */
    namespace GestionnaireObjet {
      
//    class GestionnaireObjet : public Base::Singleton
//    {
//    public:

      /*!
        @name Op�ration sur les objets
        
        On peut 
        - ajouter une contrainte entre 2 objets (Assembler)
        - supprimer une contriante entre 2 objets (Desassembler)
        - d�truire un objet (Detruire)
        - construire une objet
      */
      // @{

      

      Base::Association<ObjetPhysique> Ajouter(ObjetPhysique*) ;

      void Ajouter(Contrainte*) ;
                            
      void Enlever(const Base::Association<Contrainte>&) ;

      void Enlever(const Base::Association<ObjetPhysique>&) ;
      
      
      /// Cr�er un objet � partir d'un mod�le.
      /*!
        Si le mod�le de l'objet est trop vague, comme par exemple 
        "un vaisseau", en prend un au hasard.
        
      */
      void CreerInstance(const Base::Association<TypeObjet>&) ;
      
      // @}
      
      /*!
        @name Op�ration sur les types d'objets
        
      */
      // @{


      void Ajouter(TypeContrainte*) ;
      void Ajouter(TypeObjet*) ;
                             
      
      // @}
      
            
    }

    
//      Base::EnsembleComposition<Objet> objets ;
//
//      Base::EnsembleAssociation<Assemblage> assemblages ;
//
//      
//      Base::EnsembleComposition<TypeObjet> typeObjets ;
//      Base::EnsembleComposition<TypeContrainte> typeContraintes ;
//      
//
//    };


  }

}

#endif 
