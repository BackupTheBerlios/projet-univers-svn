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
#include <opencxx/mop.h>
#include <iostream.h>

using namespace Opencxx ;

/*
CLASS
  Serialisable

  Classe des classes qui sont s�rialis�es en XML.

*/
class Serialisable : public Class {
public:

  ///////////////////////
  // Modifie une classe s�rialisable. Il s'agit d'ajouter deux m�thodes 
  // publiques : lire(fichier) et ecrire(fichier), qui d�s�rialise et 
  // s�rialisent en xml.
  void TranslateClass(Environment* env) ;
 
};

void Serialisable::TranslateClass(Environment* env)
{

  // on ajoute deux membres biens choisis

  // on r�cup�re tous les membres :
  MemberList* membres = GetMemberList() ;

  int nombreDeMembres = membres->Number() ;

  //cout << "nombre de membres " << nombreDeMembres << "\n" ;
  

  while(nombreDeMembres > 0) 
  {
    // on r�cup�re le membre courant
    Member membre ;
    LookupMember(membres->Ref(nombreDeMembres-1)->name, membre) ;
    
    // on teste voir si c'est un attribut
    bool attribut = ! membre.IsFunction() && 
                    ! membre.IsConstructor() &&
                    ! membre.IsDestructor() ;
  
 
    if (attribut) {
      
      // c'en est un, ouf !
      
      // on affiche le nom de l'attribut
      cout << membre.Name() << " --> attribut\n" ;
      

      // on r�cup�re son type
      TypeInfo type ;
      membre.Signature(type) ;
      
      // ...ainsi que le ptree de la d�claration (servira si le type est 
      // template, vu que opencpp2.8 les g�re assez mal)
      Ptree* declarationAttribut 
          = membres->Ref(nombreDeMembres-1)->definition ;


      // c'est soit 
      // un type pr�d�fini, 
      // une classe (de valeur)
      // un de nos templates (en profondeur 1)

      // interdiction d'utiliser des namespace::
      // pour que ca marche

      switch(type.WhatIs())
      {
      
      case BuiltInType:
      
        break ;
        
      case ClassType:
        
        
        break;
        
      case TemplateType:  
        { 
        
          
          // on parcours les param�tres du template
          
          TypeInfo typeArgument ;
          int nombreArgumentsTemplate ;
          
          // le parcours proprement dit
          for(nombreArgumentsTemplate = 0 ;
              type.NthTemplateArgument(nombreArgumentsTemplate,typeArgument) ; 
              nombreArgumentsTemplate++)
          {
          
          
            cout << typeArgument.FullTypeName() << "\n" ;
          
          
          }
          
          cout << "ce template a " << nombreArgumentsTemplate << " arguments\n" ;
        }
        break ;
      }

    }
    --nombreDeMembres ;
  }

  

}


