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
#include <opencxx/parser/PtreeUtil.h>

#include <base/composition.h>
#include <base/implantation/liste_valeur.h>
#include <base/implantation/iterateur_liste_valeur.h>
#include <base/implantation/iterateur_liste_composition.h>


#include <outils/compilateur/parametre_template.h>
#include <outils/compilateur/type_template.h>
#include <outils/compilateur/utilitaires_opencxx.h>

using namespace Opencxx ;
using namespace ProjetUnivers::Base ;
using namespace ProjetUnivers::Base::Implantation ;

namespace ProjetUnivers {

  namespace Outils {
    
    namespace Compilateur 
    {

//      /// Identifie la selection par un namespace
//      /*!
//        Reconnait des arbre de la forme : 
//        [<i>namespace</i> :: <i>reste</i>]
//      */
//      TypeTemplate* TypeTemplate::IdentifierParcoursNamespace
//                  (Ptree* type, Environment* environement) 
//      {
//      
//        rDebug("coucou 1") ;
//          
//      
//        Ptree* espaceDeNom ;
//        Ptree* suiteType ;
//      
//        if (PtreeUtil::Match(type, "[%? :: %r]", &espaceDeNom, &suiteType))
//        {
//          
//          rDebug("coucou 2") ;
//          
//          
//          /*!
//            on vérifie que le premier élément est bien un identifiant de 
//            namespace
//          */
//          char* nom = espaceDeNom->GetPosition() ;
//          int len = espaceDeNom->GetLength() ;
//          
//          Environment* environementNameSpace 
//            = environement->LookupNamespace(nom, len) ;
//
//          Class* Classe 
//            = environement->LookupClassMetaobject(espaceDeNom) ;
//      
//          rDebug("coucou 3") ;
//          
//          // ce n'est pas un namespace... on arrete
//          if (environementNameSpace != NULL) 
//            
//            return IdentifierParcoursNamespace(suiteType, environementNameSpace) ;
//          
//          if (Classe != NULL)
//          
//            return IdentifierParcoursNamespace(suiteType, Classe->GetEnvironment()) ;
//            
//          rDebug(" " + Chaine(espaceDeNom->ToString())+"non reconnu dans "+
//                 NomComplet(environement)) ;
//          return NULL ;
//          
//        }
//        
//        Ptree* nomClasseTemplate ;
//        Ptree* parametres ;
//        
//        if (PtreeUtil::Match(type, "[[%? [< %? >]]]", 
//                             &nomClasseTemplate, &parametres))
//        {
//      
//      
//          rDebug("dans "+NomComplet(environement)+ 
//                 " on a trouve le template "+nomClasseTemplate->ToString()) ;
//                  
//          // on récupère sa classe
//          TemplateClass* classeTemplate = static_cast<TemplateClass*>(
//            environement->LookupClassMetaobject(nomClasseTemplate)) ;
//          
//          // les paramètres
//          parametres->Display() ;
//          
//          int nombreParametres = (PtreeUtil::Length(parametres) +1)/2 ;
//          
//          for(int numeroParametre = 1 ;
//              numeroParametre <= nombreParametres;
//              ++numeroParametre)
//          {
//          
//            /// de la forme 
//            /// x où x est un nombre
//            /// [type [0]]    
//            Ptree* parametre 
//              = PtreeUtil::Nth(parametres,2*(numeroParametre-1)) ;
//
//            parametre->Display() ;            
//
//            Ptree* type ; 
//
//            if (PtreeUtil::Match(parametre, "[%? %*]", &type))
//            {
//              //this->parametres.Ajouter(Type::Construire  
//              rDebug("parametre classe = " + Chaine(type->ToString())) ;
//              rDebug("encoding = " + Chaine(type->GetEncodedName())) ;
//            }              
//            else
//              rDebug("pas de classe parametre trouvée") ;
//            
//          }
//              
//          
//          Composition<TypeTemplate> resultat(
//              new TypeTemplate(classeTemplate, parametres)) ;
//      
//          return resultat.Liberer() ;
//         
//          
//        }
//        
//        rDebug(" "+Chaine(type->ToString())+" na pas la forme dun template") ;
//        
//        // ce n'en est pas un
//        return NULL ;
//      
//      }
      
      
      
      
      /// Identifie un type template
      /*!
        Est capable de reconnaitre les templates préfixés par des 
        namespaces, ainsi que ceux déjà identifiés comme des templates par 
        opencxx.
      */
      TypeTemplate* TypeTemplate::IdentifierTypeTemplate
                    (TypeInfo informationType, 
                     Environment* environement)
      {


        rDebug("TypeTemplate::IdentifierTypeTemplate") ;
        
      
        switch(informationType.WhatIs())
        {
        case TemplateType:  
          
        { 
         
          rDebug("whatis dit que c'ets un template") ;

          
               
          TemplateClass* classeTemplate 
            =  informationType.TemplateClassMetaobject() ;


          Base::Composition<TypeTemplate>
            resultat(new TypeTemplate(classeTemplate)) ;


          // arguments
          int nombreArguments = 0 ;
          TypeInfo typeArgument ;
      
          while(informationType.NthTemplateArgument(nombreArguments++,typeArgument))
          {
            
            if (typeArgument.WhatIs() == UndefType)
            {
              rDebug("parametre n'a pas de type") ;
              
              
            }
            else
            
              resultat->_parametres.AjouterEnQueue(Type::Construire(typeArgument, environement)) ;
          }

      
          return resultat.Liberer() ;
          break ;
        }
          
        default:
        
          rDebug("whatis dit que c'ets autre chose") ;
        
          return NULL ;
        
        }
        
      }



