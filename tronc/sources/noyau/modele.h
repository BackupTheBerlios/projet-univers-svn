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
 
#ifndef _PU_NOYAU_MODELE_H_
#define _PU_NOYAU_MODELE_H_

#include <base/ensemble_association.h>
#include <base/association.h>


namespace ProjetUnivers {

  namespace Noyau {
  
    class Vue ;
  
    /// \brief 
    /// Classe abstraite du modèle de données.
    
    /// Il s'agit de la partie Modèle de l'application du patron : 
    /// 
    /// modèle (Modele), vue (Vue), contrôleur (Controle)
    class Modele {
    public:

      // *************************    
      /// @name Méthode principale
      // *************************
      // @{

      
      /// Enregistre une vue.
      
      /*!
        Toutes les vues enregistrées seront notifiées des changements 
        de cet objet.
      */
      void EnregistrerVue(const Base::Association<Vue>& _vue) ;



    
      // @}
      // *******************************
      /// @name Constructeur Destructeur
      // *******************************
      // @{
     
      

      /// Classe abstraite donc destructeur virtuel.
      virtual ~Modele() ;
    
    
    protected:

      /// Classe abstraite donc constructeur protégé.
      Modele() ;
       
      // }@
    
    private:
    
    
      /// Les vues qu'il faut notifier des changements.
      Base::EnsembleAssociation<Vue> observateurs ;
    
    
    
    
    };
  
  }
}

#endif
