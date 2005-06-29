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

#include <iterator>

#include <opencxx/TypeInfo.h>

#include <base/iterateur_ensemble_composition.h>

#include <outils/compilateur/traceur.h>
#include <outils/compilateur/meta_classe.h>
#include <outils/compilateur/utilitaires_opencxx.h>

using namespace Opencxx ;
using namespace ProjetUnivers::Outils::Compilateur ;
using namespace ProjetUnivers::Base ;


bool MetaClasse::Valeur() 
{


  for(std::set<MetaClasse*>::iterator parent = this->parents.begin() ; 
      parent != this->parents.end() ;
      ++parent)
  {   
    if (NomComplet(*parent) == Chaine("ProjetUnivers::Base::Valeur"))
      
      return VRAI ;

    if ( (*parent)->Valeur() )
      
      return VRAI ;

    
  }
  
  return FAUX ;
}


bool MetaClasse::Objet() 
{


  for(std::set<MetaClasse*>::iterator parent = this->parents.begin() ; 
      parent != this->parents.end() ;
      ++parent)
  {   
    if (NomComplet(*parent) == Chaine("ProjetUnivers::Base::Objet"))
      
      return VRAI ;
    
    if ( (*parent)->Objet() )
      
      return VRAI ;
    
  }
  
  
  
  return FAUX ;
}

bool MetaClasse::Persistante() 
{
  
  for(std::set<MetaClasse*>::iterator parent = this->parents.begin() ; 
      parent != this->parents.end() ;
      ++parent)
  {   
    if (NomComplet(*parent) == Chaine("ProjetUnivers::Base::Persistante"))
      
      return VRAI ;
    
    if ( (*parent)->Persistante() )
      
      return VRAI ;
    
  }
  
  return FAUX ;  
}


bool MetaClasse::NamespaceProjetUnivers() 
{
  
  rDebug("MetaClasse::NamespaceProjetUnivers") ;
  
  Environment* courant = this->GetEnvironment() ;
  Environment* precedent ;
  
  while (courant->GetOuterEnvironment() != NULL 
         && courant->GetOuterEnvironment()->IsNamespace() != NULL)
  {       
    precedent = courant ;
    courant = courant->GetOuterEnvironment() ;
  
  }

  rDebug("fin MetaClasse::NamespaceProjetUnivers") ;

  
  if (Chaine(courant->IsNamespace()->ToString()) == Chaine("ProjetUnivers")
      && Chaine(precedent->IsNamespace()->ToString()) != Chaine("Base"))
  
    return true ;
  
  else
    
    return false ;
  
  
}


void MetaClasse::GenererSchemaXml() const
{
  
  Chaine resultat ;
  
//        for(IterateurEnsembleComposition<Attribut> attribut(attributs) ;
//            attribut.Valide() ;
//            ++attribut)
//        {
//        
//          
//        
//          
//          
//        }
  
  
}

/// Determine si la classe v�rifie les r�gles de programmatoins.


