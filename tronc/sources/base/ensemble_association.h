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
 
#ifndef ENSEMBLE_ASSOCIATION_H
#define ENSEMBLE_ASSOCIATION_H

#include "association.h"

namespace ProjetUnivers {

  namespace Base {


    
    /*
    CLASS
      EnsembleAssociation
    
      Représente un ensemble d'élément d'une classe d'objets en association.
    
    UTILISATION
      Même utilisations que pour Association, en ce qui concerne les ensembles.
    */
    template <class OBJET> class EnsembleAssociation {
    public:
    
    
      
      // ********************
      // GROUP: Construction
      // ********************
    
      
      //////////////
      // Constructeur par défaut.
      EnsembleAssociation() ;
    
      //////////////
      // Destructeur par défaut.
      ~EnsembleAssociation() ;
    
      /////////////////
      // Constructeur de copie, _e est vidé après cela.
      EnsembleAssociation(const EnsembleAssociation< OBJET >& _e);
    
      /////////////////
      // Aggrege un élément à l'ensemble.
      void add(const Association< OBJET >& _elt);
    
      //////////////////
      // Enlève l'élément _el, s'il n'y est pas ne fait rien.
      void remove(const Association< OBJET >& _el) ;
    
    
      // ********************
      // GROUP: Consultation
      // ********************
    
    
      ///////////////////
      // Determine si _el fait partie de l'ensemble.
      Booleen contains(const Association< OBJET >& _el) const ;
    
    
    };
    
    #ifdef _INC_TEMP_CODE_
    #include "implantation/ensemble_association.cxx"
    #endif
    
  }
}




#endif
