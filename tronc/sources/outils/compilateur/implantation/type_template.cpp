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
#include <base/implantation/liste_valeur.h>
#include <base/implantation/iterateur_liste_valeur.h>

#include <outils/compilateur/type_template.h>
#include <outils/compilateur/utilitaires_opencxx.h>

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
                  (Ptree* type, Environment* environement) 
      {
      
        rDebug("coucou 1") ;
          
      
        Ptree* espaceDeNom ;
        Ptree* suiteType ;
      
        if (PtreeUtil::Match(type, "[%? :: %r]", &espaceDeNom, &suiteType))
        {
          
          rDebug("coucou 2") ;
          
          
          /*!
            on vérifie que le premier élément est bien un identifiant de 
            namespace
          */
          char* nom = espaceDeNom->GetPosition() ;
          int len = espaceDeNom->GetLength() ;
          
          Environment* environementNameSpace 
            = environement->LookupNamespace(nom, len) ;

          Class* Classe 
            = environement->LookupClassMetaobject(espaceDeNom) ;
      
          rDebug("coucou 3") ;
          
          // ce n'est pas un namespace... on arrete
          if (environementNameSpace != NULL) 
            
            return IdentifierParcoursNamespace(suiteType, environementNameSpace) ;
          
          if (Classe != NULL)
          
            return IdentifierParcoursNamespace(suiteType, Classe->GetEnvironment()) ;
            
          rDebug(" " + Chaine(espaceDeNom->ToString())+"non reconnu dans "+
                 NomComplet(environement)) ;
          return NULL ;
          
        }
        
        Ptree* nomClasseTemplate ;
        Ptree* parametres ;
        
        if (PtreeUtil::Match(type, "[[%? [< %? >]]]", 
                             &nomClasseTemplate, &parametres))
        {
      
      
          rDebug("dans "+NomComplet(environement)+ 
                 " on a trouve le template "+nomClasseTemplate->ToString()) ;
                  
          // on récupère sa classe
          TemplateClass* classeTemplate = static_cast<TemplateClass*>(
            environement->LookupClassMetaobject(nomClasseTemplate)) ;
          
          Composition<TypeTemplate> resultat(
              new TypeTemplate(classeTemplate, parametres)) ;
      
          return resultat.Liberer() ;
         
          
        }
        
        rDebug(" "+Chaine(type->ToString())+" na pas la forme dun template") ;
        
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


        rDebug("TypeTemplate::IdentifierTypeTemplate") ;
        
      
        switch(informationType.WhatIs())
        {
        case TemplateType:  
          
//          nomComplet.AjouterEnQueue(informationType.FullTypeName()->ToString()) ;
        { 
         
          rDebug("whatis dit que c'ets un template") ;
               
          Class* classe = environement->LookupClassMetaobject(
            informationType.FullTypeName()) ;
          TemplateClass* classeTemplate = static_cast<TemplateClass*>(classe) ;
      
          Ptree* parametre ;
          PtreeUtil::Match(type, "[%* [< %? >]]", &parametre) ;
      
          return new TypeTemplate(classeTemplate, parametre) ;
          break ;
        }
        
        case UndefType :

          rDebug("whatis dit que c'ets indefini") ;
                
          // ici c'ets plus compliqué, on a probablemenr affaire à un 
          // template un peu trop compliqué pour OpenC++ (avec des namesapces)
          
          // exemple : 
          // Base::Association< A > a ;
          // Ptree correspondant : 
          // [0 [Base :: [Association [< [[[A] [0]]] >]]] [[a]] ;]
          
          return IdentifierParcoursNamespace(type, environement) ;
          
      
          break;
          
        default:
        
          rDebug("whatis dit que c'ets autre chose") ;
        
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
        int rang = _membre.Nth() ;
        Ptree* declarationAttribut 
            = membres->Ref(rang)->definition ;

        Environment* environement 
            = classe->GetEnvironment()->GetOuterEnvironment() ;
        
        
        rDebug("TypeTemplate::Construire = "+informationType.WhatIs()) ;
        return IdentifierTypeTemplate(declarationAttribut->Cdr()->Car(),
                                      informationType, 
                                      environement) ;
      }
      
  
      TypeTemplate::TypeTemplate(
                     TemplateClass* _classeTemplate,
                     Ptree* _parametres) 
      : Type(_classeTemplate->GetEnvironment()->GetOuterEnvironment()), 
        classeTemplate(_classeTemplate), parametres(_parametres)
      {}

      void TypeTemplate::Initialiser()
      {
        // @todo
      }





      
      Chaine TypeTemplate::Afficher() const
      {
        
        Chaine resultat(NomComplet(this->espaceDeNom)) ;
                
        Chaine sortieParametres(parametres->ToString()) ;
      
        return "template " + resultat + Chaine("::") + 
               classeTemplate->Name()->ToString() + 
               "<" + sortieParametres +">" ;
        
      }
  
      Booleen TypeTemplate::VerifieRegles() const 
      {
        
        // todo
        return VRAI ;
      }

  
    } 
  }
}

