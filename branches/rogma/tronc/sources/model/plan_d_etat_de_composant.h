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

#ifndef _PU_MODELE_PLAN_D_ETAT_DE_COMPOSANT_H_
#define _PU_MODELE_PLAN_D_ETAT_DE_COMPOSANT_H_

#include <modele/masse.h>
#include <modele/objet.h>

namespace ProjetUnivers {

  namespace Model {
    
    class Model3D ;
    class PlanDePointDAttache ;
    class PlanDeComposant ;
    class Composant ;
    
    /// Plan d'un composant dans un certain �tat.
    /*!
      Un objet de cette classe repr�sente le plan d'un composant se trouvant 
      dans un certain �tat de d�gats.
      
      Ici, on est donc implictement dans un certain �tat de d�gat et sur un 
      composant.

      @deprecated
      
    */
    class PlanDEtatDeComposant : public Object
    {
    public:
    
    /*!
      @name Construction
    */
    // @{
    
    
      /// Construction.
      PlanDEtatDeComposant(
          const Base::Association<PlanDeComposant>& _planDeComposant) ;
      
      /// Ajout des points d'attache
      void add(const Base::Association<PlanDePointDAttache>&) ;
      
    // @}

      /// Chaine repr�sentant une r�f�rence � l'objet.
      virtual std::string AfficherReference() const ;
      
      /// Chaine repr�sentant la d�finition de l'objet.      
      virtual std::string AfficherDefinition() const ;
    
    private:
    
    
      /// Les point d'attaches du composant dans cet �tat.
      /*!
        D'un �tat � l'autre, le nombre de plans de points d'attache peut varier. 
        Ils sont partag�s entre les diff�rents �tats d'un m�me composant.
      */
      Base::EnsembleAssociation<PlanDePointDAttache> plansDePointsDAttache ;
 
      /// Optionnel, mod�le 3D du composant.
      /*!
        Dans le cas o� il n'y a pas de mod�le, le composant est un composant 
        technique interne, non affich�.
      */
      Base::Association<Model3D> modele ;
            
      /// Le plan correspondant � cet �tat.
      Base::Association<PlanDeComposant> planDeComposant ;
      
      Masse masse ;

      friend class Composant ;
            
    };
    
  }
}

#endif 
