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

#ifndef PU_ACTION_ACTION_H_
#define PU_ACTION_ACTION_H_

#include <string.h>


namespace ProjetUnivers {
  
 
  /// Gestion des actions sur Model.
  /*!
    
  */ 
  namespace Action 
  {

  /*!
    @name Initialisation/Terminaison.
  */
  //@{        
    
    /// Initialise le module.
    void init() ;

    /// Termine le module.
    void close() ;

  //@}
  /*!
    @name Gestion des actions.
  
  
  */
  //@{
  
  
    /// Execute les actions en cours.
    /*!
      @post
        Il n'y a plus d'actions à traiter
    */
    void update() ;


    /// Ajoute une action
    /*!
      Les actions sont désignées par un identificateur @c _nomAction.
      @todo 
        il faut ajouter un timestamp à l'action (pour savoir à quel moment 
        on l'a déclenché)
    */
    void add(const std::string& _name) ;

    /// 
    bool finished() ;

  //@}
  
  }

  
}

#endif

