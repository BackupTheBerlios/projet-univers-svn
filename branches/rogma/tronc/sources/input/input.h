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

#ifndef _PU_INPUT_INPUT_H_
#define _PU_INPUT_INPUT_H_

namespace ProjetUnivers {

  /// Gestion des entr�es
  /*!
    Certaines entr�es ou combinaisons d'entr�es engendrent des actions dans 
    la pile d'acions � r�aliser.
  */
  namespace Input {
   
    /// Intitailise le module d'entr�es
    void init() ;
   
    /// Termine le module.
    void close() ;
    
    /// Engendre les actions correspondant aux entr�es qui restent dans la pile.
    /*!
      La fonction qui associe une entr�e ou une combinaison d'entr�e avec une 
      action d�pend de l'�tat dans lequel se trouve ce module. 
    */
    void update() ;
   
    
  }
}

#endif
