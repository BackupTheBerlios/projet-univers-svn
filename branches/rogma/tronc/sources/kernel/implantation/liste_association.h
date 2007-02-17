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

#ifndef _PU_BASE_LISTE_ASSOCIATION_H_
#define _PU_BASE_LISTE_ASSOCIATION_H_


#include <base/types.h>



namespace ProjetUnivers {

  namespace Base {

    template <class OBJET> class Association ;

    namespace Implantation {
  
      template <class OBJET> class ListeComposition ;
      template <class OBJET> class TamponListeAssociation ;
      template <class OBJET> class IterateurListeAssociation ;
      
      
      
      
        
      ///  Classe g�n�rique des listes en association.
      
      /// UTILISATION
      ///  La m�me que pour Association
      template <class OBJET> class ListeAssociation {
      	
      public:
      
      
        // ********************
        // GROUP: Constructeurs
        // ********************
      
        /// Constructeur.
        ListeAssociation() ;
      
        /// Destructeur.
        ~ListeAssociation() ;
      
        /// Constructeur de copie.
        ListeAssociation(const ListeAssociation< OBJET >& _l) ;
      
        /// Constructeur.
        ListeAssociation(const ListeComposition< OBJET >& _l) ;
      
        /// Op�rateur d'affectation.
        ListeAssociation< OBJET >& operator=(const ListeComposition< OBJET >& _l) ;
      
      
        /// Op�rateur d'affectation.
        ListeAssociation< OBJET >& operator=(const ListeAssociation< OBJET >& _l) ;
      
        /// Ajoute un nouvel �l�ment en d�but de liste.
        void addEnTete(const Association< OBJET > _elt) ;
      
        /// Ajoute un nouvel �l�ment en fin de liste.
        void addEnQueue(const Association< OBJET > _elt) ;
      
        /// Ajoute des nouveaux �l�ments en fin de liste.
        void addEnQueue(const ListeAssociation< OBJET > _elt) ;
      
        /// Enl�ve tous les �l�ments.
        void Vider() ;
  
        
        // ***********************
        // GROUP: M�thodes d'acc�s
        // ***********************
      
        /// Acc�s au nombre d'�l�ments.
        unsigned int NombreDElements() const ;
      
      
        /// Determine si l'�l�ment _elt fait parti de la liste.
        Booleen Contient(const Association< OBJET >& _elt) const ;
      
        /// Determine si _el fait partie de la liste et renvoie sa position.
        unsigned int Position(const Association< OBJET >& _el) const ;
      
        /// Enl�ve l'�l�ment � la position _pos;
        void remove(unsigned int _pos) ;
      
        /// Acc�s au dernier �l�ment.
        Association< OBJET > Dernier() const ;
      
      
      private:
      
        /// Vrai liste proprement dite
        /// elle va �tre partag�e par toutes les copies
        TamponListeAssociation< OBJET >* liste ;
      
        friend class IterateurListeAssociation<OBJET> ;
      
      };
      
      
      
      
      /// Intersection des �l�ments des listes, consid�r�es comme des ensembles.
      template <class OBJET > 
      ListeAssociation< OBJET > Intersection
          ( const ListeAssociation< OBJET >& _l1,
            const ListeAssociation< OBJET >& _l2) ;
    

    }
  }
}

#include <base/implantation/liste_association.cxx>

#endif 


