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
#include <base/ensemble_valeur.h>
#include <base/evenement.h>
#include <base/implantation/base_vue.h>

namespace ProjetUnivers {
  namespace Base {
    
    

    /// Un point de vue est une observation cohérente d'un modèle de données.
    /*!
      Un point de vue est un ensemble de vues. Généralement, toutes ces vues 
      portent sur des modèles reliés les uns aux autres. 
      
      Ces vues doivent toutes avoir été rafraichies pour que le point de vue 
      puisse être affiché. 
      
      @par Exemples 
      - ce que voit un personnage
      - ce que détecte un capteur
    
      @par Utilisation 
      -# Création d'un point de vue
      -# Enregistrement des vues par PointDeVue::Ajouter
      -# Raffraichissement périodique par PointDeVue::Raffraichir
        
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

      /// Enlève une vue.
      void Enlever(const Association<Implantation::BaseVue>& _vue) ;

    // @}
    /*!
      @name Utilisation
      
    */
    // @{

    
      /// Rafraichissement du point de vue.
      virtual void Rafraichir() ;

    
    // @}
      
      /// Destructeur, détruit les vues.
      virtual ~PointDeVue()
      {}

      
    private:

    /*!
      @name Pour la gestion des vues
      
      
    */
    // @{
    
      /// Marque _vue comme devant être rafraichie.
      void PenserARafraichir(const Association<Implantation::BaseVue> _vue,
                              const Evenement& _evenement) ;
    
      /// Marque _vue comme devant être supprimée.
      void PenserADetruire(const Association<Implantation::BaseVue> _vue) ;
      
    //@}
    
      /// Les vues constituant ce point de vue.
      EnsembleComposition<Implantation::BaseVue> vues ;

      /// Ses vues qui doivent être détruites au prochain tour.
      /*!
      @invariant
        vuesADetruire inclus dans vues
      */
      EnsembleAssociation<Implantation::BaseVue> vuesADetruire ;
      
      
      struct Rafraichissement
      {
        Rafraichissement(const Association<Implantation::BaseVue>& _vue,
                         const Evenement& _evenement)
        : vue(_vue), evenement(_evenement)
        {}

        bool operator==(const Rafraichissement& _r) const
        {
          return vue == _r.vue && evenement == _r.evenement ;
        }
          
        Association<Implantation::BaseVue> vue ;
        Evenement evenement ;
      };
      
      /// Les rafraichissements à effectuer au prochain tour.
      /*!
        N'importe quelles des vues cosntituant récursivement ce point de vue.
      */
      EnsembleValeur<Rafraichissement> rafraichissements ;
      
      friend class Implantation::BaseVue ;
      
    };

    
  }
}


#endif

