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

#ifndef _PU_BASE_IMPLANTATION_LISTE_COMPOSITION_H_
#define _PU_BASE_IMPLANTATION_LISTE_COMPOSITION_H_

#include <base/implantation/liste_abstraite.h>

namespace ProjetUnivers {

  namespace Base {
  
    namespace Implantation {
        
      template <class OBJET> class ListeAssociation ;
      
      
      /// Classe g�n�rique r�alisant l'agr�gation d'une liste d'objets.

      /*!
      UTILISATION
        M�me utilisations que pour Composition, en ce qui concerne les 
       listes.
      */
      template <class OBJET> class ListeComposition 
        : public ListeAbstraite {
      
      public:
      
      
        
        // ********************
        /// @name Construction
        // ********************
        // @{
        
        
        /// Constructeur par d�faut.
        ListeComposition() ;
      
        /// Destructeur.
        ~ListeComposition() ;
      
        /// Constructeur de copie, @_l est vide apr�s cela.
        ListeComposition(const ListeComposition<OBJET> &_l);
      
        /// Aggrege un �l�ment � la liste en premi�re position.
        void addEnTete(OBJET* _elt);
      
        /// Aggrege des �l�ments � la liste en premi�re position.
        void addEnTete(const ListeComposition< OBJET >& _l) ;
      
        /// Aggrege un �l�ment � la liste en derni�re position.
        void addEnQueue(OBJET* _elt);
      
  
        /// Enl�ve l'�l�ment � la position @_pos;
        void remove(unsigned int _pos) ;
      
        /// Affectation, �pr�s �a,@ _l est vide.
        ListeComposition< OBJET >& operator = (const ListeComposition<OBJET> &_l);
      
      
        // @}
        // ********************
        /// @name Consultation
        // ********************
        // @{
      
        /// Determine si @_el fait partie de la liste.
        Booleen Contient(const Association< OBJET >& _el) const ;
      
        /// 
        
        /*!
          
          \param _el �l�ment recherch�
         \return 
           renvoie 0 si l'�l�ment ne fait pas partie de la liste
           renvoie sa position s'il en fait partie
        */
        unsigned int Position(const Association< OBJET >& _el) const ;
      
      
        /// Renvoie l'�l�ment � la position @_pos.
        Association< OBJET > Element(unsigned int _pos) const ;
      
        // @}
      };
      
      
    }
  }
}

#include <base/implantation/liste_composition.cxx>

#endif 


