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
 
  /// Actions on Model.
  namespace Action 
  {

  /*!
    @name Init/close.
  */
  //@{        
    
    /// Module initialisation.
    void init() ;

    /// Module closing.
    void close() ;

  //@}
  /*!
    @name actions management.
  
  */
  //@{
  
    /// Execute pending actions.
    /*!
      @post
        there is no more actions to process.
    */
    void update() ;


    ///   Add an action
    /*!
      Les actions sont d�sign�es par un identificateur @c _nomAction.
      @todo 
        il faut ajouter un timestamp � l'action (pour savoir � quel moment 
        on l'a d�clench�)
    */
    void add(const std::string& _name) ;

    /// True iff finished.
    /*!
      @todo treat termination in an other way.
    */
    bool finished() ;

  //@}
  
  }

  
}

#endif

