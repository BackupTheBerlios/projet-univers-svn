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


#include <modele/plan_de_composant.h>
#include <modele/plan_d_etat_de_composant.h>

namespace ProjetUnivers {

  namespace Modele {
    
    
    PlanDeComposant::PlanDeComposant(const Nom& _nom)
    : Objet(_nom)
    {}

      
    Base::Association<PlanDEtatDeComposant> 
      PlanDeComposant::Etat(const Base::Entier& _pourcentagePointDeVie) const
    {
      /// 
      /*!
        @todo 
          implanter; il faut trouver dans l'ensemble des couples 
         (point de vie, etat) l'état qui correspond au point de vie le plus 
          proche de _pourcentagePointDeVie
      
        Pour l'instant on ne renvoie qu'un truc.
      
      
      */
      return this->etat ;
    }

    void 
    PlanDeComposant::DefinirEtat(
        const Base::Entier& _degat,
        const Base::Association<PlanDEtatDeComposant>& _etat)
    {
      /*!
        temporaire
      */
      etat = _etat ;
    }


    Base::Chaine PlanDeComposant::AfficherReference() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDeComposant identificateur=\"" ;
      resultat += identificateur ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ; 
    }
    
    Base::Chaine PlanDeComposant::AfficherDefinition() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDeComposant nom=\"" ;
      resultat += nom ;
      resultat += "\" identificateur=" ;
      resultat += identificateur ;
      resultat += ">" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;

      resultat += this->etat->AfficherReference() ;
       
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</PlanDeComposant>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
      
    }


//    Base::Association<PointDAttache> 
//      PlanDeComposant::AccesPointDAttache(
//            const Base::Association<PlanDePointDAttache>& _plan) const
//    {
//      this->etat->AccesPointDAttache(_plan) ;
//    }

      
  }
}

