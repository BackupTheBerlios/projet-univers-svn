/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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


#include <kernel/joli_affichage.h>
#include <kernel/exception_base.h>

namespace ProjetUnivers {

  namespace Kernel {    
    
    
    ////////////////
    // Indentation courante, initialisée à 0
    EntierPositif indentation(0) ;
    
    //////////////
    // Décalage, à ajouter où à soustraire
    EntierPositif tabulation(2) ;
    
    ////////////////
    // fonction locale d'affichage de indentation espaces
    Chaine AfficheEspaces() {
    
      Chaine resultat ;
    
      // on ajoute des espaces
      for(EntierPositif i(0) ; i < indentation ; ++i)
        
        resultat += " " ;
    
      return resultat ;
    }

    void AugmenteIndentation()
    {
      // on accroit l'indentation
      indentation = indentation + tabulation ;
    }
    
    /// Diminue l'indentation
    void DiminueIndentation()
    {
        // on décroit l'indentation
      if (indentation >= tabulation)
      {    
       indentation = indentation - tabulation ;
      }
      else
      {
        indentation = 0 ;
      }      
      
    }
    
    Chaine FinDeLigne()
    {
      return "\n" ;
    }
    
    Chaine FinDeLigneEtIndente()
    {
      return "\n" + AfficheEspaces() ;
    }
    
    Chaine FinDeLigneAugmenteIndentation()
    {
      AugmenteIndentation() ;
      return FinDeLigne() ;
    }
    
    Chaine FinDeLigneDiminueIndentation()
    {
      DiminueIndentation() ;
      return FinDeLigne() ;
    
    }
  }   
}
