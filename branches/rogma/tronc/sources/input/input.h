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

  /// Gestion des entrées
  /*!
    Certaines entrées ou combinaisons d'entrées engendrent des actions dans 
    la pile d'acions à réaliser.
  */
  namespace Input {
   
    /// Intitailise le module d'entrées
    void init() ;
   
    /// Termine le module.
    void close() ;
    
    /// Engendre les actions correspondant aux entrées qui restent dans la pile.
    /*!
      La fonction qui associe une entrée ou une combinaison d'entrée avec une 
      action dépend de l'état dans lequel se trouve ce module. 
    */
    void update() ;
   
    
  }
}

#endif