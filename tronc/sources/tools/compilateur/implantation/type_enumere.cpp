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

#include <tools/compilateur/type_enumere.h>

#include <tools/compilateur/utilitaires_opencxx.h>

using namespace Opencxx ;

namespace ProjetUnivers {

  namespace Tools {
    
    namespace Compiler 
    {

      TypeEnumere* TypeEnumere::Construire(Opencxx::TypeInfo& informationType,
                                           Opencxx::Environment* environement)
      {

        
        if (informationType.WhatIs() == EnumType)
        {
          Ptree* spec ;
          informationType.IsEnum(spec) ;
          
          return new TypeEnumere(spec->Cdr()->Cdr()->Car()->Cdr()->Car()) ;
          
          
        }
        else
          
          return NULL ;
          
      }

      void TypeEnumere::Initialiser()
      {}
   
  
          /// Transforme en chaine pour l'affichage.
      std::string TypeEnumere::Afficher() const
      {
        return std::string("enumere ") + this->elements->ToString() ;  
      }
          
      TypeEnumere::TypeEnumere(Ptree* _elements)
      : Type(NULL), elements(_elements)
      {}

      bool TypeEnumere::TypeAttributCorrect() const 
      { 
        return true ;
      }

      bool TypeEnumere::TypeParametreCorrect() const 
      { 
        return false ;
      }

      
      bool TypeEnumere::Valeur() const
      {
        return true ;
      }

      bool TypeEnumere::Objet() const
      {
        return false ;
      }


    }
  }
}
