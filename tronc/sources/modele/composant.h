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

#include <modele/facette.h>


namespace ProjetUnivers {

  namespace Modele {
    
    
    
    class PlanDeComposant ;
    class PointDAttache ;
    class PlanDePointDAttache ;
    
    /// Propri�t� d'avoir des points d'attaches
    /*!
      @par Type de classe
      - Objet
      - Concret
    */
    class Attachable : public Facette
    {
    public:

    /*!
      @name Construction
      
    */
    // @{

      Attachable() ;
      
      void Ajouter(const Base::Association<PointDAttache>&) ;

    // @}
    /*!
      @name Affichage
      
      Construit une chaine XML repr�sentant l'objet.
    */
    // @{

      /// Chaine repr�sentant une r�f�rence � l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine repr�sentant la d�finition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;

    // @}

    private:
    
    /*! 
      @name Attributs
    */
    // @{
      
      /// Les points d'attaches actifs.
      /*!
        Cet ensemble diminue avec l'augmentation des d�gats du composant, 
        conform�ment aux informations de this->plan.
      */
      Base::EnsembleAssociation<PointDAttache> pointsDAttaches ;
      
      
    // @}
      
      
    };
    
    
  }

}

#endif
