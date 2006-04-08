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
#include <modele/plan_de_point_d_attache.h>
#include <modele/plan_de_contrainte.h>

namespace ProjetUnivers {

  namespace Modele {
 
    PlanDeContrainte::PlanDeContrainte(
      const Base::Association<PlanDePointDAttache>& _p1,
      const Base::Association<PlanDePointDAttache>& _p2,
      const TypeDeContrainte& _type)
    : planDePointDAttache1(_p1), 
      planDePointDAttache2(_p2),
      typeDeContrainte(_type)
    {}
    
    Base::Association<PlanDePointDAttache> 
    PlanDeContrainte::AccesPlanDePointDAttache1() const
    {
      return this->planDePointDAttache1 ;
    }
    
    Base::Association<PlanDePointDAttache> 
    PlanDeContrainte::AccesPlanDePointDAttache2() const
    {
      return this->planDePointDAttache2 ;
    }

    Base::Chaine PlanDeContrainte::AfficherReference() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDeContrainte identificateur=\"" ;
      resultat += identificateur ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ; 
      
    }
    
    Base::Chaine PlanDeContrainte::AfficherDefinition() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PlanDeContrainte nom=\"" ;
      resultat += nom ;
      resultat += "\" identificateur=" ;
      resultat += identificateur ;
      resultat += ">" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;
      
      resultat += this->planDePointDAttache1->AfficherReference() ;
      resultat += this->planDePointDAttache2->AfficherReference() ;
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</PlanDAssemblage>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
     }

  }
}
