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


#ifndef _PU_MODELE_DESTRUCTIBLE_H_
#define _PU_MODELE_DESTRUCTIBLE_H_


#include <modele/energie.h>

namespace ProjetUnivers {


  namespace Modele {


    
      
    /// Propriété des objets pouvant subir des dégâts et être détruits

    /*!
    */
    class Destructible
    {
    public:
   
      /// Valeur de point de vie en pourcentage.
      /*!
        100% correspond à un objet neuf
        0% à un objet détruit
      */
      Base::Reel PourcentagePointsDeVie() const ;
   
      /// Fait dubir un dégat d'une certaine quantité d'énergie.
      void SubirDegats(const Energie& _energie) ;
   
      /// Classe abstraite donc destructeur virtuel.
      virtual ~Destructible() ;
    
   
    protected:


      /// Classe abstraite donc constructeur protégé.
      Destructible(const Energie& _pointsDeVieTotal) ;
      
      /// Enérgie nécéssaire à sa destruction
      Energie pointsDeVieTotal ;
      
      Energie pointsDeVieActuel ;


    };

  }

}

#endif
