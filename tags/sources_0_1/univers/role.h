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

#include "ensemble_composition.h"
#include "ensemble_association.h"
#include "composition.h"



namespace ProjetUnivers {

  namespace Univers {
    
    using namespace ProjetUnivers::Base ;
    
    class Mission ;
    class Objectif ;
    class Poste ;
    
    /*
    CLASS
      Role
      
      Représente un rôle dans une mission, c'est-à-dire "quelque chose qui 
      peut être joué par un personnage".
    
    TYPE_DE_CLASSE
      Objet
      Abstrait
    */
    class Role {
    public:
    
    
      //////////////
      // Destructeur.
	    virtual ~Role() ;

	

    protected:

	
      ///////////////////
      // Constructeur.
      Role() ;
  
      

      // ****************
      // GROUP: Attributs
      // ****************

      
      ////////////////
      // Mission dans lequel ce rôle apparait, attribut inverse de 
      // Mission::roles.
      Association< Mission > mission ;

      ////////////////
      // L'objectif du rôle.
      Composition< Objectif > objectif ;

      //////////////////
      // Postes associés au rôle.
      EnsembleAssociation< Poste > postes ;



    private:
      
 
    };
    
    
  }

}

#endif
