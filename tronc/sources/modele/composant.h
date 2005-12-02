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
#include <modele/destructible.h>


namespace ProjetUnivers {

  namespace Modele {
    
    
      
    ///  Repr�sente un composant d'un vaisseau.
    
    /*!
      Type de classe
      - Objet
      - Concret
    */
    class Composant : public Bien, public Destructible
    {
    public:

      /// Les diff�rents types de composant.
      typedef enum {
        Coque
      } TypeDeComposant ;


      /// Le type du composant.
//      virtual Base::Association<TypeDeComposant> AccesType() const = 0 ;

    
    
  	

      /// Classe abstraite donc constructeur prot�g�.
      Composant(const TypeDeComposant& _type) ;


    private:
    
      /*! @name Attributs
      */
      
      
      /// Pourcentage d'�tat de marche du composant.
      
      /*!
        Un entier entre 0 et 100.
        
        @deprecated
          d�pend des d�gats subits ?
      */
      Base::Entier pourcentageEtatDeMarche ;
      
      /// Type du composant.
      TypeDeComposant type ;
      
      
      
      
    };
    
    
  }

}

#endif
