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

#ifndef _PU_NOYAU_AFFICHABLE_H_
#define _PU_NOYAU_AFFICHABLE_H_

#include <base/chaine.h>
#include <base/composition.h>

namespace ProjetUnivers {

  namespace Noyau {

    // using namespace ProjetUnivers::Base ;


    /// Classe des objets affichables.
    
    /// \remark
    ///   � supprimer...
    class Affichable {
    public:
    
      /// Classe abstraite donc destructeur virtuel.
      virtual ~Affichable() ;

     
    protected:

      /// Classe abstraite donc constructeur prot�g�.
      /// On indique le nom du mesh Ogre.
      Affichable(const Base::Chaine& _nomDuMesh = "") ;
  
  
      // *********************************
      // GROUP: Attributs sp�cifiques Ogre
      // *********************************
      
  
      /// Le nom du mesh Ogre, correspondant � l'affichage de 
      Base::Chaine nomDuMesh ;
  
      /// Les objets affichables le sont pour l'instant par Ogre.
      /// Composition< Ogre::Mesh > mesh ;
    };
  }
}
#endif
