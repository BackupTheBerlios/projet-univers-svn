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

#include <base/chaine.h>
#include <base/composition.h>
#include <outils/compilateur/type.h>


namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
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
        Base::Chaine ModeleAceDBEquivalent() const ;

        /// Determine si l'attribut vérifie les règles de programmations.
        Base::Booleen VerifieRegles() const ;

        /// Affiche l'attribut.
        Base::Chaine Afficher() const ;


        //@}
        
      private:
      
        /// Nom
        Base::Chaine nom ;
        
        /// Type
        Base::Composition<Type> type ;
        
        
      };
    }
  }
}

#endif //_PU_COMPILATEUR_ATTRIBUT_H_
