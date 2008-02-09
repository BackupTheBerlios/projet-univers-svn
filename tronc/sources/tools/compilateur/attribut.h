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



#ifndef _PU_COMPILATEUR_ATTRIBUT_H_
#define _PU_COMPILATEUR_ATTRIBUT_H_

#include <memory>
#include <tools/compilateur/type.h>


namespace ProjetUnivers {

  namespace Tools {
  
    namespace Compiler 
    {
    
      /// Attribut d'une classe C++.
      class Attribut 
      {
      public:

        /*!
          @name Construction
        */
        //@{

        /// Construit un attribut à partir d'un membre.
        /*!
          Précondition :
            _membre doit est un attribut.
        */
        Attribut(Opencxx::Member& _membre) ;

        /// Initialisation de la structure.
        void Initialiser() ;

        //@}
        /*!
          @name Introspection
        */
        //@{


        /// La partie du modèle acedb correspondant.
        std::string ModeleAceDBEquivalent() const ;

        /// Determine si l'attribut vérifie les règles de programmations.
        /*!
          En cas d'erreur, cette méthode engendre une erreur de compilation.
        */
        bool VerifieRegles() const ;

        /// Affiche l'attribut.
        std::string Afficher() const ;


        //@}
        
      private:
      
        /// Une copie du membre
        Opencxx::Member membre ;
      
        /// Nom
        std::string nom ;
        
        /// Type
        std::auto_ptr<Type> type ;
        
        Opencxx::Class* classe ;

        
      };
    }
  }
}

#endif //_PU_COMPILATEUR_ATTRIBUT_H_