      TypeTemplate* TypeTemplate::Construire(Opencxx::TypeInfo& informationType,
                                             Environment* environement)
      {
        
        rDebug("TypeTemplate::Construire = "+informationType.WhatIs()) ;
        return IdentifierTypeTemplate(informationType, 
                                      environement) ;
      }
      
  
      TypeTemplate::TypeTemplate(
                     TemplateClass* _classeTemplate,
                     Ptree* _parametres) 
      : Type(_classeTemplate->GetEnvironment()->GetOuterEnvironment()), 
        classeTemplate(_classeTemplate), parametres(_parametres)
      {}

      TypeTemplate::TypeTemplate(TemplateClass* _classeTemplate )
      : Type(_classeTemplate->GetEnvironment()->GetOuterEnvironment()), 
        classeTemplate(_classeTemplate), parametres()
      {}


      void TypeTemplate::Initialiser()
      {
        // @todo
      }





      
      Chaine TypeTemplate::Afficher() const
      {
        
        rDebug("TypeTemplate::Afficher") ;
        
        Chaine resultat(NomComplet(this->espaceDeNom)) ;

        rDebug("TypeTemplate::Afficher 2") ;        

        Chaine sortieParametres ;
//        if (parametres)
//          sortieParametres = (parametres->ToString()) ;

        for(IterateurListeComposition<ParametreTemplate> parametre(this->_parametres) ;
            parametre.Valide() ;
            ++parametre)
        {
        
          sortieParametres += ',' ;
          sortieParametres += parametre->Afficher() ;
          rDebug("parametre = " + parametre->Afficher()) ;
        }


        rDebug("fin TypeTemplate::Afficher") ;
        
        return "template " + resultat + Chaine("::") + 
               classeTemplate->Name()->ToString() + 
               "<" + sortieParametres +">" ;

        
      }

      Base::Booleen TypeTemplate::NamespaceProjetUniversBase() const
      {
        Environment* courant = this->classeTemplate->GetEnvironment() ;
        Environment* precedent ;
        
        while (courant->GetOuterEnvironment() != NULL 
               && courant->GetOuterEnvironment()->IsNamespace() != NULL)
        {       
          precedent = courant ;
          courant = courant->GetOuterEnvironment() ;
        
        }
        
        if (Chaine(courant->IsNamespace()->ToString()) == Chaine("ProjetUnivers")
            && Chaine(precedent->IsNamespace()->ToString()) == Chaine("Base"))
        
          return true ;
        
        else
          
          return false ;
  
        
      }


