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


#include <rlog/rlog.h>

#include <tools/compilateur/utilitaires_opencxx.h>

#include <tools/compilateur/type.h>
#include <tools/compilateur/type_template.h>
#include <tools/compilateur/type_classe.h>
#include <tools/compilateur/type_predefini.h>
#include <tools/compilateur/type_enumere.h>

using namespace Opencxx ;


namespace ProjetUnivers {

  namespace Tools {
  
    namespace Compiler 
    {

      /// Destructeur de classe abstraite.
      Type::~Type()
      {}
       
      Type::Type(Environment* _espaceDeNom)
      : espaceDeNom(_espaceDeNom)
      {}

    
      Type* Type::Construire(Opencxx::TypeInfo& informationType,
                             Opencxx::Environment* environement)
      {

        rDebug("Type::Construire") ;
        
        Type* resultat ;
        
        resultat = TypeTemplate::Construire(informationType, environement) ;
        if (resultat)
          return resultat ;
          
        resultat = TypeClasse::Construire(informationType, environement) ;
        if (resultat)
          return resultat ;

        resultat = TypeEnumere::Construire(informationType, environement) ;
        if (resultat)
          return resultat ;
        
        resultat = TypePredefini::Construire(informationType, environement) ;
        if (resultat)
          return resultat ;
         
        
      }

      
    }
  }
}
