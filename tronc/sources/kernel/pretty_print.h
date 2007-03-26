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
#ifndef PU_KERNEL_PRETTY_PRINT_H_
#define PU_KERNEL_PRETTY_PRINT_H_



#include <string>

namespace ProjetUnivers {
  namespace Kernel {
    
  /*!
    @name Display with indent
    

  */
  // @{
    
    /// Passe à la ligne suivante
    /*!
      conserve l'indentation actuelle.
    */
    std::string EndOfLineIndent() ;

    /// Passe à la ligne suivante
    /*!
      N'indente pas.
    */
    std::string EndOfLine() ;

    /// Augmente l'indentation
    void IncreaseIndent() ;
    
    /// Diminue l'indentation
    void DecreaseIndent() ;

    /// Display des espaces.
    std::string PrintIndent() ;

    /// Passe à la ligne suivante, augmente l'indentation
    std::string EndOfLineIncreaseIndent() ;
    
    /// Passe à la ligne suivante, diminue l'indentation
    std::string EndOfLineDecreaseIndent() ;

  // @}

    


  }
}

#endif 
