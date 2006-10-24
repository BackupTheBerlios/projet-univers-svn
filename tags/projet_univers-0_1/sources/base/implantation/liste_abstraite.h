/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PU_BASE_LISTE_ABSTRAITE_H_
#define _PU_BASE_LISTE_ABSTRAITE_H_

#include <base/composition.h>
#include <base/association.h>



namespace ProjetUnivers {

  namespace Base {
  
      
    namespace Implantation {
                  
      class NoeudAbstrait ;
      
      ///  Classe de base des listes.
      /*!
        @deprecated
      */
      class ListeAbstraite 
      {
      public:
      
        /// Constructeur par défaut.
        
        /*!
          \todo 
            vérifier si ce constructeur doit être public
        */
        ListeAbstraite() ;
      
        /// Destructeur virtuel. 
        
        /*!
          ne sert pas à grand chose à part rendre la classe polymorphe.
        */
        virtual ~ListeAbstraite() ;
      
        /// Accès au nombre d'éléments.
        unsigned int NombreDElements() const ;
      
        /// Vide la liste.
        void Vider() ;
      
      protected:
      
        /// Dernier noeud.
        Association<NoeudAbstrait> dernierNoeud ;


        /// Premier noeud.
        Composition<NoeudAbstrait> premierNoeud ;
      
             
        /// Nombre d'éléments.
        unsigned int nombreDElements ;
      
        // Ajoute un noeud en début de liste.
        void AjouterEnTete(NoeudAbstrait* _n) ;
      
        /// Ajoute un noeud en fin de liste.
        void AjouterEnQueue(NoeudAbstrait* _n) ;
      
        /// 
        friend class IterateurListe ;
      
      
      };
    }
  }
}

#endif


