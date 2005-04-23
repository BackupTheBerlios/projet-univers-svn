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

#ifndef _PU_MODELE_MISSION_H_
#define _PU_MODELE_MISSION_H_

#include <base/ensemble_composition.h>
#include <base/ensemble_association.h>
#include <base/composition.h>

#include <modele/objet_abstrait.h>

namespace ProjetUnivers {

  namespace Modele {
    
    
    class Role ;
        
      
    /// Représente une mission.
    /*!
    
      \remark  
        Une mission peut se jouer, et alors cela crée un EtatMission

      Type de classe
        - Objet
        - Concret
    */
    class Mission : public ObjetAbstrait {
    public:


      

      
    private:
      

      // ****************
      /// @name Attributs
      // ****************
      // @{
      
      
      /// Les différents rôles de la mission.
      Base::EnsembleComposition< Role > roles ;
  
      /// Les rôles qu'on peut jouer dans la mission.
      /// C'est un sous-ensemble de Mission::roles.
      Base::EnsembleAssociation< Role > rolesJouables ;


      // @}

    };
    
    
  }

}

#endif
