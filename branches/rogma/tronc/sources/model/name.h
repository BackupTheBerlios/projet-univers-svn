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

#ifndef _PU_MODEL_NAME_H_
#define _PU_MODEL_NAME_H_

#include <string>

namespace ProjetUnivers {
  namespace Model {

      
    /// Un nom.
    
    /*!
      Cette classe de valeur est un exemple de ce qu'il faut pr�f�rer. Au lieu 
      de dire "un nom est une chaine" et utiliser une chaine partout o� on veut 
      un nom, on a d�finit une classe des noms et on la r�alise avec une chaine 
      sachant que plus tard, on pourra faire autrement.
      
      @todo
        ajouter 
    */
    class Name
    {
    public:

      /// Constructeur par d�faut.
      /*!
        Construit le nom ind�fini.
      */
      Name() ;
      
      
      Name(const std::string&) ;
      
      /// Constructeur de copie.
      Name(const Name&) ;
    
      /// Conversion vers une chaine pour l'affichage.
      operator std::string() const ; 
    
      /// Operateur d'affectation.
      Name& operator=(const std::string&) ;
      Name& operator=(const Name&) ;
      
      /// Operateurs de comparaison
      bool operator==(const std::string&) const ;
      bool operator==(const Name&) const ;
      bool operator!=(const Name&) const ;
    
      /// Vrai si le nom n'en est pas un.
      /*!
        C'est le nom de ce qui n'a pas de nom.
      */
      bool isUndefined() const ;
    
    
    private:
    
      /// Pour l'instant une simple chaine
      /*!
        @todo
          Un nom peut varier d'une langue � l'autre :
          implanter � l'aide d'une fonction des langues vers les chaines
        
      */
      std::string name ;
      
    };
  }
}
#endif
