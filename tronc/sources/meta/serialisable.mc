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



// Includes
#include <meta/serialisable.mh>
#include <base/chaine.h>
#include <base/composition.h>
#include <base/implantation/liste_valeur.h>
#include <base/implantation/iterateur_liste_valeur.h>
#include <iostream>
#include <opencxx/parser/Token.h>
#include <meta/utilitaires_opencxx.h>
#include <opencxx/parser/Encoding.h>
#include <opencxx/EncodingUtil.h>
#include <string.h>

using namespace std ;
using namespace Opencxx ;
using namespace ProjetUnivers::Base ;
using namespace ProjetUnivers::Base::Implantation ;

/// Un template.
class TypeTemplate
{
public:

  /// Constructeur  
  TypeTemplate(const ListeValeur<Chaine>& _nomComplet, 
               Ptree* _parametres) ;
  
  /// Transforme en chaine pour l'affichage.
  Chaine Afficher() const ;
  
private:
  
  /// Le nom complet de la classe template.
  /*!
    Une liste des noms des namespaces, le dernier élément est le nom 
    de la classe template proprement dite.
  */
  ListeValeur<Chaine> nomComplet ;
  
  /// Les paramètres.
  Ptree* parametres ;

}  ;

TypeTemplate::TypeTemplate(const ListeValeur<Chaine>& _nomComplet, 
               Ptree* _parametres)
: nomComplet(_nomComplet), parametres(_parametres)
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




/// Donne le nom complet d'un namespace
/*!
  \remarks 
    testé
    marche avec openc++ 2.8.5 (la mienne)
*/
Chaine GetFullName(Environment* espaceDeNom)
{
  Chaine resultat ;
  
  while(espaceDeNom != NULL && espaceDeNom->IsNamespace() != NULL)
  {
    if (resultat == Chaine(""))
      resultat = espaceDeNom->IsNamespace()->ToString() ;
    else
      resultat = Chaine(espaceDeNom->IsNamespace()->ToString()) + "::" + resultat ;
    
    espaceDeNom = espaceDeNom->GetOuterEnvironment() ;
  }
  
  return resultat ;
}

/// Donne le nom complet d'une classe
/*!
  \remarks 

    marche avec openc++ 2.8.5 (la mienne)
*/
Chaine GetFullName(Class* classe)
{
  Chaine resultat ;

  resultat = GetFullName(classe->GetEnvironment()->GetOuterEnvironment()) 
             + "::" 
             + classe->Name()->ToString() ;

  return resultat ;
}


/// Identifie la selection par un namespace
/*!
  Reconnait des arbre de la forme : 
  [<i>namespace</i> :: <i>reste</i>]
*/
TypeTemplate* IdentifierParcoursNamespace
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
  Est capable de reconnaitre aussi les templates préfixés par des namespaces.
