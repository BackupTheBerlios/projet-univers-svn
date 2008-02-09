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



#ifndef _PU_COMPILATEUR_TRAITEMENT_H_
#define _PU_COMPILATEUR_TRAITEMENT_H_

#include <string>
#include <map>

#include <opencxx/parser/Ptree.h>
#include <opencxx/Environment.h>

namespace ProjetUnivers {
  namespace Tools {
    namespace Compiler {
      
      class Type ;
      
      /// Représente quelque chose d'homogène à une fonction C.
      /*!
        Classe abstraite pour une fonction ou une méthode. 
        
        @note
          Les méthodes statiques sont considérées comme des fonctions C.
          Les constructeurs sont traités à part.
          Une méthode s'appliquant sur un objet possède un paramètre appelé 
          @c this.
        
      */
      class Traitement
      {
      public:
        

        /*!
          @name Vérification des règles
        */
        //@{
        
        /// Dit si elle vérifie les règles
        bool VerifieRegles() const ;

        //@}

        /// Destructeur de classe abstraite.
        virtual ~Traitement() ;

        
      protected:
      
        /*!
          @name Construction
        */
        //@{
        
        /// Constructeur.
        Traitement(const Opencxx::Member& _membre, 
                   const Type* _retours,
                   const std::string& _nom);

        /// Ajoute un paramètre.
        void AjouterParamètre(const std::string _nom, const Type* _type) ;

        //@}

      
        /// Le membre représentant cette méthode.
        Opencxx::Member& membre ;
        
        /// Le type de retours
        Type* retours ;

        /// Le nom de la méthode
        std::string nom ;
        
        /// Les parametres
        std::map<std::string, Type*> parametres ;
        
        
      };
    }
  }
}

#endif

