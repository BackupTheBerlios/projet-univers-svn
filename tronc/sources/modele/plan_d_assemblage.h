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

#ifndef _PU_MODELE_PLAN_D_ASSEMBLAGE_H_
#define _PU_MODELE_PLAN_D_ASSEMBLAGE_H_

#include <modele/objet.h>
#include <modele/plan_de_contrainte.h>

namespace ProjetUnivers {

  namespace Modele {
      
      
    class PlanDeComposant ;
    class PlanDeContrainte ;
      
    /// Un plan d'assemblage.
    /*!
      D�fini les caract�ristique communes des assemblages construits � partir 
      de ce plan. 
    */
    class PlanDAssemblage : public Objet
    {
    public:
    
    // ***********************************************
    /*!
      @name Construction.
    */
    // ***********************************************
    // @{
  
      /// Constructeur.
      PlanDAssemblage(const Nom&) ;
    
      void Ajouter(const Base::Association<PlanDeComposant>&) ;
      void Ajouter(const Base::Association<PlanDeContrainte>&) ;
    
    // @}
    // ***********************************************
    /*!
      @name Utilisation.
    */
    // ***********************************************
    // @{

      Base::IterateurEnsembleAssociation<PlanDeComposant> Composants() ;
      Base::IterateurEnsembleAssociation<PlanDeContrainte> Contraintes() ;

      /// Chaine repr�sentant une r�f�rence � l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine repr�sentant la d�finition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;

    // @}
    
    protected:
      
      /// Les plans de chacuns des composants 
      Base::EnsembleAssociation<PlanDeComposant> composants ;

      /// Les contraintes reliant les composants.
      Base::EnsembleAssociation<PlanDeContrainte> contraintes ;

      
    };
  }
}

#endif 
