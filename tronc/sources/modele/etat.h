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

#ifndef _PU_MODELE_JEU_ETAT_H_
#define _PU_MODELE_JEU_ETAT_H_


#include <base/composition.h>
#include <base/ensemble_composition.h>


namespace ProjetUnivers {
  namespace Modele {
    namespace Jeu {    

      /// Etat d'une partie.
      /*!
        Un état caractérise le fait d'être dans une certaine étape du 
        déroulement d'une partie, il s'agit par exemple 
        du fait d'être dans un menu, 
        ou dans une certaine situation au cours d'une partie. 
         
        Un état peut avoir des sous-états, mais un seul est alors activé. 
         
        Un état possède une donnée utilisateur, qui contient les 
        informations fonctionnelles. 
      */
      class Etat {
      public:
          
      // ***************************
      /*! 
        @name Méthodes principales
      */
      // ***************************
      // @{

  
        /// Activation de l'état.
        void Entrer() ;
  
  
      // @}
      // ***************************
      /*!
        @name Méthodes à redéfinir pour utiliser la classe
      */
      // ***************************
      // @{

        
        /// Initialisation de l'état, réalisée une fois à l'entrée
        virtual void Initialiser() = 0 ;
  
        /// Terminaison de l'état, réaliser à la sortie
        virtual void Finaliser() = 0 ;
  
  
      // @}
      // *****************************
      /*!
        @name Gestion des sous-états
      */
      // *****************************
      // @{       

        
        /// Ajout d'un sous-état.
        void AjouterSousEtat(Etat*) ;
        
        /// Suppression d'un sous-état.
        void SupprimererSousEtat(const Base::Association< Etat >&) ;   
        
        /// Active un sous-état.
        void ActiverSousEtat(const Base::Association< Etat >&) ;
        
        
      // @}
      // *************
      /*!
        @name Divers
      */
      // *************
      // @{
      
              
        /// Classe abstraite donc destructeur virtuel.
        virtual ~Etat() ;
      
      
      protected:
      
        /// Contruit un état.
        Etat(const Base::Chaine& _nom) ;
          
      // @}
      // ****************    
      /*!
        @name Attributs
      */
      // ****************
      // @{   

      
        /// Le sous-état actif, s'il y a des sous-états.
        /*!
          C'est un élément de sousEtats.
        */
        Base::Association<Etat> sousEtatActif ;    
  
        /// Sous état éventuels.
        Base::EnsembleComposition<Etat> sousEtats ;
              
        /// Sur état éventuel.
        Base::Association<Etat> surEtat ;

      // @}
      };

    }
  }
}

#endif
