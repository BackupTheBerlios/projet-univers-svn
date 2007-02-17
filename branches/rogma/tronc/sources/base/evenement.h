/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#ifndef _PU_BASE_EVENEMENT_H_
#define _PU_BASE_EVENEMENT_H_

#include <base/chaine.h>
#include <base/association.h>


namespace ProjetUnivers {
  namespace Base {

    class Modele ;

    /// Définition d'un évènement survenu sur un Modele.
    /*!
    @todo
      Le paramètre peut être une valeur aussi?
    */
    struct Evenement
    {
      /// Représentation la mise à jour
      typedef enum
      {
        /// Pour un attribut mono-valué
        Modification,
        /// Pour un attribut multi-valué
        Ajout,
        /// Pour un attribut multi-valué
        Suppression,
        /// Valeur par défaut
        Indefini

      } Action ;
      
      /// Constructeur par défaut.
      Evenement() ;
      
      /// Constructeur par défaut.
      Evenement(const Action&, const Chaine&, const Association<Modele>&) ;
      
      
      /// Constructeur de copie.
      Evenement(const Evenement&) ;
      
      bool operator==(const Evenement&) const ;
      
      
      /// Action 
      Action action ;
      
      /// Nom de l'élément modifié.
      /*!
      c'ets généralement le nom d'un atribut C++; mais pas forcément.
      */
      Chaine nom ;
      
      /// Paramètre de l'évenement.
      /*!
      @todo
        voir ce dont on a besoin, par exemple de plusieurs paramètres ?
      */
      Association<Modele> parametre ;
    };
  }
}

#endif /*_PU_BASE_EVENEMENT_H_*/
