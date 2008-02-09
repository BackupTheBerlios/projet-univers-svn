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

#include <tools/compilateur/type_classe.h>
#include <tools/compilateur/utilitaires_opencxx.h>
#include <tools/compilateur/meta_classe.h>

using namespace Opencxx ;

namespace ProjetUnivers {
  namespace Tools {
    namespace Compiler {

      TypeClasse* TypeClasse::Construire(Opencxx::TypeInfo& informationType,
                                         Opencxx::Environment* environement)
      {

        rDebug("TypeClasse::Construire = "+informationType.WhatIs()) ;
        
        if (informationType.WhatIs() == ClassType)
        {
          Class* classe = informationType.ClassMetaobject() ;

          MetaClasse* metaClasse = static_cast<MetaClasse*>(classe) ;
          
          return new TypeClasse(
            metaClasse->GetEnvironment()->GetOuterEnvironment(), metaClasse) ;
          
          
        }
        else
          
          return NULL ;
          
      }

      
      void TypeClasse::Initialiser()
      {
        this->classe->Initialiser() ;
      }
   
  
      
      std::string TypeClasse::Afficher() const
      {
        return "classe " + NomComplet(this->classe) ;  
      }
          
      TypeClasse::TypeClasse(Environment* _espaceDeNom, MetaClasse* _classe)
      : Type(_espaceDeNom), classe(_classe)
      {}

      bool TypeClasse::TypeAttributCorrect() const 
      {
        
        // la classe doit être une classe de valeur...ou bien ne pas faire 
        // partie de PU
        if (classe->NamespaceProjetUnivers())
        {
          
          return classe->Valeur() ;
        }
        return true ;
          
      }
      bool TypeClasse::TypeParametreCorrect() const
      {
        return false ;
      }
      

      bool TypeClasse::Valeur() const
      {
        return classe->Valeur() ;
      }

      bool TypeClasse::Objet() const
      {
        return classe->Objet() ;
      }



    }
  }
}
