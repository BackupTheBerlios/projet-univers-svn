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

#ifndef _PU_UNIVERS_PERSONNAGE_H_
#define _PU_UNIVERS_PERSONNAGE_H_

#include <base/association.h>
#include <modele/poste.h>


namespace ProjetUnivers {

  namespace Modele {

    class Vaisseau ;
    

    /// Un poste de pilote d'un vaisseau.
    /*!
      Un poste peut être par exemple le fait d'être le pilote d'un vaisseau.
    
      Type de classe :
        - Objet
        - Concret
    */
    class Pilote : public Poste {
    public:




      /// Constructeur.
      Pilote() ;
      
    private:
    
      /// Vaisseau piloté
      Base::Association< Vaisseau > vaisseau ;
    
      
    };
    
  }
}

#endif

