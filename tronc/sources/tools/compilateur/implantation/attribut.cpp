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

#include <opencxx/mop.h>

#include <tools/compilateur/attribut.h>


using namespace Opencxx ;

namespace ProjetUnivers {
  namespace Tools {
    namespace Compiler {
  
      /// Message d'erreur pour les types d'attribut
      const std::string MessageErreurTypeAttribut = "type d'attribut incorect" ;
  
      Attribut::Attribut(Member& _membre)
      : membre(_membre), nom(_membre.Name()->ToString()), type(),
        classe(_membre.Supplier())
      {
      
        TypeInfo informationType ;
        _membre.Signature(informationType) ;
        
        type.reset(Type::Construire(informationType, _membre.Supplier()->GetEnvironment())) ;
      
      }

      void Attribut::Initialiser()
      {
        if (type.get() != NULL)
          type->Initialiser() ;
      }
  
      bool Attribut::VerifieRegles() const 
      {
        
        if (this->type.get() != NULL)
        {
          
          bool validiteType(type->TypeAttributCorrect()) ;

          if ( ! validiteType)
          {
            
            char* nomCString = (char *)malloc(sizeof(char)*(nom.length() +1)) ;
            strcpy(nomCString, nom.c_str()) ;
            
            Ptree* ArbreNom = (new Leaf(nomCString,
                               nom.length())) ;
                               
                               
            
            
//            std::string message = "dans la classe : " + std::string(classe->Name()->ToString()) + 
//                             " l'attribut " + membre.Name()->ToString() + 
//                             " a un type interdit" ;
//
//            rDebug(message) ;
//            
//            classe->ErrorMessage(
//                                 classe->GetEnvironment()->GetOuterEnvironment(), 
//                                 "type d'attribut incorrect:", 
//                                 membre.Name(), 
//                                 membre.Name()) ;
                                   
          }

          /*!
            \todo
              vérifier que le nom est bien un identificateur dans les 
              bonnes formes
          */
          bool validiteNom(true) ;
          
          return validiteType && validiteNom ;
        }
        else
          return false ;
      }
    
      std::string Attribut::Afficher() const
      {
        std::string resultat = nom ;
        if (type.get() != NULL)
          resultat += " : " + type->Afficher() ;  
        else
          resultat += " : type non reconnu" ;  
        
        return resultat ;
      }
      
    }
  }
  
}
