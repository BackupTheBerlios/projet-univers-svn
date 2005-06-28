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



#ifndef _PU_COMPILATEUR_TYPE_PREDEFINI_H_
#define _PU_COMPILATEUR_TYPE_PREDEFINI_H_

#include <opencxx/parser/Ptree.h>
#include <outils/compilateur/type.h>


namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {
    
      /// Types simples C++
      class TypePredefini : public Type
      {
      public:

        // Construction.
        static TypePredefini* Construire(Opencxx::TypeInfo& informationType,
                                         Opencxx::Environment* environement) ;

        /// Initialisation de la structure.
        virtual void Initialiser() ;
 
        /// Determine si ce type est un type autorisé pour un attribut.
        /*!
          Ce type est un type autorisé pour un attribut si c'est un des types 
          suivants :
          
          - 
          -

        */
        virtual Base::Booleen TypeAttributCorrect() const ;

        virtual Base::Booleen Valeur() const ;

        virtual Base::Booleen Objet() const ;

        /// Transforme en chaine pour l'affichage.
        virtual Base::Chaine Afficher() const ;
        
      private:


      /// Identifie la selection par un namespace
      /*!
        Reconnait des arbre de la forme : 
        [<i>namespace</i> :: <i>reste</i>]
        
        @param[in] environement 
          l'environement dans lequel il faut chercher

        @param[in] type 
          l'arbre qu'il faut chercher
      */
       static TypePredefini* IdentifierParcoursNamespace
                                 (Opencxx::Ptree* type, 
                                  Opencxx::Environment* environement) ;
         

        /// Constructeur.
        /*!
          @param[in] _environement 
            l'environement dans le quel est définit le type
          @param[in] _nom
            le petit nom du type 
        */
        TypePredefini(Opencxx::Environment* _environement, const Base::Chaine& _nom) ;
      
        /// Le nom du type prédéfini
        Base::Chaine nom ;
             
      };
    }
  }
}




#endif //_PU_COMPILATEUR_TYPE_PREDEFINI_H_
