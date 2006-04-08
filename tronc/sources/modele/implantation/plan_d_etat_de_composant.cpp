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

#include <base/iterateur_ensemble_association.h>
#include <base/joli_affichage.h>
#include <modele/plan_de_point_d_attache.h>
#include <modele/plan_d_etat_de_composant.h>

namespace ProjetUnivers {

  namespace Modele {
    
    PlanDEtatDeComposant::PlanDEtatDeComposant(
          const Base::Association<PlanDeComposant>& _planDeComposant)
    : Objet(), planDeComposant(_planDeComposant)
    {}
      
    void PlanDEtatDeComposant::Ajouter(
          const Base::Association<PlanDePointDAttache>& _plan)
    {
      this->plansDePointsDAttache.Ajouter(_plan) ;
    }

    Base::Chaine PlanDEtatDeComposant::AfficherReference() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDEtatDeComposant identificateur=\"" ;
      resultat += identificateur ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ; 
      
    }
    
    Base::Chaine PlanDEtatDeComposant::AfficherDefinition() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDEtatDeComposant nom=\"" ;
      resultat += nom ;
      resultat += "\" identificateur=" ;
      resultat += identificateur ;
      resultat += ">" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;

      resultat += Base::AfficheEspaces() + "<plansDePointsDAttache>" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;
      
      for(Base::IterateurEnsembleAssociation<PlanDePointDAttache> point(this->plansDePointsDAttache) ;
          point.Valide() ;
          ++point)
      {
        resultat += point->AfficherReference() ;
      }
      
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</plansDePointsDAttache>" ;
      resultat += Base::FinDeLigne() ;
      
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</PlanDEtatDeComposant>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
 
    }

    
    
  }
}
