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

#include <modele/contrainte.h>
#include <modele/point_d_attache.h>

namespace ProjetUnivers {

  namespace Modele {


    Contrainte::Contrainte(const Base::Association<PlanDeContrainte>& _plan,
                           const Base::Association<PointDAttache>& _p1,
                           const Base::Association<PointDAttache>& _p2)
    : plan(_plan), pointDAttache1(_p1), pointDAttache2(_p2)
    {}


    Base::Chaine Contrainte::AfficherReference() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<Contrainte identificateur=\"" ;
      resultat += identificateur ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ; 
      
    }
    
    Base::Chaine Contrainte::AfficherDefinition() const
    {
      Base::Chaine resultat ;
      
      resultat += Base::AfficheEspaces() ;
      resultat += "<Contrainte nom=\"" ;
      resultat += nom ;
      resultat += "\" identificateur=" ;
      resultat += identificateur ;
      resultat += ">" ;
      resultat += Base::FinDeLigne() ;
      Base::AugmenteIndentation() ;
      
      resultat += this->pointDAttache1->AfficherReference() ;
      resultat += this->pointDAttache1->AfficherReference() ;
      Base::DiminueIndentation() ;
      resultat += Base::AfficheEspaces() + "</Contrainte>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
     }


    
  }
  
}
