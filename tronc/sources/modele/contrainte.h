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

#ifndef _PU_MODELE_CONTRAINTE_H_
#define _PU_MODELE_CONTRAINTE_H_

#include <modele/facette.h>

namespace ProjetUnivers {
  namespace Modele {
    
    class PointDAttache ;
    class Assemblage ;

    /// Liaison entre deux points d'attache.
    /*!
    @par Etat
      planning
    */
    class Contrainte : public Facette
    {
    public:
    
    
      /// Constructeur.
      Contrainte(const Base::Association<PointDAttache>&,
                 const Base::Association<PointDAttache>&) ;
    
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
      
    /*!
      @name Mécanique interne
      
      
    */
    // @{
      


    // @}

      /// Les deux points d'attache de la liaison.
      Base::Association<PointDAttache> pointDAttache1 ;
      Base::Association<PointDAttache> pointDAttache2 ;
      
      
      friend class Assemblage ;
    };

  }
}


#endif /*_PU_MODELE_CONTRAINTE_H_*/
