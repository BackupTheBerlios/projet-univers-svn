/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#ifndef PU_DISPLAY_DISPLAY_INPUT_H_
#define PU_DISPLAY_DISPLAY_INPUT_H_

#include <stddef.h>

namespace ProjetUnivers {
  namespace Display {

  /*!
    @name Interface for input module.
  */
  // @{

    /// Acc�s aux descripteur de la fenetre d'affichage
    size_t getWindowHandle() ;

    /// Acc�s � la taille de la fen�tre
    void getWindowSize(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top );
  
  
  // @}

  }
}


#endif /*PU_DISPLAY_DISPLAY_INPUT_H_*/
