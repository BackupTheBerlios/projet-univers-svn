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

using namespace ProjetUnivers::Base ;
using namespace Opencxx ;

namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {

      /*!
        Quelques fonctions utiles pour openc++.
      
      */


      /// Test si le membre est un attribut.
      Base::Booleen EstAttribut(Opencxx::Member& _membre)
      {
        return ! _membre.IsFunction() && 
               ! _membre.IsConstructor() &&
               ! _membre.IsDestructor() ;
      }
      
      /// Donne le nom complet d'un namespace.
      /*!
        \remarks 
          marche avec openc++ 2.8.5 (la mienne)
      */
      Base::Chaine NomComplet(Opencxx::Environment* _espaceDeNom)
      {
        Chaine resultat ;
        Opencxx::Environment* espaceDeNom = _espaceDeNom ;
        
        while(espaceDeNom != NULL && espaceDeNom->IsNamespace() != NULL)
        {
          if (resultat == Chaine(""))
            resultat = espaceDeNom->IsNamespace()->ToString() ;
          else
            resultat = Chaine(espaceDeNom->IsNamespace()->ToString()) 
                       + "::" + resultat ;
          
          espaceDeNom = espaceDeNom->GetOuterEnvironment() ;
        }
        
        return resultat ;  
      }
      
      /// Donne le nom complet d'une classe.
      /*!
        \remarks 
          marche avec openc++ 2.8.5 (la mienne)
      */
      Base::Chaine NomComplet(Opencxx::Class* _classe)
      {
        Chaine resultat ;
      
        resultat = 
            NomComplet(_classe->GetEnvironment()->GetOuterEnvironment()) 
            + "::" 
            + _classe->Name()->ToString() ;
      
        return resultat ;
      }
      
      
      /// Recherche une classe dans l'environement spécifié
      /*!
        Est capable de traiter les identificateurs de classes avec parcours 
        de namespaces/classes.
      */
//      Class* RechercheClasse(Environment* _environement, Ptree* _identificateur)
//      {
//        
//        
//        
//                
//      }
//
//
//      /*!
//        Recherche _parentSuppute dans les sur-classes de _classe.
//      */
//      Booleen HeriteDe(Class* _classe, Ptree* _parentSuppute)
//      {
//        
//        
//        Ptree* parents = _classe->BaseClasses() ;
//        
//        // parents est de la forme :
//        /*!
//          [: [public classe] , [classe] , ... , [protected classe] ]
//          [: ([ {virtual} (empty | public | protected | private) classe]) ]
//          Il faut reconnaitre les : 
//          [public classe] 
//          [classe]
//          [virtual protected classe]
//        */
//
//        Ptree* parent ;
//        
//        while(parents) 
//        {
//          
//          parent = parents->Cdr()->Car() ;
//          parents = parents->Cdr()->Cdr() ;
//          
//          Ptree* nomParent ;
//          
//          if (PtreeUtil::Match(parent, "[%* %?]", &nomParent) ||
//              PtreeUtil::Match(parent, "[%?]", &nomParent) || 
//              PtreeUtil::Match(parent, "[%* %* %?]", &nomParent))
//          {
//            if (Eq(nomParent,_parentSuppute))
//            
//              return VRAI ;
//              
//            else
//            {
//              Class* classeParente = _classe->GetEnvironment()
//              bool grandParent = 
//            }
//              
//              
//          }
//          
//        }
//
//                        
//        
//        while (PtreeUtil::Match(parents, "[%? [< %? >]]",
//        
//        
//        
//        
//      }
//      
//      Booleen HeriteDe(Class* _classe, const Chaine& _nomClasse) 
//      {
//        
//        
//        Ptree* nomClasse = (new Leaf(_nomClasse,_nomClasse.len())) ;
//        Ptree* nomBase = (new Leaf("Base",4)) ;
//        Ptree* nomProjetUnivers = (new Leaf("ProjetUnivers",13)) ;
//        Token tokenScope ;
//        tokenScope.ptr = "::" ;
//        tokenScope.len = 2 ;
//        tokenScope.kind = 274 ;
//        Ptree* scope = new Leaf(tokenScope) ;
//        Ptree* nomClasse2 = PtreeUtil::List(nomBase, scope, nomClasse) ;
//        Ptree* nomClasse3 = PtreeUtil::List(
//                                  nomProjetUnivers, scope, nomClasse2) ;  
//
//        // Maintenant, on cherche nomClasse, nomClasse2, nomClasse3 dans 
//        // toutes les classes...
//        
//        
//        
//       // Class*         
//        
//
//
//        
//
//      }

      
      

    }
  }
}



