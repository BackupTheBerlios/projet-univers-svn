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

#include <outils/compilateur/type_classe.h>
#include <outils/compilateur/utilitaires_opencxx.h>
#include <outils/compilateur/meta_classe.h>

using namespace Opencxx ;
using namespace ProjetUnivers::Base ;

namespace ProjetUnivers {

  namespace Outils {
    
    namespace Compilateur 
    {

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
   
  
      
      Chaine TypeClasse::Afficher() const
      {
        return "classe " + NomComplet(this->classe) ;  
      }
          
      TypeClasse::TypeClasse(Environment* _espaceDeNom, MetaClasse* _classe)
      : Type(_espaceDeNom), classe(_classe)
      {}

      Booleen TypeClasse::TypeAttributCorrect() const 
      {
        
        // la classe doit être une classe de valeur...ou bien ne pas faire 
        // partie de PU
        if (classe->NamespaceProjetUnivers())
        {
          
          return classe->Valeur() ;
        }
        return VRAI ;
          
      }

      Base::Booleen TypeClasse::Valeur() const
      {
        return classe->Valeur() ;
      }

      Base::Booleen TypeClasse::Objet() const
      {
        return classe->Objet() ;
      }



    }
  }
}
