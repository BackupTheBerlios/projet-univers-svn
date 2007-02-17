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

#ifndef _PU_BASE_VUE_H_
#define _PU_BASE_VUE_H_


#include <base/association.h>
#include <base/implantation/base_vue.h>


namespace ProjetUnivers {
  namespace Base {
    
    class Model ;
    
    /// L'abstraction d'une vue sur un Model
    /*!
    @par Utilisation

      D�river de cette classe et implanter update.
           
    @par Fonctionnement
    
      Une Vue sur un mod�le est notifi�e des changements apparus sur ce 
      mod�le. 
      La notification est effectu�e globalement lorsque le ViewPoint 
      contenant cette Vue est rafraichi.
    
    @pre
      Model doit �tre une sous classe de ProjetUnivers::Base::Model
    
    */
    template <class M> class Vue : virtual public Implantation::BaseVue
    {
    public:
    
      /// Mise � jour.
      virtual void update(const Evenement& _evenement) = 0 ;
    
      /// Destructeur de classe abstraite.
      virtual ~Vue() ;
    
      virtual Association<Model> AccesObserve() const ;
    
    protected:
    
      /// Constructeur de classe abstraite.
      Vue(const Association<M>& _modele) ;
    
      /// Efface la relation vers mod�le
      virtual void DetacherDeModel() ;
      
      /// Ce que la vue voit.
      Association<M> observe ;
    };
    
  }
}

#include <base/implantation/vue.cxx>


#endif

