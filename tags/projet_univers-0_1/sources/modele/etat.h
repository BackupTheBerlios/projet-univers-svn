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
        Un �tat caract�rise le fait d'�tre dans une certaine �tape du 
        d�roulement d'une partie, il s'agit par exemple 
        du fait d'�tre dans un menu, 
        ou dans une certaine situation au cours d'une partie. 
         
        Un �tat peut avoir des sous-�tats, mais un seul est alors activ�. 
         
        Un �tat poss�de une donn�e utilisateur, qui contient les 
        informations fonctionnelles. 
    @par Etat
      planning


      */
      class Etat {
      public:
          
      // ***************************
      /*! 
        @name M�thodes principales
      */
      // ***************************
      // @{

  
        /// Activation de l'�tat.
        void Entrer() ;
  
  
      // @}
      // ***************************
      /*!
        @name M�thodes � red�finir pour utiliser la classe
      */
      // ***************************
      // @{

        
        /// Initialisation de l'�tat, r�alis�e une fois � l'entr�e
        virtual void Initialiser() = 0 ;
  
        /// Terminaison de l'�tat, r�aliser � la sortie
        virtual void Finaliser() = 0 ;
  
  
      // @}
      // *****************************
      /*!
        @name Gestion des sous-�tats
      */
      // *****************************
      // @{       

        
        /// Ajout d'un sous-�tat.
        void AjouterSousEtat(Etat*) ;
        
        /// Suppression d'un sous-�tat.
        void SupprimererSousEtat(const Base::Association< Etat >&) ;   
        
        /// Active un sous-�tat.
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
      
        /// Contruit un �tat.
        Etat(const Base::Chaine& _nom) ;
          
      // @}
      // ****************    
      /*!
        @name Attributs
      */
      // ****************
      // @{   

      
        /// Le sous-�tat actif, s'il y a des sous-�tats.
        /*!
          C'est un �l�ment de sousEtats.
        */
        Base::Association<Etat> sousEtatActif ;    
  
        /// Sous �tat �ventuels.
        Base::EnsembleComposition<Etat> sousEtats ;
              
        /// Sur �tat �ventuel.
        Base::Association<Etat> surEtat ;

      // @}
      };

    }
  }
}

#endif
