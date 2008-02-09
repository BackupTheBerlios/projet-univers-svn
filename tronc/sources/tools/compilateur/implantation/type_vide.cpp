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

#include <tools/compilateur/type_vide.h>
#include <tools/compilateur/utilitaires_opencxx.h>

using namespace Opencxx ;

namespace ProjetUnivers {

  namespace Tools {
    
    namespace Compiler 
    {

      TypeVide* TypeVide::Construire(Opencxx::TypeInfo& informationType,
                                     Opencxx::Environment* environement)
      {

        rDebug("TypeVide::Construire = "+informationType.WhatIs()) ;
        
        if (informationType.IsBuiltInType() & VoidType)
        {
          return new TypeVide() ;
          
        }
        else
          
          return NULL ;
          
      }

      
      void TypeVide::Initialiser()
      {}
   
  
      
      std::string TypeVide::Afficher() const
      {
        return "void" ;  
      }
          
      TypeVide::TypeVide()
      : Type(NULL)
      {}

      bool TypeVide::TypeAttributCorrect() const 
      {
        return false ;
      }

      bool TypeVide::TypeParametreCorrect() const 
      {
        return true ;
      }


      bool TypeVide::Valeur() const
      {
        return false ;
      }

      bool TypeVide::Objet() const
      {
        return false ;
      }



    }
  }
}
