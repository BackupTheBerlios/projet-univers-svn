/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PU_BASE_POINT_DE_VUE_H_
#define _PU_BASE_POINT_DE_VUE_H_

#include <base/association.h>
#include <base/ensemble_composition.h>
#include <base/ensemble_association.h>
#include <base/implantation/base_vue.h>

namespace ProjetUnivers {

  namespace Base {
    
    

    /// Un point de vue est une observation coh�rente d'un mod�le de donn�es.
    /*!
      Un point de vue est un ensemble de vues. G�n�ralement, toutes ces vues 
      portent sur des mod�les reli�s les uns aux autres. 
      
      Ces vues doivent toutes avoir �t� raffraichies pour que le point de vue 
      puisse �tre affich�. 
      
      @par Exemples 
      - ce que voit un personnage
      - ce que d�tecte un capteur
    
      @par Utilisation 
      -# Cr�ation d'un point de vue
      -# Enregistrement des vues par PointDeVue::Ajouter
      -# Raffraichissement p�riodique par PointDeVue::Raffraichir
        
    */
    class PointDeVue 
    {
    public:

    /*!
      @name Construction
      
    */
    // @{

      /// Constructeur.
      PointDeVue() ;

      /// Ajoute une vue.
      void Ajouter(Implantation::BaseVue* _vue) ;

      /// Enl�ve une vue.
      void Enlever(const Association<Implantation::BaseVue>& _vue) ;

    // @}
    /*!
      @name Utilisation
      
    */
    // @{

    
      /// Raffraichissement du point de vue.
      void Raffraichir() ;

    
    // @}
      
      /// Destructeur, d�truit les vues.
      virtual ~PointDeVue()
      {}

      
    private:

    /*!
      @name Pour la gestion des vues
      
      
    */
    // @{
    
      /// Marque _vue comme devant �tre rafraichie.
      void PenserARaffraichir(const Association<Implantation::BaseVue> _vue) ;
    
      /// Marque _vue comme devant �tre supprim�e.
      void PenserADetruire(const Association<Implantation::BaseVue> _vue) ;
      
    //@}
    
      /// Les vues constituant ce point de vue.
      EnsembleComposition<Implantation::BaseVue> vues ;

      /// Ses vues qui doivent �tre d�truites au prochain tour.
      EnsembleAssociation<Implantation::BaseVue> vuesADetruire ;
      
      /// Ses vues qui doivent �tre raffraichies au prochain tour.
      EnsembleAssociation<Implantation::BaseVue> vuesARaffraichir ;
      
      
      friend class Implantation::BaseVue ;
      
    };
    
  }
}


#endif