      BaseTemplate TypeTemplate::TemplateDeBase() const
      {
      
        Chaine nom(this->classeTemplate->Name()->ToString()) ;
        
        rDebug(nom) ;
        
        if (nom == Chaine("Association"))
          return Compilateur::Association ;
        else if (nom == Chaine("Composition"))
          return Compilateur::Composition ;
        else if (nom == Chaine("EnsembleComposition"))
          return Compilateur::EnsembleComposition ;
        else if (nom == Chaine("EnsembleAssociation"))
          return Compilateur::EnsembleAssociation ;
        else if (nom == Chaine("FonctionObjetValeur"))
          return Compilateur::FonctionObjetValeur ;
        else if (nom == Chaine("FonctionCompositionObjetObjet"))
          return Compilateur::FonctionCompositionObjetObjet ;
        else if (nom == Chaine("FonctionAssociationObjetObjet"))
          return Compilateur::FonctionAssociationObjetObjet ;
        else if (nom == Chaine("FonctionCompositionValeurObjet"))
          return Compilateur::FonctionCompositionValeurObjet ;
        else if (nom == Chaine("FonctionAssociationValeurObjet"))
          return Compilateur::FonctionAssociationValeurObjet ;
        
        else
          return Compilateur::NonPrisEnCompte ;
      }


  
      /*
      @todo
        générer des erreurs de compilation explicites
        ... pas sur...
      */
      Booleen TypeTemplate::TypeAttributCorrect() const
      {
        
        IterateurListeComposition<ParametreTemplate> parametre(this->_parametres) ;
        
        // 1. est il un des templates de PU::Base
        if (this->NamespaceProjetUniversBase())
        {

          Booleen parametreObjet ;
          
          rDebug("Vérification du type en tant que type d'attribut") ;
          rDebug(this->Afficher()) ;
          
          BaseTemplate identiteTemplate(this->TemplateDeBase()) ;
          
          switch (identiteTemplate)
          {
          case Compilateur::Association:
          case Compilateur::Composition:
          case Compilateur::EnsembleAssociation:
          case Compilateur::EnsembleComposition:
            
            rDebug("un seul paramètre objet") ;
            
            // le template a un seul paramètre Objet
            if (this->_parametres.NombreDElements() != 1)
            {
              /// @todo corriger
              // provoque une erreur interne parceque pas de where...
              classeTemplate->ErrorMessage("mauvais nombre d'arguments",0,0) ;
              return FAUX ;
            }
            

            parametreObjet = parametre->Objet() ;
            if (parametreObjet == VRAI)
              rDebug("le parametre est objet") ;
            else
              rDebug("le parametre n'est pas objet") ;
            
            return parametreObjet ;
            break ;

          case Compilateur::EnsembleValeur:
          
            // le template a un seul paramètre Valeur

            if (this->_parametres.NombreDElements() != 1)
              return FAUX ;
            
            return parametre->Valeur() ;
            break ;
            
          case Compilateur::FonctionCompositionValeurObjet:
          case Compilateur::FonctionAssociationValeurObjet:
          
            // le premier parametre est valeur, le second objet
            if (this->_parametres.NombreDElements() != 2)
              return FAUX ;
            
            if (! parametre->Valeur())
              return FAUX ;
            
            ++parametre ;            
            return parametre->Objet() ;
            break ;
            
          case Compilateur::FonctionCompositionObjetObjet:
          case Compilateur::FonctionAssociationObjetObjet:

            // les 2 paramètres sont objets
            if (this->_parametres.NombreDElements() != 2)
              return FAUX ;
            
            if (! parametre->Objet())
              return FAUX ;
            
            ++parametre ;            
            return parametre->Objet() ;
            
            break ;
          default:
          
            return VRAI ;
            // ??
            
          }
          

        }
        

        return VRAI ;
      }

      Booleen TypeTemplate::TypeParametreCorrect() const
      {

        return FAUX ;
      }
      
      
      Base::Booleen TypeTemplate::EstComposition() const
      {

        if (this->NamespaceProjetUniversBase())
        {

          BaseTemplate identiteTemplate(this->TemplateDeBase()) ;
          
          switch (identiteTemplate)
          {
          case Compilateur::Composition:
          case Compilateur::EnsembleComposition:
          case Compilateur::FonctionCompositionObjetObjet:
          case Compilateur::FonctionCompositionValeurObjet:
            return VRAI ;
          default:
            return FAUX ;
          }        
        }
        
        return FAUX ;
      }

      Base::Booleen TypeTemplate::Valeur() const
      {
        if (this->NamespaceProjetUniversBase())
        {
        
          return !EstComposition() ;
          
        }
        
        return FAUX ;
        
      }

      Base::Booleen TypeTemplate::Objet() const
      {
        return FAUX ;        
      }

  
    } 
  }
}

