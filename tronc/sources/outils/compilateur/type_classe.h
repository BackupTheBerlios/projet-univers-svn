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



#ifndef _PU_COMPILATEUR_TYPE_CLASSE_H_
#define _PU_COMPILATEUR_TYPE_CLASSE_H_

#include <outils/compilateur/type.h>


namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {
    
      /// Types des classes C++
      class TypeClasse : public Type
      {
      public:

        // Construction.
        /*!
          \param _membre Un attribut d'une classe.
          \result Le type de l'attribut
        */
        static TypeClasse* Construire(Opencxx::Member& _membre) ;
 

        /// Transforme en chaine pour l'affichage.
        virtual Base::Chaine Afficher() const ;
        
      protected:

        /// Constructeur.      
        TypeClasse(const Base::Chaine& _nomComplet) ;
      
        /// Le nom de la classe.
        Base::Chaine nomComplet ;
             
      };
    }
  }
}

#endif //_PU_COMPILATEUR_TYPE_CLASSE_H_
