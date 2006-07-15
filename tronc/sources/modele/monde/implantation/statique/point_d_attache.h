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

#ifndef _PU_MODELE_POINT_D_ATTACHE_H_
#define _PU_MODELE_POINT_D_ATTACHE_H_

#include <modele/objet.h>

namespace ProjetUnivers {

  namespace Modele {
    
    class Composant ;
    class PlanDePointDAttache ;
    
    /// Un endroi d'un composant où on peut en attacher un autre.
    class PointDAttache : public Objet
    {
    public:
    
    /*!
      @name Construction
      
      
    */
    // @{
    
      /// Constructeur.
      PointDAttache(const Base::Association<PlanDePointDAttache>&,
                    const Base::Association<Composant>&) ;
    
    // @}
      
      Base::Association<PlanDePointDAttache> AccesPlanPointDAttache() const ;

    /*!
      @name Affichage
      
      Construit une chaine XML représentant l'objet.
    */
    // @{

      /// Chaine représentant une référence à l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine représentant la définition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;

    // @}


    private:
      
      
      /// Informations communes.
      Base::Association<PlanDePointDAttache> plan ;

      /// Le composant de ce point d'attache
      /*!
        Relation inverse de Composant::pointsDAttaches
      */
      Base::Association<Composant> composant ;
    };

  }
}


#endif 
