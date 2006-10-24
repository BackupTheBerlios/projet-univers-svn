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
#ifndef _PU_MODELE_PLAN_DE_POINT_D_ATTACHE_H_
#define _PU_MODELE_PLAN_DE_POINT_D_ATTACHE_H_


#include <base/association.h>

#include <modele/objet.h>

namespace ProjetUnivers {
  namespace Modele {
 
    class PlanDeComposant ;
    
    /// Un point d'attache dans un plan d'assemblage.
    /*!
      C'est un endroit où on peut attacher un autre plan d'assemblage.
    @deprecated
    */
    class PlanDePointDAttache : public Objet
    {
    public:
      
      /// Construction
      PlanDePointDAttache(const Base::Association<PlanDeComposant>&) ;

      /// Accès au plan.
      Base::Association<PlanDeComposant> AccesPlanDeComposant() const ;

      /// Chaine représentant une référence à l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine représentant la définition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;
                       
    private:
    
      // Plan de composant dans laquelle ce plan intervient.
      Base::Association<PlanDeComposant> planDeComposant ;
      
    };
  }
}

#endif
