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

#ifndef _PU_NOYAU_VUE_H_
#define _PU_NOYAU_VUE_H_

#include <base/association_virtuelle.h>
#include <base/association.h>


namespace ProjetUnivers {

  namespace Noyau {
  
    class Modele ;
    
  
    /*
    CLASS
      Vue
      
      Un point de vue sur une partie du modèle.

    TYPE_DE_CLASSE
      Objet
      Abstrait
    */
    
    /// Point de vue sur une partie du modèle de données.
    
    /// Il s'agit de la partie vue de l'application du patron : 
    /// modele (Modele), vue (Vue), contrôleur (Controle)
    class Vue {
    public:
        
    
    
    protected:

      /// Constructeur.
      Vue(const Base::Association< Modele > _modele) ;
      
      /// Modèle vu observé.
      DECLARATION_ASSOCIATION_VIRTUELLE(Modele, modele)
    
    };
  
  }
}

#endif
