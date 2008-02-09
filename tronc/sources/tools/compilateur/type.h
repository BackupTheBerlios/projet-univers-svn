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



#ifndef _PU_COMPILATEUR_TYPE_H_
#define _PU_COMPILATEUR_TYPE_H_

#include <opencxx/Member.h>
#include <opencxx/Environment.h>


#include <string>

#include <tools/compilateur/parametre_template.h>


namespace ProjetUnivers {

  namespace Tools {
  
    namespace Compiler 
    {
    
      /// Types C++
      class Type : public ParametreTemplate
      {
      public:

        /*!
          @name Construction
        */
        //@{

      
        // Construction.
        static Type* Construire(Opencxx::TypeInfo& informationType,
                                Opencxx::Environment* environement) ;
 
        /// Initialisation de la structure.
        virtual void Initialiser() = 0 ;


        //@}
        /*!
          @name Introspection
        */
        //@{
        
        
        /// Determine si ce type est un type autoris� pour un attribut.
        virtual bool TypeAttributCorrect() const = 0 ;
      
        /// Determine si ce type est un type autoris� pour un param�tre.
        virtual bool TypeParametreCorrect() const = 0 ;      
      
        /// Determine si ce type est un type de valeur.
        virtual bool Valeur() const = 0 ;

        /// Determine si ce type est un type d'objets.
        virtual bool Objet() const = 0 ;
      
        //@}

        /// Transforme en chaine pour l'affichage.
        virtual std::string Afficher() const = 0 ;
        
        
                 
        /// Destructeur de classe abstraite.
        virtual ~Type() ;
      
      protected:
      
        /// Constructeur de classe abstraite.
        Type(Opencxx::Environment* _espaceDeNom) ;
       
        /// Environement (namespace ou classe) o� est d�clar� ce type
        Opencxx::Environment* espaceDeNom ;
       
      };
    
    } 

  }  
}

#endif //_PU_COMPILATEUR_TYPE_H_
