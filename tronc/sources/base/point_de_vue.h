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
    
    

    /// Un point de vue est une observation cohérente d'un modèle de données.
    /*!
      Un point de vue est un ensemble de vues. Généralement, toutes ces vues 
      portent sur des modèles reliés les uns aux autres. Ces vues doivent être 
      toutes avoir été raffraichies, pour former un point de vue cohérent (i.e. 
      on n'a pas oublié de raffraichir une vue). 
      
      Exemples :
      - ce que voit un personnage
      - ce que détecte un capteur
    
      Utilisation :
      -# Création d'un point de vue
      -# Enregistrement des vues par PointDeVue::Ajouter
      -# Raffraichissement périodique par PointDeVue::Raffraichir
    
      @todo
        Envisager la possibilité de remplacer la composition par une 
        aggregation (pointeur à comptage de référence) ce qui permettrait à des 
        point de vue différents de partager les mêmes vues. Exemple : un point 
        de vue d'un personnage et un point de vue d'une caméra.
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

      /// Destructeur.
      virtual ~PointDeVue()
      {}


      /// Ajoute une vue.
      void Ajouter(Implantation::BaseVue* _vue) ;

      /// Enlève une vue.
      void Enlever(const Association<Implantation::BaseVue>& _vue) ;

      // @}
      /*!
        @name Utilisation
        
      */
      // @{

    
      /// Raffraichissement du point de vue.
      void Raffraichir() ;

    
      // @}
      
      
    private:

      /*!
        @name Pour la gestion des vues
        
        
      */

      /// Marque _vue comme devant être rafraichie.
      void PenserARaffraichir(const Association<Implantation::BaseVue> _vue) ;
    
      /// Marque _vue comme devant être supprimée.
      void PenserADetruire(const Association<Implantation::BaseVue> _vue) ;
      
      /// Les vues constituant ce point de vue.
      EnsembleComposition<Implantation::BaseVue> vues ;

      /// Ses vues qui doivent être détruites au prochain tour.
      EnsembleAssociation<Implantation::BaseVue> vuesADetruire ;
      
      /// Ses vues qui doivent être raffraichies au prochain tour.
      EnsembleAssociation<Implantation::BaseVue> vuesARaffraichir ;
      
      
      friend class Implantation::BaseVue ;
      
    };
    
  }
}


#endif

