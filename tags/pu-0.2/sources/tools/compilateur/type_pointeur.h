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



#ifndef _PU_COMPILATEUR_TYPE_POINTEUR_H_
#define _PU_COMPILATEUR_TYPE_POINTEUR_H_

#include <base/composition.h>

#include <outils/compilateur/type.h>

class MetaClasse ;

namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {

      
      /// Type pointeur.
      class TypePointeur : public Type
      {
      public:

        /// Construction.
        static TypePointeur* Construire(Opencxx::TypeInfo& informationType,
                                        Opencxx::Environment* environement) ;

        /// Initialisation de la structure.
        virtual void Initialiser() ;

 
        /// Determine si ce type est un type autoris� pour un attribut.
        /*!
          D�pend du type point�.
          Si ce n'est pas un type faisant partie du module qui doit respecter 
          les r�gles alors c'est bon, sinon c'ets faux.
        */
        virtual Base::Booleen TypeAttributCorrect() const ;

        /// Determine si ce type est un type autoris� pour un param�tre.
        /*!
          Ce type est autoris� pour un param�tre
        */
        virtual Base::Booleen TypeParametreCorrect() const ;      

        virtual Base::Booleen Valeur() const ;

        virtual Base::Booleen Objet() const ;

        /// Transforme en chaine pour l'affichage.
        virtual Base::Chaine Afficher() const ;
        
      protected:

        /// Constructeur.      
        TypePointeur(Type* _pointe, Opencxx::Environment* _environement) ;
             
        /// Type point�
        Base::Composition< Type > pointe ;
      };
    }
  }
}

#endif
