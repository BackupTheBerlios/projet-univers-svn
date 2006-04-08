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

#include <base/joli_affichage.h>
#include <base/iterateur_ensemble_association.h>

#include <modele/plan_de_composant.h>
#include <modele/plan_de_contrainte.h>

#include <modele/plan_d_assemblage.h>

namespace ProjetUnivers {

  namespace Modele {
    
    PlanDAssemblage::PlanDAssemblage(const Nom& _nom)
    : Objet(_nom)
    {}
    
    void PlanDAssemblage::Ajouter(const Base::Association<PlanDeComposant>& _plan)
    {
      this->composants.Ajouter(_plan) ;
    }
    
    void PlanDAssemblage::Ajouter(const Base::Association<PlanDeContrainte>& _plan)
    {
      this->contraintes.Ajouter(_plan) ;
    }

    Base::IterateurEnsembleAssociation<PlanDeComposant> 
    PlanDAssemblage::Composants()
    {
      return this->composants ;
    }
    
    Base::IterateurEnsembleAssociation<PlanDeContrainte> 
    PlanDAssemblage::Contraintes()
    {
      return this->contraintes ;      
    }

    Base::Chaine PlanDAssemblage::AfficherReference() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDAssemblage identificateur=\"" ;
      resultat += identificateur ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ; 
    }
    
    Base::Chaine PlanDAssemblage::AfficherDefinition() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDAssemblage nom=\"" ;
      resultat += nom ;
      resultat += "\" identificateur=" ;
      resultat += identificateur ;
      resultat += ">" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;

      resultat += Base::AfficheEspaces() + "<composants>" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;
      
      for(Base::IterateurEnsembleAssociation<PlanDeComposant> composant(this->composants) ;
          composant.Valide() ;
          ++composant)
      {
        resultat += composant->AfficherReference() ;
      }
      
      
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</composants>" ;
      resultat += Base::FinDeLigne() ;

      resultat += Base::AfficheEspaces() + "<contraintes>" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;

      for(Base::IterateurEnsembleAssociation<PlanDeContrainte> contrainte(this->contraintes) ;
          contrainte.Valide() ;
          ++contrainte)
      {
        resultat += contrainte->AfficherReference() ;
        
      }

      
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</contraintes>" ;
      resultat += Base::FinDeLigne() ;
      
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</PlanDAssemblage>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
      
    }


  }
}
