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
#ifndef PU_AFFICHAGE_FACETTE_H_
#define PU_AFFICHAGE_FACETTE_H_

#include <base/association.h>
#include <base/modele.h>


namespace ProjetUnivers {
  namespace Affichage {
    
    class Objet ;

    /// Une facette d'affichage d'un objet.
    /*!
    */
    class Facette
    {
    public:

    /*!
      @name Accès
      
    */
    // @{

      /// Objet de cette facette.          
      Base::Association<Objet> AccesObjet() const ;
    
    // @}          
    /*!
      @name Mises à jour
      
      Par défaut, ces traitements ne font rien.
    */
    // @{
    
    
//      /// Initialise la vue.
//      virtual void Initialiser() ;
//
//      /// Termine la vue.
//      virtual void Terminer() ;
//    
//      /// Mise à jour.
//      virtual void Raffraichir() ;
    
    // @}

      /// Destructeur de classe abstraite.    
      virtual ~Facette() ;

    
    protected: 
    
      /// Constructeur de classe abstraite.
      Facette() ;
      
      /// Objet sur lequel s'applique la facette.
      Base::Association<Objet> objet ;
      
      friend class Objet ;
            
    };
  }
}



#endif /*PU_AFFICHAGE_FACETTE_H_*/