/// Fabrique les informations.
void MetaClasse::Initialiser()
{
  
  if (! initialisee)
  {

    initialisee = true ;
    
    this->nom = this->Name()->ToString() ;
    rDebug("initialisation classe " + this->nom) ;
      
    if (this->NamespaceProjetUnivers())
    {
    
      
      // Traitement des membres
      int nombreDeMembres = 0 ;

      Member membre ;
          
      while(this->NthMember(nombreDeMembres, membre)) 
      {

        rDebug(" membre = "+ Chaine(membre.Definition()->ToString())) ;
           
        if (membre.IsAttribute()) 

          attributs.Ajouter(new Attribut(membre)) ;

        // constructeur
        else if (membre.IsConstructor())
        {

          
          rDebug("membre est constructeur") ;


//          ExisteDeclarationConstructeur = true ;
        
          TypeInfo constructeur ;
          membre.Signature(constructeur) ;
          int nombreArguments = constructeur.NumOfArguments() ;

          rDebug("nombre arguments = " + Chaine(nombreArguments)) ;
          
          if (nombreArguments == 0)
          {
          
            // constructeur par d�faut
//            ExisteDeclarationConstructeurParDefaut = true ;

            if (membre.IsPublic())
              ExisteDeclarationConstructeurParDefautPublic = true ;
            else if (membre.IsProtected())
              ExisteDeclarationConstructeurParDefautProtege = true ;

            
          }
          else if (nombreArguments == 1)
          {

            rDebug("constructeur avec un argument") ;
            
            TypeInfo argument ;
            if (membre.IsPublic() && constructeur.NthArgument(0, argument))
            {

              rDebug("argument est public") ;
              
              if (argument.IsConst())              
                rDebug("argument est const") ;
              if (argument.IsReferenceType())
                rDebug("argument est reference") ;
              
              
              
              
              if (argument.IsReferenceType())
              {
                
                TypeInfo argumentClass ;
                argument.Dereference(argumentClass) ;
                
                if (argumentClass.IsConst())
                  rDebug("argument est reference to const") ;
                
                if (argumentClass.WhatIs() == ClassType)
                  rDebug("argument est reference to class") ;
                
                
                if (argumentClass.IsConst() && 
                    argumentClass.WhatIs() == ClassType &&
                    argumentClass.ClassMetaobject() == this)
                {
                  rDebug("constructeur de copie") ;
                  ExisteConstructeurDeCopiePublic = true ;
                }
              }
            }
            
          }
          
        }
        else if (membre.IsDestructor())
        {
          
        rDebug("membre est destructeur") ;
          
          if (membre.IsPublic() && membre.IsVirtual() && 
              ! membre.IsPureVirtual())
          
            ExisteDestructeurVirtuelNonPur = true ;
        
        }
        else if (! membre.IsStatic() && ! membre.IsPrivate())
        {

          rDebug("membre est fonction") ;
        
          // m�thode d'objets non priv�e
          
          if (membre.IsVirtual() && ! membre.IsPureVirtual())
            ExisteMethodeVirtuelleNonPure = true ;

          else if (membre.IsPureVirtual())
            ExisteMethodeVirtuellePure = true ;



          Chaine nom(membre.Name()->ToString()) ;
          
          rDebug("la methode sappelle : " + nom ) ;
          
          
          if (nom == "operator ==")
          {
            
            rDebug("la methode est operateur de comparaison") ;
            
            TypeInfo comparaison ;
            membre.Signature(comparaison) ;
            int nombreArguments(comparaison.NumOfArguments()) ;
            TypeInfo parametre ;
            
            if (nombreArguments == 1 && membre.IsPublic() && 
                comparaison.NthArgument(0, parametre))
            {

              if (parametre.IsReferenceType())
              {
                TypeInfo argumentClass ;
                parametre.Dereference(argumentClass) ;
                
                if (argumentClass.IsConst() && 
                    argumentClass.WhatIs() == ClassType &&
                    argumentClass.ClassMetaobject() == this)
                {
                  rDebug("operateur egalite") ;
                  ExisteOperateurEgalPublic = true ;
                }
                
              }

            
              
            }
            
              

          }  
          
        }
 
        nombreDeMembres++ ;  
      }
    
      // les classes parentes
      rDebug("gestion des parents") ;
      Ptree* arebreParents = this->BaseClasses() ;
      rDebug("parents = " + Chaine(arebreParents->ToString())) ;
    
        
      while(arebreParents)
      {
      
        
        Ptree* parent = arebreParents->Cdr()->Car() ;
    
        rDebug(Chaine(parent->ToString())) ;
    
        // parent->Display() ;
        // PtreeUtil::Last(parent)->Car()->Display() ;
    
        Class* classeParente 
          = this->GetEnvironment()
                    ->LookupClassMetaobject(PtreeUtil::Last(parent)->Car()) ;
    
        MetaClasse* classe = static_cast<MetaClasse*>(classeParente) ;
    
        this->parents.insert(classe) ;
    
        // passage au suivant    
        arebreParents = arebreParents->Cdr()->Cdr() ;
      }

      rDebug("fin gestion des parents") ;

      rDebug("initialisation des classes utilis�es") ;
   
      // on initialise les autres classes utilis�es
      for(std::set<MetaClasse*>::iterator parent = this->parents.begin() ; 
      parent != this->parents.end() ;
      ++parent)
      {   
        (*parent)->Initialiser() ;
      }
      
      // idem pour les attributs
      for(IterateurEnsembleComposition<Attribut> attribut(attributs) ;
          attribut.Valide() ;
          ++attribut)
      {
        attribut->Initialiser() ;
      }

      rDebug("fin initialisation des classes utilis�es") ;

   
    }

    rDebug("fin initialisation classe " + this->nom) ;

            
  }    
}


