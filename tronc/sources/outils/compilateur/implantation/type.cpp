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


#include <outils/compilateur/utilitaires_opencxx.h>

#include <outils/compilateur/type.h>
#include <outils/compilateur/type_template.h>
#include <outils/compilateur/type_classe.h>
#include <outils/compilateur/type_predefini.h>
#include <outils/compilateur/type_enumere.h>

using namespace Opencxx ;

namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {

      /// Destructeur de classe abstraite.
      Type::~Type()
      {}
       
      Type::Type()
      {}

    
      // Construction.
      /*!
        Un faux constructeur.
        \param _membre Un attribut d'une classe.
        \result Le type de l'attribut
        
      */
      Type* Type::Construire(Member& _membre)
      {
        
        Type* resultat ;
        
        if (EstAttribut(_membre))
        {
        
          resultat = TypeTemplate::Construire(_membre) ;
          if (resultat)
            return resultat ;
            
          resultat = TypeClasse::Construire(_membre) ;
          if (resultat)
            return resultat ;

          
         
         
          
        }
        
        else
          return NULL ;
                
      }

      
    }
  }
}
