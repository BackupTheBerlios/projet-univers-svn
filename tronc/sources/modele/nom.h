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

#ifndef _PU_MODELE_NOM_H_
#define _PU_MODELE_NOM_H_

#include <base/types.h>
#include <base/chaine.h>

namespace ProjetUnivers {

  namespace Modele {

      
    /// Un nom.
    
    /*!
      Cette classe de valeur est un exemple de ce qu'il faut pr�f�rer. Au lieu 
      de dire "un nom est une chaine" et utiliser une chaine partout o� on veut 
      un nom, on a d�finit une classe des noms et on la r�alise avec une chaine 
      sachant que plus tard, on pourra faire autrement.
      
      @todo
        ajouter 
    */
    class Nom {
    public:

      /// Constructeur par d�faut.
      /*!
        Instanti� � ind�fini.
      */
      Nom() ;
      
      Nom(const Base::Chaine&) ;
      
      /// Constructeur de copie.
      Nom(const Nom&) ;
    
      /// Conversion vers une chaine.
      operator Base::Chaine() const ; 
    
      /// Operateur d'affectation.
      Nom& operator=(const Base::Chaine&) ;
      Nom& operator=(const Nom&) ;
      
      /// Operateur de comparaison
      Base::Booleen operator==(const Base::Chaine&) const ;
      Base::Booleen operator==(const Nom&) const ;
    
      /// Vrai si le nom n'en est pas un.
      Base::Booleen EstIndefini() const ;
    
    
    private:
    
      /// Pour l'instant une simple chaine
      /*!
        @todo
          une fonction des langues vers les chaines
        
      */
      Base::Chaine nom ;
      
    };
  }
}
#endif
