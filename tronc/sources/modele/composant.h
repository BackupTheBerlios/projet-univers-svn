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

#ifndef _PU_MODELE_COMPOSANT_H_
#define _PU_MODELE_COMPOSANT_H_

#include <base/association.h>
#include <base/types.h>

#include <modele/bien.h>


namespace ProjetUnivers {

  namespace Modele {
    
    class TypeDeComposant ;
    
      
    ///  Repr�sente un composant d'un vaisseau.
    
    /*!
      Type de classe
      - Objet
      - Abstrait
    */
    class Composant : public Bien {
    public:
    
      /// Classe abstraite donc destructeur virtuel.
      virtual ~Composant() ;
    
  	
    protected:


      /// Classe abstraite donc constructeur prot�g�.
      Composant(const Base::Association< TypeDeComposant >& _type) ;

      /// Classe abstraite donc constructeur prot�g�.
      Composant() ;

      
      /// Type du composant.
      Base::Association< TypeDeComposant > type ;
      
      /// Pourcentage d'�tat de marche du composant.
      
      /*!
        Un entier entre 0 et 100.
      */
      Base::Entier pourcentageEtatDeMarche ;
      
      
    };
    
    
  }

}

#endif
