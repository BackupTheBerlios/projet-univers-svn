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



#ifndef _PU_COMPILATEUR_FONCTION_H_
#define _PU_COMPILATEUR_FONCTION_H_

#include <opencxx/Environment.h>

#include <outils/compilateur/traitement.h>


namespace ProjetUnivers {

  namespace Outils {
      
    namespace Compilateur 
    {
  
      /// Une fonction C.
      class Fonction
      {
      public:

        /*!
          @name Construction
        */
        //@{
        
        /// Constructeur.
        /*!
          @param[in] _environement
            environnement de déclaration de la fonction.
        */
        Fonction(const Opencxx::Member& _membre, 
                 const Opencxx::Environment* _environement) ;

        //@}
        

        /*!
          @name Vérification des règles
        */
        //@{
        
        /// Dit si elle vérifie les règles
        bool VerifieRegles() const ;

        //@}


        
      private:
      
      
        
        /// Environement de définition.
        /*!
          C'est soit une classe soit un espace de nom.
        */
        Opencxx::Environment* environement ;
        
      };
    }
  }
}

#endif

