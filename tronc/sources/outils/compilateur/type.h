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


#include <base/chaine.h>

#include <outils/compilateur/parametre_template.h>


namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
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
        
        
        /// Determine si ce type est un type autorisé pour un attribut.
        virtual Base::Booleen TypeAttributCorrect() const = 0 ;
      
        virtual Base::Booleen Valeur() const = 0 ;

        virtual Base::Booleen Objet() const = 0 ;
      
        //@}

        /// Transforme en chaine pour l'affichage.
        virtual Base::Chaine Afficher() const = 0 ;
        
        
                 
        /// Destructeur de classe abstraite.
        virtual ~Type() ;
      
      protected:
      
        /// Constructeur de classe abstraite.
        Type(Opencxx::Environment* _espaceDeNom) ;
       
        /// Environement (namespace ou classe) où est déclaré ce type
        Opencxx::Environment* espaceDeNom ;
       
      };
    
    } 

  }  
}

#endif //_PU_COMPILATEUR_TYPE_H_