bool MetaClasse::VerifieRegles() {


  Booleen validiteAttributs = VRAI ;
  
  // v�rification des types des attributs.
  for(IterateurEnsembleComposition<Attribut> attribut(attributs) ;
      attribut.Valide() ;
      ++attribut)
  {       
      validiteAttributs = validiteAttributs && attribut->VerifieRegles() ;
  }

  return validiteAttributs ;
}




bool MetaClasse::EstValeur() const
{
  
}
  
bool MetaClasse::EstObjet() const
{
  
}




const char* MetaClasse::Afficher()  
{

  rDebug("MetaClasse::Afficher") ;  

  Chaine resultat ;
  resultat = "Class " ; 
  
  if (this->Valeur())
    
    resultat += "Valeur " ;
    
  else if (this->Objet())
    
    resultat += "Objet " ;
    
  
  resultat += this->AbsoluteName()->ToString() ;
  resultat += " : ";
  
  rDebug("MetaClasse::Afficher parents") ;  

  
  for(std::set<MetaClasse*>::iterator parent = this->parents.begin() ; 
      parent != this->parents.end() ;
      ++parent)
      
    resultat += NomComplet(*parent) + "," ;
    
  resultat += "\n" ;

  rDebug("MetaClasse::Afficher attributs") ;  
    
  for(IterateurEnsembleComposition<Attribut> attribut(attributs) ;
      attribut.Valide() ;
      ++attribut)
  {
    resultat = resultat + "  " + attribut->Afficher() + "\n" ;     
  }
  
  resultat = resultat + "\n" ;

  if(ExisteDeclarationConstructeurParDefautPublic)
    resultat = resultat + "ExisteDeclarationConstructeurParDefautPublic\n" ;
     
  if(ExisteDeclarationConstructeurParDefautProtege)
    resultat = resultat + "ExisteDeclarationConstructeurParDefautProtege\n" ;

  if(ExisteConstructeurDeCopiePublic)
    resultat = resultat + "ExisteConstructeurDeCopiePublic\n" ;
  
  if(ExisteDestructeurVirtuelNonPur)
    resultat = resultat + "ExisteDestructeurVirtuelNonPur\n" ;

  if(ExisteOperateurEgalPublic)
    resultat = resultat + "ExisteOperateurEgalPublic\n" ;

  if(ExisteOperateurDifferentPublic)
    resultat = resultat + "ExisteOperateurDifferentPublic\n" ;

  if(ExisteMethodeVirtuellePure)
    resultat = resultat + "ExisteMethodeVirtuellePure\n" ;

  if(ExisteMethodeVirtuelleNonPure)
    resultat = resultat + "ExisteMethodeVirtuelleNonPure\n" ;

  rDebug("fin MetaClasse::Afficher") ;  
  
  return resultat ;
  
    
  
}

MetaClasse::MetaClasse()
: initialisee(false)
{}


bool MetaClasse::Initialize() 
{
  OuvrirTraceur() ;
  Class::ChangeDefaultMetaclass("MetaClasse") ;
  return true ;
  
}


void MetaClasse::TranslateClass(Environment* env)
{
  
  rDebug("MetaClasse::TranslateClass") ;
  
  if (this->NamespaceProjetUnivers())
  {
    this->Initialiser() ;
    Chaine affichage("\n") ;
    affichage += this->Afficher() ;

    rLog(RLOG_CHANNEL("compilateur"),affichage) ;
    
    std::cout << affichage << std::endl ;
    
    if (this->VerifieRegles())
      rLog(RLOG_CHANNEL("compilateur"), "la classe " + this->nom + 
                                      " v�rifie les r�gles") ;
    else
      rLog(RLOG_CHANNEL("compilateur"), "la classe " + this->nom + 
                                      " ne v�rifie pas les r�gles") ;

  }
  rDebug("fin MetaClasse::TranslateClass") ;
}


Ptree* MetaClasse::FinalizeClass()
{
  // ici on fait ce qu'on veut :
  FermerTraceur() ;

  return 0 ;
  
}


Ptree* MetaClasse::TranslateMemberRead(Environment* env,
             Ptree* object, Ptree* access_op,
             Ptree* member_name)
{             

  return Class::TranslateMemberRead(env, object, access_op, member_name) ;
}

Ptree* MetaClasse::TranslateMemberRead(
                          Environment* env, 
                          Ptree* member_name)
{

  return Class::TranslateMemberRead(env,member_name) ;
}      

