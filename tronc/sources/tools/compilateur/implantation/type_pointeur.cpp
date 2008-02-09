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

#include <tools/compilateur/type_pointeur.h>

using namespace Opencxx ;

namespace ProjetUnivers {

  namespace Tools {
    
    namespace Compiler 
    {

      TypePointeur* TypePointeur::Construire(Opencxx::TypeInfo& informationType,
                                             Opencxx::Environment* environement)
      {

        rDebug("TypePointeur::Construire = "+informationType.WhatIs()) ;
        
        if (informationType.IsPointerType())
        {
          Opencxx::TypeInfo pointe ;
          informationType.Dereference(pointe) ;
          
          return new TypePointeur(Type::Construire(pointe, environement), 
                                  environement) ;
          
        }
        else
          
          return NULL ;
          
      }

      
      void TypePointeur::Initialiser()
      {
        pointe->Initialiser() ;
      }
      
      std::string TypePointeur::Afficher() const
      {
        return pointe->Afficher() + "*" ;  
      }
          
      TypePointeur::TypePointeur(Type* _pointe, Opencxx::Environment* _environement)
      : Type(_environement), pointe(_pointe)
      {}

      bool TypePointeur::TypeAttributCorrect() const 
      {
        /// ça dépend de ce qu'est le type pointé...
        return false ;
      }

      bool TypePointeur::TypeParametreCorrect() const 
      {
        /// correct si le type pointé est objet
        if (pointe->Objet())
          return true ;
        else
          return false ;
      }


      bool TypePointeur::Valeur() const
      {
        return true ;
      }

      bool TypePointeur::Objet() const
      {
        return false ;
      }



    }
  }
}
