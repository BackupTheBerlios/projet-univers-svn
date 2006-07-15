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

#ifndef _PU_AFFICHAGE_POINT_DE_VUE_H_
#define _PU_AFFICHAGE_POINT_DE_VUE_H_


#include <base/association.h>
#include <base/point_de_vue.h>

namespace ProjetUnivers {

  // D�claration en-avant.
  namespace Modele { 
    class Objet ;
  }

  namespace Affichage {


    /// Le point de vue subjectif par rapport � un observateur.
    /*!
      C'est par exmple la vue � la premi�re personne d'un personnage.
      
      Type de classe :
        - Objet
        - Abstrait
    */
    class PointDeVue : public Base::PointDeVue 
    {
    public:

      virtual ~PointDeVue() ;
    
      /// Contruit le point de vue
      virtual void Construire() ;
    
    protected:

     /*!
        @name Construction
      */
      // @{
      
      
      /// Constructeur.
      
      /*!
        Construit tout ce qu'il ya � construire.
      */
      PointDeVue(const Base::Association<Modele::Objet>& _observateur) ;
      
      
      // @}
    
      /// L'observateur.
      Base::Association<Modele::Objet> observateur ;
      
      
      
    };
  }
}


#endif
