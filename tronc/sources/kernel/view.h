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

#ifndef _PU_KERNEL_VUE_H_
#define _PU_KERNEL_VUE_H_


#include <kernel/implementation/base_view.h>


namespace ProjetUnivers {
  namespace Kernel {
    
    class Model ;
    
    /// L'abstraction d'une vue sur un Model
    /*!
    @par Utilisation

      Dériver de cette classe et implanter update.
           
    @par Fonctionnement
    
      Une View sur un modèle est notifiée des changements apparus sur ce 
      modèle. 
      La notification est effectuée globalement lorsque le ViewPoint 
      contenant cette View est rafraichi.
    
    @pre
      Model doit être une sous classe de ProjetUnivers::Kernel::Model
    
    */
    template <class M> class View : virtual public Implementation::BaseView
    {
    public:
    
      /// Mise à jour.
      virtual void update(const Event& _event) = 0 ;
    
      /// Destructeur de classe abstraite.
      virtual ~View() ;
    
      virtual Model* getModel() const ;
    
    protected:
    
      /// Constructeur de classe abstraite.
      View(M* _model) ;
    
      /// Efface la relation vers modèle
      virtual void detach() ;
      
      /// Ce que la vue voit.
      M* observed ;
    };
    
  }
}

#include <kernel/implementation/view.cxx>


#endif

