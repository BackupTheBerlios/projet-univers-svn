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

#include <tools/compilateur/parametre_template.h>
#include <tools/compilateur/type_template.h>
#include <tools/compilateur/utilitaires_opencxx.h>

using namespace Opencxx ;

namespace ProjetUnivers {

  namespace Tools {
    
    namespace Compiler 
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


          std::auto_ptr<TypeTemplate>
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
            
              resultat->_parametres.push_back(Type::Construire(typeArgument, environement)) ;
          }

      
          return resultat.release() ;
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
      : Type(_classeTemplate?
                _classeTemplate->GetEnvironment()->GetOuterEnvironment():
                NULL), 
        classeTemplate(_classeTemplate), parametres()
      {}


      void TypeTemplate::Initialiser()
      {
        // @todo
      }





      
      std::string TypeTemplate::Afficher() const
      {
        
        rDebug("TypeTemplate::Afficher") ;
        
        std::string resultat(NomComplet(this->espaceDeNom)) ;

        rDebug("TypeTemplate::Afficher 2") ;        

        std::string sortieParametres ;
//        if (parametres)
//          sortieParametres = (parametres->ToString()) ;

        for(std::list<ParametreTemplate*>::const_iterator parametre = _parametres.begin() ;
            parametre != _parametres.end() ;
            ++parametre)
        {
        
          sortieParametres += ',' ;
          sortieParametres += (*parametre)->Afficher() ;
          rDebug("parametre = %",(*parametre)->Afficher().c_str()) ;
        }


        rDebug("fin TypeTemplate::Afficher") ;
        
        return "template " + resultat + std::string("::") + 
               std::string(classeTemplate?classeTemplate->Name()->ToString():"unknown")  + 
               "<" + sortieParametres +">" ;

        
      }

      bool TypeTemplate::NamespaceProjetUniversBase() const
      {
        if (! classeTemplate)
          return false ;
          
        Environment* courant = this->classeTemplate->GetEnvironment() ;
        Environment* precedent ;
        
        while (courant->GetOuterEnvironment() != NULL 
               && courant->GetOuterEnvironment()->IsNamespace() != NULL)
        {       
          precedent = courant ;
          courant = courant->GetOuterEnvironment() ;
        
        }
        
        if (std::string(courant->IsNamespace()->ToString()) == std::string("ProjetUnivers")
            && std::string(precedent->IsNamespace()->ToString()) == std::string("Base"))
        
          return true ;
        
        else
          
          return false ;
  
        
      }


      BaseTemplate TypeTemplate::TemplateDeBase() const
      {
      
        std::string nom(this->classeTemplate->Name()->ToString()) ;
        
        rDebug(nom.c_str()) ;
        
        if (nom == std::string("Association"))
          return Compiler::Association ;
        else if (nom == std::string("Composition"))
          return Compiler::Composition ;
        else if (nom == std::string("EnsembleComposition"))
          return Compiler::EnsembleComposition ;
        else if (nom == std::string("EnsembleAssociation"))
          return Compiler::EnsembleAssociation ;
        else if (nom == std::string("FonctionObjetValeur"))
          return Compiler::FonctionObjetValeur ;
        else if (nom == std::string("FonctionCompositionObjetObjet"))
          return Compiler::FonctionCompositionObjetObjet ;
        else if (nom == std::string("FonctionAssociationObjetObjet"))
          return Compiler::FonctionAssociationObjetObjet ;
        else if (nom == std::string("FonctionCompositionValeurObjet"))
          return Compiler::FonctionCompositionValeurObjet ;
        else if (nom == std::string("FonctionAssociationValeurObjet"))
          return Compiler::FonctionAssociationValeurObjet ;
        
        else
          return Compiler::NonPrisEnCompte ;
      }


  
      /*
      @todo
        générer des erreurs de compilation explicites
        ... pas sur...
      */
      bool TypeTemplate::TypeAttributCorrect() const
      {
        
        std::list<ParametreTemplate*>::const_iterator parametre = _parametres.begin() ;
        
        // 1. est il un des templates de PU::Base
        if (this->NamespaceProjetUniversBase())
        {

          bool parametreObjet ;
          
          rDebug("Vérification du type en tant que type d'attribut") ;
          rDebug(this->Afficher().c_str()) ;
          
          BaseTemplate identiteTemplate(this->TemplateDeBase()) ;
          
          switch (identiteTemplate)
          {
          case Compiler::Association:
          case Compiler::Composition:
          case Compiler::EnsembleAssociation:
          case Compiler::EnsembleComposition:
            
            rDebug("un seul paramètre objet") ;
            
            // le template a un seul paramètre Objet
            if (this->_parametres.size() != 1)
            {
              /// @todo corriger
              // provoque une erreur interne parceque pas de where...
              classeTemplate->ErrorMessage("mauvais nombre d'arguments",0,0) ;
              return false ;
            }
            

            parametreObjet = (*parametre)->Objet() ;
            if (parametreObjet == true)
              rDebug("le parametre est objet") ;
            else
              rDebug("le parametre n'est pas objet") ;
            
            return parametreObjet ;
            break ;

          case Compiler::EnsembleValeur:
          
            // le template a un seul paramètre Valeur

            if (this->_parametres.size() != 1)
              return false ;
            
            return (*parametre)->Valeur() ;
            break ;
            
          case Compiler::FonctionCompositionValeurObjet:
          case Compiler::FonctionAssociationValeurObjet:
          
            // le premier parametre est valeur, le second objet
            if (this->_parametres.size() != 2)
              return false ;
            
            if (! (*parametre)->Valeur())
              return false ;
            
            ++parametre ;            
            return (*parametre)->Objet() ;
            break ;
            
          case Compiler::FonctionCompositionObjetObjet:
          case Compiler::FonctionAssociationObjetObjet:

            // les 2 paramètres sont objets
            if (this->_parametres.size() != 2)
              return false ;
            
            if (! (*parametre)->Objet())
              return false ;
            
            ++parametre ;            
            return (*parametre)->Objet() ;
            
            break ;
          default:
          
            return true ;
            // ??
            
          }
          

        }
        

        return true ;
      }

      bool TypeTemplate::TypeParametreCorrect() const
      {

        return false ;
      }
      
      
      bool TypeTemplate::EstComposition() const
      {

        if (this->NamespaceProjetUniversBase())
        {

          BaseTemplate identiteTemplate(this->TemplateDeBase()) ;
          
          switch (identiteTemplate)
          {
          case Compiler::Composition:
          case Compiler::EnsembleComposition:
          case Compiler::FonctionCompositionObjetObjet:
          case Compiler::FonctionCompositionValeurObjet:
            return true ;
          default:
            return false ;
          }        
        }
        
        return false ;
      }

      bool TypeTemplate::Valeur() const
      {
        if (this->NamespaceProjetUniversBase())
        {
        
          return !EstComposition() ;
          
        }
        
        return false ;
        
      }

      bool TypeTemplate::Objet() const
      {
        return false ;        
      }

  
    } 
  }
}

