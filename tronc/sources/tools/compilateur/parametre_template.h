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



#ifndef _PU_COMPILATEUR_PARAMETRE_TEMPLATE_H_
#define _PU_COMPILATEUR_PARAMETRE_TEMPLATE_H_

#include <opencxx/parser/Ptree.h>
#include <opencxx/Environment.h>

#include <base/chaine.h>
#include <base/types.h>


namespace ProjetUnivers {

  namespace Outils {
      
    namespace Compilateur 
    {
  
      /// Représente un paramètre d'instantiation d'un template
      /*!
        Un paramètre est soit un type, soit une valeur.
      */
      class ParametreTemplate
      {
      public:

        /*!
          @name Construction
        */
        //@{
        
        /// Construit le paramètre.
        static ParametreTemplate* Construire(Opencxx::Ptree* parametre,
                                             Opencxx::Environment* environement) ;

        //@}
        /*!
          @name Affichage
        */
        //@{

        /// Transforme en chaine pour l'affichage.
        virtual Base::Chaine Afficher() const = 0 ;


        //@}
        /*!
          @name Introspection
        */
        //@{

        virtual Base::Booleen Valeur() const = 0 ;

        virtual Base::Booleen Objet() const = 0 ;


        //@}



        /// Destructeur de classe abstraite.
        virtual ~ParametreTemplate() ;
      
      protected:
      
        /// Constructeur de classe abstraite.
        ParametreTemplate() ;
        
      };
    }
  }
}

#endif
