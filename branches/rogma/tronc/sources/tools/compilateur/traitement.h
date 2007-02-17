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

#include <opencxx/parser/Ptree.h>
#include <opencxx/Environment.h>

#include <base/chaine.h>
#include <base/types.h>
#include <base/fonction_composition_valeur_objet.h>
#include <base/composition.h>


namespace ProjetUnivers {

  namespace Outils {
      
    namespace Compilateur 
    {
  
      /// Repr�sente quelque chose d'homog�ne � une fonction C.
      /*!
        Classe abstraite pour une fonction ou une m�thode. 
        
        @note
          Les m�thodes statiques sont consid�r�es comme des fonctions C.
          Les constructeurs sont trait�s � part.
          Une m�thode s'appliquant sur un objet poss�de un param�tre appel� 
          @c this.
        
      */
      class Traitement
      {
      public:
        

        /*!
          @name V�rification des r�gles
        */
        //@{
        
        /// Dit si elle v�rifie les r�gles
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
                   const Base::Chaine& _nom);

        /// Ajoute un param�tre.
        void AjouterParam�tre(const Base::Chaine _nom, const Type* _type) ;

        //@}

      
        /// Le membre repr�sentant cette m�thode.
        Opencxx::Member& membre ;
        
        /// Le type de retours
        Base::Composition< Type > retours ;

        /// Le nom de la m�thode
        Base::Chaine nom ;
        
        /// Les parametres
        Base::FonctionCompositionValeurObjet<Base::Chaine, Type> parametres ;
        
        
      };
    }
  }
}

#endif

