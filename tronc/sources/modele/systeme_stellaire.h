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

#ifndef _PU_UNIVERS_SYSTEME_STELLAIRE_H_
#define _PU_UNIVERS_SYSTEME_STELLAIRE_H_

#include <base/ensemble_composition.h>
#include <base/types.h>
#include <base/chaine.h>
#include <modele/objet_physique.h>




namespace ProjetUnivers {

  namespace Modele {


    class Planetoide ;
    class Etoile ;
    
    
    /// Représente un système stellaire.

    /*!
    Type de classe
    
      Objet
    
      Concret
    */
    class SystemeStellaire : public ObjetPhysique {
    public:


      // *******************
      /// @name Constructeur
      // *******************
      // @{

      /// Constructeur.
      SystemeStellaire() ;
      
      /// Ajoute une étoile.
      void AjouterEtoile(Etoile* _etoile) ;
      
      /// Ajoute un planétoïde.
      void AjouterPlanetoide(Planetoide* _planetoide) ;
      
      // @}
      
    private:

      // *******************
      /// @name Attributs
      // *******************
      // @{

      
      /// Etoiles du système 
      Base::EnsembleComposition< Etoile > etoiles ;
      
      /// Planètes/Satélites
      Base::EnsembleComposition< Planetoide > planetoides ;

      /// Nom du système.
      Base::Chaine nom ;

      // @}
    };
    
    
  }

}

#endif
