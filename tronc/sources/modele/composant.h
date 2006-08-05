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

#include <modele/mobile.h>
#include <modele/destructible.h>


namespace ProjetUnivers {

  namespace Modele {
    
    
    
    class PlanDeComposant ;
    class PointDAttache ;
    class PlanDePointDAttache ;
    
    ///  Représente un composant d'un vaisseau.
    
    /*!
      @par Type de classe
      - Objet
      - Concret
      
    */
    class Composant : public Mobile, public Destructible
    {
    public:


      /// Construit un composant selon un plan.
      Composant(const Base::Association<PlanDeComposant>&) ;
      Composant(const Nom&, const Base::Association<PlanDeComposant>&) ;

      /// Accès à un point d'attache en fonction de son plan.
      Base::Association<PointDAttache> 
        AccesPointDAttache(const Base::Association<PlanDePointDAttache>&) const ;

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
      @name Attributs
    */
    // @{
      
      /// Le plan de construction du composant.
      Base::Association<PlanDeComposant> plan ;
      
      /// Les points d'attaches actifs.
      /*!
        Cet ensemble diminue avec l'augmentation des dégats du composant, 
        conformément aux informations de this->plan.
      */
      Base::EnsembleAssociation<PointDAttache> pointsDAttaches ;
      
      
    // @}
      
      
    };
    
    
  }

}

#endif
