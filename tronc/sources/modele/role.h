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

#ifndef _PU_UNIVERS_ROLE_H_
#define _PU_UNIVERS_ROLE_H_

#include <base/ensemble_composition.h>
#include <base/ensemble_association.h>
#include <base/composition.h>
#include <univers/objet_abstrait.h>


namespace ProjetUnivers {

  namespace Univers {
    
    
    class Mission ;
    class Objectif ;
    class Poste ;
    
      
    /// Représente un rôle dans une mission, c'est-à-dire "quelque chose qui 
    /// peut être joué par un personnage".
    
    /*!
    Type de classe
    
      Objet
    
      Abstrait
    */
    class Role : public ObjetAsbtrait {
    public:
    
    
      /// Destructeur.
	    virtual ~Role() ;

	

    protected:

	
      /// Constructeur.
      Role() ;
  
      

      // ****************
      /// @name Attributs
      // ****************

      
      /// Mission dans lequel ce rôle apparait, attribut inverse de 
      /// Mission::roles.
      Base::Association< Mission > mission ;

      /// L'objectif du rôle.
      Base::Composition< Objectif > objectif ;

      //////////////////
      // Postes associés au rôle.
      Base::EnsembleAssociation< Poste > postes ;



    private:
      
 
    };
    
    
  }

}

#endif
