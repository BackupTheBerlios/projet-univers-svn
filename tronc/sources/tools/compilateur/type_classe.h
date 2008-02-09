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

#include <tools/compilateur/type.h>

class MetaClasse ;

namespace ProjetUnivers {

  namespace Tools {
  
    namespace Compiler 
    {

      
      /// Types des classes C++
      class TypeClasse : public Type
      {
      public:

        /// Construction.
        static TypeClasse* Construire(Opencxx::TypeInfo& informationType,
                                      Opencxx::Environment* environement) ;

        /// Initialisation de la structure.
        virtual void Initialiser() ;

 
        /// Determine si ce type est un type autorisé pour un attribut.
        /*!
          Ce type est un type autorisé pour un attribut si :
          
          - la classe est une classe de valeurs.

        */
        virtual bool TypeAttributCorrect() const ;

        /*!
          Ce type n'est pas autorisé pour un paramètre.
        */
        virtual bool TypeParametreCorrect() const ;      

        virtual bool Valeur() const ;

        virtual bool Objet() const ;


        /// Transforme en chaine pour l'affichage.
        virtual std::string Afficher() const ;
        
      protected:

        /// Constructeur.      
        TypeClasse(Opencxx::Environment* _espaceDeNom, MetaClasse* _classe) ;
      
        /// La classe proprement dite.
        MetaClasse* classe ;
             
      };
    }
  }
}

#endif //_PU_COMPILATEUR_TYPE_CLASSE_H_
