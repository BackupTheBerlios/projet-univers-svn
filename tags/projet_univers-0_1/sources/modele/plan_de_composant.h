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

#ifndef _PU_MODELE_PLAN_DE_COMPOSANT_H_
#define _PU_MODELE_PLAN_DE_COMPOSANT_H_


#include <base/ensemble_association.h>
#include <base/fonction_association_valeur_objet.h>
#include <modele/objet.h>

namespace ProjetUnivers {
  namespace Modele {
    
    class PlanDEtatDeComposant ;
    class PointDAttache ;
    class PlanDePointDAttache ;
    
    /// Un plan de composant 
    /*!
    @deprecated
    */
    class PlanDeComposant : public Objet
    {
    public:
    
    /*!
      @name Construction
    */
    // @{
    
      /// Constructeur.
      PlanDeComposant(const Nom&) ;

      /// Defini un état pour un pourcentage de points de vie donné.
      void DefinirEtat(const Base::Entier&,
                       const Base::Association<PlanDEtatDeComposant>&) ;

    // @}
    /*!
      @name Utilisation
    */
    // @{
    
      
      /// Etat correspondant à @c _pourcentagepointsDeVie.
      Base::Association<PlanDEtatDeComposant> 
        Etat(const Base::Entier& _pourcentagepointsDeVie) const ;
      
      /// Accès à un point d'attache en fonction de son plan.
      Base::Association<PointDAttache> 
        AccesPointDAttache(const Base::Association<PlanDePointDAttache>&) const ;

      /// Chaine représentant une référence à l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine représentant la définition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;

    // @}
    private:
    
      
      /// Les différents états en fonction des points de vie.
      /*!
        @remark 
          pas encore implanté; pour l'instant on se contente d'un seul état de 
          composant, c.f. 
          
        @todo
          Ajouter les états pour les modèles destructibles. A réaliser. 
          
        Pour chaque état :
        - Un modèle 3D
        - Des points d'attaches 
      */
      /// Base::FonctionAssociationValeurObjet<Base::Entier,PlanDEtatDeComposant> etats ;

      /// Temporairement, on n'a qu'un seul état.
      /*!
        @remark 
          Implantation temporaire.
        @todo 
          A supprimer lors de la réalisation de la tache 2378. 
      */
      Base::Association<PlanDEtatDeComposant> etat ;
 
    };
  }
}

#endif 
