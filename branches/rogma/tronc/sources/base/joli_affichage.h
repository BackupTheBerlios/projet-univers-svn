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


#ifndef _PU_BASE_JOLI_AFFICHAGE_
#define _PU_BASE_JOLI_AFFICHAGE_



#include <base/chaine.h>

namespace ProjetUnivers {

  namespace Base {
    
  /*!
    @name Affichage avec indentation
    
    @par Utilisation
    
    

  */
  // @{
    
    /// Passe � la ligne suivante
    /*!
      conserve l'indentation actuelle.
    */
    Chaine FinDeLigneEtIndente() ;

    /// Passe � la ligne suivante
    /*!
      N'indente pas.
    */
    Chaine FinDeLigne() ;

    /// Augmente l'indentation
    void AugmenteIndentation() ;
    
    /// Diminue l'indentation
    void DiminueIndentation() ;

    /// Affichage des espaces.
    Chaine AfficheEspaces() ;

    /// Passe � la ligne suivante, augmente l'indentation
    Chaine FinDeLigneAugmenteIndentation() ;
    
    /// Passe � la ligne suivante, diminue l'indentation
    Chaine FinDeLigneDiminueIndentation() ;

  // @}

    


  }
}

#endif 
