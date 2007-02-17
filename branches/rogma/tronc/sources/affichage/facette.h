/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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
#ifndef PU_AFFICHAGE_FACETTE_H_
#define PU_AFFICHAGE_FACETTE_H_

#include <base/association.h>
#include <base/modele.h>
#include <base/implantation/base_vue.h>


namespace ProjetUnivers {
  namespace Affichage {
    
    class Objet ;

    /// Une facette d'affichage d'un objet.
    /*!
    */
    class Facette : virtual public Base::Implantation::BaseVue
    {
    public:

      /// Objet de cette facette.          
      Base::Association<Objet> AccesObjet() const ;
   
    
    // @}
    /*!
      @name Construction/Destruction
    */
    // @{


      /// Initialise la vue, active les ressources nécessaires.
      virtual void Initialiser() =0 ;

      /// Termine la vue, libère les ressources.
      virtual void Terminer() = 0 ;

      /// Destructeur de classe abstraite.    
      virtual ~Facette() ;

    
    protected: 
    
      /// Constructeur de classe abstraite.
      Facette() ;
    // @}
    
      /// Objet sur lequel s'applique la facette.
      /*!
      @remark
        Mis à jour par l'objet lorsque la facette lui est attachée.
      */
      Base::Association<Objet> objet ;
      
      /// Vrai si la facette a été initialisée.
      Base::Booleen initialise ;
      
      friend class Objet ;
            
    };
  }
}



#endif /*PU_AFFICHAGE_FACETTE_H_*/
