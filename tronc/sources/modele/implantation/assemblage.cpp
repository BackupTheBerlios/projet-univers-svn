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

#include <base/erreur.h>
#include <base/fonction_association_objet_objet.h>
#include <base/iterateur_ensemble_association.h>
#include <base/joli_affichage.h>


#include <modele/exception.h>
#include <modele/assemblage.h>
#include <modele/composant.h>
#include <modele/contrainte.h>

#include <modele/gestionnaire_objets.h>
#include <modele/plan_de_composant.h>
#include <modele/plan_d_assemblage.h>
#include <modele/plan_de_point_d_attache.h>



namespace ProjetUnivers {

  namespace Modele {


    namespace {

      /// Factorisation de la construction d'un assemblage à partir d'un plan.
      void Construire(Assemblage* _assemblage,
                      const Base::Association<PlanDAssemblage>& _plan)
      {
        /// 1. on créé les composants et on les ajoute
        
        /// Au passage, on mémorise les liens entre les plans de composant et 
        // les composants effectifs construits.
        
        Base::FonctionAssociationObjetObjet<PlanDeComposant,Composant> association ;
        
        for(Base::IterateurEnsembleAssociation<PlanDeComposant> 
                planComposant(_plan->Composants()) ;
            planComposant.Valide() ;
            ++planComposant)
        {
          
          Base::Composition<Composant> composant(new Composant(*planComposant)) ;
          _assemblage->AjouterObjet(composant) ;
          
          association.Ajouter(*planComposant, composant) ;
          
          GestionnaireObjets::Ajouter(composant.Liberer()) ;
          
        }
        
        
        /// 2. on créé les contraintes
        for(Base::IterateurEnsembleAssociation<PlanDeContrainte> 
                typeDeContrainte(_plan->Contraintes()) ;
            typeDeContrainte.Valide() ;
            ++typeDeContrainte)
        {
          /// Une contrainte opère entre 2 points de liaisons 
          Base::Association<PointDAttache> pointDAttache1 ;
          Base::Association<PointDAttache> pointDAttache2 ;
          
          pointDAttache1 = 
            association.Acces(
              typeDeContrainte->AccesPlanDePointDAttache1()->AccesPlanDeComposant()
                             )->AccesPointDAttache(
                                  typeDeContrainte->AccesPlanDePointDAttache1()
                                             ) ;

         pointDAttache2 = 
            association.Acces(
              typeDeContrainte->AccesPlanDePointDAttache2()->AccesPlanDeComposant()
                             )->AccesPointDAttache(
                                  typeDeContrainte->AccesPlanDePointDAttache2()
                                             ) ;


          Base::Composition<Contrainte> 
            contrainte(new Contrainte(*typeDeContrainte,
                             pointDAttache1,
                             pointDAttache2)) ;

          _assemblage->AjouterContrainte(contrainte) ;
          GestionnaireObjets::Ajouter(contrainte.Liberer()) ;
        }


        
        
      }
    }

    Assemblage::Assemblage(const Base::Association<PlanDAssemblage>& _plan)
    : plan(_plan)
    {}

    Assemblage::Assemblage(const Nom& _nom, 
                           const Base::Association<PlanDAssemblage>& _plan)
    : Objet(_nom), plan(_plan)
    {}


    void Assemblage::AjouterObjet(
      const Base::Association<Positionne>& _objet)
    {
      this->composants.Ajouter(_objet) ;
    }

    void Assemblage::AjouterContrainte(
      const Base::Association<Contrainte>& _contrainte)
    {
      /// On vérifie la précondition
//      VerifieCondition(this->composants.Contient(_contrainte->pointDAttache1) &&
//                       this->composants.Contient(_contrainte->pointDAttache1),
//                       Exception("contrainte ne portant pas sur un objet"));
      
      this->contraintes.Ajouter(_contrainte) ;
    }

    Base::Chaine Assemblage::AfficherReference() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<Assemblage identificateur=\"" ;
      resultat += identificateur ;
      resultat += "\">" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ; 
    }
    
    Base::Chaine Assemblage::AfficherDefinition() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<Assemblage nom=\"" ;
      resultat += nom ;
      resultat += "\" identificateur=" ;
      resultat += identificateur ;
      resultat += ">" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;

      resultat += Base::AfficheEspaces() + "<composants>" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;
      
      for(Base::IterateurEnsembleAssociation<Positionne> composant(this->composants) ;
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

      for(Base::IterateurEnsembleAssociation<Contrainte> contrainte(this->contraintes) ;
          contrainte.Valide() ;
          ++contrainte)
      {
        resultat += contrainte->AfficherReference() ;
        
      }

      
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</contraintes>" ;
      resultat += Base::FinDeLigne() ;
      
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</Assemblage>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
      
    }

     
  }
}
