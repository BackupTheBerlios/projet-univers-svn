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

    /// D�finition d'un �v�nement survenu sur un Modele.
    /*!
    @todo
      Le param�tre peut �tre une valeur aussi?
    */
    struct Evenement
    {
      /// Repr�sentation la mise � jour
      typedef enum
      {
        /// Pour un attribut mono-valu�
        Modification,
        /// Pour un attribut multi-valu�
        Ajout,
        /// Pour un attribut multi-valu�
        Suppression,
        /// Valeur par d�faut
        Indefini

      } Action ;
      
      /// Constructeur par d�faut.
      Evenement() ;
      
      /// Constructeur par d�faut.
      Evenement(const Action&, const Chaine&, const Association<Modele>&) ;
      
      
      /// Constructeur de copie.
      Evenement(const Evenement&) ;
      
      bool operator==(const Evenement&) const ;
      
      
      /// Action 
      Action action ;
      
      /// Nom de l'�l�ment modifi�.
      /*!
      c'ets g�n�ralement le nom d'un atribut C++; mais pas forc�ment.
      */
      Chaine nom ;
      
      /// Param�tre de l'�venement.
      /*!
      @todo
        voir ce dont on a besoin, par exemple de plusieurs param�tres ?
      */
      Association<Modele> parametre ;
    };
  }
}

#endif /*_PU_BASE_EVENEMENT_H_*/
