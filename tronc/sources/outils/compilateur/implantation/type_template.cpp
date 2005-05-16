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

#include <outils/compilateur/type_template.h>
#include <base/implantation/liste_valeur.h>
#include <base/implantation/iterateur_liste_valeur.h>
#include <opencxx/mop.h>

using namespace std ;
using namespace Opencxx ;
using namespace ProjetUnivers::Base ;
using namespace ProjetUnivers::Base::Implantation ;

namespace ProjetUnivers {

  namespace Outils {
    
    namespace Compilateur 
    {

      /// Identifie la selection par un namespace
      /*!
        Reconnait des arbre de la forme : 
        [<i>namespace</i> :: <i>reste</i>]
      */
      TypeTemplate* TypeTemplate::IdentifierParcoursNamespace
                  (Ptree* type, Environment* environement, 
                   const ListeValeur<Chaine>& prefixe) 
      {
      
      //  cout << "coucou 1" << endl ;
          
      
        Ptree* espaceDeNom ;
        Ptree* suiteType ;
      
        if (PtreeUtil::Match(type, "[%? :: %? %_]", &espaceDeNom, &suiteType))
        {
          
      //    cout << "coucou 2" << endl ;
          
          
          // on vérifie que le premier élément est bien un identifiant de 
          // namespace
          Environment* environementNameSpace 
            = environement->LookupNamespace0(espaceDeNom) ;
      
      //    cout << "coucou 3" << endl ;
          
          // ce n'est pas un namespace... on arrete
          if (environementNameSpace == NULL)
            return NULL ;
          
      //    cout << "coucou 4" << endl ;
          
          // si on en a trouvé un c'est que c'ets un namespace 
            
          if (environementNameSpace->IsNamespace() != NULL)
          {  
      
            
            // on a bien affaire à un namespace cool...
            // maintenant on cherche à reconnaitre la suite...
            Chaine nom = espaceDeNom->ToString() ;
      
            ListeValeur<Chaine> nouveauPrefixe(prefixe) ;
            nouveauPrefixe.AjouterEnQueue(nom) ;
            
            // récurrence
            return IdentifierParcoursNamespace(suiteType, 
                    environement, nouveauPrefixe) ;
          }
        }
        
        Ptree* classeTemplate ;
        Ptree* parametres ;
        
        if (PtreeUtil::Match(type, "[%? [< %? >]]", &classeTemplate, &parametres))
        {
          // on a affaire à un template
          Chaine nomTemplate(classeTemplate->ToString()) ;
      
          ListeValeur<Chaine> nomComplet(prefixe) ;
          nomComplet.AjouterEnQueue(nomTemplate) ;
          
          Composition<TypeTemplate> resultat(
              new TypeTemplate(nomComplet, parametres)) ;
      
          return resultat.Liberer() ;
         
          
        }
        
        // ce n'en est pas un
        return NULL ;
      
      }
      
      
      
      
      /// Identifie un type template
      /*!
        Est capable de reconnaitre les templates préfixés par des 
        namespaces, ainsi que ceux déjà identifiés comme des templates par 
        opencxx.
      */
      TypeTemplate* TypeTemplate::IdentifierTypeTemplate
                    (Ptree* type,   
                     TypeInfo informationType, 
                     Environment* environement)
      {
        ListeValeur<Chaine> nomComplet ;
      
        switch(informationType.WhatIs())
        {
        case TemplateType:  
          
          nomComplet.AjouterEnQueue(informationType.FullTypeName()->ToString()) ;
      
          Ptree* parametre ;
          PtreeUtil::Match(type, "[%* [< %? >]]", &parametre) ;
      
          return new TypeTemplate(nomComplet, parametre) ;
          break ;
      
        case UndefType :
          
          // ici c'ets plus compliqué, on a probablemenr affaire à un 
          // template un peu trop compliqué pour OpenC++ (avec des namesapces)
          
          // exemple : 
          // Base::Association< A > a ;
          // Ptree correspondant : 
          // [0 [Base :: [Association [< [[[A] [0]]] >]]] [[a]] ;]
          
          return IdentifierParcoursNamespace(type, environement, ListeValeur<Chaine>()) ;
          
      
          break;
          
        default:
          return NULL ;
        
        }
        
      }



      TypeTemplate* TypeTemplate::Construire(Opencxx::Member& _membre)
      {
        TypeInfo informationType ;
        _membre.Signature(informationType) ;
      
        
        // un peu de bricolage
        Class* classe = _membre.Supplier() ;
        MemberList* membres = classe->GetMemberList() ;
        Entier nombreDeMembres = membres->Number() ;
        Ptree* declarationAttribut 
            = membres->Ref(nombreDeMembres-1)->definition ;

        Environment* environement 
            = classe->GetEnvironment()->GetOuterEnvironment() ;
        
        return IdentifierTypeTemplate(declarationAttribut->Cdr()->Car(),
                                      informationType, 
                                      environement) ;
      }
      
  
      TypeTemplate::TypeTemplate(
                     const ListeValeur<Chaine>& _nomComplet, 
                     Ptree* _parametres)
      : Type(), nomComplet(_nomComplet), parametres(_parametres)
      {}
      
      Chaine TypeTemplate::Afficher() const
      {
        
        Chaine resultat ;
        
        for(IterateurListeValeur<Chaine> i(nomComplet) ; i.Valide() ; ++i)
        {
          if (resultat == Chaine(""))
            resultat = i ;
          else
            resultat = resultat + "::" + (Chaine)i ;  
        }
        
        Chaine sortieParametres(parametres->ToString()) ;
      
        return resultat + "<" + sortieParametres +">" ;
        
      }
  
    } 
  }
}

