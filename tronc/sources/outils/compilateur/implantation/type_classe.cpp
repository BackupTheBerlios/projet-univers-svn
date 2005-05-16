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

#include <outils/compilateur/type_classe.h>
#include <opencxx/mop.h>

#include <outils/compilateur/utilitaires_opencxx.h>

using namespace Opencxx ;
using namespace ProjetUnivers::Base ;

namespace ProjetUnivers {

  namespace Outils {
    
    namespace Compilateur 
    {

      TypeClasse* TypeClasse::Construire(Member& _membre)
      {

        TypeInfo informationType ;
        _membre.Signature(informationType) ;

        
        if (informationType.WhatIs() == ClassType)
        {
          Class* classe = informationType.ClassMetaobject() ;
          
          return new TypeClasse(NomComplet(classe)) ;
          
          
        }
        else
          
          return NULL ;
          
      }
   
  
          /// Transforme en chaine pour l'affichage.
      Chaine TypeClasse::Afficher() const
      {
        return this->nomComplet ;  
      }
          
      TypeClasse::TypeClasse(const Chaine& _nomComplet)
      : Type(), nomComplet(_nomComplet)
      {}



    }
  }
}
