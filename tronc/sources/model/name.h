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

#ifndef PU_MODEL_NAME_H_
#define PU_MODEL_NAME_H_

#include <string>

namespace ProjetUnivers {
  namespace Model {

      
    /// A name.
    /*!

    */
    class Name
    {
    public:

      /// Construct.
      /*!
        The name is undefined.
      */
      Name() ;
      
      //: Basic construct.
      Name(const std::string&) ;
      
      /// Constructeur de copie.
      Name(const Name&) ;
    
      /// Convert to string.
      operator std::string() const ; 
    
      /// Assignment.
      Name& operator=(const std::string&) ;
      Name& operator=(const Name&) ;
      
      /// Operateurs de comparaison
      bool operator==(const std::string&) const ;
      bool operator==(const Name&) const ;
      bool operator!=(const Name&) const ;
    
      /// True iff undefined.
      bool isUndefined() const ;
    
    
    private:
    
      /// Basic implementation.
      /*!
        @todo
          for future : map languages to string, because a name can change 
          according to the language.
        
      */
      std::string name ;
      
    };
  }
}
#endif