*/
TypeTemplate* IdentifierTypeTemplate(Ptree* type, TypeInfo informationType, 
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

bool Serialisable::Initialize() 
{
  // La méta-class par défaut n'est plus Class mais 
  // ReglesProgrammation.
  Class::ChangeDefaultMetaclass("Serialisable") ;
  return true ;
  
}


void Serialisable::TranslateClass(Environment* env)
{
  
  
  
//  cout.flush() ;
//  // 
  cout << "classe " << ::ProjetUnivers::Outils::Compilateur::NomComplet(this) << endl ;
  
  char* valeur ;
  
//  if (LookupCmdLineOption("sortie",valeur))
//  
//  	cout << "sortie=" << valeur << endl ;


//  Booleen estValeur = FAUX ;      
//
//
//  Ptree* nomValeur = (new Leaf("Valeur",6)) ;
//  Ptree* nomBase = (new Leaf("Base",4)) ;
//  Ptree* nomProjetUnivers = (new Leaf("ProjetUnivers",13)) ;
//  Token tokenScope ;
//  tokenScope.ptr = "::" ;
//  tokenScope.len = 2 ;
//  tokenScope.kind = 274 ;
//  Ptree* scope = new Leaf(tokenScope) ;
//  Ptree* nomClasseValeur2 = PtreeUtil::List(nomBase, scope, nomValeur) ;
//  Ptree* nomClasseValeur3 = PtreeUtil::List(nomProjetUnivers, scope, nomClasseValeur2) ;
  
//  nomValeur->Display() ;
//  nomClasseValeur2->Display() ;
//  nomClasseValeur3->Display() ;
  
//  if (this->IsSubclassOf(nomClasseValeur2) || 
//      this->IsSubclassOf(nomClasseValeur3))
//    
//    estValeur = VRAI ;
//    
//  if (GetFullName(this->GetEnvironment()->GetOuterEnvironment()) ==
//      Chaine("ProjetUnivers::Base") && this->IsSubclassOf(nomValeur))
//      
//    estValeur = VRAI ;

//  if (this->BaseClasses())
//  {
//    //cout << "parents = " << this->BaseClasses()->ToString() << endl ;
//    cout << "parents = " << this->BaseClasses()->ToString() << endl ;
//    
//    int compteur = 0 ;
//    
//    //Class* parent = this->NthBaseClass(compteur) ;
//    Ptree* parentName = this->NthBaseClassName(compteur) ;
//    
//    
//    while(parentName)
//    {
//     
////      if (parent)
////        cout << "classe = " << GetFullName(parent) << endl ;
//  
//      cout << "nom classe = " << parentName->ToString() << endl ;
//      cout.flush() ;
//      
//      Class* parent = env->LookupClassMetaobject(parentName) ;
//      
//      if (parent)
//        cout << "classe trouve = " << GetFullName(parent) << endl ;
//      else
//        cout << "classe non trouvee" << endl ;        
//      cout.flush() ;
//      
//      // itération
//      ++compteur ;
////      parent = this->NthBaseClass(compteur) ;
//      parentName = this->NthBaseClassName(compteur) ;
//    }
//    
//  }
  
//  if (this->IsSubclassOf(nomValeur))
//      
//    estValeur = VRAI ;
      
//  if (estValeur)
//    cout << "herite de Valeur" << endl ;
//  else
//    cout << "n'herite pas de Valeur" << endl ;
    




//
//  cout << "namespace " << GetFullName(env) << endl ;

//  if (this->GetEnvironment()->GetOuterEnvironment() == env)
//    cout << "test ok" << endl ;
//  else
//    cout << endl <<"WARNING" << endl << endl ;
    
  //env->Dump(0) ;
//  Ptree* nomNamespace = env->IsNamespace() ;
//  
//  cout << "nom : " << nomNamespace->ToString() << endl ;
//  cout.flush() ;  
////  nomNamespace->Display() ;
////  cerr.flush() ;
//  cout.flush() ;
  
//  Environment* outer = env->GetOuterEnvironment() ;
//  if (outer != NULL)
//  {
//    cout << "top" << endl ;
//    outer->Dump() ;
//    cout << "bottom" << endl ;
//    Environment* bottom = env->GetBottom() ;
//    bottom->Dump() ;
//
//  }
//  else
//  {
//    cout << "bottom" << endl ;
//    Environment* bottom = env->GetBottom() ;
//    bottom->Dump() ;
//  }
//  
//  cout.flush() ;
    

//  Environment* espaceDeNom = env->LookupNamespace("Base",4) ;
//  
//  if (espaceDeNom == NULL)
//    cout << "pas trouve" << endl ;
//  else
//    cout << "le namespace Base existe" << endl ;
//  
//  espaceDeNom = env->LookupNamespace("Vue",3) ;
//  
//  if (espaceDeNom == NULL)
//    cout << "pas trouve" << endl ;
//  else
//    cout << "le namespace Vue existe" << endl ;


  // on ajoute deux membres biens choisis

//  // 1. on récupère tous les membres de la classe
//  // doit être détuit... (putain de programmation pas claire)
  MemberList* membres = this->GetMemberList() ;
//  
//  // ces membres contiennent à la fois les attributs et les méthodes 
//  // alors on filtre les attributs 
//
//  // cout << "membres " << endl ;
//
//  // variable de boucle
  int nombreDeMembres = membres->Number() ;
//
//  // test interne
  cout << "nombre de membres " << nombreDeMembres << "\n" ;
//  
  cout.flush() ;
//  
  while(nombreDeMembres > 0) 
  {
    // on récupère le membre courant
    Member membre ;
    MemberList::Mem* mem = membres->Ref(nombreDeMembres-1) ;
    
    LookupMember(membres->Ref(nombreDeMembres-1)->name, membre) ;
    
    // on teste voir si c'est un attribut
    bool attribut = ! membre.IsFunction() && 
                    ! membre.IsConstructor() &&
                    ! membre.IsDestructor() ;

    TypeInfo type ;
    membre.Signature(type) ;
    Ptree* declarationAttribut 
        = membres->Ref(nombreDeMembres-1)->definition ;

    cout << "membre " << membre.Name() << " " << declarationAttribut->ToString() << endl ;
    declarationAttribut->Display() ;
    type.WhatIs() ;
  
 
//    if (membre.IsAttribute()) {
//      
//      // ce membre est un attribut
//
//      // on récupère son type
//      TypeInfo type ;
//      membre.Signature(type) ;
//      
//
//      
//      // ...ainsi que le ptree de la déclaration (servira si le type est 
//      // template, vu que opencpp2.8 les gère assez mal)
//      Ptree* declarationAttribut 
//          = membres->Ref(nombreDeMembres-1)->definition ;
//
//      cout << "attribut " << membre.Name() << " " << declarationAttribut->ToString() << endl ;
//
//      Ptree* arbreType = declarationAttribut->Cdr()->Car() ;
//
//      if (arbreType)
//        arbreType->Display() ;
//
//
//      if (mem->declarator->GetEncodedType())
//      {
//        cout << "encoding of " << arbreType->ToString() << " = " ; 
//        Encoding::Print(cout,mem->declarator->GetEncodedType()) ;
//        cout << endl ;
//
//        char* encodedType = mem->declarator->GetEncodedType() ;
//        int len ;
//        Environment* environnement = env ;
//        char* baseName = EncodingUtil::GetBaseName(encodedType, len, environnement) ;
//        
//        if (baseName)
//        {
//          cout << "base name = " << baseName << endl ;
//          cout << "defined in " << GetFullName(environnement) << endl ;
//        }
//        
//        
//
//      }

//      cout << declarationAttribut->ToString() << endl ;

      // cout << membre.Comments() << endl ;

      
      // test interne
      // on affiche le nom de l'attribut
//      cout << membre.Name() << endl ;
      // cout << type.FullTypeName() << endl ;

      // c'est soit 
      // un type prédéfini, 
      // une classe (de valeur)
      // un de nos templates (en profondeur 1)
      // un enum
  
      // un pointer (dans ce cas on traite comme une réf)


      // on cherche un template...
      //Composition< TypeTemplate> typeTemplate(
      //  IdentifierTypeTemplate(arbreType,type,env)) ;
//      {
//        
//        // ce n'est pas un template mais autre chose :
//
//        switch(type.WhatIs())
//        {
//        
//        case BuiltInType:
        
//          cout << "predefini\n" ;
//          declarationAttribut->Display() ;
          // cout << declarationAttribut->What() << endl ;
//          type.FullTypeName()->Display() ;
          
          
//          break ;
//
//        case TemplateType:
//        {  
//          Class* classe = type.ClassMetaobject() ;
//          Class* classe2 = env->LookupClassMetaobject(arbreType) ;
//          
//          TypeInfo temp ;
//          
//          if (env->Lookup(arbreType, temp))
//          {
//            cout << "typeinfo=" << temp.WhatIs() << endl ;
//          }
//          
//          cout << 
//          
//          cout << "attribut de type : " << arbreType->ToString() << "classe : " ;
//          cout.flush() ;
//          if (classe2)
//            cout << GetFullName(classe2) << endl ;
//          else
//            cout << endl ;
//          // cout << "classe\n" ;        
//          break;
//        }
//          
//        case ClassType:
//          
//          cout <<"attribut de type classe : " << endl ; // GetFullName(type.ClassMetaobject()) << endl ;
//          
//          // cout << "classe\n" ;        
//          break;
//          
//        case EnumType :
////          cout << "enum\n" ;        
//          
//          Ptree* spec ;
//          type.IsEnum(spec) ;
////          spec->Display() ;
////          arbreType->Display() ;
//          
////          spec->Cdr()->Cdr()->Car()->Cdr()->Car()->Car()->Display() ;
//          
//          break;
//        case PointerType:
//          // cout << "pointeur\n" ;        
//          break;
//        case ReferenceType:
//          // cout << "reference\n" ;        
//          break;
//        case PointerToMemberType:
//          // cout << "pointeur de fonction\n" ;        
//          break;
//        case ArrayType:
//          // cout << "tableau\n" ;        
//          break;
//        case FunctionType:
//          // cout << "fonction\n" ;        
//          break;
//          default:
//            break ;
//        }
//      
//      
//      }
//    }
    --nombreDeMembres ;
  }

  // apparemment, il ne faut pas le détruire
  // delete membres ;

  cout << "fin classe " << this->Name()->ToString() << endl ;
  cout.flush() ;

}

Ptree* Serialisable::TranslateMemberRead(Environment* env,
             Ptree* object, Ptree* access_op,
             Ptree* member_name)
{             
//  cout << "TranslateMemberRead 1 " << member_name->ToString() << "" 
//       << access_op->ToString() << " " << object->ToString() << endl ;

  return Class::TranslateMemberRead(env, object, access_op, member_name) ;
}

Ptree* Serialisable::TranslateMemberRead(Environment* env, Ptree* member_name)
{
//  cout << "TranslateMemberRead 2 " << member_name->ToString() << endl ;

  return Class::TranslateMemberRead(env,member_name) ;
}


