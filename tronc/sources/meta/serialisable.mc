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
#include "serialisable.mh"
#include <iostream.h>

void Serialisable::TranslateClass(Environment* env)
{

  // on ajoute deux membres biens choisis

  // 1. on récupère tous les membres de la classe
  MemberList* membres = GetMemberList() ;


  // test interne
  //cout << "nombre de membres " << nombreDeMembres << "\n" ;
  
  // ces membres contiennent à la fois les attributs et les méthodes 
  // alors on filtre les attributs 

  // variable de boucle
  int nombreDeMembres = membres->Number() ;

  
  while(nombreDeMembres > 0) 
  {
    // on récupère le membre courant
    Member membre ;
    LookupMember(membres->Ref(nombreDeMembres-1)->name, membre) ;
    
    // on teste voir si c'est un attribut
    bool attribut = ! membre.IsFunction() && 
                    ! membre.IsConstructor() &&
                    ! membre.IsDestructor() ;
  
 
    if (attribut) {
      
      // ce membre est un attribut
      
      // test interne
      // on affiche le nom de l'attribut
      cout << membre.Name() << " --> attribut\n" ;
      

      // on récupère son type
      TypeInfo type ;
      membre.Signature(type) ;
      
      // ...ainsi que le ptree de la déclaration (servira si le type est 
      // template, vu que opencpp2.8 les gère assez mal)
      Ptree* declarationAttribut 
          = membres->Ref(nombreDeMembres-1)->definition ;


      // c'est soit 
      // un type prédéfini, 
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
        
          
          // on parcours les paramètres du template
          
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


