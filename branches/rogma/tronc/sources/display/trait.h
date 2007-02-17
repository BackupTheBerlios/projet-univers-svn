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
  namespace Display {
    
    class Object ;

    /// Une facette d'affichage d'un objet.
    /*!
    */
    class Trait : virtual public Base::Implantation::BaseVue
    {
    public:

      /// Object de cette facette.          
      Base::Association<Object> AccesObject() const ;
   
    
    // @}
    /*!
      @name Construction/Destruction
    */
    // @{


      /// Initialise la vue, active les ressources n�cessaires.
      virtual void init() =0 ;

      /// Termine la vue, lib�re les ressources.
      virtual void close() = 0 ;

      /// Destructeur de classe abstraite.    
      virtual ~Trait() ;

    
    protected: 
    
      /// Constructeur de classe abstraite.
      Trait() ;
    // @}
    
      /// Object sur lequel s'applique la facette.
      /*!
      @remark
        Mis � jour par l'objet lorsque la facette lui est attach�e.
      */
      Base::Association<Object> objet ;
      
      /// Vrai si la facette a �t� initialis�e.
      Base::Booleen initialise ;
      
      friend class Object ;
            
    };
  }
}



#endif /*PU_AFFICHAGE_FACETTE_H_*/
