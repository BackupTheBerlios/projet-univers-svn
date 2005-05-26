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
#include <opencxx/BindTypedefName.h>
#include <opencxx/parser/TheErrorLog.h>
#include <opencxx/parser/ErrorLog.h>
#include <opencxx/parser/MopMsg.h>

#include <outils/compilateur/type_predefini.h>
#include <outils/compilateur/utilitaires_opencxx.h>



using namespace Opencxx ;
using namespace ProjetUnivers::Base ;



namespace ProjetUnivers {

  namespace Outils {
    
    namespace Compilateur 
    {

      /// Identifie la selection par un namespace
      /*!
        Reconnait des arbre de la forme : 
        [<i>namespace</i> :: <i>reste</i>]
        
        @param[in] environement 
          l'environement dans lequel il faut chercher

        @param[in] type 
          l'arbre qu'il faut chercher
      */
      TypePredefini* TypePredefini::IdentifierParcoursNamespace
                  (Ptree* type, Environment* environement) 
      {
      
      //  cout << "coucou 1" << endl ;
          
      
        Ptree* espaceDeNom ;
        Ptree* suiteType ;
      
        if (PtreeUtil::Match(type, "[%? :: %r]", &espaceDeNom, &suiteType))
        {
          
      //    cout << "coucou 2" << endl ;
          
          
          char* nom = espaceDeNom->GetPosition() ;
          int len = espaceDeNom->GetLength() ;
          
          /*!
            on vérifie que le premier élément est bien un identifiant de 
            namespace
          */
          Environment* environementNameSpace 
            = environement->LookupNamespace(nom,len) ;

          Class* classe 
            = environement->LookupClassMetaobject(espaceDeNom) ;
      
      //    cout << "coucou 3" << endl ;
          
          // ce n'est pas un namespace... on arrete
          if (environementNameSpace == NULL && classe == NULL)
          {
            rDebug(Chaine(espaceDeNom->ToString())+ 
                   "non reconnu dans "+ NomComplet(environement)) ;
            return NULL ;
          }
          
          // si on en a trouvé un c'est que c'ets un namespace 
          if (environementNameSpace != NULL)
          {

            rDebug("scope trouve = environement "+
                   NomComplet(environementNameSpace));

            // récurrence
            return IdentifierParcoursNamespace(suiteType, 
                                               environementNameSpace) ;
          }
          
          rDebug("scope trouve = classe "+NomComplet(classe)) ;
          
          // c'est qu'il est défini dans une classe
          return IdentifierParcoursNamespace(suiteType, 
                                             classe->GetEnvironment()) ;
          
          
        }
        
        Ptree* nomType ;
        if (PtreeUtil::Match(type, "[%?]",&nomType))
        {  
        
          // c'est soit un type de base, soit un type qu'on a défini nous
          // pour distinguer il suffit de chercher l'existence d'un lien entre 
          // le nom et un typedef

//          TypeInfo informationType ;
        
//          if (environement->GetBottom()->Lookup(nomType, informationType))
          
          rDebug("type " + Chaine(nomType->ToString())) ;
         
          Bind* lien ;
          if (environement->Lookup(nomType, lien))
          {
            
            rDebug("typedef trouve") ;
            
            // ce doit être obligatoirement un typedef...
            if (dynamic_cast<BindTypedefName*>(lien))
            
              return new TypePredefini(environement, nomType->ToString()) ;
            
            else
            {
              // pas bon... erreur
              TheErrorLog().Report(MopMsg(Msg::Fatal, 
                                          "TypePredefini::Construire", 
                                          "predefinite type whithout typedef"));
              
            }
              
          }
          else
          {

            rDebug("typedef non trouve") ;

            // ce nom n'est pas défini --> le type est int ou char
            return new TypePredefini(environement->GetBottom(), 
                                     nomType->ToString()) ;
          }
        
        }
        // ce n'en est pas un
        return NULL ;
      
      }

      void TypePredefini::Initialiser()
      {}


      TypePredefini* TypePredefini::Construire(Member& _membre)
      {

        TypeInfo informationType ;
        _membre.Signature(informationType) ;
        
        if (informationType.WhatIs() == BuiltInType)
        {
  
          // un peu de bricolage
          Class* classe = _membre.Supplier() ;
          MemberList* membres = classe->GetMemberList() ;
          int rang = _membre.Nth() ;
          Ptree* declarationAttribut 
              = membres->Ref(rang)->definition ;
  
          Environment* environement 
              = classe->GetEnvironment()->GetOuterEnvironment() ;
          
          rDebug("TypePredefini::Construire "+
                 Chaine(declarationAttribut->ToString())) ;
          
          return IdentifierParcoursNamespace(declarationAttribut->Cdr()->Car(),
                                             environement) ;
        }
        else
          return NULL ;
      }
   
  
          /// Transforme en chaine pour l'affichage.
      Chaine TypePredefini::Afficher() const
      {
        return "predefini " + NomComplet(this->espaceDeNom) + "::" + this->nom ;  
      }
          
      TypePredefini::TypePredefini(Environment* _environement,const Chaine& _nom)
      : Type(_environement), nom(_nom)
      {}

      Booleen TypePredefini::VerifieRegles() const 
      {
        /*! 
          \todo
            tester qu'on utilise bien les bons types
        */
        return VRAI ;
      }


    }
  }
}
