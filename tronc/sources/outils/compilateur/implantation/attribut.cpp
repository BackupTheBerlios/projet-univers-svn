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


#include <outils/compilateur/attribut.h>
#include <opencxx/mop.h>

using namespace Opencxx ;

namespace ProjetUnivers {

  using namespace Base ;

  namespace Outils {
  
    namespace Compilateur 
    {
  
      Attribut::Attribut(Member& _membre)
      : nom(_membre.Name()->ToString()), type()
      {
      
        TypeInfo informationType ;
        _membre.Signature(informationType) ;
        
        type = Type::Construire(informationType, _membre.Supplier()->GetEnvironment()) ;
      
      }

      void Attribut::Initialiser()
      {
        if (type != NULL)
          type->Initialiser() ;
      }
  
      Booleen Attribut::VerifieRegles() const 
      {
        
        if (this->type != 0)
        {
          
          Booleen validiteType(type->TypeAttributCorrect()) ;

          /*!
            \todo
              vérifier que le nom est bien un identificateur dans les 
              bonnes formes
          */
          Booleen validiteNom(VRAI) ;
          
          return validiteType && validiteNom ;
        }
        else
          return FAUX ;
      }
    
      Chaine Attribut::Afficher() const
      {
        Chaine resultat = nom ;
        if (type != NULL)
          resultat += " : " + type->Afficher() ;  
        else
          resultat += " : type non reconnu" ;  
        
        return resultat ;
      }
      
    }
  }
  
}
