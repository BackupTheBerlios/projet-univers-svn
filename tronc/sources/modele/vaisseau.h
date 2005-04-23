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

#ifndef _PU_MODELE_VAISSEAU_H_
#define _PU_MODELE_VAISSEAU_H_

#include <base/ensemble_composition.h>
#include <base/composition.h>

#include <modele/bien.h>

namespace ProjetUnivers {

  namespace Modele {
    
    
    class Composant ;
    class Poste ;
      
    /// Repr�sente un vaisseau.
    
    /*!
    Type de classe
    
      Objet
    
      Concret  
    */
    class Vaisseau : public Bien {
    public:
    

      // *******************
      /// @name Construction
      // *******************
      // @{


      /// constructeur.
      Vaisseau() ;
    
      /// Ajoute un composant.
      void AjouterComposant(Composant* _composant) ;


      // @}
    private:  
      

      // ****************
      /// @name Attributs
      // ****************
      // @{
      

      /// Les composants du vaisseau.
      Base::EnsembleComposition< Composant > composants ;

      /// Les postes pouvant �tre occup�s sur le vaisseau.
      Base::EnsembleComposition< Poste > postes ;
    

      /// Le fabriquant du vaisseau
//    Base::Association< Groupe > fabriquant ;
 
 
      // @}
    };
    
    
  }

}

#endif
