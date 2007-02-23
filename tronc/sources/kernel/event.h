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

#ifndef _PU_KERNEL_EVENT_H_
#define _PU_KERNEL_EVENT_H_

#include <string>


namespace ProjetUnivers {
  namespace Kernel {

    class Model ;

    /// Définition d'un évènement survenu sur un Modele.
    /*!
    @todo
      Le paramètre peut être une valeur aussi?
    */
    struct Event
    {
      /// Représentation la mise à jour
      typedef enum
      {
        /// Pour un attribut mono-valué
        Update,
        /// Pour un attribut multi-valué
        Add,
        /// Pour un attribut multi-valué
        Delete,
        /// Valeur par défaut
        Undefined

      } Action ;
      
      /// Constructeur par défaut.
      Event() ;
      
      /// Constructeur par défaut.
      Event(const Action&, const std::string&, Model*) ;
      
      
      /// Constructeur de copie.
      Event(const Event&) ;
      
      bool operator==(const Event&) const ;
      
      
      /// Action 
      Action action ;
      
      /// Nom de l'élément modifié.
      /*!
      c'ets généralement le nom d'un atribut C++; mais pas forcément.
      */
      std::string name ;
      
      /// Paramètre de l'évenement.
      /*!
      @todo
        voir ce dont on a besoin, par exemple de plusieurs paramètres ?
      */
      Model* parameter ;
    };
  }
}

#endif /*_PU_KERNEL_EVENT_H_*/
