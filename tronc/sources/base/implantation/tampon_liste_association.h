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


#ifndef _PU_BASE_TAMPON_LISTE_ASSOCIATION_H_
#define _PU_BASE_TAMPON_LISTE_ASSOCIATION_H_

#include <base/association.h>
#include <base/implantation/liste_abstraite.h>

namespace ProjetUnivers {

  namespace Base {
    
    namespace Implantation {

      
      template <class OBJET> class ListeAssociation ;      
      template <class OBJET> class IterateurListeAssociation ;
      
      ///  Classe générique des listes internes d'association. 
      
      /*!
        Cette classe ne doit 
        pas être utilisée directement. D'ailleurs tout est privé pour empécher 
        de vouloir l'utiliser. 
      
        Elle permet de partager les listes en association, et de construire des 
        listes temporaires qui ne sont pas détruites lorsqu'on itère dessus.
      */
      template <class OBJET> class TamponListeAssociation 
        : public ListeAbstraite {
      
      private:
      
      
        // ********************
        /// @name Constructeurs
        // ********************
        // @{
        
      
        /// Constructeur.
        TamponListeAssociation() ;
      
        /// Destructeur.
        ~TamponListeAssociation() ;
      
        /// Constructeur de copie.
        TamponListeAssociation(const TamponListeAssociation< OBJET >& _l) ;
      
        /// Ajoute un nouvel élément en début de liste.
        void AjouterEnTete(const Association< OBJET > _elt) ;
      
        /// Ajoute un nouvel élément en fin de liste.
        void AjouterEnQueue(const Association< OBJET > _elt) ;
      
        /// Obtient une référence, et donc augmente le nombre de référencants.
        TamponListeAssociation< OBJET >* Prendre() ;
      
        /// Relache une référence et renvoie 
        /// vrai s'il faut la détruire.
        Booleen Laisser() ;
      
        
      
        // @}
        // ***********************
        /// @name Méthodes d'accès
        // ***********************
        // @{
      
      
        /// Determine si @_el fait partie de la liste et renvoie sa position.
        EntierPositif Position(const Association< OBJET >& _el) const ;
      
        /// Enlève l'élément à la position @_pos;
        void Enlever(const EntierPositif& _pos) ;
      
        /// renvoie le nombre de références.
        EntierPositif NombreDeReferences() const ;
      
      
        // @}
        // ********************
        /// @name Attributs
        // ********************
        // @{
       
        /// Nombre de références à la liste, 
        /// lorsque ce nombre tombe à zéro, il y a destruction.
        EntierPositif nombreDeReferences ;
      
        // @}
      
        /// Ce sont les seules classes qui ont le droit d'utiliser 
        /// les fonctionnalités de ce tampon
        friend class ListeAssociation<OBJET> ;
        friend class IterateurListeAssociation<OBJET> ;
      
      };
      
    

      

    }
  }
}



#include <base/implantation/tampon_liste_association.cxx>

#endif
