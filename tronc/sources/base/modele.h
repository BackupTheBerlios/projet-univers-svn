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

#ifndef _PU_BASE_MODELE_H_
#define _PU_BASE_MODELE_H_


#include <base/association.h>
#include <base/ensemble_association.h>


namespace ProjetUnivers {

  namespace Base {
    
    namespace Implantation
    {
      class BaseVue ;
    }


    /// L'abstraction d'un mod�le.
    /*!
      A utiliser en combinaison avec ProjetUnivers::Base::Vue.
    */
    class Modele
    {
    public:
    
      /// Enregistre une vue.
      /*!
        Toutes les vues enregistr�es seront notifi�es des changements 
        de cet objet.
      */
      void AjouterVue(const Association<Implantation::BaseVue>& _vue) ;
      
      /// Des-enregistre une vue.
      void EnleverVue(const Association<Implantation::BaseVue>& _vue) ;
    
      /// Classe abstraite donc destructeur virtuel.
      virtual ~Modele() ;
    
    protected:

      /// Classe abstraite donc constructeur prot�g�.
      Modele() ;

      /// Notifie les vues du changement.
      void Notifier() ;
    
    private:
    
      /// Les vues pour lesquelles il faut avertir des changements.
      EnsembleAssociation<Implantation::BaseVue> observateurs ;
      
      /// Les constructeurs de vue � appeler lorsqu'on cr�e un nouveau mod�le
//      static Implantation::BaseVue* (*) const Association<Modele>&) ...

    };
    
  }
}

#endif

