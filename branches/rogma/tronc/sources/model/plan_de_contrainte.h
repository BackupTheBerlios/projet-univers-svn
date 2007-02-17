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
#ifndef _PU_MODELE_PLAN_DE_CONTRAINTE_H_
#define _PU_MODELE_PLAN_DE_CONTRAINTE_H_


#include <base/association.h>

#include <modele/objet.h>

namespace ProjetUnivers {
  namespace Model {
 
    class PlanDePointDAttache ;
 
    /// Liaison entre deux points d'attache dans un plan d'assemblage.
    /*!
    @deprecated
    */
    class PlanDeContrainte : public Object
    {
    public:
      
      /// Les différents types de contraintes
      /*!
        
      */
      typedef enum
      {
        /// Pour une liaison rigide.
        Rigide,
        
        /// Pour une liaison souple
        Souple
        
      } TypeDeContrainte ;
      
      
      /// Construit une contrainte entre deux plans de points d'attache.
      PlanDeContrainte(const Base::Association<PlanDePointDAttache>&,
                       const Base::Association<PlanDePointDAttache>&,
                       const TypeDeContrainte&) ;

      Base::Association<PlanDePointDAttache> AccesPlanDePointDAttache1() const ;
      Base::Association<PlanDePointDAttache> AccesPlanDePointDAttache2() const ;

      /// Chaine représentant une référence à l'objet.
      virtual std::string AfficherReference() const ;
      
      /// Chaine représentant la définition de l'objet.      
      virtual std::string AfficherDefinition() const ;
                       
    private:
    
      Base::Association<PlanDePointDAttache> planDePointDAttache1 ;
      Base::Association<PlanDePointDAttache> planDePointDAttache2 ;
      TypeDeContrainte typeDeContrainte ;
      
    };
  }
}

#endif
