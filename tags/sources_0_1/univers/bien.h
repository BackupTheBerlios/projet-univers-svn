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


#ifndef _PU_UNIVERS_BIEN_H_
#define _PU_UNIVERS_BIEN_H_

//#include "ensemble_composition.h"


namespace ProjetUnivers {

  namespace Univers {


    
    /*
    CLASS
      Bien
      
      Repr�sente un objet fabriqu� artificellement par des membres d'esp�ces 
      vivantes. 

    TYPE_DE_CLASSE
      Objet
      Abstrait
    */
    class Bien {
    public:
		
      //////////////////
      // Classe abstraite donc destructeur virtuel.
      virtual ~Bien() ;
    
  	
    protected:


      //////////////////////
      // Classe abstraite donc constructeur prot�g�.
      Bien();
      
      //////////////////////
      // Propri�taire ??

    };

  }

}

#endif
