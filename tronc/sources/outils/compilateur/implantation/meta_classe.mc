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
    
  }
  
  return FAUX ;
}


bool MetaClasse::NamespaceProjetUnivers() 
{
  Environment* courant = this->GetEnvironment() ;
  Environment* precedent ;
  
  while (courant->GetOuterEnvironment() != NULL 
         && courant->GetOuterEnvironment()->IsNamespace() != NULL)
  {       
    precedent = courant ;
    courant = courant->GetOuterEnvironment() ;
  
  }
  
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

/// Determine si la classe vérifie les règles de programmatoins.


/// Fabrique les informations.
void MetaClasse::Initialiser()
{
  
  if (! initialisee)
  {

    // on place le drapeau
    initialisee = true ;
    
    // le nom de la classe
    this->nom = this->Name()->ToString() ;
      
      
    if (this->NamespaceProjetUnivers())
    {
    
      
      // les attributs     
      MemberList* membres = this->GetMemberList() ;
      int nombreDeMembres = membres->Number() ;
          
      while(nombreDeMembres > 0) 
      {
        // on récupère le membre courant
        Member membre ;
        LookupMember(membres->Ref(nombreDeMembres-1)->name, membre) ;
      
        rDebug(" membre = "+ Chaine(membre.Name()->ToString())) ;
        rDebug("membre fonction = "+membre.IsFunction()) ;
        rDebug("membre destructeur = "+membre.IsDestructor()) ;
        rDebug("membre constructeur = "+membre.IsConstructor()) ;
           
        if (membre.IsAttribute()) 
          attributs.Ajouter(new Attribut(membre)) ;
               
        --nombreDeMembres ;  
      }
    
      // les classes parentes
      Ptree* arebreParents = this->BaseClasses() ;
      rDebug("parents = " + Chaine(arebreParents->ToString())) ;
    
        
      while(arebreParents)
      {
      
        
        Ptree* parent = arebreParents->Cdr()->Car() ;
    
        rDebug(Chaine(parent->ToString())) ;
    
        parent->Display() ;
        PtreeUtil::Last(parent)->Car()->Display() ;
    
        Class* classeParente 
          = this->GetEnvironment()
                    ->LookupClassMetaobject(PtreeUtil::Last(parent)->Car()) ;
    
        MetaClasse* classe = static_cast<MetaClasse*>(classeParente) ;
    
        this->parents.insert(classe) ;
    
        // passage au suivant    
        arebreParents = arebreParents->Cdr()->Cdr() ;
      }
   
      // on initialise les autres classes utilisées
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
   
    }
            
  }    
}


bool MetaClasse::VerifieRegles() {


//        Booleen validiteAttributs = VRAI ;
//        
//        // vérification des types des attributs.
//        for(IterateurEnsembleComposition<Attribut> attribut(attributs) ;
//            attribut.Valide() ;
//            ++attribut)
//        {       
//            validiteAttributs = validiteAttributs && attribut->VerifieRegles() ;
//        }

  return VRAI ;
}

const char* MetaClasse::Afficher()  
{

  Chaine resultat ;
  
  resultat = "Class " + NomComplet(this) + " : ";
  
  for(std::set<MetaClasse*>::iterator parent = this->parents.begin() ; 
      parent != this->parents.end() ;
      ++parent)
      
    resultat += NomComplet(*parent) + "," ;
    
  resultat += "\n" ;
    
  for(IterateurEnsembleComposition<Attribut> attribut(attributs) ;
      attribut.Valide() ;
      ++attribut)
  {
    resultat = resultat + "  " + attribut->Afficher() + "\n" ;     
  }
  
  resultat = resultat + "\n" ;
  
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
  
  if (this->NamespaceProjetUnivers())
  {
    this->Initialiser() ;
    rLog(RLOG_CHANNEL("compilateur"),"\n"+Chaine(this->Afficher())) ;

  }
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

