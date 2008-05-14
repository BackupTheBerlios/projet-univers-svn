/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <kernel/pretty_print.h>
#include <kernel/exception_kernel.h>

namespace ProjetUnivers {
  namespace Kernel {    
    
    
    ////////////////
    // Indentation courante, initialisée à 0
    unsigned int indent(0) ;
    
    //////////////
    // Décalage, à ajouter où à soustraire
    unsigned int tabulation(2) ;
    
    ////////////////
    // fonction locale d'affichage de indent espaces
    std::string PrintIndent() {
    
      std::string resultat ;
    
      // on ajoute des espaces
      for(unsigned int i(0) ; i < indent ; ++i)
        
        resultat += " " ;
    
      return resultat ;
    }

    void IncreaseIndent()
    {
      // on accroit l'indent
      indent = indent + tabulation ;
    }
    
    /// Diminue l'indent
    void DiminueIndentation()
    {
        // on décroit l'indent
      if (indent >= tabulation)
      {    
       indent = indent - tabulation ;
      }
      else
      {
        indent = 0 ;
      }      
      
    }
    
    std::string EndOfLine()
    {
      return "\n" ;
    }
    
    std::string EndOfLineEtIndente()
    {
      return "\n" + PrintIndent() ;
    }
    
    std::string EndOfLineIncreaseIndent()
    {
      IncreaseIndent() ;
      return EndOfLine() ;
    }
    
    std::string EndOfLineDiminueIndentation()
    {
      DiminueIndentation() ;
      return EndOfLine() ;
    
    }
  }   
}
