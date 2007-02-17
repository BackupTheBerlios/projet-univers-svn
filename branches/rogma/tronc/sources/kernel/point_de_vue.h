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

#include <vector>

#include <base/association.h>
#include <base/ensemble_composition.h>
#include <base/ensemble_association.h>
#include <base/ensemble_valeur.h>
#include <base/evenement.h>
#include <base/implantation/base_vue.h>

namespace ProjetUnivers {
  namespace Base {
    
    

    /// Un point de vue est une observation coh�rente d'un mod�le de donn�es.
    /*!
      Un point de vue est un ensemble de vues. G�n�ralement, toutes ces vues 
      portent sur des mod�les reli�s les uns aux autres. 
      
      Ces vues doivent toutes avoir �t� rafraichies pour que le point de vue 
      puisse �tre affich�. 
      
      @par Exemples 
      - ce que voit un personnage
      - ce que d�tecte un capteur
    
      @par Utilisation 
      -# Cr�ation d'un point de vue
      -# Enregistrement des vues par ViewPoint::add
      -# Raffraichissement p�riodique par ViewPoint::Raffraichir
        
    */
    class ViewPoint 
    {
    public:

    /*!
      @name Construction
      
    */
    // @{

      /// Constructeur.
      ViewPoint() ;

      /// Ajoute une vue.
      void add(Implantation::BaseVue* _vue) ;

      /// Enl�ve une vue.
      void remove(const Association<Implantation::BaseVue>& _vue) ;

    // @}
    /*!
      @name Utilisation
      
    */
    // @{

    
      /// Rafraichissement du point de vue.
      virtual void update() ;

      /// Demande au point de vue de d�truire la vue.
      virtual void destroy(const Association<Implantation::BaseVue>&) ;
    
    // @}
      
      /// Destructeur, d�truit les vues.
      virtual ~ViewPoint()
      {}

    protected:
    
      /// Les vues constituant ce point de vue.
      EnsembleComposition<Implantation::BaseVue> vues ;
    
      
    private:

    /*!
      @name Pour la gestion des vues
      
      
    */
    // @{
    
      /// Marque _vue comme devant �tre rafraichie.
      void PenserAupdate(const Association<Implantation::BaseVue> _vue,
                              const Evenement& _evenement) ;
    
      /// Marque _vue comme devant �tre supprim�e.
      void PenserAdestroy(const Association<Implantation::BaseVue> _vue) ;
      
    //@}

      /// Les vues qui doivent �tre d�truites au prochain tour.
      /*!
      C'est une collection 
      -# ordonn�e (car l'ordre est important pour la destruction) en effet on 
         suppose que l'ordre de destruction des objets du mod�le respecte la 
         composition (ce qui est le cas).
      -# pour le reste, il serait plus judicieux de mettre un vecteur sans 
         d�salocation (pour ne pas r�allouer l'espace allou�) �tant donn� que 
         le nombre d'objets � d�truire sera en pratique "born�".
      */
      std::vector<Implantation::BaseVue*> vuesAdestroy ;
      
      
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
      
      /// Les rafraichissements � effectuer au prochain tour.
      /*!
        N'importe quelles des vues cosntituant r�cursivement ce point de vue.
      */
      EnsembleValeur<Rafraichissement> rafraichissements ;
      
      friend class Implantation::BaseVue ;
      
    };

    
  }
}


#endif

