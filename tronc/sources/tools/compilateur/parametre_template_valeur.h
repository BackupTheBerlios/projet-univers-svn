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
#ifndef _PU_COMPILATEUR_PARAMETRE_TEMPLATE_VALEUR_H_
#define _PU_COMPILATEUR_PARAMETRE_TEMPLATE_VALEUR_H_

#include <tools/compilateur/parametre_template.h>


namespace ProjetUnivers {

  namespace Tools {
      
    namespace Compiler 
    {
  
      /// Représente une valeur en tant que paramètre d'instantiation d'un template.
      class ParametreTemplateValeur : public ParametreTemplate
      {
      public:

        /// Constructeur.
        ParametreTemplateValeur() ;

        //@}
        /*!
          @name Affichage
        */
        //@{

        /// Transforme en chaine pour l'affichage.
        virtual std::string Afficher() const ;

        //@}
      
        
      };
    }
  }
}

#endif


 