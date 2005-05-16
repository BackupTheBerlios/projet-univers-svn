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



#ifndef _PU_COMPILATEUR_TYPE_TEMPLATE_H_
#define _PU_COMPILATEUR_TYPE_TEMPLATE_H_

#include <outils/compilateur/type.h>
#include <base/implantation/liste_valeur.h>
#include <opencxx/TypeInfo.h>

class Opencxx::Environment ;


namespace ProjetUnivers {

  namespace Outils {
      
    namespace Compilateur 
    {
  
      /// Type des templates C++.
      class TypeTemplate : public Type
      {
      public:
      
        /// Faux constructeur.
        static TypeTemplate* Construire(::Opencxx::Member& _membre) ;
        
        /// Transforme en chaine pour l'affichage.
        virtual Base::Chaine Afficher() const ;


      protected:
      
        /// Constructeur  
        TypeTemplate(
          const Base::Implantation::ListeValeur<Base::Chaine>& _nomComplet, 
          ::Opencxx::Ptree* _parametres) ;

        static TypeTemplate* IdentifierTypeTemplate
                    (Opencxx::Ptree* type,   
                     Opencxx::TypeInfo informationType, 
                     Opencxx::Environment* environement) ;

        static TypeTemplate* IdentifierParcoursNamespace
                  (Opencxx::Ptree* type, Opencxx::Environment* environement, 
                   const Base::Implantation::ListeValeur<Base::Chaine>& prefixe) ;
                     

        
      private:
        
        /// Le nom complet de la classe template.
        /*!
          Une liste des noms des namespaces, le dernier élément est le nom 
          de la classe template proprement dite.
        */
        Base::Implantation::ListeValeur<Base::Chaine> nomComplet ;
        
        /// Les paramètres.
        Opencxx::Ptree* parametres ;
      
      };
  
    } 

  }  
}

#endif //_PU_COMPILATEUR_TYPE_TEMPLATE_H_
