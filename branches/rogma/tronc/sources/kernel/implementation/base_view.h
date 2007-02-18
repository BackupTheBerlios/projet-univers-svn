/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#ifndef _PU_KERNEL_BASE_VIEW_H_
#define _PU_KERNEL_BASE_VIEW_H_


#include <kernel/event.h>


namespace ProjetUnivers {
  namespace Kernel {
    
    class ViewPoint ;
    class Model ;
    
    namespace Implementation {

      /// Classe de base des vues.
      /*!
        @todo
          Choisir quoi faire lorsqu'on a oublié d'ajouter la vue à un point de 
          vue; pour l'instant la vue n'est pas rafraichie.
      */
      class BaseView
      {
      public:

        /// Mise à jour.
        virtual void update(const Event& _event) = 0 ;


      /*!
        @name Gestion des mises à jour
      */
      // @{

        /// Marque la vue comme devant être rafraichie au prochain tour.
        void markToUpdate(const Event& _event) ;

        /// Marque la vue comme devant être détruite au prochain tour.
        void markToDestroy() ;

      // @}

        /// Destructeur de classe abstraite.
        virtual ~BaseView() ;
        
        /// get au modele.
        virtual Model* getModel() const = 0 ;

      protected:
      
        /// Constructeur de classe abstraite.
        BaseView() ;

        /// Efface la relation vers modèle
        virtual void detach() = 0 ;
        
        /// Les vues sont groupées au sein d'un point de vue
        ViewPoint* viewPoint ;

        /*!
          Chemin complet pour gcc 4
        */
        friend class ::ProjetUnivers::Kernel::ViewPoint ;
        friend class ::ProjetUnivers::Kernel::Model ;
      };
    }    
  }
}

#endif

