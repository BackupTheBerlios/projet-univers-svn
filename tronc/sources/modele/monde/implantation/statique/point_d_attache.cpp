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

#include <modele/composant.h>
#include <modele/plan_de_point_d_attache.h>

#include <modele/point_d_attache.h>

namespace ProjetUnivers {

  namespace Modele {
    
    PointDAttache::PointDAttache(
                  const Base::Association<PlanDePointDAttache>& _plan,
                  const Base::Association<Composant>& _composant)
    : plan(_plan), composant(_composant)
    {}
      
    Base::Association<PlanDePointDAttache> 
    PointDAttache::AccesPlanPointDAttache() const
    {
      return this->plan ;
    }


    Base::Chaine PointDAttache::AfficherReference() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PointDAttache identificateur=\"" ;
      resultat += identificateur ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ; 
      
    }
    
    Base::Chaine PointDAttache::AfficherDefinition() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<PointDAttache nom=\"" ;
      resultat += nom ;
      resultat += "\" identificateur=" ;
      resultat += identificateur ;
      resultat += ">" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;
      
      resultat += this->plan->AfficherReference() ;
      resultat += this->composant->AfficherReference() ;

      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</PointDAttache>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
     }


  }
}

